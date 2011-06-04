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

const OniDevicePtr OniDeviceManager::getOniDevice(int id){
    std::map<int, OniDevicePtr>::iterator it;
    it = m_DevIDMap.find(id);
    if(it == m_DevIDMap.end()){
        OniDevicePtr devPtr = OniDevicePtr(new OniDevice());
        m_DevIDMap.insert(DeviceIDMap::value_type(id, devPtr));
        return devPtr;
    }else{
        return it->second;
    }
}

} //End namespace avg
