//
//  While.h
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-21.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#ifndef __CompileFrontEnd__While__
#define __CompileFrontEnd__While__

#include <iostream>
#include "Stmt.h"
#include "Expr.h"
#include <sstream>

class While : public Stmt {
    
    
public:
    Expr *expr; Stmt *stmt;
    
    While() { expr = &Expr::Null; stmt = &Stmt::Null; }
    
    void init(Expr *x, Stmt *s) {
        expr = x;  stmt = s;
        if( *(expr->type) != Type::Bool ) expr->error("boolean required in while");
    }
    void gen(int b, int a) {
        after = a;                // save label a
        expr->jumping(0, a);
        int label = newlabel();   // label for stmt
        emitlabel(label); stmt->gen(label, b);
        ostringstream ss;
        ss << "goto L" << b;
        emit(ss.str());
    }
};
#endif /* defined(__CompileFrontEnd__While__) */
