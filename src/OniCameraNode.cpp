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
    if(m_pCamera.get()){
        render(rect);
    }
}

void OniCameraNode::render(const DRect& Rect){

    if(m_pCamera.get()){
    BitmapPtr pBmp = getSurface()->lockBmp();

    pBmp->copyPixels(*(m_pCamera->getBitmap(true)));
    getSurface()->unlockBmps();

    bind();
    blt32(getSize(), getEffectiveOpacity(), getBlendMode());
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

}//End namespace avg
