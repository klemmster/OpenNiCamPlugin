#include <wrapper/WrapHelper.h>
#include <wrapper/raw_constructor.hpp>
#include "OniDeviceManager.h"
#include "OniStreamNode.h"

using namespace boost::python;

char OniStreamNodeName[] = "onistream";

BOOST_PYTHON_MODULE(openni)
{
    class_<avg::OniDeviceManager,bases<>, boost::noncopyable>("DeviceManager", no_init);
    
    class_<avg::OniStreamNode, bases<avg::RasterNode>,
                boost::shared_ptr<avg::OniStreamNode>, boost::noncopyable>
                ("StreamNode", no_init)
                .def("__init__", raw_constructor(createNode<OniStreamNodeName>))
                .def("getBitmap", &avg::OniStreamNode::getBitmap)
                ;

    /*
    class_<avg::OniCamera, boost::shared_ptr<avg::OniCamera>, boost::noncopyable>("OniCamera", no_init)
        ;

    enum_<avg::OniCameraType>("OniCameraType")
        .value("ONI_RGB_CAMERA", avg::ONI_RGB_CAMERA)
        .value("ONI_DEPTH_CAMERA", avg::ONI_DEPTH_CAMERA)
        .export_values()
        ;
    */
};

AVG_PLUGIN_API void registerPlugin()
{
    initopenni();
    object mainModule(handle<>(borrowed(PyImport_AddModule("__main__"))));
    object openniModule(handle<>(PyImport_ImportModule("openni")));
    //mainModule.attr("openni") = boost::python::ptr(avg::OniDeviceManager::get());
    mainModule.attr("openni") = openniModule;
    
    avg::OniStreamNode::registerType();
};
