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
#include <cstring>
#include <array>
#include <execution>

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

        size_t getIndicesSize() const noexcept;

        // allows for getting the object reference but not write to it (since writing will modify ALL instances, because indexes will point to that one object)
        const T &operator[](int index) const;

        constexpr std::string toString() const override {
            return std::string("PalletizedStorage{")
            + "capacity=" + std::to_string(m_capacity)
            + ", paletteSize=" + std::to_string(m_paletteSize)
            + ", indiceCount=" + std::to_string(m_indices.size());
        };
    protected:
        int getPaletteIndex(int index) const;
        void setPaletteIndex(int index, int value);

        int obtainPaletteEntry();
        void resize();
    private:
        // todo do we want array pool?
        std::vector<uint8_t> m_indices;
        std::vector<PaletteEntry> m_palette;

        const int m_capacity;
        int m_paletteSize = 0;
        int m_indexBits = 1;
    };

#include "Lodestone.Common/storage/palette/PalletizedStorage.tpp"
}

#endif // LODESTONE_PALLETIZEDSTORAGE_H
