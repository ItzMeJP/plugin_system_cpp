//
// Created by joaopedro on 28/06/21.
//

#ifndef PLUGIN_TEST_V1_CALCULATOR_H
#define PLUGIN_TEST_V1_CALCULATOR_H

#include "plugin_handling/plugin_handling.h"
#include "base_operations.h"
#include <iostream>
#include <vector>

class Calculator : public PluginHandling{
    public:
        Calculator();
        ~Calculator();
        bool run(bool _dynamic_load = true);
        void executeMenu(bool _dynamic_load);
    protected:

};
#endif //PLUGIN_TEST_V1_CALCULATOR_H
