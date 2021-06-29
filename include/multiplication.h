//
// Created by joaopedro on 28/06/21.
//

#include "base_operations.h"
#include "psdk/factory.h"

#ifndef PLUGIN_TEST_V1_MULTIPLICATION_H
#define PLUGIN_TEST_V1_MULTIPLICATION_H
class Multiplication : public BaseOperations {
public:
    Multiplication();
    ~Multiplication();
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
    auto p = PluginFactory("PluginMultiplication", "0.1-alpha");
    p.registerClass<Multiplication>("Multiplication"); //could register more than one Class inside a plugin...
    return p;
}();
return &pinfo;
}

struct _DLLInit{
    _DLLInit(){
        std::cerr << " [TRACE] Shared library PluginMultiplication loaded OK." << std::endl;
    }
    ~_DLLInit(){
        std::cerr << " [TRACE] Shared library PluginMultiplication unloaded OK." << std::endl;
    }
} dll_init;
#endif //PLUGIN_TEST_V1_MULTIPLICATION_H
