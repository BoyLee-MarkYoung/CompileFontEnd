//
//  Env.cpp
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-19.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#include "Env.h"

using namespace std;


Id Env::get(Token w) {
    for( Env e = *this; e != Env::Null; e = *(e.prev) ) {
        Id found = (Id)(e.table[w]);
        if( found != Id::Null ) return found;
    }
    return Id::Null;
}




//Env Env::Null;

Env& Env::operator=(const Env& rhs)
{
    this->prev = rhs.prev;
    this->table = rhs.table;
    return *this;
}

bool Env::operator==(const Env &rhs)
{
    return this->prev == rhs.prev;
}

bool Env::operator!=(const Env &rhs)
{
    return !(*this==rhs);
}

//const Env Env::Null;