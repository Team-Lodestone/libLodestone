/** @file JavaSerializedClassParser.cpp
*
* @author Zero_DSRS_VX
* @date 3/22/26
*
* @device mac-8
*
* @copyright Copyright (c) 2026 Team Lodestone
* @license This project is licensed under the LGPL 3.0 license, see the LICENSE file for details.
*/

#include "Lodestone.Minecraft.Java/classic/minev3/JavaSerializedClassParser.h"

#include "BinaryIO/stream/BinaryInputStream.h"
#include "Lodestone.Common/util/Logging.h"

namespace lodestone::minecraft::common::java::classic::minev3 {
    SerializedField
    SerializedField::parseFieldEntry(const SerializedClass &clazz, bio::stream::BinaryInputStream &strm) {
        // Parse field entry
        const char type = strm.readByte();
        auto descriptor = std::string(1, type);

        const std::string name = strm.readStringWithLength<char>(bio::util::ByteOrder::BIG,
                                                                 bio::util::string::StringLengthEncoding::LENGTH_PREFIX);

        // Check if descriptor is object or array
        if (type == 'L' || type == '[') {
            descriptor = parseSignature(clazz, type, strm);
        }
        return SerializedField{clazz, name, descriptor};
    }

    std::string SerializedField::parseSignature(const SerializedClass &clazz, const char type,
                                                bio::stream::BinaryInputStream &strm) {
        auto descriptor = std::string(1, type);

        // Check if descriptor is object or array
        if (type == 'L' || type == '[') {
            char typeCode = strm.readByte();
            if (typeCode == '[') {
                // Read primitive array
                const char arrayType = strm.readByte();
                if (arrayType != 'L') {
                    descriptor += arrayType;
                } else {
                    descriptor += parseSignature(clazz, arrayType, strm);
                }
            } else if (typeCode == 't') {
                descriptor = strm.readStringWithLength<char>(bio::util::ByteOrder::BIG,
                                                             bio::util::string::StringLengthEncoding::LENGTH_PREFIX);
            } else if (typeCode == 'q') {
                // Type is the same as the field before this one
                if (!clazz.m_fields.empty()) {
                    descriptor = clazz.m_fields.back().desc;

                    // skip a few bytes
                    // TODO: Figure out if this means anything
                    for (int i = 0; i < 4; i++) {
                        strm.readByte();
                    }
                }
            } else {
                LOG_DEBUG("Unrecognized type code!");
            }
        }
        return descriptor;
    }

    JavaValue SerializedField::readFieldValue(JavaSerializedClassParser& parser, const SerializedField &field, bio::stream::BinaryInputStream &strm) {
        const auto descriptor = field.desc;
        if (descriptor == "B") {
            return JavaValue { strm.readSignedByte() };
        }
        if (descriptor == "Z") {
            return JavaValue { (strm.readByte() != 0) };
        }
        if (descriptor == "C") {
            return JavaValue { static_cast<char>(strm.readByte()) };
        }
        if (descriptor == "D") {
            return JavaValue { strm.readBE<double>() };
        }
        if (descriptor == "F") {
            return JavaValue { strm.readBE<float>() };
        }
        if (descriptor == "I") {
            // Java always stores integers as signed
            // C++ uses two's-complements when reading the integer in
            // which means we need to shift this down to get the
            // correct sign and value.
            return JavaValue { static_cast<int32_t>(strm.readBE<uint32_t>() >> 8) };
        }
        if (descriptor == "J") {
            return JavaValue { static_cast<int64_t>(strm.readBE<uint64_t>() >> 8) };
        }
        if (descriptor.starts_with("L")) {
            if (descriptor == "Ljava/lang/String;") {
                return JavaValue { std::string(strm.readStringWithLength<char>(bio::util::ByteOrder::BIG, bio::util::string::StringLengthEncoding::LENGTH_PREFIX)) };
            }
            strm.seekRelative(-1);
            int offset = strm.getOffset();
            // Object!
            SerializedClass clazz = parser.parseEntry();
            return JavaValue { std::make_shared<JavaObject>(clazz)};
        }
        if (descriptor.starts_with("[")) {
            // Array!
            return JavreadFieldValue(parser, field, strm) });
        }

        LOG_DEBUG("Descriptor not yet implemented!");
        return {};
    }

    std::vector<SerializedClass> JavaSerializedClassParser::parseAllEntries() {
        std::vector<SerializedClass> result;
        if (!this->m_stream.getStream().eof()) {
            SerializedClass clazz = this->parseEntry();
        }

        return result;
    }

    SerializedClass JavaSerializedClassParser::parseEntry() {
        SerializedClass result;

        if (const uint16_t classMagic = this->m_stream.readBE<uint16_t>(); classMagic != 0x7372) {
            return result;
        }

        // Read class name
        result.m_className = this->m_stream.readStringWithLength<char>(bio::util::ByteOrder::BIG,
                                                                       bio::util::string::StringLengthEncoding::LENGTH_PREFIX);
        this->m_stream.seekRelative(8);

        // TODO: Read fields from serialized class object
        this->m_stream.seekRelative(2); // TODO: Look at this more

        const int8_t numberOfFields = this->m_stream.readSignedByte();

        result.m_fields.clear();

        for (int i = 0; i < numberOfFields; i++) {
            SerializedField field = SerializedField::parseFieldEntry(result, this->m_stream);
            result.m_fields.push_back(field);
        }

        char tcEndBlockData = this->m_stream.readByte();
        if (tcEndBlockData != 0x78) {
            LOG_ERROR(
                "TCEndBlockData was not found after reading fields! Stream is either corrupted or signature parsing failed!");
        }
        char tcSuperclassDesc = this->m_stream.readByte();
        if (tcSuperclassDesc == 0x72) {
            // Superclass was specified
            // TODO: Implement reading of superclass

            tcEndBlockData = this->m_stream.readByte();
            if (tcEndBlockData != 0x78) {
                LOG_ERROR(
                    "TCEndBlockData was not found after reading superclass! Stream is either corrupted or superclass could not be parsed!");
            }

            // TODO: Remove this hack:
            // This will skip over the superclass declaration if it exists
            while (true) {
                if (this->m_stream.readByte() == 0x78) {
                    break;
                }
            }
        } else if (tcSuperclassDesc == 0x70) {
            // Superclass was null
        }
        // Skip one byte
        this->m_stream.seekRelative(1);

        // Read field values
        for (int i = 0; i < numberOfFields; i++) {
            SerializedField& field = result.m_fields[i];
            field.value = field.readFieldValue(*this, field, this->m_stream);
        }

        this->m_serializedClasses.push_back(result);
        return result;
    }
} // lodestone::minecraft::common::java::classic::minev3
