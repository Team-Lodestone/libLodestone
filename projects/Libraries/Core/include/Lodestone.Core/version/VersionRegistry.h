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
        void registerEdition(
            const std::string &edition,
            std::vector<std::string> versions
        );

        void registerVersion(
            const std::string &edition,
            std::string version
        );

        bool isValid(
            const common::registry::Identifier &identifier
        ) const;

        bool isValid(const std::string &edition, const std::string &version) const;

        std::optional<int> getVersionId(
            const common::registry::Identifier &identifier
        ) const;

        std::optional<int> getVersionId(
            const std::string &edition,
            const std::string &version
        ) const;

        std::optional<std::string> getVersionName(
            int id
        ) const;

        std::optional<std::string> getEdition(
            int id
        ) const;

        std::unordered_map<std::string, std::unordered_set<std::string> >
        getEditions() const;

        std::unordered_set<std::string>
        getVersions(const std::string &edition) const;

        std::unordered_set<common::registry::Identifier>
        getAllVersions() const;

    private:
        int m_nextId = 0;

        std::unordered_map<std::string, std::unordered_set<std::string> >
        m_editions;

        std::unordered_map<std::string, int> m_versionIds;

        std::unordered_map<int, std::pair<std::string, std::string> >
        m_idToVersion;
    };
}
#endif //LODESTONE_CORE_VERSION_REGISTRY_H
