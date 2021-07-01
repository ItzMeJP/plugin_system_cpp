/**\file
 * \brief
 * Sum Plugin declaration
 * @version 01.07.2021
 * @author João Pedro Carvalho de Souza
 */

#ifndef PLUGIN_TEST_V1_SUM_H
#define PLUGIN_TEST_V1_SUM_H

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

PLUGIN_EXPORT_C
auto GetPluginFactory() -> IPluginFactory*
{

static PluginFactory pinfo = []{
    auto p = PluginFactory("PluginSum", "01_06_2021");
    p.registerClass<Sum>("Sum"); //could register more than one Class inside a plugin...
    return p;
}();
return &pinfo;
}

struct _DLLInit{
    _DLLInit(){
        std::cerr << " [TRACE] Shared library PluginSum loaded OK." << std::endl;
    }
    ~_DLLInit(){
        std::cerr << " [TRACE] Shared library PluginSum unloaded OK." << std::endl;
    }
} dll_init;

#endif //PLUGIN_TEST_V1_SUM_H
