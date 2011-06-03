#include "OniTouchPlugin.h"

#include <wrapper/WrapHelper.h>
#include <wrapper/raw_constructor.hpp>
#include "OniCameraNode.h"

using namespace boost::python;

char OniCameraNodeName[] = "OniCameraNode";

BOOST_PYTHON_MODULE(OniTouchPlugin)
{

    class_<avg::OniCameraNode, bases<avg::AreaNode>, boost::shared_ptr<avg::OniCameraNode>, boost::noncopyable>("OniCameraNode", no_init)
        .def("__init__", raw_constructor(createNode<OniCameraNodeName>))
        .def("activateDevice", &avg::OniCameraNode::activateDevice)
        ;
}

AVG_PLUGIN_API void registerPlugin()
{
    initOniTouchPlugin();
    object mainModule(handle<>(borrowed(PyImport_AddModule("__main__"))));
    object swipeModule(handle<>(PyImport_ImportModule("OniTouchPlugin")));
    mainModule.attr("OniTouch") = swipeModule;

    avg::NodeDefinition myNodeDefinition = avg::OniCameraNode::createNodeDefinition();
    const char* allowedParentNodeNames[] = {"avg", "div", "canvas", 0};

    // Register this node type
    avg::Player::get()->registerNodeType(myNodeDefinition, allowedParentNodeNames);
}
