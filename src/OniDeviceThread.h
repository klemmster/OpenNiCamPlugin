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

//OpenNI - Header
#include <XnCppWrapper.h>

namespace avg {

class OniDeviceThread : public WorkerThread<OniDeviceThread>
{
    public:
        OniDeviceThread(CQueue& CmdQ,const std::string& threadName);
        virtual ~OniDeviceThread();

        bool init();
        void deinit();
        bool work();

    protected:
    private:
};

} //end namespace avg
#endif // ONIDEVICETHREAD_H
