//
// Created by zero on 11/19/26.
//

#include "Lodestone.Core/version/VersionRegistry.h"

#include <ranges>

void lodestone::core::version::VersionRegistry::registerEdition(
    const std::string &edition,
    std::vector<std::string> versions
) {
    for (auto &version: versions) {
        registerVersion(edition, std::move(version));
    }
}

void lodestone::core::version::VersionRegistry::registerVersion(
    const std::string &edition,
    std::string version
) {
    auto &versions = m_editions[edition];

    if (versions.contains(version))
        return;

    versions.insert(version);

    const int id = m_nextId++;

    const std::string key = edition + ":" + version;

    m_versionIds.emplace(key, id);
    m_idToVersion.emplace(
        id,
        std::make_pair(edition, version)
    );
}

bool lodestone::core::version::VersionRegistry::isValid(const common::registry::Identifier &identifier) const {
    return this->isValid(identifier.getNamespace(), identifier.getPath());
}

bool lodestone::core::version::VersionRegistry::isValid(const std::string& edition, const std::string& version) const {
    const auto it = m_editions.find(edition);

    return it != m_editions.end() &&
           it->second.contains(version);
}

std::unordered_set<std::string>
lodestone::core::version::VersionRegistry::getVersions(const std::string &edition) const {
    const auto it = m_editions.find(edition);

    if (it == m_editions.end())
        return {};

    return it->second;
}

std::unordered_set<lodestone::common::registry::Identifier>
lodestone::core::version::VersionRegistry::getAllVersions() const {
    std::unordered_set<common::registry::Identifier> allVersions;

    for (const auto &[edition, versions]: this->m_editions) {
        for (const auto &version: versions) {
            allVersions.emplace(edition.data(), version.data());
        }
    }

    return allVersions;
}

std::optional<int> lodestone::core::version::VersionRegistry::getVersionId(
    const std::string &edition,
    const std::string &version
) const {
    const auto it = m_versionIds.find(edition + ":" + version);

    if (it == m_versionIds.end())
        return std::nullopt;

    return it->second;
}

std::optional<int> lodestone::core::version::VersionRegistry::getVersionId(
    const lodestone::common::registry::Identifier &identifier
) const {
    const auto it = m_versionIds.find(
        std::string(identifier.getNamespace()) + ":" + identifier.getPath()
    );

    if (it == m_versionIds.end())
        return std::nullopt;

    return it->second;
}

std::optional<std::string> lodestone::core::version::VersionRegistry::getVersionName(const int id) const {
    const auto it = m_idToVersion.find(id);

    if (it == m_idToVersion.end())
        return std::nullopt;

    return it->second.second;
}

std::optional<std::string> lodestone::core::version::VersionRegistry::getEdition(const int id) const {
    const auto it = m_idToVersion.find(id);

    if (it == m_idToVersion.end())
        return std::nullopt;

    return it->second.first;
}

std::unordered_map<std::string, std::unordered_set<std::string> >
lodestone::core::version::VersionRegistry::getEditions() const {
    return m_editions;
}
