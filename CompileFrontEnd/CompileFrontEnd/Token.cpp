//
//  Token.cpp
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-19.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#include "Token.h"

string Token::toString() {
    char temp[64];
    sprintf(temp, "%d",tag);
    return string(temp);
}

bool Token::operator==(const Token &rhs)
{
    return (this->tag == rhs.tag);
}


Token& Token::operator=(const Token &rhs)
{
    this->tag = rhs.tag;
    return *this;
}


/*
Token::operator Word() {
    return Word("", tag);
}

*/