//
//  Env.h
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-19.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#ifndef __CompileFrontEnd__Env__
#define __CompileFrontEnd__Env__

#include <iostream>
#include "Token.h"
#include "Id.h"
#include <map>
#include "Word.h"
//#include "Word.h"


using namespace std;
struct classcomp {
    bool operator() (Token* lhs, Token* rhs) const
    {
        Word *lhw = dynamic_cast<Word*>(lhs);
        Word *rhw = dynamic_cast<Word*>(rhs);
        bool isWordSame = true;
        if ( lhw && rhw)
        {
            isWordSame = (lhw->lexeme < rhw->lexeme);
        }
        return (lhs->tag <= rhs->tag) && isWordSame;
    }
};


class Env {
private:
    map<Token*, Id, classcomp> table;
    
protected:
    Env * prev;
    
public:
    Env(Env *n) { prev = n; }
    
    
    Env()
    :prev(NULL)
    {
        //cout << "default Env constructing";
    }
    
    void put(Token *w, Id i)
    {
        table.insert(make_pair(w,i));
    }

    Id get(Token *w);
    
    static Env Null;
    
    Env& operator=(const Env& rhs);
    bool operator==(const Env& rhs);
    bool operator!=(const Env& rhs);
};
#endif /* defined(__CompileFrontEnd__Env__) */
