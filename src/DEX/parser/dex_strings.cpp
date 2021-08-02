#include "dex_strings.hpp"

namespace KUNAI {
    namespace DEX {

        /**
         * @brief Generate new DexStrings object.
         * @param input_file: file where to read DexString.
         * @param file_size: size of file for checks.
         * @param number_of_strings: number of different strings from DEX.
         * @param strings_offsets: offset where to read the strings.
         */
        DexStrings::DexStrings(std::ifstream& input_file, 
                                std::uint64_t file_size, 
                                std::uint32_t number_of_strings, 
                                std::uint32_t strings_offsets)
        {
            this->number_of_strings = number_of_strings;
            this->offset = strings_offsets;

            if (!parse_strings(input_file, file_size))
                throw exceptions::ParserReadingException("Error reading DEX strings");
        }

        /**
         * @brief DexStrings destructor, clear strings vector.
         */
        DexStrings::~DexStrings()
        {
            if (!strings.empty())
                strings.clear();
        }

        /**
         * @brief Return a string pointer by the offset.
         * @param offset: string offset in DEX file.
         * @return std::string* string from DEX file.
         */
        std::string* DexStrings::get_string_from_offset(std::uint32_t offset)
        {
            if (this->strings.find(offset) == this->strings.end())
                return nullptr;
            
            return &(this->strings[offset]);
        }
        
        /**
         * @brief Return a string pointer by order of the string.
         * @param pos: position where toget the string.
         * @return std::string* string from DEX file.
         */
        std::string* DexStrings::get_string_from_order(std::uint32_t pos)
        {
            if (pos >= this->strings.size())
                return nullptr;
            
            return ordered_strings[pos];
        }

        /**
         * @brief Return all the strings in a vector.
         * @return std::vector<std::string> all the list of strings.
         */
        std::vector<std::string> DexStrings::get_all_strings()
        {
            std::vector<std::string> all_strings;

            for (auto it = this->strings.begin(); it != this->strings.end(); it++)
                all_strings.push_back(it->second);
            
            return all_strings;
        }

        /**
         * @brief Get number of all the DEX strings.
         * @return number of all DEX strings.
         */
        std::uint32_t DexStrings::get_number_of_strings()
        {
            return number_of_strings;
        }

        /**
         * Private methods
         */
        
        /**
         * @brief private method to parse strings of DEX file.
         * @param input_file: file where to search the strings.
         * @param file_size: size of file for checks.
         * @return true if correct, false if a problem happen.
         */
        bool DexStrings::parse_strings(std::ifstream& input_file, std::uint64_t file_size)
        {
            auto current_offset = input_file.tellg();
            size_t i;
            // string values
            std::uint32_t str_offset;
            std::string str;

            // move to offset where are the string ids
            input_file.seekg(this->offset);

            // go one by one reading offset and string
            for (i = 0; i < this->number_of_strings; i++)
            {
                if (!KUNAI::read_data_file<std::uint32_t>(str_offset, sizeof(std::uint32_t), input_file))
                    return false;
                
                if (str_offset > file_size)
                    throw exceptions::OutOfBoundException("Error offset from string out of file bound");

                str = KUNAI::read_dex_string(input_file, str_offset);

                this->strings.insert(std::pair<std::uint32_t, std::string>(str_offset, str));
                ordered_strings.push_back(&this->strings[str_offset]);
            }

            input_file.seekg(current_offset);

            return true;
        }

        /**
         * friend methods
         */
        
        /**
         * @brief pretty print strings
         * @return std::ostream with strings pretty printed
         */
        std::ostream& operator<<(std::ostream& os, const DexStrings& entry)
        {
            size_t i = 0;
            os << std::hex;
            os << std::setw(30) << std::left << std::setfill(' ') << "=========== DEX Strings ===========" << std::endl;
            for (auto it = entry.strings.begin(); it != entry.strings.end(); it++)
            {
                os << std::left << std::setfill(' ') << "String (" << std::dec << i++ << std::hex << "): " << it->first << "->\"" << it->second << "\"" << std::endl;
            }

            return os;
        }

        /**
         * @brief dump to a std::fstream the strings in XML format.
         * @return std::fstream with strings in XML format
         */
        std::fstream& operator<<(std::fstream& fos, const DexStrings& entry)
        {
            std::stringstream stream;

            stream << std::hex;
            stream << "<strings>" << std::endl;
            for (auto it = entry.strings.begin(); it != entry.strings.end(); it++)
            {
                stream << "\t<string>" << std::endl;
                stream << "\t\t<offset>" << it->first << "</offset>" << std::endl;
                stream << "\t\t<value>" << it->second << "</value>" << std::endl;
                stream << "\t</string>" << std::endl;
            }
            stream << "</strings>" << std::endl;

            fos.write(stream.str().c_str(), stream.str().size());

            return fos;
        }
    }
}