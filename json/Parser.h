#pragma once
#include "Scanner.h"
#include "JsonElement.h"
namespace civitasv
{
    namespace json
    {
        class Parser
        {
        public:
            Parser(Scanner scanner) : scanner_(scanner){};
            JsonElement *Parse();

        private:
            Scanner scanner_;

            JsonObject *ParseObject();
            JsonArry *ParseArry();
        };
    } // namespace json

} // namespace civitasv
