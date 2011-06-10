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

    XnStatus rc = XN_STATUS_OK;
    xn::EnumerationErrors errors;
    rc = m_Context.Init();
    RCisOK(rc);
    rc = m_DepthGenerator.Create(m_Context);
    RCisOK(rc);
    rc = m_ImageGenerator.Create(m_Context);
    RCisOK(rc);
    rc = m_Context.StartGeneratingAll();
    RCisOK(rc);
    return true;
}

void OniDeviceThread::deinit(){
    AVG_TRACE(Logger::PLUGIN, "Deinit Thread");
}

bool OniDeviceThread::work(){
    XnStatus rc = m_Context.WaitAndUpdateAll();
    if(RCisOK(rc)){
        IntPoint size(640, 480);
        m_pQrgb->push(BitmapPtr(new Bitmap(size, R8G8B8,
                (unsigned char *)m_ImageGenerator.GetImageMap(), size.x*3, false)));
        m_pQdepth->push(BitmapPtr(new Bitmap(size, I16,
                (unsigned char*)m_DepthGenerator.GetDepthMap(), size.x*2, false )));
    }else{
        return false;
    }
    return true;
}

bool OniDeviceThread::RCisOK(const XnStatus rc){
    if(rc != XN_STATUS_OK){
        AVG_TRACE(Logger::PLUGIN, "ERROR: " << xnGetStatusString(rc));
        throw(Exception(AVG_ERR_CORRUPT_PLUGIN,
                   xnGetStatusString(rc)));
    }
    return true;
};

}//end namespace avg
