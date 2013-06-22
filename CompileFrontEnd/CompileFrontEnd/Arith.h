//
//  Arith.h
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-19.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#ifndef __CompileFrontEnd__Arith__
#define __CompileFrontEnd__Arith__

#include <iostream>
#include "Op.h"

class Arith :public Op {
    
    
public:
    Expr *expr1, *expr2;
    
    Arith(Token *tok, Expr *x1, Expr *x2)
    : Op(tok, &Type::Null), expr1(x1), expr2(x2)
    {
        type = Type::max(expr1->type, expr2->type);
        if (*type == Type::Null ) error("type error");
    }
    
    Expr gen() {
        return Arith(op, expr1->reduce(), expr2->reduce());
    }
    
    string toString() {
        return expr1->toString()+" "+op->toString()+" "+expr2->toString();
    }
};
#endif /* defined(__CompileFrontEnd__Arith__) */
