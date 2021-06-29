//
// Created by joaopedro on 28/06/21.
//

#include "calculator.h"


/*
#include "sum.h"
#include "multiplication.h"
#include "subtraction.h"
#include "division.h"
*/


using namespace std;

Calculator::Calculator() {};

Calculator::~Calculator() {};

void Calculator::run(){
    loadPlugins();

}

bool Calculator::loadPlugins() {
    PluginManager ma;
    std::vector<IPluginFactory*> p_factor_arr;
    p_factor_arr = ma.addPlugins("/home/joaopedro/clion_ws/plugin_test_v1/plugins_remove/");
    assert(ma.GetNumberOfPluginsLoaded()!=0);
    std::cout << "Number of loaded libs: " << ma.GetNumberOfPluginsLoaded() << std::endl;
    printPluginsInfo(p_factor_arr);

    return true;
}

void Calculator::printPluginsInfo(std::vector<IPluginFactory*> &_arr){

    for (size_t i = 0; i < _arr.size(); ++i) {
        assert(_arr.at(i) != nullptr);
    }
    for (size_t i = 0; i < _arr.size(); ++i) {
        std::cout << " ---- Plugin Information --------- " << "\n"
                  << "  =>              Name = " << _arr.at(i)->Name() << "\n"
                  << "  =>           Version = " << _arr.at(i)->Version() << "\n"
                  << "  => Number of classes = " << _arr.at(i)->NumberOfClasses()
                  << "\n\n";

        std::cout << "Classes exported by the Plugin #"<< i << " " << _arr.at(i)->Name() << ":\n";

        for(size_t n = 0; n < _arr.at(i)->NumberOfClasses(); n++)
        {
            std::cout << " -> Exported Class: " << _arr.at(i)->GetClassName(n) << "\n\n";
        }
    }
}

bool Calculator::loadKnownPlugins(){

    PluginManager ma;
    std::vector<IPluginFactory*> p_factor_arr;

    IPluginFactory* infoSum = ma.addPlugin("libsum");
    IPluginFactory* infoSub = ma.addPlugin("libsubtraction");
    IPluginFactory* infoDiv = ma.addPlugin("libdivision");
    IPluginFactory* infoMult = ma.addPlugin("libmultiplication");

    p_factor_arr.push_back(infoSum);
    p_factor_arr.push_back(infoSub);
    p_factor_arr.push_back(infoDiv);
    p_factor_arr.push_back(infoMult);

    // * infoA = ma.GetPluginInfo("PluginA");
    assert(infoSum != nullptr || infoSub != nullptr || infoDiv != nullptr || infoMult != nullptr);

    for (int i = 0; i < 4; ++i) {
        std::cout << " ---- Plugin Information --------- " << "\n"
                  << "  =>              Name = " << p_factor_arr.at(i)->Name() << "\n"
                  << "  =>           Version = " << p_factor_arr.at(i)->Version() << "\n"
                  << "  => Number of classes = " << p_factor_arr.at(i)->NumberOfClasses()
                  << "\n\n";

        std::cout << "Classes exported by the Plugin "<< i << ":\n";

        for(size_t n = 0; n < p_factor_arr.at(i)->NumberOfClasses(); n++)
        {
            std::cout << " -> Exported Class: " << p_factor_arr.at(i)->GetClassName(n) << "\n";
        }

    }
    float num[2];
    float *numPtr;
    int option;

    for(;;)
    {
        std::cout << "Type two numbers:" << std::endl;
        cin >> num[0] >> num[1];
        numPtr = &num[0];
        std::cout << "Select Operation (1-Sum, 2-Sub, 3-Mult, 4-Div):" << std::endl;
        cin >> option;

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

    return true;
}
