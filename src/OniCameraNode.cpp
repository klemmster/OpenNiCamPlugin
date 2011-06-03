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
	//TODO: Fix getSurface
    getSurface()->create(IntPoint(640, 480), R8G8B8A8);
}

void OniCameraNode::maybeRender(const DRect& rect){
    render(rect);
}

void OniCameraNode::render (const DRect& Rect){

    if(m_pImage){
    AVG_TRACE(Logger::PLUGIN, "Render");
    BitmapPtr pBmp = getSurface()->lockBmp();
    pBmp->copyPixels(*m_pImage);
    getSurface()->unlockBmps();

    bind();
    blt32(getSize(), getEffectiveOpacity(), getBlendMode());
    }
}

void OniCameraNode::activateDevice(int id){
    m_pOniDev = OniDeviceManager::get().getOniDevice(id);
    activateCamera(ONI_RGB_CAMERA);
}

void OniCameraNode::activateCamera(OniCameraType type ){
    m_pImage = m_pOniDev->getCamera(ONI_RGB_CAMERA)->getBitmapPtr();
}

}//End namespace avg
