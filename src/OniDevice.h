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
#include <base/Logger.h>
#include <base/Exception.h>
#include <graphics/Bitmap.h>
#include <base/IPlaybackEndListener.h>

#include "OniCamera.h"

namespace avg{

class OniDevice : public IPlaybackEndListener
{
    public:
        OniDevice();
        virtual ~OniDevice();

        void onPlaybackEnd();
        OniCameraPtr getCamera(OniCameraType type);
    protected:
    private:

    boost::thread* m_pDeviceThread;
    OniDeviceThread::CQueuePtr m_pDevCmdQueue;
    OniCameraPtr m_pOniCam;

    OniDeviceThread::BitmapQueuePtr m_pQPtrDepthBmpPtr;
    OniDeviceThread::BitmapQueuePtr m_pQPtrRGBBmpPtr;
};

typedef boost::shared_ptr<OniDevice> OniDevicePtr;

}//End namespace avg

#endif // _ONIDEVICE_H_
