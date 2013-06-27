//
//  Do.cpp
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-21.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#include "Do.h"


void Do::gen(int b, int a) {
    after = a;
    int label = newlabel();   // label for expr
    stmt->gen(b,label);
    emitlabel(label);
    expr->jumping(b,0);
}

void Do::init(Stmt *s, Expr *x) {
    expr = x; stmt = s;
    if( *(expr->type) != Type::Bool ) expr->error("boolean required in do");
}