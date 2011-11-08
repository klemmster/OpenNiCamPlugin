#ifndef _OniDeviceManager_H_
#define _OniDeviceManager_H_

#define AVG_PLUGIN
#include <api.h>

#include <base/ObjectCounter.h>

#include "OniDevice.h"

namespace avg {

class AVG_PLUGIN OniDeviceManager
{
public:

    const OniDevicePtr getOniDevice(int number);

    static OniDeviceManager& get() {
        static OniDeviceManager instance;
        return instance;
    }

private:
    typedef std::map<int, OniDevicePtr> DeviceIDMap;
    OniDeviceManager();
    OniDeviceManager(const OniDeviceManager&) {};
    ~OniDeviceManager();

    DeviceIDMap m_DevIDMap;
};

}//End namespace avg

#endif
