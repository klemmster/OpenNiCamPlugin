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

#ifndef _ONIDEVICE_H_
#define _ONIDEVICE_H_

#define AVG_PLUGIN
#include <api.h>

//Header AVG
#include <imaging/Camera.h>
#include <base/Logger.h>
#include <base/Exception.h>
#include <graphics/Bitmap.h>
#include <base/IPlaybackEndListener.h>

#include "OniDeviceThread.h"
#include "OniCameraNode.h"

namespace avg{

enum OniCameraType{
    ONI_RGB_CAMERA, ONI_DEPTH_CAMERA
};

class OniDevice : public IPlaybackEndListener
{
    public:
        OniDevice();
        virtual ~OniDevice();

        void onPlaybackEnd();

        OniCameraNode getRGBCameraNode();

    protected:
    private:

    void registerCamera(OniCameraType camType);

    boost::thread* m_pDeviceThread;
    OniDeviceThread::CQueuePtr m_pDevCmdQueue;

};

typedef boost::shared_ptr<OniDevice> OniDevicePtr;

}//End namespace avg

#endif // _ONIDEVICE_H_
