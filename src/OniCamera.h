/*************************************************************************
 * Project: Bonnie - Server
 * Function:
 *************************************************************************
 * : Richy $
 * : Richard Klemm $
 *************************************************************************
 *
 * Copyright 2009 by Coding Reality GbR
 *
 ************************************************************************/
#ifndef _ONICAMERA_H_
#define _ONICAMERA_H_

#define AVG_PLUGIN
#include <api.h>

#include <graphics/Bitmap.h>

#include "OniDeviceThread.h"

namespace avg{

enum OniCameraType{
    ONI_RGB_CAMERA, ONI_DEPTH_CAMERA
};

class OniCamera
{
    public:
        OniCamera(OniCameraType type, OniDeviceThread::BitmapQueuePtr bmpQueuePtr);
        OniCameraType getType() { return m_type; };

        OniDeviceThread::BitmapQueuePtr getBmpQueue();
        BitmapPtr getBitmap(bool blocking = true);
        virtual ~OniCamera();
    protected:
    private:

    OniDeviceThread::BitmapQueuePtr m_pQBmpPtr;
    OniCameraType m_type;
    BitmapPtr m_pLastImage;
};

typedef boost::shared_ptr<OniCamera> OniCameraPtr;

}//End namespace avg

#endif // _ONICAMERA_H_
