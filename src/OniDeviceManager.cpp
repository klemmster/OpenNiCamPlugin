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

const OniDevice* OniDeviceManager::getOniDevice(int number){
    //TODO: Save & pass return by reference
    myDevicePtr = OniDevicePtr(new OniDevice());
    return myDevicePtr.get();
}

} //End namespace avg
