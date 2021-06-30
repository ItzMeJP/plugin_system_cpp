//
// Created by joaopedro on 28/06/21.
//
#ifndef PLUGIN_TEST_V1_SUM_H
#define PLUGIN_TEST_V1_SUM_H

#include "base_operations.h"
#include "plugin_handling/factory.h"


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

// ===== Factory Function - Plugin EntryPoint ==== //

PSDK_PLUGIN_EXPORT_C
auto GetPluginFactory() -> IPluginFactory*
{

static PluginFactory pinfo = []{
    auto p = PluginFactory("PluginSum", "0.1-alpha");
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
