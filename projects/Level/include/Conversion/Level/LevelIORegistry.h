//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#ifndef LODESTONE_CHUNKIOFACTORY_H
#define LODESTONE_CHUNKIOFACTORY_H
#include <string>

#include "LevelIO.h"

namespace lodestone::level::conversion::level {
    /** Creates chunks based on registered chunk IO classes */
    class LODESTONE_API LevelIORegistry {
    protected:
        LevelIORegistry() = default;
    public:
        static LevelIORegistry *sInstance;

        void registerLevelIO(const std::string &id, const LevelIO* io);

        const LevelIO *getLevelIO(const std::string &id) const;
    private:
        std::unordered_map<std::string, const LevelIO*> mRegisteredLevelIOs = {};
    };
}

#endif //LODESTONE_CHUNKIOFACTORY_H
