/**\file
 * \brief
 * PluginManagement declaration
 * @version 01.07.2021
 * @author João Pedro Carvalho de Souza
 */

#define MSG_PREFIX "<PluginSystemManagement> "
#ifndef NDEBUG
#define DEBUG_MSG(str) do { std::cout << "\033[;33m" << MSG_PREFIX << str << "\033[0m"<< std::endl; } while( false )
#else
#define DEBUG_MSG(str) do { } while ( false )
#endif

#include <filesystem>
#include "plugin.h"

#ifndef PLUGIN_SYSTEM_MANAGEMENT_H
#define PLUGIN_SYSTEM_MANAGEMENT_H

class PluginSystemManagement {

public:
    PluginSystemManagement();

    ~PluginSystemManagement();

    void setPluginsFolderPath(std::string _path);

    std::string getPluginsFolderPath();

    bool loadDynamicPlugins(std::string _plugins_folder_path, bool _log);

    void getPluginsInfo(std::string &_plugin_info_str);

    bool getLoadedPluginList(std::vector<std::string> &_arr);

    IPluginFactory *GetPluginFactoryInfo(int _index);

    std::string getPluginFileName(int _index);
    int getIndexOfPlugin(std::string _plugin_filename);

    int GetNumberOfPluginsLoaded();

    bool verifyLoadedPlugins();

    std::string getPluginManagementOutputMsg();

/// <summary>
/// Map a plugin name to a index in the loaded plugin stack
/// </summary>
/// <param name="_plugin_name"> The plugin name to be found.</param>
/// <param name="_index"> The mapped index. </param>
/// <returns> true if success, otherwise false if the stack has size zero or if the plugin is not into stack.</returns>
    bool getPluginIndex(std::string _plugin_name, int &_index) {

        if (GetNumberOfPluginsLoaded() == 0) {
            output_msg_ = "Cannot find plugin index since none plugin was loaded.";
            return false;
        }

        for (size_t i = 0; i < GetNumberOfPluginsLoaded(); ++i) {
            if (_plugin_name == plugin_factory_info_arr_.at(i)->Name()) {
                _index = i;
                return true;
            }
        }

        output_msg_ = "The plugin  \"" + _plugin_name + "\" was not found in loaded plugin list.";
        return false;

    }

/// <summary>
/// Map a class name to a index in the loaded plugin's stack class.
/// </summary>
/// <param name="_plugin_index"> The plugin index where the class should be searched.</param>
/// <param name="_index"> The mapped index. </param>
/// <returns> true if success, otherwise false if the stack has size zero or if the plugin is not into stack.</returns>
    bool getClassIndex(int _plugin_index, std::string _class_name, int &_class_index) {

        std::string plugin_name = plugin_factory_info_arr_.at(_plugin_index)->Name();
        if (GetNumberOfPluginsLoaded() == 0) {
            output_msg_ =
                    "Cannot find class index since the plugin \"" + plugin_name + "\" does not have a class defined";
            return false;
        }

        for (size_t i = 0; i < plugin_factory_info_arr_.at(_plugin_index)->NumberOfClasses(); ++i) {
            if (_class_name == plugin_factory_info_arr_.at(_plugin_index)->GetClassName(i)) {
                _class_index = i;
                return true;
            }
        }

        output_msg_ = "The class  \"" + _class_name + "\" was not found in the loaded plugin \"" + plugin_name + "\"";
        return false;
    }

    /** @brief Instantiate a class exported by some loaded plugin.
*  @tparam T           Interface (interface class) implemented by the loaded class.
*  @param  _plugin_index  The stacked index to access the plugin that exports the class.
*  @param  _class_index   The stacked index to access the class inside the plugin.
*  @return             Instance of exported class casted to some interface T.
* */
    template<typename T>
    std::shared_ptr<T>
    CreateInstanceAs(int _plugin_index, int _class_index) {
        void *pObj = CreateInstance(std::move(_plugin_index), std::move(_class_index));
        return std::shared_ptr<T>(reinterpret_cast<T *>(pObj));
    }

    /** @brief Instantiate a class exported by some loaded plugin.
*  @tparam T           Interface (interface class) implemented by the loaded class.
*  @param  _plugin_name  The plugin name to access the plugin that exports the class.
*  @param  _class_name   The class name to access the class inside the plugin.
*  @return             Instance of exported class casted to some interface T.
* */
    template<typename T>
    std::shared_ptr<T>
    CreateInstanceAs(std::string _plugin_name, std::string _class_name) {

        int plugin_index, class_index;
        if (!getPluginIndex(_plugin_name, plugin_index)
            || !getClassIndex(plugin_index, _class_name, class_index))
            return nullptr;

        void *pObj = CreateInstance(std::move(plugin_index), std::move(class_index));
        return std::shared_ptr<T>(reinterpret_cast<T *>(pObj));
    }

    void ClearPluginList();

protected:
    bool loadDynamicPluginsFromFolder();

    std::string GetExtension() const;

    bool addPlugins(const std::string &_plugins_folder_path);

    void *CreateInstance(int _plugin_index, int _class_index);

private:
    std::vector<Plugin> plugin_arr_;
    std::vector<std::string> plugin_file_name_arr_;
    std::vector<IPluginFactory *> plugin_factory_info_arr_;

    std::string output_msg_ = "NULL",
            plugins_folder_path_ = "NULL";

    int number_of_plugins_loaded_ = 0;

};

#endif //PLUGIN_SYSTEM_MANAGEMENT_H
