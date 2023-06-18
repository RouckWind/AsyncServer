#include <client.h>
#include <threadpool.h>

#include <iostream>
#include <string>

std::string randomMessage(){
    srand(time(NULL));
    std::string result;
    std::string symbols{ "abcdefghijklmnopqrstuvwxyz"};

    for( int i = 0; i < 10; ++i ) {
        int random = rand() % 26;
        result.push_back(symbols[random]);
    }
    return result;
}

int main() {
    //auto pool = ThreadPool::create(3) ;
    TCPClient::Client client(randomMessage());

    //std::cout << randomMessage();

    return 0;
}