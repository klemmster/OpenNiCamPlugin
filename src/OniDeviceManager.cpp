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
#include <boost/make_shared.hpp>
#include <base/Exception.h>

using boost::make_shared;

namespace avg {

namespace {
    OniDeviceManager* s_pOniDeviceManager = 0;
}

OniDeviceManager::OniDeviceManager()
{
    if(openni::OpenNI::initialize() != openni::STATUS_OK){
        throw Exception(AVG_ERR_CORRUPT_PLUGIN, "OpenNI::initialize failed");
    }
    ObjectCounter::get()->incRef(&typeid(*this));
    LOG_PLUGIN_CONFIG("Initialized OniDeviceManager");
}

OniDeviceManager::~OniDeviceManager()
{
    StreamMap::iterator sit;
    for(sit=m_streamMap.begin(); sit != m_streamMap.end(); sit++) {
        (sit->second)->stop();
        (sit->second)->destroy();
    }
    DeviceMap::iterator it;
    for(it=m_deviceMap.begin(); it != m_deviceMap.end(); it++) {
        (it->second)->close();
    }
    openni::OpenNI::shutdown;
    ObjectCounter::get()->decRef(&typeid(*this));
    LOG_PLUGIN_CONFIG("Deconstructed OniDeviceManager");
}

StreamPtr OniDeviceManager::getVideoStream(UTF8String deviceID, UTF8String STREAMTYPE) {
    //TODO: Directly expose ans use Streamtype from openni
    size_t streamHash = makeHash(deviceID + STREAMTYPE);
    StreamMap::iterator it;
    it = m_streamMap.find(streamHash);
    if( it != m_streamMap.end()){
        return it->second;
    } else {
        DevicePtr device = getDevice(deviceID);
        StreamPtr stream = make_shared<VideoStream>();
        openni::Status status;
        status = stream->create(*device, openni::SENSOR_DEPTH);
        if( status != openni::STATUS_OK){
            throw Exception(AVG_ERR_CORRUPT_PLUGIN, "OpenNI:: couldn't open stream");
        }
        stream->start();
        m_streamMap[streamHash] = stream;
        return stream;
    }
}

DevicePtr OniDeviceManager::getDevice(UTF8String id){
    DeviceMap::iterator it;
    size_t devIDHash = makeHash(id);
    it = m_deviceMap.find(devIDHash);
    if(it == m_deviceMap.end()){
        DevicePtr device = make_shared<Device>();
        openni::Status status;
        status = device->open(openni::ANY_DEVICE);
        if( status != openni::STATUS_OK ){
            throw Exception(AVG_ERR_CORRUPT_PLUGIN, "OpenNI:: device open failed");
        }
        m_deviceMap[devIDHash] = device;
        return device;
    }else{
        return it->second;
    }
}

} //End namespace avg
