/**\file
 * \brief
 * Division Plugin declaration
 * @version 01.07.2021
 * @author João Pedro Carvalho de Souza
 */

#ifndef PLUGIN_TEST_V1_DIVISION_H
#define PLUGIN_TEST_V1_DIVISION_H

#include "base_operations.h"

// ################## Plugin Classes Definitions  ###########################  //

class Division : public BaseOperations {
public:
    Division();
    ~Division();

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
        auto p = PluginFactory("PluginDivision", "01_06_2021");
        p.registerClass<Division>("Division"); //could register more than one Class inside a plugin...
        return p;
    }();
    return &pinfo;
}

struct _DLLInit{
    _DLLInit(){
        std::cerr << " [TRACE] Shared library PluginDivision loaded OK." << std::endl;
    }
    ~_DLLInit(){
        std::cerr << " [TRACE] Shared library PluginDivision unloaded OK." << std::endl;
    }
} dll_init;
#endif //PLUGIN_TEST_V1_DIVISION_H
