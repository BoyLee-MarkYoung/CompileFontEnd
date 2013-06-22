//
//  Do.h
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-21.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#ifndef __CompileFrontEnd__Do__
#define __CompileFrontEnd__Do__

#include <iostream>
#include "Stmt.h"
#include "Expr.h"

class Do :public Stmt {
    
    
public:
    Expr *expr; Stmt *stmt;
    
    Do() { expr = &Expr::Null; stmt = &Stmt::Null; }
    
    void init(Stmt *s, Expr *x) {
        expr = x; stmt = s;
        if( *(expr->type) != Type::Bool ) expr->error("boolean required in do");
    }
    
    void gen(int b, int a) {
        after = a;
        int label = newlabel();   // label for expr
        stmt->gen(b,label);
        emitlabel(label);
        expr->jumping(b,0);
    }
};
#endif /* defined(__CompileFrontEnd__Do__) */
