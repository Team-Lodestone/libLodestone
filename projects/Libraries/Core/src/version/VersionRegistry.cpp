//
// Created by zero on 11/19/26.
//


#include "Lodestone.Core/version/VersionRegistry.h"

void lodestone::core::version::VersionRegistry::registerEdition(
    std::string edition,
    std::vector<std::string> versions
) {
    m_editions[std::move(edition)] = {
        versions.begin(),
        versions.end()
    };
}

void lodestone::core::version::VersionRegistry::registerVersion(
    const std::string& edition,
    std::string version
) {
    const auto it = m_editions.find(edition);

    if (it == m_editions.end()) {
        throw std::runtime_error(
            "Unknown edition: " + edition
        );
    }

    it->second.insert(std::move(version));
}

bool lodestone::core::version::VersionRegistry::isValid(const common::registry::Identifier& identifier) const {
    const auto it = m_editions.find(identifier.getNamespace());

    return it != m_editions.end() &&
           it->second.contains(identifier.getPath());
}

std::unordered_map<std::string, std::unordered_set<std::string>> lodestone::core::version::VersionRegistry::
getEditions() {
    return this->m_editions;
}
