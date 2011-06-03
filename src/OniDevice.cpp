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
   BitmapPtr rgbImage = BitmapPtr(new Bitmap(IntPoint(640, 480), R8G8B8));
   m_pDeviceThread = new boost::thread(OniDeviceThread(rgbImage, *m_pDevCmdQueue, std::string("DeviceThread")));
   m_pOniCam = OniCameraPtr(new OniCamera(rgbImage));
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
    //TODO: Actually do different Things with different types
    return m_pOniCam;
}

}//end namespace avg
