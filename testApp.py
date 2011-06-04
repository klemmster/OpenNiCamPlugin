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
        g_Player.loadPlugin('onitouch')
        #self.plugin = OniTouch.OniTouchPlugin()
        #self.manager = self.plugin.getDeviceManager()
        #self.oniDev = self.manager.getDevice(1)
        #node = self.oniDev.getRGBCameraNode()
        cam1Container = avg.DivNode(size=(800, 600))
        node = OniTouch.OniCameraNode(size=(640, 480))
        node.activateDevice(0)
        node.activateCamera(OniTouch.ONI_RGB_CAMERA)
        cam1Container.appendChild(node)

        cam2Container = avg.DivNode(size=(800, 600), pos=(640, 0))
        node = OniTouch.OniCameraNode(size=(640, 480))
        node.activateDevice(0)
        node.activateCamera(OniTouch.ONI_DEPTH_CAMERA)
        cam2Container.appendChild(node)

        g_Player.getRootNode().appendChild(cam1Container)
        g_Player.getRootNode().appendChild(cam2Container)

if __name__ == '__main__':
    TestPlugin.start(resolution=(1280, 480))
