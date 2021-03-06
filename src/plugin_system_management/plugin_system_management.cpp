/**\file
 * \brief
 * PluginManagement class definition
 * @version 01.07.2021
 * @author João Pedro Carvalho de Souza (based on https://github.com/caiorss/sample-cpp-plugin)
 */

#include "plugin_system_management.h"

/// <summary>
/// Contructor
/// </summary>
PluginSystemManagement::PluginSystemManagement() {
    number_of_plugins_loaded_ = 0;
    plugin_file_name_arr_.clear();
    plugin_factory_info_arr_.clear();
    plugin_arr_.clear();
};

/// <summary>
/// Destructor
/// </summary>
PluginSystemManagement::~PluginSystemManagement() {
    this->ClearPluginList();
};

/// <summary>
/// Set plugins folder path
/// </summary>
/// <param name="_path"> Plugin path.</param>
void PluginSystemManagement::setPluginsFolderPath(std::string _path) {
    plugins_folder_path_ = _path;
}

/// <summary>
/// Get plugins folder path
/// </summary>
/// <returns> Plugin path.</returns>
std::string PluginSystemManagement::getPluginsFolderPath() {
    return plugins_folder_path_;
}

/// <summary>
/// Load the plugins in dynamic library format
/// </summary>
/// <param name="_plugins_folder_path"> Plugin folder path.</param>
/// <param name="_log"> true to print information log regarding the loaded plugins.</param>
/// <returns> true if success, false if there are any plugin loading error or none plugin were found.</returns>
bool PluginSystemManagement::loadDynamicPlugins(std::string _plugins_folder_path, bool _log) {

    setPluginsFolderPath(_plugins_folder_path);

    if (!loadDynamicPluginsFromFolder()
        || !verifyLoadedPlugins())
        return false;

    if (_log) {
        std::string log_str = "";
        getPluginsInfo(log_str);
        DEBUG_MSG (  "Loaded plugins information:\n\n" << log_str );
    }

    return true;

}

/// <summary>
/// Load the plugins from the defined folder
/// </summary>
/// <returns> true if success, false if there are any plugin loading error or none plugin were found.</returns>
bool PluginSystemManagement::loadDynamicPluginsFromFolder() {

    if (!addPlugins(plugins_folder_path_))
        return false;

    if (GetNumberOfPluginsLoaded() == 0) {
        output_msg_ = "None plugins identified in dir: " + plugins_folder_path_;
        return false;
    }

    output_msg_ = "Number of loaded plugins: " + std::to_string(GetNumberOfPluginsLoaded());

    return true;
}

/// <summary>
/// Verify if all Factory Information (see interface.h) is properly set
/// </summary>
/// <returns> true if success, false if the factory information definition is missed .</returns>
bool PluginSystemManagement::verifyLoadedPlugins() {

    for (size_t i = 0; i < plugin_factory_info_arr_.size(); ++i) {

        if (plugin_factory_info_arr_.at(i) == nullptr) {
            output_msg_ = "Loaded plugin \"" + getPluginFileName(i) + "\" factory information definition missed.";
            return false;
        }
    }
    output_msg_ = "All " + std::to_string(GetNumberOfPluginsLoaded()) + " plugins are properly loaded. ";
    return true;
};

/// <summary>
/// Get a structured string with all plugins factory information
/// </summary>
/// <param name="_plugin_info_str"> The structured output string.</param>
void PluginSystemManagement::getPluginsInfo(std::string &_plugin_info_str) {

    std::stringstream ss;

    for (size_t i = 0; i < plugin_factory_info_arr_.size(); ++i) {
        ss << "Plugin #" << i << ":" << "\n"
           << "- Name " << plugin_factory_info_arr_.at(i)->Name() << "\n"
           << "- Version = " << plugin_factory_info_arr_.at(i)->Version() << "\n"
           << "- Number of classes = " << plugin_factory_info_arr_.at(i)->NumberOfClasses() << "\n"
           << "- Classes exported:\n";
        for (size_t n = 0; n < plugin_factory_info_arr_.at(i)->NumberOfClasses(); n++) {
            ss << "-- " << n << "): " << plugin_factory_info_arr_.at(i)->GetClassName(n) << "\n\n";
        }
    }
    output_msg_ = "Plugin information returned ";

    _plugin_info_str = ss.str();
}

/// <summary>
/// Get the loaded plugin list names.
/// </summary>
/// <param name="_arr"> The plugin list name.</param>
/// <returns> false if there is none plugin loaded </returns>
bool PluginSystemManagement::getLoadedPluginList(std::vector<std::string> &_arr) {

    _arr.clear();

    if (GetNumberOfPluginsLoaded() == 0) {
        output_msg_ = "Cannot retrieve a plugin list name since none plugin were identified.";
        return false;
    }

    for (size_t i = 0; i < GetNumberOfPluginsLoaded(); ++i) {
        _arr.push_back(plugin_factory_info_arr_.at(i)->Name());
    }

    return true;

}

/// <summary>
/// Get current API output message
/// </summary>
/// <returns> output message. </returns>
std::string PluginSystemManagement::getPluginManagementOutputMsg() {
    return output_msg_;
}

/// <summary>
/// Get the dynamic library extension
/// </summary>
/// <returns> the extension string. </returns>
std::string PluginSystemManagement::GetExtension() const {
    std::string ext;
#if defined (_WIN32)
    ext = ".dll"; // Windows
#elif defined(__unix__) && !defined(__apple__)
    ext = ".so";  // Linux, BDS, Solaris and so on.
#elif defined(__apple__)
    ext = ".dylib"; // MacOSX
#else
#error "Not implemented for this platform"
#endif
    return ext;
}

/// <summary>
/// Create the plugins instance and stack all in array. Also stack the library file name and plugin factory information
/// </summary>
/// <param name="_plugins_folder_path"> The plugins folder path.</param>
/// <returns> true if success, false if:
///  - the plugin path is not correctly defined;
///  - the plugin name is not correct
///  - the library does not correspond to a supported plugin. Check /templates folder for creating plugins guideline.</returns>
bool PluginSystemManagement::addPlugins(const std::string &_plugins_folder_path) {

    ClearPluginList();

    std::string sub_s;
    std::filesystem::path pluginPath;
    std::filesystem::directory_iterator pluginDirectory(_plugins_folder_path);

    for (auto &pluginFile : pluginDirectory) {

        //std::cout <<" PLUGIN: pluginFile.path() " <<  pluginFile.path().string() << std::endl;

        //std::cout <<" loading plugin number " <<  number_of_plugins_loaded_ << std::endl;

        pluginPath = pluginFile.path();
        sub_s = pluginPath.filename().string().substr(0, pluginPath.filename().string().find(GetExtension()));

        //std::cout <<" PLUGIN: pluginPath.filename() " <<   pluginPath.filename().string() << std::endl;
        //std::cout <<" PLUGIN: sub_s " <<   sub_s << std::endl;

        char first_letter = pluginFile.path().string().at(0);

        std::string append = first_letter != '/'?"/":"";
        //std::cout <<" PLUGIN: cmd to exec plugin " <<  append + pluginFile.path().string() << std::endl;

        plugin_arr_.emplace_back(append + pluginFile.path().string());
        plugin_file_name_arr_.push_back(sub_s);

        if (!plugin_arr_.at(number_of_plugins_loaded_).checkSharedLibHandle()) {
            output_msg_ = "Plugin \"" + plugin_file_name_arr_.at(number_of_plugins_loaded_) +
                    "\" loading error.\n" + dlerror() ;
            return false;
        }
        if (!plugin_arr_.at(number_of_plugins_loaded_).checkFactoryHandle()) {
            output_msg_ = "Plugin loading error. Plugin \"" + plugin_file_name_arr_.at(number_of_plugins_loaded_) +
                          "\" does not follow the plugin design convention.";
            return false;
        }

        plugin_factory_info_arr_.push_back(plugin_arr_.at(number_of_plugins_loaded_).GetInfo());
        number_of_plugins_loaded_++;
    }

    return true;
}

/// <summary>
/// Get the plugin file name associated with the index in the stack pile.
/// </summary>
/// <param name="_index"> The stacked index to access the plugin .</param>
/// <returns> the file name. The file name will be null if the index is out of range </returns>
std::string PluginSystemManagement::getPluginFileName(int _index) {
    if (_index > plugin_file_name_arr_.size()) {
        output_msg_ = "Plugin file name out of range.";
        return "NULL -> Index out of range";
    }
    return plugin_file_name_arr_.at(_index);
}

/// <summary>
/// Get the index associated with the plugin file name in the stack pile.
/// </summary>
/// <param name="_plugin_filename"> The file name.</param>
/// <returns> The stacked index to access the plugin. The index will be null if the index is out of range </returns>
int PluginSystemManagement::getIndexOfPlugin(std::string _plugin_filename) {
    std::vector<std::string>::iterator it;
    it = std::find(plugin_file_name_arr_.begin(), plugin_file_name_arr_.end(), _plugin_filename);
    if (it != plugin_file_name_arr_.end())
    {
        return std::distance( plugin_file_name_arr_.begin(), it );
    }
    else
        return -1;
}

/// <summary>
/// Get the number of successfully plugins loaded.
/// </summary>
/// <returns> the number of successfully plugins loaded. </returns>
int PluginSystemManagement::GetNumberOfPluginsLoaded() {
    return number_of_plugins_loaded_;
}

/// <summary>
/// Clear the plugin stacks
/// </summary>
void PluginSystemManagement::ClearPluginList() {

    if(plugin_arr_.size()==0)
        return;

    for (size_t i = 0; i < plugin_arr_.size(); ++i) {
        DEBUG_MSG("Unloading/destructing plugin: " << plugin_file_name_arr_.at(i));
        plugin_arr_.at(i).Unload();
    }
    number_of_plugins_loaded_ = 0;
    plugin_file_name_arr_.clear();
    plugin_factory_info_arr_.clear();
    plugin_arr_.clear();
}

/// <summary>
/// Get a specific plugin factory information
/// </summary>
/// <param name="_index"> The stacked index to access the plugin .</param>
/// <returns> The plugin factory information. The pointer is null if the index is out of range </returns>
IPluginFactory *PluginSystemManagement::GetPluginFactoryInfo(int _index) {
    if (_index > plugin_arr_.size()){
        output_msg_ = "Factory info _index out of range";
        return nullptr;
    }
    return plugin_arr_.at(_index).GetInfo();
}

/// <summary>
/// Create a instance of a specific class inside a specific plugin.
/// </summary>
/// <param name="_plugin_index"> The stacked index to access the plugin.</param>
/// <param name="_class_index"> The stacked index to access the class inside the plugin.</param>
/// <returns> the initialized object. The object will be null if any of the indexes were out of range. </returns>
void *PluginSystemManagement::CreateInstance(int _plugin_index, int _class_index) {
    if (_plugin_index > plugin_arr_.size()){
        output_msg_ = "_plugin_index out of range";
        return nullptr;
    }
    if (_class_index > plugin_arr_.at(_plugin_index).GetInfo()->NumberOfClasses()){
        output_msg_ = "_class_index out of range";
        return nullptr;
    }

    return plugin_arr_.at(_plugin_index).CreateInstance(
            plugin_arr_.at(_plugin_index).GetInfo()->GetClassName(_class_index));
}


