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

#ifndef ONIDEVICETHREAD_H
#define ONIDEVICETHREAD_H

#define AVG_PLUGIN
#include <api.h>

#include <base/WorkerThread.h>
#include <graphics/Bitmap.h>

//OpenNI - Header
#include <XnOpenNI.h>
#include <XnCppWrapper.h>

#include "OniCamera.h"

namespace avg {

class AVG_API OniDeviceThread : public WorkerThread<OniDeviceThread>
{
    public:
        OniDeviceThread(CQueue& CmdQ,const std::string& threadName);
        virtual ~OniDeviceThread();

        bool init();
        void deinit();
        bool work();

        void setBitmapPtr(OniCameraPtr camPtr);

    protected:

        bool RCisOK(const XnStatus rc);
    private:

        xn::Context m_Context;
        xn::DepthGenerator m_DepthGenerator;
        xn::ImageGenerator m_ImageGenerator;

        XnMapOutputMode rgbConfig;
        //TODO: Improvement: Use Image/Depth Metadata

        BitmapPtr m_pRGBImage;
        BitmapPtr m_pDepthImage;
};

} //end namespace avg
#endif // ONIDEVICETHREAD_H
