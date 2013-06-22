//
//  Unary.h
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-20.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#ifndef __CompileFrontEnd__Unary__
#define __CompileFrontEnd__Unary__

#include <iostream>
#include "Op.h"
#include "Type.h"
class Unary :public Op {
    
    
public:
    Expr *expr;
    
    Unary(Token *tok, Expr *x)     // handles minus, for ! see Not
    :Op(tok, &Type::Null),expr(x)
    {
        type = Type::max(&Type::Int, expr->type);
        if (*type == Type::Null ) error("type error");
    }
    
    Expr* gen() { return new Unary(op, expr->reduce()); }
    
    string toString() { return op->toString()+" "+expr->toString(); }
};

#endif /* defined(__CompileFrontEnd__Unary__) */
