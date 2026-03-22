//
// Created by DexrnZacAttack on 2/14/26 using zPc-i2.
//
#ifndef LODESTONE_ABSTRACTOBJECTIO_H
#define LODESTONE_ABSTRACTOBJECTIO_H
#include <Lodestone.Common/util/Concepts.h>

#include <Lodestone.Common/registry/Identifier.h>
#include <Lodestone.Level/entity/Player.h>
#include <Lodestone.Level/region/Region.h>

#include "Lodestone.Conversion/io/IObjectIo.h"
#include "Lodestone.Conversion/io/interfaces/IChunkIo.h"
#include "Lodestone.Conversion/io/interfaces/ILevelIo.h"
#include "Lodestone.Conversion/io/interfaces/IPlayerIo.h"
#include "Lodestone.Conversion/io/interfaces/IRegionIo.h"
#include "Lodestone.Conversion/io/interfaces/IWorldIo.h"
#include "Lodestone.Conversion/io/options/OptionsBuilder.h"
#include "Lodestone.Conversion/io/types/Readable.h"
#include "Lodestone.Conversion/io/types/Writable.h"

#include <proxy/proxy.h>

#include <Lodestone.Common/registry/Identifiable.h>

namespace lodestone::conversion::io {
    /** Basic Object IO class
     *
     * @tparam I The identifier of the IO class
     * @tparam R The return type of the Reader
     * @tparam W The type to be written out when using the Writer
     * @tparam RO Options provided to the Reader
     * @tparam WO Options provided to the Writer
     * @tparam WR Optional return type from the Writer
     */
    template <const common::registry::Identifier *I, typename R, typename W, typename RO, typename WO, typename WR = void>
    requires lodestone::common::util::concepts::void_or_derived_from_v<options::IOptions, RO> && lodestone::common::util::concepts::void_or_derived_from_v<options::IOptions, WO>
    struct LODESTONE_CONVERSION_API AbstractObjectIO : virtual IObjectIO, common::registry::Identifiable<I>, types::Readable<R, RO>, types::Writable<W, WO, WR> {
        AbstractObjectIO() = default;

        pro::proxy<ReallyAny> baseRead(void *options) const override {
            return this->read(*static_cast<const RO *>(options));
        }

        void baseWrite(void *obj, void *options) const override {
            this->write(static_cast<W>(obj), *static_cast<const WO *>(options));
        }
    };
}

#endif // LODESTONE_ABSTRACTOBJECTIO_H
