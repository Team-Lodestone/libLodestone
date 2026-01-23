//
// Created by DexrnZacAttack on 11/27/25 using zPc-i2.
//
#ifndef LODESTONE_PALLETIZEDSTORAGE_H
#define LODESTONE_PALLETIZEDSTORAGE_H

#include <cstdint>
#include <vector>
#include <stdexcept>

#include <algorithm>
#include <vector>
#include "Lodestone.Common/exception/PaletteIndexTooLargeException.h"
#include "Lodestone.Common/exception/InvalidPaletteReferenceCountException.h"
#include "Lodestone.Common/string/StringSerializable.h"

namespace lodestone::common::storage::palette {
    // thanks danil for allowing us to port your code
    // modified slightly to allow for any arbitrary object to be stored
    // also based off of https://www.longor.net/articles/voxel-palette-compression-reddit
    template <typename T>
    class PalletizedStorage : public string::StringSerializable {
    public:
        struct PaletteEntry {
            T value;
            int references;
        };

        explicit PalletizedStorage(int capacity);
        explicit PalletizedStorage(int capacity, T fillWith);

        void setValue(int index, T value);
        T getCopy(int index) const;

        void fill(T value);

        const T &getValue(int index) const;

        size_t getNewSize() const;

        // allows for getting the object reference but not write to it (since writing will modify ALL instances, because indexes will point to that one object)
        const T &operator[](int index) const;

        constexpr std::string toString() const override {
            return std::string("PalletizedStorage{")
            + "capacity=" + std::to_string(mCapacity)
            + ", paletteSize=" + std::to_string(mPaletteSize)
            + ", indiceCount=" + std::to_string(mIndices.size());
        };
    protected:
        int getPaletteIndex(int index) const;
        void setPaletteIndex(int index, int value);

        int obtainPaletteEntry();
        void grow();
    private:
        // todo do we want array pool?
        std::vector<uint8_t> mIndices;
        std::vector<PaletteEntry> mPalette;

        const int mCapacity;
        int mPaletteSize = 0;
        int mIndexBits = 1;
    };

#include "Lodestone.Common/storage/palette/PalletizedStorage.tpp"
}

#endif // LODESTONE_PALLETIZEDSTORAGE_H
