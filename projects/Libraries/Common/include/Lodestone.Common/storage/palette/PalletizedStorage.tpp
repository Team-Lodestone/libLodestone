//
// Created by DexrnZacAttack on 11/28/25 using zPc-i2.
//
#ifndef PALLETIZEDSTORAGE_TPP
#define PALLETIZEDSTORAGE_TPP

// TODO we need to document this whole file since I don't really understand the logic behind it

template<typename T>
PalletizedStorage<T>::PalletizedStorage(const int capacity) : m_capacity(capacity) {
    fill(T{});
}

template<typename T>
PalletizedStorage<T>::PalletizedStorage(const int capacity, T fillWith) : m_capacity(capacity) {
    fill(fillWith);
}

template<typename T>
void PalletizedStorage<T>::setValue(const int index, T value) {
    int idx = getPaletteIndex(index);
    PaletteEntry &cur = m_palette[idx];

    if (cur.references <= 0)
        throw exception::InvalidPaletteReferenceCountException();

    // we are overwriting the value at the index, therefore the object already present at this index is no longer referenced
    --cur.references;

    // is it already in the palette
    for (int i = 0; i < m_palette.size(); i++) {
        if (PaletteEntry &e = m_palette[i]; e.value == value) {
            setPaletteIndex(index, i);
            ++e.references;
            return;
        }
    }

    // can we overwrite the current entry
    if (cur.references == 0) {
        cur = {
            std::move(value),
            1
        };

        return;
    }

    // otherwise we need to get an entry and emplace
    int n = obtainPaletteEntry();
    m_palette[n] = {
        std::move(value),
        1
    };

    setPaletteIndex(index, n);
    m_paletteSize++;
}

template<typename T>
T PalletizedStorage<T>::getCopy(const int index) const {
    return m_palette[getPaletteIndex(index)].value;
}

template<typename T>
const T &PalletizedStorage<T>::getValue(const int index) const {
    return m_palette[getPaletteIndex(index)].value;
}

template<typename T>
size_t PalletizedStorage<T>::getIndicesSize() const noexcept {
    return (m_capacity * m_indexBits + 7) >> 3;
}

template<typename T>
const T & PalletizedStorage<T>::operator[](const int index) const {
    return m_palette[getPaletteIndex(index)].value;
}

template<typename T>
void PalletizedStorage<T>::fill(T value)
{
    m_indices.assign(getIndicesSize(), 0);
    m_palette.clear();
    m_palette.resize(1);

    m_palette[0] = { value, m_capacity };

    m_indexBits = 0;
    m_paletteSize = 1;
}

template<typename T>
int PalletizedStorage<T>::getPaletteIndex(const int index) const {
    // https://github.com/Pannoniae/BlockGame/blob/2e02356c73dd927a09c4299b41a13cbad972a57f/src/world/chunk/PaletteBlockData.cs#L145
    // Permission was given from Pannoniae to continue porting this code
    switch (m_indexBits) {
        case 0: return 0;
        case 1: return (m_indices[index >> 3] >> (index & 7)) & 1;
        case 2: return (m_indices[index >> 2] >> ((index & 3) << 1)) & 3;
        case 4: return (m_indices[index >> 1] >> ((index & 1) << 2)) & 15;
        case 8: return m_indices[index];
        case 16: {
            const int idx = index << 1;
            return (m_indices[idx] << 8)
                 | (m_indices[idx + 1]);
        }
        case 32: {
            const int idx = index << 2;
            return (m_indices[idx] << 24)
                 | (m_indices[idx + 1] << 16)
                 | (m_indices[idx + 2] << 8)
                 | (m_indices[idx + 3]);
        }
        default: throw exception::PaletteIndexTooLargeException();
    }
}

template<typename T>
void PalletizedStorage<T>::setPaletteIndex(const int index, const int value) {
    // https://github.com/Pannoniae/BlockGame/blob/2e02356c73dd927a09c4299b41a13cbad972a57f/src/world/chunk/PaletteBlockData.cs#L185
    // Permission was given from Pannoniae to continue porting this code
    switch (m_indexBits)
    {
        case 0:
            return;
        case 1:
            m_indices[index >> 3] = static_cast<unsigned char>((m_indices[index >> 3] & ~(1 << (index & 7))) |
                                                     ((value & 1) << (index & 7)));
            return;
        case 2:
            m_indices[index >> 2] = static_cast<unsigned char>((m_indices[index >> 2] & ~(3 << ((index & 3) << 1))) |
                                                              ((value & 3) << ((index & 3) << 1)));
            return;
        case 4:
            m_indices[index >> 1] = static_cast<unsigned char>((m_indices[index >> 1] & ~(15 << ((index & 1) << 2))) |
                                                              ((value & 15) << ((index & 1) << 2)));
            return;
        case 8:
            m_indices[index] = static_cast<unsigned char>(value);
            return;
        case 16: {
            const int idx = index << 1;
            m_indices[idx    ] = static_cast<uint8_t>(value & 0xFF);
            m_indices[idx + 1] = static_cast<uint8_t>((value >> 8) & 0xFF);
            return;
        }
        case 32: {
            const int idx = index << 2;
            m_indices[idx    ] = static_cast<uint8_t>(value & 0xFF);
            m_indices[idx + 1] = static_cast<uint8_t>((value >> 8) & 0xFF);
            m_indices[idx + 2] = static_cast<uint8_t>((value >> 16) & 0xFF);
            m_indices[idx + 3] = static_cast<uint8_t>((value >> 24) & 0xFF);

            return;
        }
        default:
            throw exception::PaletteIndexTooLargeException();
    }
}

template<typename T>
int PalletizedStorage<T>::obtainPaletteEntry() {
    while (true) {
        for (int i = 0; i < m_palette.size(); i++)
            if (m_palette[i].references == 0) return i;

        this->resize();
    }
}

template<typename T>
void PalletizedStorage<T>::resize() {
    if (m_indexBits >= 32)
        throw exception::PaletteIndexTooLargeException(); // was originally "how many fucking blocks have you placed????"

    // decode
    std::vector<int> indices(m_capacity);
    for (int i = 0; i < m_capacity; ++i)
        indices[i] = getPaletteIndex(i);

    m_indexBits = (m_indexBits == 0) ? 1 : (m_indexBits << 1); // it implodes if I don't do this

    m_palette.resize(1 << m_indexBits);
    m_indices.resize(getIndicesSize());

    // re encode
    for (int i = 0; i < m_capacity; ++i)
        setPaletteIndex(i, indices[i]);
}
#endif // PALLETIZEDSTORAGE_TPP
