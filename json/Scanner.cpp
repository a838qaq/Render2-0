#include "Scanner.h"
#include "Error.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace civitasv
{
    namespace json
    {
        std::string GetJsonString(const char *path)
        {
            std::string source;
            std::ifstream input;
            try
            {
                input.open("../RenderConfig.json");
                std::stringstream ss;
                ss << input.rdbuf();
                input.close();
                source = ss.str();
            }
            catch (std::ifstream::failure e)
            {
                std::cout << "Error:Can not open file" << std::endl;
            }
            return source;
        }

        void Scanner::Rollback()
        {
            current_ = pre_pos;
        }

        Scanner::Scanner(std::string source)
        {
            source_ = source;
            current_ = 0;
        }

        bool Scanner::ifDigit(char c)
        {
            return c >= '0' && c <= '9';
        }

        char Scanner::Peek()
        {
            if (ifEnd())
                return '\0';
            return source_[current_];
        }

        char Scanner::PeekNext()
        {
            if (current_ + 1 >= source_.size())
                return '\0';
            return source_[current_ + 1];
        }

        void Scanner::ScanTrue()
        {
            if (source_.compare(current_, 3, "rue") == 0)
            {
                current_ += 3;
            }
            else
            {
                Error("Scan 'true' error");
            }
        }

        void Scanner::ScanFalse()
        {
            if (source_.compare(current_, 4, "alse") == 0)
            {
                current_ += 4;
            }
            else
            {
                Error("Scan 'false' error");
            }
        }

        void Scanner::ScanNull()
        {
            if (source_.compare(current_, 3, "ull") == 0)
            {
                current_ += 3;
            }
            else
            {
                Error("Scan 'null' error");
            }
        }

        void Scanner::ScanString()
        {
            size_t pos = current_;
            while (Peek() != '\"' && !ifEnd())
            {
                Advance();
            }
            if (ifEnd())
            {
                Error("Invalid string: missing closing quote");
            }
            Advance();
            value_string_ = source_.substr(pos, current_ - pos - 1);
        }

        void Scanner::ScanNumber()
        {
            size_t pos = current_ - 1;
            while (ifDigit(Peek()))
            {
                Advance();
            }
            if (Peek() == '.' && ifDigit((PeekNext())))
            {
                Advance();
                while (ifDigit(Peek()))
                {
                    Advance();
                }
            }
            value_number_ = std::atof(source_.substr(pos, current_ - pos).c_str());
        }

        char Scanner::Advance()
        {
            return source_[current_++];
        }

        bool Scanner::ifEnd()
        {
            return current_ >= source_.size();
        }

        Scanner::JsonTokenType Scanner::Scan()
        {
            if (ifEnd())
            {
                return Scanner::JsonTokenType::END_OF_SOURCE;
            }

            pre_pos = current_;

            char c = Advance(); // get next char
            switch (c)
            {
            case '{':
                return Scanner::JsonTokenType::BEGIN_OBJECT;
            case '}':
                return Scanner::JsonTokenType::END_OBJECT;
            case '[':
                return Scanner::JsonTokenType::BEGIN_ARRY;
            case ']':
                return Scanner::JsonTokenType::END_ARRY;
            case ':':
                return Scanner::JsonTokenType::NAME_SEPRATOR;
            case ',':
                return Scanner::JsonTokenType::VALUE_SEPRATOR;
            case 't':
                ScanTrue();
                return Scanner::JsonTokenType::LITERAL_TRUE;
            case 'f':
                ScanFalse();
                return Scanner::JsonTokenType::LITERAL_FALSE;
            case 'n':
                ScanNull();
                return Scanner::JsonTokenType::LITERAL_NULL;
            case ' ':
            case '\t':
            case '\n':
            case '\r':
                return Scan();
            case '\"':
                ScanString();
                return Scanner::JsonTokenType::VALUE_STRING;
            case '-':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case '0':
                ScanNumber();
                return Scanner::JsonTokenType::VALUE_NUMBER;

            default:
                Error("Unsupported Token: " + c);
            }
        }
    }
}