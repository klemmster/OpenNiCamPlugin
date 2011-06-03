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

#include "OniDeviceManager.h"

namespace avg {


OniDeviceManager::OniDeviceManager()
{
    ObjectCounter::get()->incRef(&typeid(*this));
    AVG_TRACE(Logger::PLUGIN, "Constructed OniDeviceManager")
}

OniDeviceManager::~OniDeviceManager()
{
    ObjectCounter::get()->decRef(&typeid(*this));
    AVG_TRACE(Logger::PLUGIN, "Deconstructed OniDeviceManager")
}

const OniDevicePtr OniDeviceManager::getOniDevice(int number){
    //TODO: Check DevicePtr
    myDevicePtr = OniDevicePtr(new OniDevice());
    return myDevicePtr;
}

} //End namespace avg
