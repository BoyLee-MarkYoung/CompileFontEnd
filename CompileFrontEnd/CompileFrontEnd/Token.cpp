//
//  Token.cpp
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-19.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#include "Token.h"
#include <sstream>
#include "Word.h"

Token Token::Null;

string Token::toString() {
    ostringstream ss;
    ss << (char)tag ;
    return ss.str();
}

bool Token::operator==(const Token &rhs)
{
    if (this->tag == rhs.tag) {
//        cout << "same Token" << endl;
        return true;
    } else {
//        cout << "diff Token" << endl;
        return false;
    }
}

bool Token::operator==( Token* rhs)
{
    Word *lhw = dynamic_cast<Word *>(this);
    Word *rhw = dynamic_cast<Word *>(rhs);
    if ( lhw && rhw) {
        return (lhw->tag == rhw->tag && lhw->lexeme == rhw->lexeme);
    }
    return *this==*rhs;
}

Token& Token::operator=(const Token &rhs)
{
    this->tag = rhs.tag;
    return *this;
}

//Token::operator Type()
//{
//    return Type()
//}


/*
Token::operator Word() {
    return Word("", tag);
}

*/