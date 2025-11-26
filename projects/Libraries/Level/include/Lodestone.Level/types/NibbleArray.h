//
// Created by Zero on 11/25/25.
//

#ifndef LODESTONE_NIBBLEARRAY_H
#define LODESTONE_NIBBLEARRAY_H
#include <vector>

namespace lodestone::level::types {

    class NibbleArray {
      public:
        NibbleArray(int length, int bits);
        NibbleArray(const std::vector<unsigned char> &data, int bits);
        ~NibbleArray();

        int getIndex(int x, int y, int z) const;
        int getNibble(int x, int y, int z) const;
        void setNibble(int x, int y, int z, int value);

        /**
         * Indexed by YZX
         */
        std::vector<unsigned char> data;

      private:
        int mBits;
    };

} // namespace lodestone::level::types

#endif // LODESTONE_NIBBLEARRAY_H
