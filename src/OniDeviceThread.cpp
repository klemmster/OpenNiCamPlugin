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

OniDeviceThread::OniDeviceThread(BitmapPtr rgbBitmap, CQueue& CmdQ,const std::string& threadName):
    WorkerThread<OniDeviceThread>(threadName, CmdQ)
{
    m_pRGBImage = rgbBitmap;
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
        const XnUInt8* pRGBPixel = m_ImageGenerator.GetImageMap();
        m_pRGBImage->setPixels(pRGBPixel);
        //TODO: Get DepthMap
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
