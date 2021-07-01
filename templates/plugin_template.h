/**\file
 * \brief
 * Plugin template declaration
 * @version 01.07.2021
 * @author João Pedro Carvalho de Souza
 */

#ifndef FOO_PLUGIN_H
#define FOO_PLUGIN_H

/** Include the interface class that provides plugin's metadata and instantiate exported classes **/
#include "plugin_interface_template.h"

/**  ################## Plugin Classes Definitions  ###########################  **/

class Foo : public FooInterface {
public:
    Foo();

    ~Foo();

    /** Define all interface methods and variables **/
    float operate(float *_input_arr, int _size);

protected:
    float *input_arr_;
    int size_;

    bool setArgs(float *_input_arr, int _size);

    void run();

    float result_ = -9.999;
};

/** ################## Factory Function - Plugin EntryPoint  ##################  **/
/** This part should be added in all plugins, therefore the plugin management can identified it. **/

/** Define the Plugin name **/
std::string plugin_name = "FooPlugin";

PLUGIN_EXPORT_C
auto GetPluginFactory() -> IPluginFactory * {

    static PluginFactory pinfo = [] {
        /** Properly set the plugin name and version **/
        auto p = PluginFactory(plugin_name.c_str(), "01_06_2021");
        /** Register all classes defined inside the plugin **/
        p.registerClass<Multiplication>("Multiplication");
        return p;
    }();
    return &pinfo;
}

struct _DLLInit {
    _DLLInit() {
        std::cout << " [TRACE] Shared library " << plugin_name << " loaded OK." << std::endl;
    }

    ~_DLLInit() {
        std::cout << " [TRACE] Shared library " << plugin_name << " unloaded OK." << std::cout;
    }
} dll_init;

#endif //FOO_PLUGIN_H
