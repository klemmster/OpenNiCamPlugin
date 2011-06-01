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
    OniDeviceManager();
    virtual ~OniDeviceManager();

    const OniDevice* getOniDevice(int number);
private:

    //TODO: MAP for devices or something
    OniDevicePtr myDevicePtr;
};

typedef boost::shared_ptr<OniDeviceManager> OniDeviceManagerPtr;
}//End namespace avg

#endif
