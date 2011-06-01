#include "OniTouchPlugin.h"

#include <wrapper/WrapHelper.h>

using namespace boost::python;
namespace avg {

OniTouchPlugin::OniTouchPlugin()
{
    oniDevManagerPtr = OniDeviceManagerPtr(new OniDeviceManager());
    ObjectCounter::get()->incRef(&typeid(*this));
    AVG_TRACE(Logger::PLUGIN, "Construct OniTouchPlugin");
}

OniTouchPlugin::~OniTouchPlugin()
{
    ObjectCounter::get()->decRef(&typeid(*this));
    AVG_TRACE(Logger::PLUGIN, "Deconstruct OniTouchPlugin");
}

const OniDeviceManager* OniTouchPlugin::getOniDevManager(){
    return oniDevManagerPtr.get();
}

}//End namespace avg

BOOST_PYTHON_MODULE(OniTouchPlugin)
{
    class_<avg::OniDeviceManager> ("OniDeviceManager")
        .def(init<>())
        .def("getDevice", &avg::OniDeviceManager::getOniDevice,
                          return_value_policy<manage_new_object>())
    ;

    class_<avg::OniDevice> ("OniDevice", no_init)
        .def(init<>())
    ;

    class_<avg::OniTouchPlugin, boost::noncopyable>("OniTouchPlugin", no_init)
     .def(init<>())
     .def("getDeviceManager", &avg::OniTouchPlugin::getOniDevManager,
                              return_value_policy<manage_new_object>())
    ;
}

AVG_PLUGIN_API void registerPlugin()
{
    initOniTouchPlugin();
    object mainModule(handle<>(borrowed(PyImport_AddModule("__main__"))));
    object swipeModule(handle<>(PyImport_ImportModule("OniTouchPlugin")));
    mainModule.attr("OniTouch") = swipeModule;
}
