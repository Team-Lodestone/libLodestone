//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#ifndef LODESTONE_CLASSICBLOCKIO_H
#define LODESTONE_CLASSICBLOCKIO_H
#include <Lodestone.Level/Conversion/Block/BlockIo.h>

namespace lodestone::java::classic {
    class ClassicBlockIO : public level::conversion::block::BlockIO<uint8_t> {
        protected:
            ClassicBlockIO();
        public:
            static ClassicBlockIO *sInstance;

            std::unordered_map<unsigned char, std::monostate> &getDefaultDataMap() override;

            level::block::state::BlockState readBlock(uint8_t *data) override {
                return convertBlockToInternal(*data, std::monostate{});
            };

            void writeBlock(level::block::state::BlockState *b, uint8_t *arr) override;

            std::unordered_map<std::string, Blk> & getFromInternalConversionMap() override;

            std::unordered_map<std::pair<unsigned char, std::monostate>, std::string, PairHash> &
            getToInternalConversionMap() override;

        private:
            std::unordered_map<std::pair<unsigned char, std::monostate>, std::string, PairHash> mToInternalConversionMap = {};
            std::unordered_map<std::string, Blk> mFromInternalConversionMap = {};
            std::unordered_map<uint8_t, std::monostate> mDefaultDataMap = {};
    };
}

#endif //LODESTONE_CLASSICBLOCKIO_H
