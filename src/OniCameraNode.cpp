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
#include "OniCameraNode.h"

namespace avg{

OniCameraNode::OniCameraNode(const ArgList& Args)
{
    AVG_TRACE(Logger::PLUGIN, "OniCameraNode Constructed with Args");
    Args.setMembers(this);
    m_pTexture = GLTexturePtr(new GLTexture(IntPoint(320, 240), I8, GL_DYNAMIC_DRAW));
    m_pTexMover = TextureMover::create(IntPoint(320, 240), I8, GL_DYNAMIC_DRAW);
    getSurface()->create(I8, m_pTexture);
    ObjectCounter::get()->incRef(&typeid(*this));
}

OniCameraNode::~OniCameraNode()
{
    ObjectCounter::get()->decRef(&typeid(*this));

}

NodeDefinition OniCameraNode::createNodeDefinition(){
    return NodeDefinition("OniCameraNode", RasterNode::buildNode<OniCameraNode>)
        .extendDefinition(RasterNode::createDefinition())
        ;
}

void OniCameraNode::preRender(const VertexArrayPtr& pVA, bool bIsParentActive,
        float parentEffectiveOpacity)
{
    Node::preRender(pVA, bIsParentActive, parentEffectiveOpacity);
    if(m_pCamera.get()){
        renderFX(getSize(), Pixel32(255, 255, 255, 255), false, false);
    }
    calcVertexArray(pVA);
}

void OniCameraNode::render()
{

    if(m_pCamera.get()){
        BitmapPtr camImg = m_pCamera->getBitmap(false);
        if(camImg.get()){
            BitmapPtr pBmp = m_pTexMover->lock();
            pBmp->copyPixels(*camImg);
            m_pTexMover->unlock();
            m_pTexMover->moveToTexture(*m_pTexture);
            blt32(getTransform(), getSize(), getEffectiveOpacity(), getBlendMode(), false);
        }
    }
}

void OniCameraNode::activateDevice(int id){
    m_pOniDev = OniDeviceManager::get().getOniDevice(id);
}

void OniCameraNode::activateCamera(OniCameraType type ){
    m_pCamera = m_pOniDev->getCamera(type);
}

BitmapPtr OniCameraNode::getBitmap(bool blocking){
    if(m_pCamera.get()){
        return m_pCamera->getBitmap(blocking);
    }else{
        throw Exception(AVG_ERR_NO_NODE, "Activate Camera first");
    }
}

OniCameraPtr OniCameraNode::getCamera(){
    return m_pCamera;
}

}//End namespace avg
