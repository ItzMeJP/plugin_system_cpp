/**\file
 * \brief
 * Factory class definition
 * @version 01.07.2021
 * @author João Pedro Carvalho de Souza
 */

#include "plugin_system_management/factory.h"

PluginFactory::PluginFactory(const char* name, const char* version):m_name(name),m_version(version){}

const char* PluginFactory::Name() const
{
    return m_name.data();
}

const char* PluginFactory::Version() const
{
    return m_version.data();
}

size_t PluginFactory::NumberOfClasses() const
{
    return m_ctordb.size();
}

const char* PluginFactory::GetClassName(size_t index) const
{
    return m_ctordb[index].first.data();
}

void* PluginFactory::Factory(const char* className) const
{
    auto it = std::find_if(m_ctordb.begin(), m_ctordb.end(),
                           [&className](const auto& p){
                               return p.first == className;
                           });
    if(it == m_ctordb.end())
        return nullptr;
    return it->second();
}

void* PluginFactory::Factory(int _class_index) const
{
    if(_class_index<m_ctordb.size())
        return nullptr;
    return m_ctordb.at(_class_index).second();
}
