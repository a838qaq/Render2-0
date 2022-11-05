#pragma once
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include "Error.h"

namespace civitasv
{
    namespace json
    {
        class JsonElement;
        using JsonObject = std::map<std::string, JsonElement *>;
        using JsonArry = std::vector<JsonElement *>;
        class JsonElement
        {
        public:
            enum class Type
            {
                JSON_OBJECT,
                JSON_ARRY,
                JSON_STRING,
                JSON_NUMBER,
                JSON_BOOL,
                JSON_NULL
            };
            union Value
            {
                JsonObject *value_object;
                JsonArry *value_arry;
                std::string *value_string;
                double value_number;
                bool value_bool;
            };

            JsonElement() : type_(Type::JSON_NULL){};
            JsonElement(JsonObject *value_object)
            {
                value(value_object);
            }
            JsonElement(JsonArry *value_arry)
            {
                value(value_arry);
            }
            JsonElement(std::string *value_strings)
            {
                value(value_strings);
            }
            JsonElement(double value_number)
            {
                value(value_number);
            }
            JsonElement(bool value_bool)
            {
                value(value_bool);
            }

            ~JsonElement()
            {
                if (type_ == Type::JSON_OBJECT)
                {
                    JsonObject *object = value_.value_object;
                    for (auto &[key, value] : *object)
                    {
                        delete value;
                    }
                }
                else if (type_ == Type::JSON_ARRY)
                {
                    JsonArry *arry = value_.value_arry;
                    for (auto &item : *arry)
                    {
                        delete item;
                    }
                    delete arry;
                }
                else if (type_ == Type::JSON_STRING)
                {
                    std::string *val = value_.value_string;
                    delete val;
                }
            }
            void value(JsonObject *value_object)
            {
                type_ = Type::JSON_OBJECT;
                value_.value_object = value_object;
            }
            void value(JsonArry *value_arry)
            {
                type_ = Type::JSON_ARRY;
                value_.value_arry = value_arry;
            }
            void value(std::string *value_strings)
            {
                type_ = Type::JSON_STRING;
                value_.value_string = value_strings;
            }
            void value(double value_number)
            {
                type_ = Type::JSON_NUMBER;
                value_.value_number = value_number;
            }
            void value(bool value_bool)
            {
                type_ = Type::JSON_BOOL;
                value_.value_bool = value_bool;
            }

            JsonObject *AsObject()
            {
                if (type_ == Type::JSON_OBJECT)
                {
                    return value_.value_object;
                }
                Error("Type of JsonElement isn't JsonObject");
            }
            JsonArry *AsArry()
            {
                if (type_ == Type::JSON_ARRY)
                {
                    return value_.value_arry;
                }
                Error("Type of JsonElement isn't JsonArry");
            }
            std::string *AsString()
            {
                if (type_ == Type::JSON_STRING)
                {
                    return value_.value_string;
                }
                Error("Type of JsonElement isn't JsonString");
            }
            double AsNumber()
            {
                if (type_ == Type::JSON_NUMBER)
                {
                    return value_.value_number;
                }
                Error("Type of JsonElement isn't JsonNumber");
            }
            bool AsBool()
            {
                if (type_ == Type::JSON_BOOL)
                {
                    return value_.value_bool;
                }
                Error("Type of JsonElement isn't JsonBool");
            }

        public:
            std::string Dumps()
            {
                std::stringstream ss;
                switch (type_)
                {
                case Type::JSON_OBJECT:
                    ss << *(value_.value_object);
                    break;
                case Type::JSON_ARRY:
                    ss << *(value_.value_arry);
                    break;
                case Type::JSON_STRING:
                    ss << *(value_.value_string);
                    break;
                case Type::JSON_NUMBER:
                    ss << (value_.value_number);
                    break;
                case Type::JSON_BOOL:
                    ss << (value_.value_bool ? "true" : "false");
                    break;
                case Type::JSON_NULL:
                    ss << "null";
                    break;
                default:
                    break;
                }
                return ss.str();
            }

            friend std::ostream &operator<<(std::ostream &os, const JsonObject &object)
            {
                os << "{";
                for (auto iter = object.begin(); iter != object.end(); iter++)
                {
                    os << '\"' << iter->first << '\"' << ":" << iter->second->Dumps();
                    if (iter != --object.end())
                    {
                        os << ",";
                    }
                }
                os << "}";
                return os;
            }

            friend std::ostream &operator<<(std::ostream &os, JsonArry &arry)
            {
                os << "[";
                for (size_t i = 0; i < arry.size(); i++)
                {
                    os << arry[i]->Dumps();
                    if (i != arry.size() - 1)
                    {
                        os << ",";
                    }
                }
                os << "]";
                return os;
            }

        private:
            Type type_;
            Value value_;
        };
    } // namespace json

} // namespace civitasv
