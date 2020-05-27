#include "Web3.h"

HTTPClient http;

Web3::Web3(String _provider) {
    provider = _provider;
}

String Web3::clientVersion() {
    String req = genReq("web3_clientVersion", {}, 0);
    return sendReq(req);
}

String Web3::sha3(String data) {
    String params[] = { data };
    String req = genReq("web3_sha3", params, 1);
    return sendReq(req);
}

String Web3::genReq(String method, String params[], int paramsSize) {
    StaticJsonDocument<300> req;
    req["jsonrpc"] = "2.0";
    req["method"] = method;
    req["id"] = 1;
    JsonArray array = req.createNestedArray("params");
    for (int i = 0; i < paramsSize; i++){
        array.add(params[i]);
    }
    String reqString;
    serializeJson(req, reqString);
    Serial.println("req: " + reqString);
    return reqString;
}

String Web3::sendReq(String req) {
    StaticJsonDocument<300> res;

    http.begin(provider);
    int httpCode = http.POST(req);
    if (httpCode > 0) {
        String payload = http.getString();
        Serial.println("res: " + payload);
        DeserializationError error = deserializeJson(res, payload);
        if (error) {
            return "Deserialize response json failed";
        }
        return res["result"];

        // Serial.println(strtol(result, NULL, 16));
    } else {
      return "Error on HTTP request";
    }
}
