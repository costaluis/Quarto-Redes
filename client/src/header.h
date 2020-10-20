#ifndef MYHEADER
#define MYHEADER
#include <vector>
#include <string>

void receiver_client(int client);

void sender_client(int client);

class msg
{
private:
    /* data */
public:
    bool flag_rec;
    bool flag_send;
    std::string dado;
    msg();
    ~msg();
};

msg::msg(/* args */)
{
}

msg::~msg()
{
}




#endif