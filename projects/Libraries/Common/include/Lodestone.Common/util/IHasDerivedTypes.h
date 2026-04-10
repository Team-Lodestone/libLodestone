/** @file IHasDerivedTypes.h
 *
 * @author DexrnZacAttack
 * @date 4/8/26
 * 
 * @device zPc-i2
 */
#ifndef LODESTONE_IHASDERIVEDTYPES_H
#define LODESTONE_IHASDERIVEDTYPES_H

namespace lodestone::common::util {
    /** Small helper class for being able to tell the class instance type without comparing against typeid */
    template <typename EType>
    class IHasDerivedTypes {
    public:
        constexpr IHasDerivedTypes() = default;
        constexpr virtual ~IHasDerivedTypes() = default;

        // TODO theoretically we can avoid the vcall if we store type as const in here?
        virtual constexpr EType type() = 0;

        bool constexpr instanceOf(EType type) {
            return this->type() == type;
        }

        bool constexpr instanceOf(const IHasDerivedTypes *inst) {
            return this->type() == inst->type();
        }

        bool constexpr instanceOf(const IHasDerivedTypes &inst) {
            return this->type() == inst.type();
        }
    };
}

#endif // LODESTONE_IHASDERIVEDTYPES_H