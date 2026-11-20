//
// Created by zero on 11/19/26.
//

#ifndef LODESTONE_CORE_VERSION_REGISTRY_H
#define LODESTONE_CORE_VERSION_REGISTRY_H

#include <string>
#include <unordered_set>
#include <Lodestone.Common/registry/Identifier.h>

namespace lodestone::core::version {
    class VersionRegistry {
    public:
        void registerEdition(std::string edition, std::vector<std::string> versions);
        void registerVersion(const std::string& edition, std::string version);
        bool isValid(const common::registry::Identifier &identifier) const;

        std::unordered_map<std::string, std::unordered_set<std::string>> getEditions();
    private:
        std::unordered_map<std::string, std::unordered_set<std::string>> m_editions;
    };
}

#endif //LODESTONE_CORE_VERSION_REGISTRY_H
