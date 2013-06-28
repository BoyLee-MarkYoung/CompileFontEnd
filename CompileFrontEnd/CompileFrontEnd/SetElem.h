//
//  SetElem.h
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-19.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#ifndef __CompileFrontEnd__SetElem__
#define __CompileFrontEnd__SetElem__

#include <iostream>
#include "Stmt.h"
#include "Id.h"
#include "Expr.h"
#include "Access.h"
#include "Array.h"
#include <typeinfo>

class SetElem :public Stmt{
public:
    Id array;
    Expr *index;
    Expr *expr;
    
    SetElem(Access *x, Expr *y, string fn)
    :array(x->array), index(x->index), expr(y), Stmt(fn)
    {
        if ( *(check(x->type, expr->type)) == Type::Null )
            error("type error");
    }
    
    
    Type* check(Type *p1, Type *p2) {
        if ( typeid(p1) == typeid(Array) || typeid(p2) == typeid(Array) ) return &Type::Null;
        else if ( *p1 == *p2 ) return p2;
        else if ( Type::numeric(*p1) && Type::numeric(*p2) ) return p2;
        else return &Type::Null;
    }
    
    void gen(int b, int a) {
        string s1 = index->reduce()->toString();
        string s2 = expr->reduce()->toString();
        emit(array.toString() + " [ " + s1 + " ] = " + s2);
    }
    
};
#endif /* defined(__CompileFrontEnd__SetElem__) */
