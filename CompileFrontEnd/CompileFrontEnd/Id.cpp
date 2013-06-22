//
//  Id.cpp
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-19.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#include "Id.h"
#include <sstream>

const Id Id::Null;

bool Id::operator==(const Id &rhs)
{
    if (this->offset == rhs.offset &&
        (Expr)(*this) == (Expr)rhs)
    {
//        cout << "same Id";
        return true;
    } else {
//        cout << "dif Id";
        return false;
    }
//    this->lexline == rhs.lexline &&
//    this->op == rhs.op &&
//    this->type == rhs.type
}

bool Id::operator!=(const Id& rhs)
{
    return !((*this == rhs));
}


Id& Id::operator=(const Id& rhs) {
    this->lexline = rhs.lexline;
    this->offset = rhs.offset;
    this->op = rhs.op;
    this->type = rhs.type;
    return *this;
}
/*
string Id::toString() {
    ostringstream ss;
    ss << op->toString() << offset;
    return ss.str();
}*/