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
#ifndef _ONISTREAMNODE_H_
#define _ONISTREAMNODE_H_

#define AVG_PLUGIN
#include <api.h>

#include <player/RasterNode.h>
#include <graphics/Bitmap.h>
#include <player/TypeDefinition.h>
#include <base/Logger.h>
#include <base/Exception.h>
//#include <base/IPlaybackEndListener>
#include <player/OGLSurface.h>
#include <graphics/TextureMover.h>
#include <graphics/Filterfill.h>

#include "OniDeviceManager.h"
#include "OpenNIWrapper.h"

using openni::VideoStream;
using openni::VideoFrameRef;

namespace avg{

class AVG_API OniStreamNode : public RasterNode, public VideoStream::NewFrameListener
{
    public:
        OniStreamNode(const ArgList& Args);
        virtual ~OniStreamNode();

        static void registerType();
        //
        virtual void preRender(const VertexArrayPtr& pVA, bool bIsParentActive,
                float parentEffectiveOpacity);
        virtual void render();

        BitmapPtr getBitmap(bool blocking=false);

        void onNewFrame(VideoStream& stream);

    protected:
    private:

        UTF8String m_deviceID;
        TextureMoverPtr m_pTexMover;
        GLTexturePtr m_pTexture;

        BitmapPtr m_pLastFrame;
        VideoFrameRef m_pLastFrameRef;
};

typedef boost::shared_ptr<OniStreamNode> OniStreamNodePtr;

}//end namespace avg

#endif // _ONISTREAMNODE_H_
