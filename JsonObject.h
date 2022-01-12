//
// Created by againstsky on 2022/1/12.
//

#ifndef SKYSON_JSONOBJECT_H
#define SKYSON_JSONOBJECT_H

#include "JsonToken.h"
#include <string>
#include <unordered_map>

namespace skyson {
    class JsonObject {
        union {
            std::unordered_map<std::string, void *> *field_;
            std::string *str_;
            void *nl = nullptr;
        } value_;

        int type_;
    public:
        JsonObject() {

        }

        JsonObject(int type) : type_(type) {
            if (type_ == Token::OBJ) {
                initField();
            }
        }

        void initField() {
            if (!value_.field_)
                value_.field_ = new std::unordered_map<std::string, void *>;
        }

        void put(const std::string *key, JsonObject *value) {
            type_ = value->type_;
            (*value_.field_)[*key] = value;
        }

        void setStr(std::string *str) {
            type_ = Token::STR;
            value_.str_ = str;
        }

        std::string *getStr(){
            return value_.str_;
        }

        void put(const std::string &key, void *value, int type) {
            type_ = type;
            (*value_.field_)[key] = value;
        }

        void *get(const std::string &key) {
            return (*value_.field_)[key];
        }

        void setType(int type) {
            type_ = type;
        }

        int getType() {
            return type_;
        }
    };
//    class JsonStr{
//    public:
//        std::string str;
//    };
}


#endif //SKYSON_JSONOBJECT_H
