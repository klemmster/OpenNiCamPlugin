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
#include <base/Exception.h>
#include <player/OGLSurface.h>
#include <graphics/TextureMover.h>

#include "OniDeviceManager.h"
#include "OniCamera.h"

namespace avg{

class AVG_API OniCameraNode : public RasterNode
{
    public:
        OniCameraNode(const ArgList& Args);
        virtual ~OniCameraNode();

        static NodeDefinition createNodeDefinition();

        virtual void preRender(const VertexArrayPtr& pVA, bool bIsParentActive,
                float parentEffectiveOpacity);
        virtual void render();

        void activateDevice(int id = 0);
        void activateCamera(OniCameraType type = ONI_RGB_CAMERA);

        BitmapPtr getBitmap(bool blocking=false);
        OniCameraPtr getCamera();

    protected:
    private:

        OniDevicePtr m_pOniDev;
        OniCameraPtr m_pCamera;
        TextureMoverPtr m_pTexMover;
        GLTexturePtr m_pTexture;
};

typedef boost::shared_ptr<OniCameraNode> OniCameraNodePtr;

}//end namespace avg

#endif // _ONICAMERANODE_H_
