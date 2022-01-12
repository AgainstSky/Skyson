//
// Created by againstsky on 2022/1/12.
//

#include "Skyson.h"
#include <sstream>
#include <string>
#include <iostream>

namespace skyson {

    std::string &trim(std::string &str) {
        str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
//        str.erase(0, str.find_last_not_of(' '));
//        str.erase(str.find_first_not_of(' ') + 1);
        return str;
    }

    void parseObject(std::stringstream &ss, JsonObject *jsonObject);

    void parseNull(std::stringstream &ss) {
        char c;
        std::string nStr;
        while (ss.get(c)) {
            c = tolower(c);
            if (c == ',') {
                if (trim(nStr) != "ull") {
                    throw "error parse null token";
                }
                return;
            } else {
                nStr += c;
            }
        }
    }

    void parseStr(std::stringstream &ss, std::string *str) {
        char c, prev;
        while (ss.get(c)) {
            if (c == '"' && prev != '\\') {
                return;
            } else {
                (*str) += c;
                prev = c;
            }
        }
    }

    bool parseBool(std::stringstream &ss, char prev) {
        std::string boolStr;
        boolStr += tolower(prev);
        char c;
        while (ss.get(c)) {
            c = tolower(c);
            //todo:: 有个bug，未处理结尾是}的情况
            if (c == ',' || c == '}') {
                if (c=='}'){
                    ss.seekg(-1,std::ios_base::cur);
                }
                if (trim(boolStr) != "false" ) {
                    return false;
                } else if ( trim(boolStr) != "true"){
                    return true;
                }
                std::cerr << "error parse bool token\n";
                return false;
            } else {
                boolStr += c;
            }
        }
    }

    void parseValue(std::stringstream &ss, JsonObject *jsonObject) {
        char c;
        while (ss.get(c)) {
            switch (c) {
                case '"': {
                    auto str = new std::string;
                    parseStr(ss, str);
                    jsonObject->setStr(str);
                }
                    return;
                case '{':
                    jsonObject->setType(Token::OBJ);
                    jsonObject->initField();
                    parseObject(ss, jsonObject);
                    return;
                case '[':
                    break;
                case 'N':
                case 'n':
                    parseNull(ss);
                    jsonObject->setType(Token::NL);
                    return;
                case 'T':
                case 't':
                case 'f':
                case 'F':
                    bool  bl = parseBool(ss, c);
                    jsonObject->setType(Token::BOOL);
                    return;
            }
        }
    }

    void parseObject(std::stringstream &ss, JsonObject *jsonObject) {
        char c;
        std::string *key = nullptr;
        bool closeObject = false;
        while (ss.get(c)) {
            switch (c) {
                case '"':
                    key = new std::string ;
                    parseStr(ss, key);
                    break;
                case ':': {
                    JsonObject *childJsonObj = new JsonObject;
                    parseValue(ss, childJsonObj);
                    //todo::判断key是否为空
                    jsonObject->put(key, childJsonObj);
                    break;
                }
                case '}':
                    closeObject = true;
                    break;
                default:
                    std::cout << c << std::endl;
                    break;
            }
        }
        if (!closeObject) {
            std::cerr << "error object not close";
        }
    }

    JsonObject *parse(const std::string &jsonStr) {
        auto jobj = new JsonObject;
        jobj->setType(Token::OBJ);
        jobj->initField();
        std::stringstream ss(jsonStr);
        char c;
        while (ss.get(c)) {
            if (c == '{') {
                parseObject(ss, jobj);
            } else {
                std::cout << c << std::endl;
            }
        }
        return jobj;
    }


}