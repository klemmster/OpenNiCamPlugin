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

#include "OniDevice.h"
#include <player/Player.h>

namespace avg{

OniDevice::OniDevice()
{
   m_pDevCmdQueue = OniDeviceThread::CQueuePtr(new OniDeviceThread::CQueue);
   m_pQPtrDepthBmpPtr = BitmapQueuePtr(new BitmapQueue());
   m_pQPtrRGBBmpPtr = BitmapQueuePtr(new BitmapQueue());

   m_pDeviceThread = new boost::thread(OniDeviceThread(*m_pDevCmdQueue,
            std::string("DeviceThread"), m_pQPtrRGBBmpPtr, m_pQPtrDepthBmpPtr ));
   Player::get()->registerPlaybackEndListener(this);
   AVG_TRACE(Logger::PLUGIN, "Create OniDevice");
}

OniDevice::~OniDevice()
{
    delete m_pDeviceThread;
    AVG_TRACE(Logger::PLUGIN, "Delete OniDevice");
}

void OniDevice::onPlaybackEnd(){
    AVG_TRACE(Logger::PLUGIN, "OnPlaybackEnd");
    m_pDevCmdQueue->pushCmd(boost::bind(&OniDeviceThread::stop,_1));
    m_pDeviceThread->join();
}

OniCameraPtr OniDevice::getCamera(OniCameraType type){
    if(type==ONI_RGB_CAMERA){
        return OniCameraPtr(new OniCamera(type, m_pQPtrRGBBmpPtr));
    }else if(type==ONI_DEPTH_CAMERA){
        return OniCameraPtr(new OniCamera(type, m_pQPtrDepthBmpPtr));
    }
    throw Exception(AVG_ERR_OPTION_UNKNOWN, "Unsupported CameraType.");
}

}//end namespace avg
