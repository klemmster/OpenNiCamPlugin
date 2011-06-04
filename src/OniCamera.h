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
        OniCamera(OniCameraType type);
        BitmapPtr& getBitmapPtr(){ return m_pImage;};
        void setBitmapPtr(BitmapPtr rhs){ m_pImage = rhs;};
        OniCameraType getType() { return m_type; };
        virtual ~OniCamera();
    protected:
    private:

    BitmapPtr m_pImage;
    OniCameraType m_type;
};

typedef boost::shared_ptr<OniCamera> OniCameraPtr;

}//End namespace avg

#endif // _ONICAMERA_H_
