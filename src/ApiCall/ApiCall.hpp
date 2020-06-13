#pragma once

#include <iostream>
#include "JsonParser/JsonParser.hpp"

#include <curl/curl.h>
#include <string>

struct Data
{
    std::string name = "";
    size_t id = 0;
    double latitude = 0;
    double longitude = 0;
    double altitude = 0;
    double velocity = 0;
    std::string visibility = "";
    time_t unix_timestamp = 0;
    std::string units = "";
};

class ApiCall
{
public:
    ApiCall(){};
    ~ApiCall(){};

    void makeRequest(const std::string &apiString, int customID = 25544);
    Data fillStructure();

    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
    {
        ((std::string *)userp)->append((char *)contents, size * nmemb);
        return size * nmemb;
    }

private:
    std::string curlRes;
};
