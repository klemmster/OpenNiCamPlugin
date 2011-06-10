#include "OniCamPlugin.h"

#include <wrapper/WrapHelper.h>
#include <wrapper/raw_constructor.hpp>
#include "OniCameraNode.h"

using namespace boost::python;

char OniCameraNodeName[] = "OniCameraNode";

BOOST_PYTHON_MODULE(OniCamPlugin)
{

    class_<avg::OniCameraNode, bases<avg::RasterNode>, boost::shared_ptr<avg::OniCameraNode>, boost::noncopyable>("OniCameraNode", no_init)
        .def("__init__", raw_constructor(createNode<OniCameraNodeName>))
        .def("activateDevice", &avg::OniCameraNode::activateDevice)
        .def("activateCamera", &avg::OniCameraNode::activateCamera)
        .def("getBitmap", &avg::OniCameraNode::getBitmap)
        ;

    enum_<avg::OniCameraType>("OniCameraType")
        .value("ONI_RGB_CAMERA", avg::ONI_RGB_CAMERA)
        .value("ONI_DEPTH_CAMERA", avg::ONI_DEPTH_CAMERA)
        .export_values()
        ;
}

AVG_PLUGIN_API void registerPlugin()
{
    initOniCamPlugin();
    object mainModule(handle<>(borrowed(PyImport_AddModule("__main__"))));
    object swipeModule(handle<>(PyImport_ImportModule("OniCamPlugin")));
    mainModule.attr("OniCam") = swipeModule;

    avg::NodeDefinition myNodeDefinition = avg::OniCameraNode::createNodeDefinition();
    const char* allowedParentNodeNames[] = {"avg", "div", "canvas", 0};

    // Register this node type
    avg::Player::get()->registerNodeType(myNodeDefinition, allowedParentNodeNames);
}
