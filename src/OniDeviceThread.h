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
#include <video/VideoDecoderThread.h>
#include <base/Queue.h>
#include <graphics/Bitmap.h>

//OpenNI - Header
#include <XnOpenNI.h>
#include <XnCppWrapper.h>

namespace avg {

class AVG_API OniDeviceThread : public WorkerThread<OniDeviceThread>
{
    public:

        OniDeviceThread(CQueue& CmdQ,const std::string& threadName,
                BitmapQueuePtr rgbQueue, BitmapQueuePtr depthQueue);
        virtual ~OniDeviceThread();

        bool init();
        void deinit();
        bool work();

    protected:

        bool RCisOK(const XnStatus rc);
    private:

        xn::Context m_Context;
        xn::DepthGenerator m_DepthGenerator;
        xn::ImageGenerator m_ImageGenerator;

        XnMapOutputMode rgbConfig;
        //TODO: Improvement: Use Image/Depth Metadata

        BitmapQueuePtr m_pQrgb;
        BitmapQueuePtr m_pQdepth;
        IntPoint m_Size;
};

} //end namespace avg
#endif // ONIDEVICETHREAD_H
