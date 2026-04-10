/** @file SectionCoordinates.h
 *
 * @author DexrnZacAttack
 * @date 4/9/26
 * 
 * @device zPc-i2
 */
#ifndef LODESTONE_SECTIONCOORDINATES_H
#define LODESTONE_SECTIONCOORDINATES_H
#include <Lodestone.Common/Defines.h>
#include <Lodestone.Common/Indexing.h>
#include <Lodestone.Common/util/Math.h>

namespace lodestone::level::coords {
    class SectionCoordinates {
    public:
        static constexpr int SECTION_BITS = common::util::Math::constevalLog(common::constants::SECTION_HEIGHT, 2);

        constexpr SectionCoordinates(const int y) : m_sectionY(y) {}

        static constexpr SectionCoordinates fromBlockCoordinates(const signed_size_t blockY) {
            return SectionCoordinates(blockToSectionCoord(blockY));
        }

        // ReSharper disable once CppNonExplicitConversionOperator
        constexpr operator int() const {
            return this->getY();
        }

        constexpr int getY() const {
            return this->m_sectionY;
        }

        static constexpr int blockToSectionCoord(const signed_size_t blockCoord) {
            return blockCoord >> SECTION_BITS;
        }

        static constexpr int blockToLocalSectionY(const signed_size_t blockX) {
            return blockX & (common::constants::SECTION_HEIGHT - 1);
        }
    private:
        int m_sectionY;
    };
}

#endif // LODESTONE_SECTIONCOORDINATES_H