/*************************************************************************
 * Project: OniPlugin
 *************************************************************************
 * $Author: Richy $
 * $Name: Richard Klemm $
 *************************************************************************
 *
 * Copyright 2011
 *
 ************************************************************************/

#include "OniDeviceThread.h"

namespace avg {

OniDeviceThread::OniDeviceThread(CQueue& CmdQ,const std::string& threadName,
            BitmapQueuePtr rgbQueue, BitmapQueuePtr depthQueue):
    WorkerThread<OniDeviceThread>(threadName, CmdQ),
    m_pQrgb(rgbQueue),
    m_pQdepth(depthQueue)
{
}

OniDeviceThread::~OniDeviceThread()
{

}

bool OniDeviceThread::init(){
    AVG_TRACE(Logger::PLUGIN, "Init Thread");

    m_Size = IntPoint(320, 240);

    XnStatus rc = XN_STATUS_OK;
    xn::EnumerationErrors errors;
    rc = m_Context.Init();
    RCisOK(rc, __LINE__);
    rc = m_DepthGenerator.Create(m_Context);
    RCisOK(rc, __LINE__);
    /*
    rc = m_ImageGenerator.Create(m_Context);
    RCisOK(rc, __LINE__);
    */
    rc = m_Context.StartGeneratingAll();
    RCisOK(rc, __LINE__);
    return true;
}

void OniDeviceThread::deinit(){
    m_Context.Release();
    AVG_TRACE(Logger::PLUGIN, "Deinit Thread");
}

bool OniDeviceThread::work(){
    XnStatus rc = m_Context.WaitAndUpdateAll();
    if(RCisOK(rc, __LINE__)){
        /*
        m_pQrgb->push(BitmapPtr(new Bitmap(m_Size, R8G8B8,
                (unsigned char *)m_ImageGenerator.GetImageMap(), m_Size.x*3, false)));
                */

        unsigned char newPixels[320*240*2];
        unsigned char* pixels = (unsigned char*)m_DepthGenerator.GetDepthMap();
        for(unsigned int i=1; i<320*240*2; i++){
            newPixels[i] = (unsigned char)(pixels[i] << 2)*1.6;
        }
        m_pQdepth->push(BitmapPtr(new Bitmap(m_Size, I16,
                newPixels, m_Size.x*2, true )));
    }
    return true;
}

bool OniDeviceThread::RCisOK(const XnStatus rc, int line){
    if(rc != XN_STATUS_OK){
        AVG_TRACE(Logger::PLUGIN, "Line: " << line << "\nERROR: " << xnGetStatusString(rc));
        throw(Exception(AVG_ERR_CORRUPT_PLUGIN,
                   xnGetStatusString(rc)));
    }
    return true;
};

}//end namespace avg
