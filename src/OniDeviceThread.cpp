/*************************************************************************
 * Project: OniPlugin
 *************************************************************************
 * $Author: Richy $
 * $Name: Richard Klemm $
 *************************************************************************
 *
 * Copyright 2011
 *
 ************************************************************************/

#include "OniDeviceThread.h"

namespace avg {

OniDeviceThread::OniDeviceThread(CQueue& CmdQ,const std::string& threadName):
    WorkerThread<OniDeviceThread>(threadName, CmdQ)
{
}

OniDeviceThread::~OniDeviceThread()
{

}

bool OniDeviceThread::init(){
    AVG_TRACE(Logger::PLUGIN, "Init Thread");

    m_pDepthImage = BitmapPtr(new Bitmap(IntPoint(640, 480), I16));
    m_pRGBImage = BitmapPtr(new Bitmap(IntPoint(640, 480), R8G8B8));

    XnStatus rc = XN_STATUS_OK;
    xn::EnumerationErrors errors;
    rc = m_Context.Init();
    RCisOK(rc);
    rc = m_DepthGenerator.Create(m_Context);
    RCisOK(rc);
    rc = m_ImageGenerator.Create(m_Context);
    RCisOK(rc);
    rc = m_Context.StartGeneratingAll();
    RCisOK(rc);
    return true;
}

void OniDeviceThread::deinit(){
    AVG_TRACE(Logger::PLUGIN, "Deinit Thread");
}

bool OniDeviceThread::work(){
    XnStatus rc = m_Context.WaitAndUpdateAll();
    if(RCisOK(rc)){
        const XnUInt8* pRGBPixel = m_ImageGenerator.GetImageMap();
        m_pRGBImage->setPixels(pRGBPixel);

        //DepthMap
        const XnDepthPixel* pDepthMap = m_DepthGenerator.GetDepthMap();
        uint8_t * map = new unsigned char[640*480*2]; //Times two, because it's 16Bits
        unsigned int pointer = 0;
        for(unsigned int y=0; y<480; y++){
            for(unsigned int x=0; x<640; x++){
                const XnDepthPixel val = pDepthMap[x+y*640];
                map[pointer+1] = 0x00 | val;
                map[pointer] = val >> 8;
                pointer+= 2;
            }
        }
        m_pDepthImage->setPixels(map);
        delete map;
    }
    return true;
}

void OniDeviceThread::setBitmapPtr(OniCameraPtr camPtr){
    OniCameraType type = camPtr->getType();
    if(type == ONI_DEPTH_CAMERA){
        m_pDepthImage = camPtr->getBitmapPtr();
        return;
    }else if(type == ONI_RGB_CAMERA){
        m_pRGBImage = camPtr->getBitmapPtr();
        return;
    }
}

bool OniDeviceThread::RCisOK(const XnStatus rc){
    if(rc != XN_STATUS_OK){
        AVG_TRACE(Logger::PLUGIN, "ERROR: " << xnGetStatusString(rc));
        throw(Exception(AVG_ERR_CORRUPT_PLUGIN,
                   xnGetStatusString(rc)));
    }
    return true;
};

}//end namespace avg
