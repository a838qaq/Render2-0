#include "Parser.h"

namespace civitasv
{
    namespace json
    {
        using JsonTokenType = Scanner::JsonTokenType;

        JsonElement *Parser::Parse()
        {
            JsonElement *element = new JsonElement();
            JsonTokenType token_type = scanner_.Scan();

            if (token_type == JsonTokenType::END_OF_SOURCE)
            {
            }
            else if (token_type == JsonTokenType::BEGIN_OBJECT)
            {
                JsonObject *object = ParseObject();
                element->value(object);
            }
            else if (token_type == JsonTokenType::BEGIN_ARRY)
            {
                JsonArry *arry = ParseArry();
                element->value(arry);
            }
            else if (token_type == JsonTokenType::VALUE_STRING)
            {
                std::string *val = new std::string(scanner_.GetValueString());
                element->value(val);
            }
            else if (token_type == JsonTokenType::VALUE_NUMBER)
            {
                double val = scanner_.GetValueNumber();
                element->value(val);
            }
            else if (token_type == JsonTokenType::LITERAL_TRUE)
            {
                element->value(true);
            }
            else if (token_type == JsonTokenType::LITERAL_FALSE)
            {
                element->value(false);
            }

            return element;
        }

        JsonObject *Parser::ParseObject()
        {
            JsonObject *res = new JsonObject;
            JsonTokenType next = scanner_.Scan();
            if (next == JsonTokenType::END_OBJECT)
            {
                return res;
            }
            scanner_.Rollback();
            while (true)
            {
                next = scanner_.Scan();
                if (next != JsonTokenType::VALUE_STRING)
                {
                    Error("Key must be string");
                }
                std::string key = scanner_.GetValueString();
                next = scanner_.Scan();
                if (next != JsonTokenType::NAME_SEPRATOR)
                {
                    Error("Expected ':'");
                }
                (*res)[key] = Parse();
                next = scanner_.Scan();
                if (next == JsonTokenType::END_OBJECT)
                {
                    break;
                }
                if (next != JsonTokenType::VALUE_SEPRATOR)
                {
                    Error("Expect ','");
                }
            }
            return res;
        }

        JsonArry *Parser::ParseArry()
        {
            JsonArry *res = new JsonArry();
            JsonTokenType next = scanner_.Scan();
            if (next == JsonTokenType::END_ARRY)
            {
                return res;
            }
            scanner_.Rollback();

            while (true)
            {
                res->push_back(Parse());
                next = scanner_.Scan();

                if (next == JsonTokenType::END_ARRY)
                    break;

                if (next != JsonTokenType::VALUE_SEPRATOR)
                {
                    Error("Expect ','");
                }
            }

            return res;
        }
    }; // namespace json
};     // namespace civitasv
