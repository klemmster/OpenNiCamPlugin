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
        self.plugin = OniTouch.OniTouchPlugin()
        self.manager = self.plugin.getDeviceManager()
        self.oniDev = self.manager.getDevice(1)

if __name__ == '__main__':
    TestPlugin.start(resolution=(800, 480))
