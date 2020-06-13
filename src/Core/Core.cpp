#include "Core.hpp"
#include "ApiCall/ApiCall.hpp"

Core::Core(std::string token) : bot(token)
{
    bot.getEvents().onCommand("start", [this](const TgBot::Message::Ptr &message) {
        this->botInfoMessage(message);
    });

    bot.getEvents().onCommand("whereTFisISS", [this](const TgBot::Message::Ptr &message) {
        this->api.makeRequest("https://api.wheretheiss.at/v1/satellites/");
        this->sendStructToChat(message);
        bot.getApi().sendLocation(message->chat->id, _p.latitude, _p.longitude);
    });

    bot.getEvents().onCommand("help", [this](const TgBot::Message::Ptr &message) {
        this->botInfoMessage(message);
    });
};

void Core::startTgPoll()
{
    try
    {
        bot.getApi().deleteWebhook();
        std::cout << "Username: " << bot.getApi().getMe()->username << std::endl;
        TgBot::TgLongPoll longPoll(bot);

        while (true)
            longPoll.start();
    }
    catch (TgBot::TgException &e)
    {
        std::cout << "error: " << e.what() << std::endl;
    }
}

void Core::sendMessageToChat(std::int64_t chat_id, const std::string &_message)
{
    bot.getApi().sendMessage(chat_id, _message);
}

void Core::botInfoMessage(const TgBot::Message::Ptr &_message)
{
    sendMessageToChat(
        _message->chat->id,
        "Usage:\n Just send /whereTFisISS command and bot will send "
        "current ISS position on map and will "
        "also provide additional nerd information.");
}

void Core::sendStructToChat(const TgBot::Message::Ptr &_message)
{
    using namespace std;
    _p = api.fillStructure();
    std::cout << "fill" << std::endl;

    string structureFormat =
        "Name: " + _p.name + '\n' +
        "ID: " + to_string(_p.id) + '\n' +
        "Latitude: " + to_string(_p.latitude) + '\n' +
        "Longitude: " + to_string(_p.longitude) + '\n' +
        "Altitude: " + to_string(_p.altitude) + '\n' +
        "Velocity: " + to_string(_p.velocity) + '\n' +
        "Visibility: " + _p.visibility + '\n' +
        "Unix Time: " + to_string(_p.unix_timestamp) + '\n' +
        "Units: " + _p.units + '\n';

    sendMessageToChat(_message->chat->id, structureFormat);
}
