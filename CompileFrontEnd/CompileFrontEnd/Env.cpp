//
//  Env.cpp
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-19.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#include "Env.h"
#include "Id.h"

using namespace std;


Id Env::get(Token *w) {
    for( Env* e = this; e != NULL; e = e->prev) {
        Id found = e->table[w];
//        cout << "found info: " << found.offset << found.op.tag << found.lexline;
//        cout << "in get id";
        if( found != Id::Null )
        {
//            cout << "found it";
            return found;
        }
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
    return (this->prev == rhs.prev);
}

bool Env::operator!=(const Env &rhs)
{
    return !(*this==rhs);
}

Env Env::Null;