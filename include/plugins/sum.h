/**\file
 * \brief
 * Sum Plugin declaration
 * @version 01.07.2021
 * @author João Pedro Carvalho de Souza
 */

#ifndef SUM_H
#define SUM_H

#include "base_operations.h"

// ################## Plugin Classes Definitions  ###########################  //

class Sum : public BaseOperations {
public:
    Sum();
    ~Sum();

    float operate(float* _input_arr, int _size);

protected:
    float* input_arr_;
    int size_;
    bool setArgs(float* _input_arr, int _size);
    void run();
    float result_ = -9.999;
};

// ################## Factory Function - Plugin EntryPoint  ##################  //

std::string plugin_name = "PluginSum";

PLUGIN_EXPORT_C
auto GetPluginFactory() -> IPluginFactory*
{

static PluginFactory pinfo = []{
    auto p = PluginFactory(plugin_name.c_str(), "01_06_2021");
    p.registerClass<Sum>("Sum"); //could register more than one Class inside a plugin...
    return p;
}();
return &pinfo;
}

struct _DLLInit{
    _DLLInit(){
        std::cout << " [TRACE] Shared library "<< plugin_name << " loaded OK." << std::endl;
    }
    ~_DLLInit(){
        std::cout << " [TRACE] Shared library "<< plugin_name << " unloaded OK." << std::endl;
    }
} dll_init;

#endif //SUM_H
