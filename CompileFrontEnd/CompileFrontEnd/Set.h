//
//  Set.h
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-19.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#ifndef __CompileFrontEnd__Set__
#define __CompileFrontEnd__Set__

#include <iostream>
#include "Stmt.h"
#include "Id.h"

class Set :public Stmt{
public:
    Id id;
    Expr *expr;
    
    Set(Id i, Expr *x)
    :id(i), expr(x)
    {
        if ( *(check(id.type, expr->type)) == Type::Null )
            error("type error");
    }
    
    Type* check(Type *p1, Type *p2) {
        if ( Type::numeric(*p1) && Type::numeric(*p2) ) return p2;
        else if ( *p1 == Type::Bool && *p2 == Type::Bool ) return p2;
        else return &Type::Null;
    }
    
    void gen(int b, int a) {
        emit( id.toString() + " = " + expr->gen()->toString());
    }
    
    
};
#endif /* defined(__CompileFrontEnd__Set__) */
