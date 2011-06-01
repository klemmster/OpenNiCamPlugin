#ifndef _OniTouchPlugin_H_
#define _OniTouchPlugin_H_

#define AVG_PLUGIN
#include <api.h>

#include <base/Logger.h>

#include "OniDeviceManager.h"

namespace avg {

class AVG_PLUGIN OniTouchPlugin
{
public:
    OniTouchPlugin();
    virtual ~OniTouchPlugin();
    const OniDeviceManager* getOniDevManager();

private:

    void onPlaybackEnd();

    OniDeviceManagerPtr oniDevManagerPtr;

};

}//End namespace avg


#endif

