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

OniCamera::OniCamera(BitmapPtr imagePtr):
    m_pImage(imagePtr)
{
    //ctor
}

OniCamera::~OniCamera()
{
    //dtor
}

}//End namespace avg
