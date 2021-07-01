/**\file
 * \brief
 * Multiplication Plugin declaration
 * @version 01.07.2021
 * @author João Pedro Carvalho de Souza
 */

#ifndef MULTIPLICATION_H
#define MULTIPLICATION_H

#include "base_operations.h"

// ################## Plugin Classes Definitions  ###########################  //

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

// ################## Factory Function - Plugin EntryPoint  ##################  //

PLUGIN_EXPORT_C
auto GetPluginFactory() -> IPluginFactory*
{

static PluginFactory pinfo = []{
    auto p = PluginFactory("PluginMultiplication", "01_06_2021");
    p.registerClass<Multiplication>("Multiplication"); //could register more than one Class inside a plugin...
    return p;
}();
return &pinfo;
}

struct _DLLInit{
    _DLLInit(){
        std::cout << " [TRACE] Shared library PluginMultiplication loaded OK." << std::endl;
    }
    ~_DLLInit(){
        std::cout << " [TRACE] Shared library PluginMultiplication unloaded OK." << std::endl;
    }
} dll_init;
#endif //MULTIPLICATION_H
