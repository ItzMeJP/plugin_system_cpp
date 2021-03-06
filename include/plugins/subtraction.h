/**\file
 * \brief
 * Subtraction Plugin declaration
 * @version 01.07.2021
 * @author João Pedro Carvalho de Souza
 */

#ifndef SUBTRACTION_H
#define SUBTRACTION_H

#include "base_operations.h"

// ################## Plugin Classes Definitions  ###########################  //

class Subtraction : public BaseOperations {
public:
    Subtraction();
    ~Subtraction();

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
        auto p = PluginFactory("PluginSubtraction", "01_06_2021");
        p.registerClass<Subtraction>("Subtraction"); //could register more than one Class inside a plugin...
        return p;
    }();
    return &pinfo;
}

struct _DLLInit{
    _DLLInit(){
        std::cout << " [TRACE] Shared library PluginSubtraction loaded OK." << std::endl;
    }
    ~_DLLInit(){
        std::cout << " [TRACE] Shared library PluginSubtraction unloaded OK." << std::endl;
    }
} dll_init;
#endif //SUBTRACTION_H
