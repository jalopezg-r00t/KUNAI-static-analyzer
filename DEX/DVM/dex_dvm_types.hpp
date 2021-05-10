/***
 * File: dex_dvm_types.hpp
 * 
 * Dictionaries used in Dalvik,
 * taken from androguard project.
 * 
 */

#ifndef DEX_DVM_TYPES_HPP
#define DEX_DVM_TYPES_HPP

#include <iostream>
#include <map>

namespace KUNAI {
    namespace DEX {
        class DVMTypes
        {
        public:
            static const std::uint32_t ENDIAN_CONSTANT = 0x12345678;
            static const std::uint32_t REVERSE_ENDIAN_CONSTANT = 0x78563412;
            static const std::uint32_t NO_INDEX = 0xFFFFFFFF;

            enum Kind
            /***
             * Identify kind of argument inside of
             * argument inside a Dalvik Instruction.
             */
            {
                METH=0,             // method reference
                STRING=1,           // string index
                FIELD=2,            // field reference
                TYPE=3,             // type reference
                PROTO=9,            // prototype reference
                METH_PROTO=10,      // method reference and proto reference
                CALL_SITE=11,       // call site item
                VARIES=4,
                INLINE_METHOD=5,    // Inlined method
                VTABLE_OFFSET=6,    // static linked
                FIELD_OFFSET=7,
                RAW_STRING=8
            };

            enum Operand
            /***
             * Enumeration used for operand type of opcodes
             */
            {
                REGISTER = 0,
                LITERAL = 1,
                RAW = 2,
                OFFSET = 3,

                KIND = 0x100 // used together with others
            };

            enum ACCESS_FLAGS
            /***
             * Access flags used in class_def_item, encoded_field, 
             * encoded_method and InnerClass
             * https://source.android.com/devices/tech/dalvik/dex-format#access-flags
             */
            {
                ACC_PUBLIC = 0x1,
                ACC_PRIVATE = 0x2,
                ACC_PROTECTED = 0x4,
                ACC_STATIC = 0x8,
                ACC_FINAL = 0x10,
                ACC_SYNCHRONIZED = 0x20,
                ACC_VOLATILE = 0x40,
                ACC_BRIDGE = 0x40,
                ACC_TRANSIENT = 0x80,
                ACC_VARARGS = 0x80,
                ACC_NATIVE = 0x100,
                ACC_INTERFACE = 0x200,
                ACC_ABSTRACT = 0x400,
                ACC_STRICT = 0x800,
                ACC_SYNTHETIC = 0x1000,
                ACC_ANNOTATION = 0x2000,
                ACC_ENUM = 0x4000,
                UNUSED = 0x8000,
                ACC_CONSTRUCTOR = 0x10000,
                ACC_DECLARED_SYNCHRONIZED = 0x20000
            };

            std::map<ACCESS_FLAGS, std::string> ACCESS_FLAGS_STR = {
                {ACC_PUBLIC, "public"},
                {ACC_PRIVATE, "private"},
                {ACC_PROTECTED, "protected"},
                {ACC_STATIC, "static"},
                {ACC_FINAL, "final"},
                {ACC_SYNCHRONIZED, "synchronized"},
                {ACC_BRIDGE, "bridge"},
                {ACC_VARARGS, "varargs"},
                {ACC_NATIVE, "native"},
                {ACC_INTERFACE, "interface"},
                {ACC_ABSTRACT, "abstract"},
                {ACC_STRICT, "strictfp"},
                {ACC_SYNTHETIC, "synthetic"},
                {ACC_ENUM, "enum"},
                {UNUSED, "unused"},
                {ACC_CONSTRUCTOR, "constructor"},
                {ACC_DECLARED_SYNCHRONIZED, "synchronized"}
            };


            


        };
    }
}

#endif