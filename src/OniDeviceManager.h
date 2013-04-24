#ifndef _OniDeviceManager_H_
#define _OniDeviceManager_H_

#define AVG_PLUGIN
#include <api.h>

#include <base/Logger.h>
#include <base/ObjectCounter.h>
#include <boost/noncopyable.hpp>

//#include "OniDevice.h"


namespace avg {
    
#define LOG_PLUGIN_CONFIG(msg){\
    AVG_TRACE(Logger::category::PLUGIN, Logger::severity::INFO, msg); \
}\

class AVG_PLUGIN OniDeviceManager:public boost::noncopyable
{
public:

    //const OniDevicePtr getOniDevice(int number);

    static OniDeviceManager* get();
    virtual ~OniDeviceManager();

private:
    //typedef std::map<int, OniDevicePtr> DeviceIDMap;
    OniDeviceManager();

    //DeviceIDMap m_DevIDMap;
};

}//End namespace avg

#endif
