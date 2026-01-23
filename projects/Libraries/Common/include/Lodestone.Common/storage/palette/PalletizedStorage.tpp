//
// Created by DexrnZacAttack on 11/28/25 using zPc-i2.
//
#ifndef PALLETIZEDSTORAGE_TPP
#define PALLETIZEDSTORAGE_TPP

// TODO we need to document this whole file since I don't really understand the logic behind it

template<typename T>
PalletizedStorage<T>::PalletizedStorage(const int capacity) : mCapacity(capacity) {
    fill(T{});
}

template<typename T>
PalletizedStorage<T>::PalletizedStorage(const int capacity, T fillWith) : mCapacity(capacity) {
    fill(fillWith);
}

template<typename T>
void PalletizedStorage<T>::setValue(int index, T value) {
    int idx = getPaletteIndex(index);
    PaletteEntry &cur = mPalette[idx];

    if (cur.references <= 0)
        throw exception::InvalidPaletteReferenceCountException();

    --cur.references;

    for (int i = 0; i < mPalette.size(); i++) {
        if (PaletteEntry &e = mPalette[i]; e.value == value) {
            setPaletteIndex(index, i);
            ++e.references;
            return;
        }
    }

    if (cur.references == 0) {
        cur = {
            std::move(value),
            1
        };

        return;
    }

    int n = obtainPaletteEntry();
    mPalette[n] = {
        std::move(value),
        1
    };

    setPaletteIndex(index, n);
    mPaletteSize++;
}

template<typename T>
T PalletizedStorage<T>::getCopy(int index) const {
    return mPalette[getPaletteIndex(index)].value;
}

template<typename T>
const T &PalletizedStorage<T>::getValue(int index) const {
    return mPalette[getPaletteIndex(index)].value;
}

template<typename T>
size_t PalletizedStorage<T>::getNewSize() const {
    return (mCapacity * mIndexBits + 7) >> 3;
}

template<typename T>
const T & PalletizedStorage<T>::operator[](int index) const {
    return mPalette[getPaletteIndex(index)].value;
}

template<typename T>
void PalletizedStorage<T>::fill(T value)
{
    mIndices.assign(getNewSize(), 0);
    mPalette.clear();
    mPalette.resize(1);

    mPalette[0] = { value, mCapacity };

    mIndexBits = 0;
    mPaletteSize = 1;
}

template<typename T>
int PalletizedStorage<T>::getPaletteIndex(int index) const {
    // https://github.com/Pannoniae/BlockGame/blob/2e02356c73dd927a09c4299b41a13cbad972a57f/src/world/chunk/PaletteBlockData.cs#L145
    // Permission was given from Pannoniae to continue porting this code
    switch (mIndexBits) {
        case 0: return 0;
        case 1: return (mIndices[index >> 3] >> (index & 7)) & 1;
        case 2: return (mIndices[index >> 2] >> ((index & 3) << 1)) & 3;
        case 4: return (mIndices[index >> 1] >> ((index & 1) << 2)) & 15;
        case 8: return mIndices[index];
        case 16: {
            const int idx = index << 1;
            return (mIndices[idx] << 8)
                 | (mIndices[idx + 1]);
        }
        case 32: {
            const int idx = index << 2;
            return (mIndices[idx] << 24)
                 | (mIndices[idx + 1] << 16)
                 | (mIndices[idx + 2] << 8)
                 | (mIndices[idx + 3]);
        }
        default: throw exception::PaletteIndexTooLargeException();
    }
}

template<typename T>
void PalletizedStorage<T>::setPaletteIndex(int index, int value) {
    // https://github.com/Pannoniae/BlockGame/blob/2e02356c73dd927a09c4299b41a13cbad972a57f/src/world/chunk/PaletteBlockData.cs#L185
    // Permission was given from Pannoniae to continue porting this code
    switch (mIndexBits)
    {
        case 0:
            return;
        case 1:
            mIndices[index >> 3] = static_cast<unsigned char>((mIndices[index >> 3] & ~(1 << (index & 7))) |
                                                     ((value & 1) << (index & 7)));
            return;
        case 2:
            mIndices[index >> 2] = static_cast<unsigned char>((mIndices[index >> 2] & ~(3 << ((index & 3) << 1))) |
                                                              ((value & 3) << ((index & 3) << 1)));
            return;
        case 4:
            mIndices[index >> 1] = static_cast<unsigned char>((mIndices[index >> 1] & ~(15 << ((index & 1) << 2))) |
                                                              ((value & 15) << ((index & 1) << 2)));
            return;
        case 8:
            mIndices[index] = static_cast<unsigned char>(value);
            return;
        case 16: {
            const int idx = index << 1;
            mIndices[idx    ] = static_cast<uint8_t>(value & 0xFF);
            mIndices[idx + 1] = static_cast<uint8_t>((value >> 8) & 0xFF);
            return;
        }
        case 32: {
            const int idx = index << 2;
            mIndices[idx    ] = static_cast<uint8_t>(value & 0xFF);
            mIndices[idx + 1] = static_cast<uint8_t>((value >> 8) & 0xFF);
            mIndices[idx + 2] = static_cast<uint8_t>((value >> 16) & 0xFF);
            mIndices[idx + 3] = static_cast<uint8_t>((value >> 24) & 0xFF);

            return;
        }
        default:
            throw exception::PaletteIndexTooLargeException();
    }
}

template<typename T>
int PalletizedStorage<T>::obtainPaletteEntry() {
    while (true) {
        for (int i = 0; i < mPalette.size(); i++)
            if (mPalette[i].references == 0) return i;

        this->grow();
    }
}

template<typename T>
void PalletizedStorage<T>::grow() {
    if (mIndexBits >= 32)
        throw exception::PaletteIndexTooLargeException();

    std::vector<int> indices(mCapacity);
    for (int i = 0; i < mCapacity; ++i)
        indices[i] = getPaletteIndex(i);

    mIndexBits = (mIndexBits == 0) ? 1 : (mIndexBits << 1); // it implodes if I don't do this

    std::vector<PaletteEntry> n(1 << mIndexBits);
    for (int i = 0; i < mPaletteSize; ++i)
        n[i] = std::move(mPalette[i]);

    mPalette = std::move(n);
    mIndices.assign(getNewSize(), 0);

    for (int i = 0; i < mCapacity; ++i)
        setPaletteIndex(i, indices[i]);
}
#endif // PALLETIZEDSTORAGE_TPP
