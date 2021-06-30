//
// Created by joaopedro on 30/06/21.
//

#include "plugin_handling/loader.h"
#include "base_operations.h"
#include <iostream>
#include <vector>

#ifndef PLUGIN_TEST_V1_PLUGIN_HANDLING_H
#define PLUGIN_TEST_V1_PLUGIN_HANDLING_H

class PluginHandling {

public:
    PluginHandling();

    ~PluginHandling();

protected:
    void setPluginsFolderPath(std::string _path);

    std::string getPluginsFolderPath(std::string _path);

    bool loadDynamicPlugins(std::string _plugins_folder_path, bool _log);

    bool loadDynamicPluginsFromFolder();

    bool loadStaticPlugins(std::vector<std::string> _plugins_names_arr,std::string _plugins_folder_path, bool _log);

    bool getPluginsInfo(std::string &_plugin_info_str);

    bool verifyLoadedPlugins();


    std::string getOutputMsg();

    PluginManager plugin_manager_;
    std::vector<IPluginFactory *> plugin_factor_arr_;
    std::string output_msg_ = "NULL",
            plugins_folder_path_ = "NULL";

};

#endif //PLUGIN_TEST_V1_PLUGIN_HANDLING_H
