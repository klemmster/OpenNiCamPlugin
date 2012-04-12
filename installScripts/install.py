#!/usr/bin/env python
# encoding: utf-8

from tempfile import mkdtemp
from shutil import rmtree
from os.path import join as joinpath
from urllib import urlretrieve
import platform
import tarfile
import os, fnmatch
import subprocess

OpenNI_URLS = {
        #'linux64': 'http://www.openni.org/downloads/openni-bin-dev-linux-x64-v1.5.2.23.tar.bz2'
        'linux64': 'http://flux:8000/openNI.tar.bz2'
        }


class Installer(object):
    """Docstring for Installer """

    def __init__(self):
        """@todo: to be defined """
        self._tmpDir = mkdtemp()

    def __del__(self):
        #rmtree(self._tmpDir, ignore_errors=True)
        pass

    def install(self):
        raise NotImplementedError


class OpenNIInstaller(Installer):
    """Docstring for OpenNIInstaller """

    def __init__(self):
        super(OpenNIInstaller, self).__init__()
        """@todo: to be defined """

    def _getSources(self):
        #TODO: Win32 / 64
        #TODO: Mac32 / 64?
        #TODO: Lin32

        if platform.system().startswith(u'Linux'):
            if u'64bit' in platform.architecture():
                key = 'linux64'
            else:
                raise NotImplementedError("No OpenNI  Package for this system configured")
        urlretrieve(OpenNI_URLS[key], joinpath(self._tmpDir, 'openNI.tar.bz2'))

    def _extractSources(self):
        niFile = tarfile.open(joinpath(self._tmpDir, 'openNI.tar.bz2'),mode='r:bz2')
        niFile.extractall(path=joinpath(self._tmpDir, 'oni'))
        niFile.close()

    def _install(self):
        #Search install.sh file
        installFile = None
        cwd = None
        for path, dirs, files in os.walk(os.path.abspath(joinpath(self._tmpDir, 'oni'))):
            for filename in fnmatch.filter(files, 'install.sh'):
                installFile = joinpath(path, filename)
                cwd = path
                break
        cmd = ['sudo sh %s' % str(installFile)]
        print installFile
        subprocess.Popen(cmd, cwd=cwd, shell=True)

    def install(self):
        self._getSources()
        self._extractSources()
        self._install()


class KinectInstaller(Installer):
    """Docstring for KinectInstaller """

    def __init__(self):
        super(KinectInstaller, self).__init__()
        """@todo: to be defined """


class XtionInstaller(Installer):
    """Docstring for MyClass """

    def __init__(self):
        super(XtionInstaller, self).__init__()
        """@todo: to be defined """


if __name__ == '__main__':
    oni = OpenNIInstaller()
    oni.install()

