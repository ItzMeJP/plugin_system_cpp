//
// Created by joaopedro on 30/06/21.
//

#include "plugin_handling/plugin_handling.h"

PluginHandling::PluginHandling(){};

PluginHandling::~PluginHandling(){};

void PluginHandling::setPluginsFolderPath(std::string _path){
    plugins_folder_path_ = _path;
}

std::string PluginHandling::getPluginsFolderPath(std::string _path){
    return plugins_folder_path_;
}

bool PluginHandling::loadDynamicPlugins(std::string _plugins_folder_path,bool _log)
{
    plugin_factor_arr_.clear();

    setPluginsFolderPath(_plugins_folder_path);

    if(!loadDynamicPluginsFromFolder()
        || !verifyLoadedPlugins())
        return false;

    if(_log){
        std::string log_str = "";
        getPluginsInfo(log_str);
        std::cout << log_str << std::endl;
    }

    return true;

}

bool PluginHandling::loadDynamicPluginsFromFolder() {

    plugin_factor_arr_ = plugin_manager_.addPlugins(plugins_folder_path_);

    if(plugin_manager_.GetNumberOfPluginsLoaded()==0) {
        output_msg_ = "None plugins identified in dir: " + plugins_folder_path_;
        return false;
    }
    output_msg_= "Number of loaded plugins: " + std::to_string(plugin_manager_.GetNumberOfPluginsLoaded());

    return true;
}

bool PluginHandling::loadStaticPlugins(std::vector<std::string> _plugins_names_arr,std::string _plugins_folder_path,  bool _log){

    plugin_factor_arr_.clear();
    plugin_manager_.ClearPluginList();

    setPluginsFolderPath(_plugins_folder_path);

    IPluginFactory* p;
    for (size_t i = 0; i < _plugins_names_arr.size(); ++i) {
        p = plugin_manager_.addPlugin(_plugins_folder_path + _plugins_names_arr.at(i));
        output_msg_ = "Plugin " + _plugins_names_arr.at(i) + " added.";
        //std::cout << output_msg_ << std::endl;
        plugin_factor_arr_.push_back(p);
    }

    if(!verifyLoadedPlugins())
        return false;

    if(_log){
        std::string log_str = "";
        getPluginsInfo(log_str);
        std::cout << log_str << std::endl;
    }

    return true;
}

bool PluginHandling::verifyLoadedPlugins(){
    for (size_t i = 0; i < plugin_factor_arr_.size(); ++i) {
        if(plugin_factor_arr_.at(i) == nullptr){
            output_msg_ = "Loaded plugin #" + std::to_string(i) +" error.";
            return false;
        }
    }
    output_msg_= "All " + std::to_string(plugin_manager_.GetNumberOfPluginsLoaded()) + " plugins are properly loaded. ";
    return true;
};

bool PluginHandling::getPluginsInfo(std::string &_plugin_info_str){

    std::stringstream ss;

    for (size_t i = 0; i < plugin_factor_arr_.size(); ++i) {
        ss << "Plugin #"<< i << ":" << "\n"
           << "- Name "<< plugin_factor_arr_.at(i)->Name() << "\n"
           << "- Version = " << plugin_factor_arr_.at(i)->Version() << "\n"
           << "- Number of classes = " << plugin_factor_arr_.at(i)->NumberOfClasses()<< "\n"
           << "- Classes exported:\n";
        for(size_t n = 0; n < plugin_factor_arr_.at(i)->NumberOfClasses(); n++)
        {
            ss << "-- "<< n <<"): " << plugin_factor_arr_.at(i)->GetClassName(n) << "\n\n";
        }
    }
    output_msg_= "Plugin information returned ";

    _plugin_info_str = ss.str();
    return true;
}

std::string PluginHandling::getOutputMsg(){
    return output_msg_;
}