/*************************************************************************
 * Project: OniPlugin
 *************************************************************************
 * : Richy $
 * : Richard Klemm $
 *************************************************************************
 *
 * Copyright 2011
 *
 ************************************************************************/
#include "OniCamera.h"

#define AVG_PLUGIN
#include <api.h>

namespace avg{

OniCamera::OniCamera(OniCameraType type):
    m_type(type)
{
    if(type == ONI_RGB_CAMERA){
        m_pImage = BitmapPtr(new Bitmap(IntPoint(640, 480), R8G8B8));
    }else if (type == ONI_DEPTH_CAMERA){
        m_pImage = BitmapPtr(new Bitmap(IntPoint(640, 480), I16));
    }
}

OniCamera::~OniCamera()
{
    //dtor
}

}//End namespace avg
