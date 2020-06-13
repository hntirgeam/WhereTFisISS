#include "ApiCall.hpp"

void ApiCall::makeRequest(const std::string &apiString, int customID)
{
    CURL *curl;
    CURLcode res;
    std::string apiURL = apiString + std::to_string(customID);
    std::string callResult;

    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, apiURL.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &callResult);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    curlRes = callResult;
    fillStructure();
    std::cout << "curlRes:" + curlRes << std::endl;
}

Data ApiCall::fillStructure()
{
    using json = nlohmann::json;
    Data p;
    json apiJSON = json::parse(curlRes);

    p.name = apiJSON.at("name");
    p.id = apiJSON.at("id");
    p.latitude = apiJSON.at("latitude");
    p.longitude = apiJSON.at("longitude");
    p.altitude = apiJSON.at("altitude");
    p.velocity = apiJSON.at("velocity");
    p.visibility = apiJSON.at("visibility");
    p.unix_timestamp = apiJSON.at("timestamp");
    p.units = apiJSON.at("units");

    return p;
}