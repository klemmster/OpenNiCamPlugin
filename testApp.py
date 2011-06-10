#!/usr/bin/env python
# -*- coding: utf-8 -*-

from libavg import avg, AVGApp
from time import sleep

g_Player = avg.Player.get()

class TestPlugin(AVGApp):

    plugin = None
    manager = None
    oniDev = None

    def init(self):
        g_Player.loadPlugin('onicam')
        #self.plugin = OniCam.OniTouchPlugin()
        #self.manager = self.plugin.getDeviceManager()
        #self.oniDev = self.manager.getDevice(1)
        #node = self.oniDev.getRGBCameraNode()
        cam1Container = avg.DivNode(size=(640, 480))
        node = OniCam.OniCameraNode(size=(640, 480))
        node.activateDevice(0)
        node.activateCamera(OniCam.ONI_RGB_CAMERA)
        cam1Container.appendChild(node)

        cam2Container = avg.DivNode(size=(640, 480), pos=(640, 0))
        node = OniCam.OniCameraNode(size=(640, 480))
        node.activateDevice(0)
        node.activateCamera(OniCam.ONI_DEPTH_CAMERA)
        cam2Container.appendChild(node)

        g_Player.getRootNode().appendChild(cam1Container)
        g_Player.getRootNode().appendChild(cam2Container)

if __name__ == '__main__':
    TestPlugin.start(resolution=(1280, 480))
