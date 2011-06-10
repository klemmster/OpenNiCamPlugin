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

OniCamera::OniCamera(OniCameraType type, BitmapQueuePtr bmpPtrQueuePtr):
    m_type(type),
    m_pQBmpPtr(bmpPtrQueuePtr)
{
}

BitmapQueuePtr OniCamera::getBmpQueue(){
    return m_pQBmpPtr;
}

BitmapPtr OniCamera::getBitmap(bool blocking){
    BitmapPtr image = m_pQBmpPtr->peek(blocking);
    if(image.get()){
        m_pLastImage = image;
    }
    return m_pLastImage;
}

OniCamera::~OniCamera()
{
    //dtor
}

}//End namespace avg
