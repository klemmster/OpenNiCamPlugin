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

    OniDeviceManager();
    OniDeviceManager(const OniDeviceManager&) {};
    ~OniDeviceManager();

    //TODO: MAP for devices or something
    OniDevicePtr myDevicePtr;
};

}//End namespace avg

#endif
