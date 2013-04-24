#include <wrapper/WrapHelper.h>
#include <wrapper/raw_constructor.hpp>
#include "OniDeviceManager.h"
//#include "OniCameraNode.h"

using namespace boost::python;

char OniCameraNodeName[] = "OniCameraNode";

BOOST_PYTHON_MODULE(openni)
{

    class_<avg::OniDeviceManager,bases<>, boost::noncopyable>("OniDeviceManager", no_init);
    /*
    class_<avg::OniCameraNode, bases<avg::RasterNode>, boost::shared_ptr<avg::OniCameraNode>, boost::noncopyable>("OniCameraNode", no_init)
        .def("__init__", raw_constructor(createNode<OniCameraNodeName>))
        .def("activateDevice", &avg::OniCameraNode::activateDevice)
        .def("activateCamera", &avg::OniCameraNode::activateCamera)
        .def("getBitmap", &avg::OniCameraNode::getBitmap)
        .def("getCamera", &avg::OniCameraNode::getCamera)
        ;

    class_<avg::OniCamera, boost::shared_ptr<avg::OniCamera>, boost::noncopyable>("OniCamera", no_init)
        ;

    enum_<avg::OniCameraType>("OniCameraType")
        .value("ONI_RGB_CAMERA", avg::ONI_RGB_CAMERA)
        .value("ONI_DEPTH_CAMERA", avg::ONI_DEPTH_CAMERA)
        .export_values()
        ;
    */
}

AVG_PLUGIN_API void registerPlugin()
{
    initopenni();
    object mainModule(handle<>(borrowed(PyImport_AddModule("__main__"))));
    object openniModule(handle<>(PyImport_ImportModule("openni")));
    mainModule.attr("openni") = boost::python::ptr(avg::OniDeviceManager::get());
    //mainModule.attr("openni") = openniModule;

    //avg::NodeDefinition myNodeDefinition = avg::OniCameraNode::createNodeDefinition();
    //const char* allowedParentNodeNames[] = {"avg", "div", "canvas", 0};

    // Register this node type
    //avg::Player::get()->registerNodeType(myNodeDefinition, allowedParentNodeNames);
}
