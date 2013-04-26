# OpenNI Camera Plugin
A plugin for [libavg](https://www.libavg.de "libavg" enabling the use of ([OpenNI](http://www.openni.org "OpenNI") based cameras.

## Setup

### Linux
CMakeLists isn't very generic yet (aka crappy), adjust paths (e.g. /home/richy) manually.
If not using a kinect, it should 'just work'. Eg. just install OpenNI2 and libavg and then do:

cmake .
make
python testApp.py

For using a kinect with OpenNI2 on Linux, you have to use [OpenNI2-Freenect](https://github.com/piedar/OpenNI2-FreenectDriver "OpenNI"-Freenect) instead of Standard OpenNI2.


### OSX
### Windows
