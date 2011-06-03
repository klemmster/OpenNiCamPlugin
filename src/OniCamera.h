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

namespace avg{

enum OniCameraType{
    ONI_RGB_CAMERA, ONI_DEPTH_CAMERA
};

class OniCamera
{
    public:
        OniCamera(BitmapPtr imagePtr);
        BitmapPtr getBitmapPtr(){ return m_pImage;};
        virtual ~OniCamera();
    protected:
    private:

    BitmapPtr m_pImage;
};

typedef boost::shared_ptr<OniCamera> OniCameraPtr;

}//End namespace avg

#endif // _ONICAMERA_H_
