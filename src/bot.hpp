#include <WString.h>

class Bot
{
    private:
        const char* access_token;
        const char* page_id;
        
    public:
        Bot();

        bool canConnect();

        void post(String content);
}