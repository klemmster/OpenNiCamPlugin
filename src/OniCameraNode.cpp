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
#include "OniCameraNode.h"

namespace avg{

OniCameraNode::OniCameraNode(const ArgList& Args)
{
    AVG_TRACE(Logger::PLUGIN, "OniCameraNode Constructed with Args");
    Args.setMembers(this);
}

OniCameraNode::~OniCameraNode()
{
    //dtor
}

NodeDefinition OniCameraNode::createNodeDefinition(){
    return NodeDefinition("OniCameraNode", VisibleNode::buildNode<OniCameraNode>)
        .extendDefinition(RasterNode::createDefinition())
        ;
}

void OniCameraNode::setRenderingEngines(DisplayEngine* pDisplayEngine,
                                  AudioEngine* pAudioEngine){
	RasterNode::setRenderingEngines(pDisplayEngine, pAudioEngine);
    getSurface()->create(IntPoint(640, 480), R8G8B8A8);
}

void OniCameraNode::maybeRender(const DRect& rect){
    render(rect);
}

void OniCameraNode::render (const DRect& Rect){

    if(m_pImage){
    BitmapPtr pBmp = getSurface()->lockBmp();
    const unsigned char * pixels = m_pImage->getPixels();
    AVG_TRACE(Logger::PLUGIN, "Value: " << (int)pixels[960]);
    AVG_TRACE(Logger::PLUGIN, "Value1: " << (int)pixels[961]);
    pBmp->copyPixels(*m_pImage);
//    AVG_TRACE(Logger::PLUGIN, "Pixel - Format:" << m_pImage->getPixelFormat())
    getSurface()->unlockBmps();

    bind();
    blt32(getSize(), getEffectiveOpacity(), getBlendMode());
    }
}

void OniCameraNode::activateDevice(int id){
    m_pOniDev = OniDeviceManager::get().getOniDevice(id);
}

void OniCameraNode::activateCamera(OniCameraType type ){
    m_pImage = m_pOniDev->getCamera(type)->getBitmapPtr();
}

}//End namespace avg
