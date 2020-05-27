#ifndef WEB3_ARDUINO_H
#define WEB3_ARDUINO_H

#include <HTTPClient.h>
#include <ArduinoJson.h>

class Web3 {
    public:
        Web3(String _provider);
        String clientVersion();
        String sha3(String data);
    private:
        String provider;
        String genReq(String method, String params[], int paramsSize);
        String sendReq(String req);
};

#endif
