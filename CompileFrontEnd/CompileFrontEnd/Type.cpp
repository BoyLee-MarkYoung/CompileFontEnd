//
//  Type.cpp
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-19.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#include "Type.h"


bool Type::operator==(const Type &rhs) {
    if (this->width == rhs.width &&
        this->lexeme == rhs.lexeme ) {
        return true;
    }
    return false;
}

Type& Type::operator=(const Type &rhs)
{
    this->lexeme = rhs.lexeme;
    this->width = rhs.width;
    return *this;
}


const Type
Type::Int   = Type( "int",   Tag::BASIC, 4 ),
Type::Float = Type( "float", Tag::BASIC, 8 ),
Type::Char  = Type( "char",  Tag::BASIC, 1 ),
Type::Bool  = Type( "bool",  Tag::BASIC, 1 ),
Type::Null  = Type( "", Tag::Null, 0);