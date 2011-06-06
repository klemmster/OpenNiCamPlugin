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

OniDeviceThread::OniDeviceThread(CQueue& CmdQ,const std::string& threadName):
    WorkerThread<OniDeviceThread>(threadName, CmdQ)
{
}

OniDeviceThread::~OniDeviceThread()
{

}

bool OniDeviceThread::init(){
    AVG_TRACE(Logger::PLUGIN, "Init Thread");

    m_pDepthImage = BitmapPtr(new Bitmap(IntPoint(640, 480), I16));
    m_pRGBImage = BitmapPtr(new Bitmap(IntPoint(640, 480), R8G8B8));

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
        m_pRGBImage->setPixels(m_ImageGenerator.GetImageMap());
        m_pDepthImage->setPixels((unsigned char*)m_DepthGenerator.GetDepthMap());
    }
    return true;
}

void OniDeviceThread::setBitmapPtr(OniCameraPtr camPtr){
    OniCameraType type = camPtr->getType();
    if(type == ONI_DEPTH_CAMERA){
        m_pDepthImage = camPtr->getBitmapPtr();
        return;
    }else if(type == ONI_RGB_CAMERA){
        m_pRGBImage = camPtr->getBitmapPtr();
        return;
    }
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
