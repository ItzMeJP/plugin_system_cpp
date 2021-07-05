/**\file
 * \brief
 * PluginManagement declaration
 * @version 01.07.2021
 * @author João Pedro Carvalho de Souza
 */

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

    bool getLoadedPluginList(std::vector<std::string>& _arr);

    IPluginFactory *GetPluginFactoryInfo(int _index);

    std::string getPluginFileName(int _index);

    int GetNumberOfPluginsLoaded();

    bool verifyLoadedPlugins();

    std::string getOutputMsg();

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

protected:
    bool loadDynamicPluginsFromFolder();

    void ClearPluginList();

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
