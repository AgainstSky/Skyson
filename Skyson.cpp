//
// Created by againstsky on 2022/1/12.
//

#include "Skyson.h"
#include <sstream>
#include <string>
#include <iostream>

namespace skyson {

    std::string& trim(std::string & str){
        str.erase(0,str.find_last_not_of(' '));
        str.erase(str.find_first_not_of(' ')+1);
        return str;
    }

    void parseObject(std::stringstream &ss, JsonObject *jsonObject);

    void parseNull(std::stringstream &ss) {
        char c;
        std::string nStr;
        while (ss.get(c)) {
            c = tolower(c);
            if (c==','){
                if (trim(nStr) != "ull"){
                    throw "error parse null token";
                }
            } else{
                nStr+=c;
            }
        }
    }

    void parseStr(std::stringstream &ss, std::string &str) {
        char c, prev;
        while (ss.get(c)) {
            if (c == '"' && prev != '/') {
                return;
            } else {
                str += c;
                prev = c;
            }
        }
    }

    void parseValue(std::stringstream &ss, JsonObject *jsonObject) {
        char c;
        while (ss.get(c)) {
            switch (c) {
                case '"': {
                    std::string str;
                    parseStr(ss, str);
                    //todo::这里是不是要动态分配str
                    jsonObject->setStr(&str);
                }
                    break;
                case '{':
                    jsonObject->setType(Token::OBJ);
                    jsonObject->initField();
                    parseObject(ss, jsonObject);
                    break;
                case '[':
                    break;
                case 'N':
                case 'n':
                    parseNull(ss);
                    jsonObject->setType(Token::NL);
                    break;
                case 'T':
                case 't':
                case 'f':
                case 'F':
                    break;
            }
        }
    }

    void parseObject(std::stringstream &ss, JsonObject *jsonObject) {
        char c;
        std::string key;
        while (ss.get(c)) {
            switch (c) {
                case '"':
                    parseStr(ss, key);
                    break;
//                case '{': {
//                    auto *childJsonObj = new JsonObject;
//                    parseObject(ss, childJsonObj);
//                    //todo::判断key是否为空
//                    jsonObject->put(key, childJsonObj, Token::OBJ);
//                }
//                    break;
                case ':': {
                    auto childJsonObj = new JsonObject;
                    parseValue(ss, childJsonObj);
                    //todo::判断key是否为空
                    jsonObject->put(key, childJsonObj);
                }

                    break;
                case '}':
                    return;
            }
        }
    }

    JsonObject *parse(const std::string &jsonStr) {
        auto jele = new JsonObject;
        std::stringstream ss(jsonStr);
        char c;
        while (ss.get(c)) {
            if (c == '{') {
                parseObject(ss, jele);
            } else {
                std::cout << c << std::endl;
            }
        }
        return nullptr;
    }


}