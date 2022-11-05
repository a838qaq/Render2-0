#pragma once
#include <string>

namespace civitasv
{
    namespace json
    {
        std::string GetJsonString(const char *path);
        class Scanner
        {
        public:
            Scanner(std::string source);
            enum class JsonTokenType
            {
                BEGIN_OBJECT, // {
                END_OBJECT,   // }

                VALUE_SEPRATOR, // ,
                NAME_SEPRATOR,  // :

                VALUE_STRING, // "string"
                VALUE_NUMBER, // 123234.123

                LITERAL_TRUE,  // true
                LITERAL_FALSE, // false
                LITERAL_NULL,  // null

                BEGIN_ARRY, // [
                END_ARRY,   // ]

                END_OF_SOURCE // EOF
            };

            friend std::ostream &operator<<(std::ostream &os, const JsonTokenType &type)
            {
                switch (type)
                {
                case JsonTokenType::BEGIN_ARRY:
                    os << (std::string) "[";
                    break;
                case JsonTokenType::END_ARRY:
                    os << (std::string) "]";
                    break;
                case JsonTokenType::BEGIN_OBJECT:
                    os << (std::string) "{";
                    break;
                case JsonTokenType::END_OBJECT:
                    os << (std::string) "}";
                    break;
                case JsonTokenType::VALUE_SEPRATOR:
                    os << (std::string) ",";
                    break;
                case JsonTokenType::NAME_SEPRATOR:
                    os << (std::string) ":";
                    break;
                case JsonTokenType::VALUE_STRING:
                    os << (std::string) "string";
                    break;
                case JsonTokenType::VALUE_NUMBER:
                    os << (std::string) "number";
                    break;
                case JsonTokenType::LITERAL_TRUE:
                    os << (std::string) "true";
                    break;
                case JsonTokenType::LITERAL_FALSE:
                    os << (std::string) "false";
                    break;
                case JsonTokenType::LITERAL_NULL:
                    os << (std::string) "null";
                    break;
                case JsonTokenType::END_OF_SOURCE:
                    os << (std::string) "EOF";
                    break;
                default:
                    break;
                }
                return os;
            }

            JsonTokenType Scan(); // return next token
            void Rollback();
            std::string GetValueString() { return value_string_; }
            double GetValueNumber() { return value_number_; }

        private:
            std::string source_;
            size_t current_; // now char position
            size_t pre_pos;  // pre position

            std::string value_string_;
            double value_number_;

        private:
            bool ifEnd();
            char Advance();
            void ScanString();
            void ScanNumber();
            void ScanTrue();
            void ScanFalse();
            void ScanNull();

            bool ifDigit(char c);
            char Peek();
            char PeekNext();
        };
    } // namespace json
} // namespace civitasv
