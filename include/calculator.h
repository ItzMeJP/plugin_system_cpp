/**\file
 * \brief
 * Calculator use case declaration
 * @version 01.07.2021
 * @author João Pedro Carvalho de Souza
 */

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "plugin_system_management/plugin_system_management.h"
#include "base_operations.h"
#include <iostream>
#include <vector>
#include <filesystem>

class Calculator {
    public:
        Calculator();
        ~Calculator();
        bool run();
        void executeMenu();
    protected:
    PluginSystemManagement ph_;

};
#endif //CALCULATOR_H
