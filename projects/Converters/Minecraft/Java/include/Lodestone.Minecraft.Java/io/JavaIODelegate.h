//
// Created by zero on 11/27/26.
//

#ifndef LODESTONE_JAVA_IO_DELEGATE_H
#define LODESTONE_JAVA_IO_DELEGATE_H

#include <Lodestone.Conversion/io/interfaces/IDelegateIO.h>
#include <Lodestone.Conversion/io/options/fs/FilesystemPathOptions.h>
#include <Lodestone.Conversion/io/options/versioned/VersionedOptions.h>
#include <Lodestone.Common/registry/Identifier.h>

#include "Lodestone.Minecraft.Java/Identifiers.h"

namespace lodestone::minecraft::java::io {
    class JavaIODelegate : public conversion::io::interfaces::IDelegateIO {
    public:
        // ReSharper disable once CppRedundantQualifier
        static const lodestone::common::registry::Identifier *getIdentifier() {
            return &identifiers::JAVA_IO_DELEGATE;
        }

        // TODO: WTF do I do with this
        pro::proxy<ReallyAny> baseRead(void *options) const override {
            return nullptr;
        }

        void baseWrite(void *obj, void *options) const override {
        }

        bool canReadWorld(const std::filesystem::path &path) override;

        bool canReadLevel(const std::filesystem::path &path) override;

        std::unique_ptr<level::world::World> readWorld(
            const conversion::io::options::fs::FilesystemPathOptions &filesystem,
            const conversion::io::options::versioned::VersionedOptions &version
        ) const override;

        void writeWorld(const conversion::io::options::fs::FilesystemPathOptions &filesystem,
                        const conversion::io::options::versioned::
                        VersionedOptions &version, const std::unique_ptr<level::world::World> &world) const override;
    };
}

#endif //LODESTONE_JAVA_IO_DELEGATE_H
