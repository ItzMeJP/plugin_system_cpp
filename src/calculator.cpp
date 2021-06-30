//
// Created by joaopedro on 28/06/21.
//

#include "calculator.h"

using namespace std;

Calculator::Calculator() {};

Calculator::~Calculator() {};

bool Calculator::run(bool _dynamic_load){

    std::string path = ("/home/joaopedro/clion_ws/plugin_test_v1/plugins_remove/");

    if(_dynamic_load)
    {
        std::cout << "######## DYNAMIC LOAD EXAMPLE ######## \n" << std::endl;
        if(!loadDynamicPlugins(path,true))
            return false;
    }
    else{
        std::cout << "######## STATIC LOAD EXAMPLE ######## \n" << std::endl;
        std::vector<std::string> names_arr{"libsum","libsubtraction","libdivision","libmultiplication"}; // The name must be equal to the plugin.so name (without extension)
        if(!loadStaticPlugins(names_arr,path,true))
            return false;
    }
    executeMenu(_dynamic_load);
    return true;
}


void Calculator::executeMenu(bool _dynamic_load){

    float num[2];
    float *numPtr;
    int option;
    for(;;)
    {
        std::cout << "Type two numbers:" << std::endl;
        cin >> num[0] >> num[1];
        numPtr = &num[0];
        std::cout << "Select Operation:\n";

        for (size_t i = 0; i < plugin_factor_arr_.size(); ++i) {
            std::cout << i << ") " << plugin_factor_arr_.at(i)->GetClassName(0)<<"\n";
        }

        cin >> option;

        if(_dynamic_load){
            auto p = plugin_manager_.CreateInstanceAs<BaseOperations>(option,0);
            assert(p != nullptr);
            std::cout << "Result = " << p->operate(numPtr,(int) sizeof(num)/sizeof(float)) << "\n";

        }
        else{
            auto p = plugin_manager_.CreateInstanceAs<BaseOperations>(plugin_manager_.m_plugindb.at(option).loaded_plugins_file_names_arr_.at(option),plugin_factor_arr_.at(option)->GetClassName(0));
            assert(p != nullptr);
            std::cout << "Result = " << p->operate(numPtr,(int) sizeof(num)/sizeof(float)) << "\n";

        }


    }

}





/*

    float num[2];
    float *numPtr;
    int option;
    for(;;)
    {
        std::cout << "Type two numbers:" << std::endl;
        cin >> num[0] >> num[1];
        numPtr = &num[0];
        std::cout << "Select Operation\n:";

        for (size_t i = 0; i < plugin_factor_arr_.size(); ++i) {
            std::cout << i << ")" << plugin_factor_arr_.at(i)->GetClassName(0);
        }

        cin >> option;

        auto p = plugin_manager_.CreateInstanceAs<BaseOperations>(plugin_factor_arr_.at(option)->Name(),p_factor_arr.at(0)->GetClassName(0));

        switch (option) {
            case 1:
            {
                std::string t0 = "libsum";
                std::string t1 = p_factor_arr.at(0)->GetClassName(0);
                auto p = ma.CreateInstanceAs<BaseOperations>(t0,t1);
                assert(p != nullptr);
                std::cout << "Result = " << p->operate(numPtr,(int) sizeof(num)/sizeof(float)) << "\n";
                break;
            }
            case 2:
            {
                std::string t0 = "libsubtraction";
                std::string t1 = p_factor_arr.at(1)->GetClassName(0);
                auto p = ma.CreateInstanceAs<BaseOperations>(t0,t1);
                assert(p != nullptr);
                std::cout << "Result = " << p->operate(numPtr,(int) sizeof(num)/sizeof(float)) << "\n";
                break;
            }
            case 3:
            {
                std::string t0 = "libmultiplication";
                std::string t1 = p_factor_arr.at(3)->GetClassName(0);
                auto p = ma.CreateInstanceAs<BaseOperations>(t0,t1);
                assert(p != nullptr);
                std::cout << "Result = " << p->operate(numPtr,(int) sizeof(num)/sizeof(float)) << "\n";
                break;
            }
            case 4:
            {
                std::string t0 = "libdivision";
                std::string t1 = p_factor_arr.at(2)->GetClassName(0);
                auto p = ma.CreateInstanceAs<BaseOperations>(t0,t1);
                assert(p != nullptr);
                std::cout << "Result = " << p->operate(numPtr,(int) sizeof(num)/sizeof(float)) << "\n";
                break;
            }
            default:{}

        }
    }

}
*/
