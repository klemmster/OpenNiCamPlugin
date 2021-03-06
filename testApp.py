#!/usr/bin/env python
# -*- coding: utf-8 -*-

from libavg import avg, AVGApp

g_Player = avg.Player.get()

class TestPlugin(AVGApp):

    plugin = None
    manager = None
    oniDev = None

    def init(self):
        g_Player.loadPlugin('openni')
        g_root = g_Player.getRootNode()
        #self.plugin = OniCam.OniTouchPlugin()
        #self.manager = self.plugin.getDeviceManager()
        #self.oniDev = self.manager.getDevice(1)
        #node = self.oniDev.getRGBCameraNode()
        stream = openni.StreamNode(deviceID="STANDARD", size=(640, 480), pos=(0, 0),
                opacity=1.0)
        
        g_root.appendChild(stream)
        """
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

        camera = node.getCamera()
        """

if __name__ == '__main__':
    TestPlugin.start(resolution=(800, 480))
