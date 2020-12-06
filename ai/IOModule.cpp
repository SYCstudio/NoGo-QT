#ifndef IO_MODULE_H
#define IO_MODULE_H

#include <iostream>
#include <vector>
#include <string>

#include "jsoncpp/json.h"

namespace IO {
    int id(int x, int y) {
        return (x-1)*9+y-1;
    }
    std::pair<std::vector<int>,std::string> Input() {
        Json::Reader reader;
        Json::Value input;

        std::string buf,msg;
        std::getline(std::cin, buf);
        std::vector<int> ret(81);

        reader.parse(buf, input);

        for (int i = 0; i < 81; i++) ret[i] = -1;

        for (int i = 0, sz = input["responses"].size(); i < sz; i++) {
            int x = input["responses"][i]["x"].asInt(), y = input["responses"][i]["y"].asInt();
            if (x != -1) ret[id(x, y)] = 0;
        }
        for (int i = 0, sz = input["requests"].size(); i < sz; i++) {
            int x = input["requests"][i]["x"].asInt(), y = input["requests"][i]["y"].asInt();
            if (x != -1) ret[id(x, y)] = 1;
        }

        //need to be rework.
        msg = input["data"].asString();

        return make_pair(ret, msg);
    }

    void Output(int x, int y, std::string msg = "", std::string log = "") {
        Json::Value ret, bp;
        Json::FastWriter writer;
        bp["x"] = x; bp["y"] = y;
        ret["response"] = bp;
        ret["data"] = msg;
        ret["debug"] = log;
        std::cout << writer.write(ret) << std::endl;
        return;
    }
}

#endif
