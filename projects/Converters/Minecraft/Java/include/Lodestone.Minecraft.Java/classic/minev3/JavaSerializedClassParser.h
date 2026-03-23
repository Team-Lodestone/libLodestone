/** @file JavaSerializedClassParser.h
*
* @author Zero_DSRS_VX
* @date 3/22/26
*
* @device mac-8
*
* @copyright Copyright (c) 2026 Team Lodestone
* @license This project is licensed under the LGPL 3.0 license, see the LICENSE file for details.
*/
#ifndef LODESTONE_JAVASERIALIZEDCLASSPARSER_H
#define LODESTONE_JAVASERIALIZEDCLASSPARSER_H
#include <istream>

#include "BinaryIO/stream/BinaryOutputStream.h"

namespace bio::stream {
    class BinaryInputStream;
}

namespace lodestone::minecraft::common::java::classic::minev3 {
    class JavaSerializedClassParser;
    class SerializedClass;
    class SerializedField;

    struct JavaObject {
        SerializedClass& m_class;
    };
    using JavaArray = std::vector<JavaObject>;

    // DO NOT RE-ORDER VARIANTS
    using JavaValue = std::variant<int64_t, double, int32_t, float, bool, JavaArray, std::shared_ptr<JavaObject>, std::string>;

    class SerializedClass {
    public:
        std::string m_className;

        std::vector<SerializedField> m_fields;
    };

    class SerializedField {
    public:
        const SerializedClass& m_class;
        std::string name;
        std::string desc;
        JavaValue value;

        explicit SerializedField(const SerializedClass& clazz, const std::string &name, const std::string &desc) : m_class(clazz), name(name), desc(desc) {}

        static SerializedField parseFieldEntry(const SerializedClass& clazz, bio::stream::BinaryInputStream &strm);
        static std::string parseSignature(const SerializedClass& clazz, char type, bio::stream::BinaryInputStream &strm);
        static JavaValue readFieldValue(JavaSerializedClassParser& parser, const SerializedField &field, bio::stream::BinaryInputStream &strm);
    };

    class JavaSerializedClassParser {
        bio::stream::BinaryInputStream& m_stream;
        std::vector<SerializedClass> m_serializedClasses;
    public:
        explicit JavaSerializedClassParser(bio::stream::BinaryInputStream &strm) : m_stream(strm) {};

        std::vector<SerializedClass> parseAllEntries();
        SerializedClass parseEntry();
    };
} // lodestone::minecraft::common::java::classic::minev3

#endif //LODESTONE_JAVASERIALIZEDCLASSPARSER_H