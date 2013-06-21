//
//  Id.cpp
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-19.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#include "Id.h"


//const Id Id::Null = Id(Word::Null, Type::Null, 0);

bool Id::operator==(const Id &rhs)
{
    return this->offset == rhs.offset &&
    (Expr)(*this) == (Expr)rhs;
//    this->lexline == rhs.lexline &&
//    this->op == rhs.op &&
//    this->type == rhs.type
}

bool Id::operator!=(const Id& rhs)
{
    return !((*this == rhs));
}
