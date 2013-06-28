//
//  Rel.h
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-19.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#ifndef __CompileFrontEnd__Rel__
#define __CompileFrontEnd__Rel__

#include <iostream>
#include "Logical.h"
#include "Array.h"
#include <typeinfo>

class Rel : public Logical {
    
    
public:
    Rel(Token *tok, Expr *x1, Expr *x2, string fn)
//    :Logical(tok, x1, x2)
    {
        this->op = tok;
        this->type = &Type::Null;
        this->expr1 = x1;
        this->expr2 = x2;
        this->objFileName = fn;
        this->type = check(expr1->type, expr2->type);
        if (*type == Type::Null )
            error("type error");
    }
    
    Type* check(Type *p1, Type* p2) {
        if ( typeid(p1) == typeid(Array) || typeid(p2) == typeid(Array) ) return &Type::Null;
        else if( *p1 == *p2 ) return &Type::Bool;
        else return &Type::Null;
    }
    
    void jumping(int t, int f) {
        Expr *a = expr1->reduce();
        Expr *b = expr2->reduce();
        string test = a->toString() + " " + op->toString() + " " + b->toString();
        emitjumps(test, t, f);
    }
};
#endif /* defined(__CompileFrontEnd__Rel__) */
