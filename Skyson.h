//
// Created by againstsky on 2022/1/12.
//

#ifndef SKYSON_SKYSON_H
#define SKYSON_SKYSON_H
#include "JsonObject.h"
namespace skyson{
    JsonObject* parse(const std::string& jsonStr);
//    std::string& toJson(const JsonObject * const jsonObject);
}



#endif //SKYSON_SKYSON_H
