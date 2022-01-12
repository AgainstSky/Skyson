//
// Created by againstsky on 2022/1/12.
//

#ifndef SKYSON_JSONTOKEN_H
#define SKYSON_JSONTOKEN_H
namespace skyson {

    enum Token {
        BOOL = 0,
        STR,
        NUM,
        ARRAY,
        OBJ,
        NL,
    };
}
#endif //SKYSON_JSONTOKEN_H
