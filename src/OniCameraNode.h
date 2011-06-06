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
#ifndef _ONICAMERANODE_H_
#define _ONICAMERANODE_H_

#define AVG_PLUGIN
#include <api.h>

#include <player/CameraNode.h>
#include <graphics/Bitmap.h>
#include <player/NodeDefinition.h>
#include <base/Logger.h>
#include <player/OGLSurface.h>

#include "OniDeviceManager.h"
#include "OniCamera.h"

namespace avg{

class AVG_API OniCameraNode : public RasterNode
{
    public:
        OniCameraNode(const ArgList& Args);
        virtual ~OniCameraNode();

        static NodeDefinition createNodeDefinition();

        virtual void setRenderingEngines(DisplayEngine* pDisplayEngine,
                AudioEngine* pAudioEngine);
        virtual void maybeRender(const DRect& Rect);
        virtual void render (const DRect& Rect);

        void activateDevice(int id = 0);
        void activateCamera(OniCameraType type = ONI_RGB_CAMERA);

    protected:
    private:

        OniDevicePtr m_pOniDev;
        BitmapPtr m_pImage;
};

typedef boost::shared_ptr<OniCameraNode> OniCameraNodePtr;

}//end namespace avg

#endif // _ONICAMERANODE_H_
