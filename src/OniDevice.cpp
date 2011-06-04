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
   m_pDeviceThread = new boost::thread(OniDeviceThread(*m_pDevCmdQueue, std::string("DeviceThread")));
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
    m_pOniCam = OniCameraPtr(new OniCamera(type));
    BitmapPtr imagePtr = m_pOniCam->getBitmapPtr();
    m_pDevCmdQueue->pushCmd(boost::bind(&OniDeviceThread::setBitmapPtr, _1, m_pOniCam));
    return m_pOniCam;
}

}//end namespace avg
