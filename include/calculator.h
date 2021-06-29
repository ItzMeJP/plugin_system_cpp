//
// Created by joaopedro on 28/06/21.
//

#ifndef PLUGIN_TEST_V1_CALCULATOR_H
#define PLUGIN_TEST_V1_CALCULATOR_H

#include "psdk/loader.h"
#include "base_operations.h"
#include <iostream>
#include <vector>

class Calculator {
    public:
        Calculator();
        ~Calculator();
        void run();
        void printPluginsInfo(std::vector<IPluginFactory*> &_arr);

    protected:
        bool loadPlugins();
        bool loadKnownPlugins();

};
#endif //PLUGIN_TEST_V1_CALCULATOR_H
