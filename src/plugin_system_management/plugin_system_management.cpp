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
PluginSystemManagement::PluginSystemManagement() {};

/// <summary>
/// Destructor
/// </summary>
PluginSystemManagement::~PluginSystemManagement() {};

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
        std::cout << log_str << std::endl;
    }

    return true;

}

/// <summary>
/// Load the plugins from the defined folder
/// </summary>
/// <returns> true if success, false if there are any plugin loading error or none plugin were found.</returns>
bool PluginSystemManagement::loadDynamicPluginsFromFolder() {

    if(!addPlugins(plugins_folder_path_))
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
/// Get current API output message
/// </summary>
/// <returns> output message. </returns>
std::string PluginSystemManagement::getOutputMsg() {
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

        pluginPath = pluginFile.path();
        sub_s = pluginPath.filename().string().substr(0, pluginPath.filename().string().find(GetExtension()));

        plugin_arr_.push_back(Plugin("./" + pluginPath.filename().string()));
        plugin_file_name_arr_.push_back(sub_s);


        if (!plugin_arr_.at(number_of_plugins_loaded_).checkSharedLibHandle()) {
            output_msg_ = "Plugin loading error. Check the plugins file and/or the folder path definitions.";
            return false;
        }
        if (!plugin_arr_.at(number_of_plugins_loaded_).checkFactoryHandle()){
            output_msg_ = "Plugin loading error. Plugin \"" + plugin_file_name_arr_.at(number_of_plugins_loaded_) + "\" does not follow the plugin design convention.";
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
std::string PluginSystemManagement::getPluginFileName(int _index){
    if (_index > plugin_file_name_arr_.size())
        return "NULL -> Index out of range";
    return plugin_file_name_arr_.at(_index);
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
    if (_index > plugin_arr_.size())
        return nullptr;
    return plugin_arr_.at(_index).GetInfo();
}

/// <summary>
/// Create a instance of a specific class inside a specific plugin.
/// </summary>
/// <param name="_plugin_index"> The stacked index to access the plugin.</param>
/// <param name="_class_index"> The stacked index to access the class inside the plugin.</param>
/// <returns> the initialized object. The object will be null if any of the indexes were out of range. </returns>
void *PluginSystemManagement::CreateInstance(int _plugin_index, int _class_index) {
    if (_plugin_index > plugin_arr_.size())
        return nullptr;
    if (_class_index > plugin_arr_.at(_plugin_index).GetInfo()->NumberOfClasses())
        return nullptr;

    return plugin_arr_.at(_plugin_index).CreateInstance(plugin_arr_.at(_plugin_index).GetInfo()->GetClassName(_class_index));
}
