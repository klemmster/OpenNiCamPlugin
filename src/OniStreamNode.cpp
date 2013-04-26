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
#define AVG_PLUGIN
#include "OniStreamNode.h"
#include <player/ExportedObject.h>
#include <player/Player.h>
#include <video/VideoDecoderThread.h>

#include <boost/make_shared.hpp>

using boost::make_shared;

namespace avg{

OniStreamNode::OniStreamNode(const ArgList& Args)
{
    Args.setMembers(this);
    m_pTexture = GLTexturePtr(new GLTexture(IntPoint(640, 480), I8, GL_DYNAMIC_DRAW));
    m_pTexMover = TextureMover::create(IntPoint(640, 480), I8, GL_DYNAMIC_DRAW);
    getSurface()->create(I8, m_pTexture);
    //TODO: get stream dependen on class and deviceID
    StreamPtr stream = OniDeviceManager::get().getVideoStream("TODO", "TODO");
    if(stream->addNewFrameListener(this) != openni::STATUS_OK){
        throw Exception(AVG_ERR_CORRUPT_PLUGIN, "OpenNI:: attach depth listener");
    }
    LOG_PLUGIN_CONFIG("Started stream");
    ObjectCounter::get()->incRef(&typeid(*this));
}

OniStreamNode::~OniStreamNode()
{
    ObjectCounter::get()->decRef(&typeid(*this));

}

void OniStreamNode::registerType(){
    TypeDefinition def = TypeDefinition("onistream", "rasternode",
            ExportedObject::buildObject<OniStreamNode>)
        .addArg(Arg<UTF8String>("deviceID", "", false, offsetof(OniStreamNode, m_deviceID)))
        ;
    const char* allowedParentNodeNames[] = { "avg", "div", 0};
    TypeRegistry::get()->registerType(def, allowedParentNodeNames);
}

void OniStreamNode::preRender(const VertexArrayPtr& pVA, bool bIsParentActive,
        float parentEffectiveOpacity)
{
    Node::preRender(pVA, bIsParentActive, parentEffectiveOpacity);
    renderFX(getSize(), Pixel32(255, 255, 255, 255), false, false);
    calcVertexArray(pVA);
}

void OniStreamNode::render()
{
    BitmapPtr camImg = getBitmap(false);
    if(camImg.get()){
        BitmapPtr pBmp = m_pTexMover->lock();
        pBmp->copyPixels(*camImg);
        m_pTexMover->unlock();
        m_pTexMover->moveToTexture(*m_pTexture);
        blt32(getTransform(), getSize(), getEffectiveOpacity(), getBlendMode(), false);
    }
}

BitmapPtr OniStreamNode::getBitmap(bool blocking){
    return m_pLastFrame;
}

void OniStreamNode::onNewFrame(VideoStream& stream){
    if ( stream.readFrame(&m_pLastFrameRef) == openni::STATUS_OK) {
        int m_bytes = 640 * 480 * 2;
        unsigned char newPixels[m_bytes];
        const unsigned char* pixels = static_cast< const unsigned char* >
                (m_pLastFrameRef.getData());
        for(unsigned int i=1; i<m_bytes; i++){
            newPixels[i] = static_cast< unsigned char >( (pixels[i] << 2) * 1.6 );
        }
        m_pLastFrame = BitmapPtr(new Bitmap(IntPoint(640, 480), I16, newPixels,
                m_pLastFrameRef.getWidth()*2, true));
    } else {
        throw Exception(AVG_ERR_CAMERA_FATAL, "Couldn't read frame");
    }
}

}//End namespace avg
