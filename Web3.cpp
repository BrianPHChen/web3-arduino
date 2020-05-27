#include "Web3.h"

Web3::Web3(String _provider) {
    provider = _provider;
}

String Web3::Web3ClientVersion() {
    String req = genReq("web3_clientVersion", "[]");
    return sendReq(req);
}

String Web3::genReq(String method, String params) {
    StaticJsonDocument<300> req;
    req["jsonrpc"] = "2.0";
    req["method"] = method;
    req["id"] = 1;
    JsonArray data = req.createNestedArray("params");
    String reqString;
    serializeJson(req, reqString);
    return reqString;
}

String Web3::sendReq(String req) {
    StaticJsonDocument<300> res;
    HTTPClient http;

    http.begin(provider);
    int httpCode = http.POST(req);
    if (httpCode > 0) {
        DeserializationError error = deserializeJson(res, http.getString());
        if (error) {
            return "Deserialize response json failed";
        }
        return res["result"];

        // Serial.println(strtol(result, NULL, 16));
    } else {
      return "Error on HTTP request";
    }
    http.end();
}