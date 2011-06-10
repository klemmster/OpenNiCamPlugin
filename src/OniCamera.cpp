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

OniCamera::OniCamera(OniCameraType type, OniDeviceThread::BitmapQueuePtr bmpPtrQueuePtr):
    m_type(type),
    m_pQBmpPtr(bmpPtrQueuePtr)
{
}

OniDeviceThread::BitmapQueuePtr OniCamera::getBmpQueue(){
    return m_pQBmpPtr;
}

BitmapPtr OniCamera::getBitmap(bool blocking){
    AVG_TRACE(Logger::PLUGIN, "ImageQueueSize: " << m_pQBmpPtr->size());
    BitmapPtr image = m_pQBmpPtr->pop(blocking);
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
