//
//  Type.h
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-19.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#ifndef __CompileFrontEnd__Type__
#define __CompileFrontEnd__Type__

#include <iostream>
#include "Word.h"
#include "Tag.h"
#include <typeinfo>

using namespace std;

class Type :public Word {
public:
    int width;          // width is used for storage allocation
    
    Type(string s, int tag, int w)
        :Word(s, tag), width(w)
    {}
    
    static Type
    Int,
    Float,
    Char,
    Bool,
    Null;
    
    static bool numeric(Type p) {
        if (p == Type::Char || p == Type::Int || p == Type::Float) return true;
        else return false;
    }
    
    static Type* max(Type *p1, Type *p2 ) {
        if ( ! numeric(*p1) || ! numeric(*p2) ) return &Type::Null;
        else if ( *p1 == Type::Float || *p2 == Type::Float ) return &Type::Float;
        else if ( *p1 == Type::Int   || *p2 == Type::Int   ) return &Type::Int;
        else return &Type::Char;
    }
    
    bool operator==(const Type &rhs);
    
    Type& operator=(const Type &rhs);
    Type& operator=(const Word &ths);

};
#endif /* defined(__CompileFrontEnd__Type__) */
