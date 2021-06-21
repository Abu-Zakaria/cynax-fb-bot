#pragma once
#include <WString.h>

class Bot
{
    private:
        const char* access_token;
        const char* page_id;
        const char* access_token_file_name = "/access_token.txt";

    public:
        void init();

        bool canConnect();

        void post(String content);
};