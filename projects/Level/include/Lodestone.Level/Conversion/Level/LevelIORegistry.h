//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#ifndef LODESTONE_LEVELIOFACTORY_H
#define LODESTONE_LEVELIOFACTORY_H
#include <string>

#include "Lodestone.Level/Conversion/Level/LevelIO.h"

namespace lodestone::level::conversion::level {
    /** Creates chunks based on registered chunk IO classes */
    class LODESTONE_API LevelIORegistry {
    protected:
        LevelIORegistry() = default;
    public:
        static LevelIORegistry sInstance;

        void registerLevelIO(const std::string &id, std::unique_ptr<const LevelIO> io);

        const LevelIO *getLevelIO(const std::string &id) const;
    private:
        std::unordered_map<std::string, std::unique_ptr<const LevelIO>> mRegisteredLevelIOs;
    };
}

#endif //LODESTONE_LEVELIOFACTORY_H
