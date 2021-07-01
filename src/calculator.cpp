/**\file
 * \brief
 * Calculator use case definition
 * @version 01.07.2021
 * @author João Pedro Carvalho de Souza
 */

#include "calculator.h"

Calculator::Calculator() {};

Calculator::~Calculator() {};

bool Calculator::run(){

    std::string path = (std::filesystem::current_path().parent_path().string() + "/plugins/");

    if(!ph_.loadDynamicPlugins(path,true)){
        std::cout << ph_.getOutputMsg() << std::endl;
        return false;
    }

    executeMenu();

    return true;
}


void Calculator::executeMenu(){

    float num[2];
    float *numPtr;
    int option;
    for(;;)
    {
        std::cout << "Type two numbers:" << std::endl;
        std::cin >> num[0] >> num[1];
        numPtr = &num[0];
        std::cout << "Select Operation:\n";

        for (size_t i = 0; i < ph_.GetNumberOfPluginsLoaded(); ++i) {
            std::cout << i << ") " << ph_.GetPluginFactoryInfo(i)->GetClassName(0)<<"\n";
        }

        std::cin >> option;

        auto p = ph_.CreateInstanceAs<BaseOperations>(option,0);
        assert(p != nullptr);

        std::cout << "Result = " << p->operate(numPtr,(int) sizeof(num)/sizeof(float)) << "\n";

        std::cout << "Continue?[1-Yes; 0-No]" << std::endl;
        std::cin >> option;

        if(option == 0)
            break;

    }

}
