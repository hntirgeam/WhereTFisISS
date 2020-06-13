#pragma once

#include <tgbot/tgbot.h>
#include "ApiCall/ApiCall.hpp"
#include <string>
#include <iostream>

class Core
{
public:
    Core(std::string token);
    ~Core(){};

    void startTgPoll();

private:
    TgBot::Bot bot;
    ApiCall api;
    Data _p;

    void getJSONStructure() { _p = api.fillStructure(); };
    void sendMessageToChat(std::int64_t chat_id, const std::string &_message);
    void botInfoMessage(const TgBot::Message::Ptr &_message);
    void sendStructToChat(const TgBot::Message::Ptr &_message);
};
