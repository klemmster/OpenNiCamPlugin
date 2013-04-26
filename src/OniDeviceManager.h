#ifndef _OniDeviceManager_H_
#define _OniDeviceManager_H_

#define AVG_PLUGIN
#include <api.h>

#include <base/Logger.h>
#include <base/ObjectCounter.h>
#include <boost/noncopyable.hpp>
#include <boost/functional/hash.hpp>
//#include <boost/shared_ptr.hpp>

#include "OpenNIWrapper.h"

using boost::shared_ptr;

using openni::Device;
using openni::VideoStream;

namespace avg {

#define LOG_PLUGIN_CONFIG(msg){\
    AVG_TRACE(Logger::category::PLUGIN, Logger::severity::INFO, msg); \
}\

typedef shared_ptr<Device> DevicePtr;
typedef shared_ptr<VideoStream> StreamPtr;

class AVG_PLUGIN OniDeviceManager:private boost::noncopyable
{
public:

    static OniDeviceManager& get() {
        static OniDeviceManager instance;
        return instance;
    }

    StreamPtr getVideoStream(UTF8String device, UTF8String STREAMTYPE);

    // vector <string> getDeviceIDS();

private:
    typedef std::map<const size_t, DevicePtr> DeviceMap;
    typedef std::map<const size_t, StreamPtr> StreamMap;
    
    OniDeviceManager();
    virtual ~OniDeviceManager();

    DevicePtr getDevice(UTF8String id);

    DeviceMap m_deviceMap;
    StreamMap m_streamMap;
    boost::hash<std::string> makeHash;
};

}//End namespace avg

#endif
