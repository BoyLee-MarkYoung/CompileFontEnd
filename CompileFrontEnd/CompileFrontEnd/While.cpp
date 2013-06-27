//
//  While.cpp
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-21.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#include "While.h"


void While::init(Expr *x, Stmt *s) {
    expr = x;  stmt = s;
    if( *(expr->type) != Type::Bool ) expr->error("boolean required in while");
}

void While::gen(int b, int a) {
    after = a;                // save label a
    expr->jumping(0, a);
    int label = newlabel();   // label for stmt
    emitlabel(label); stmt->gen(label, b);
    ostringstream ss;
    ss << "goto L" << b;
    emit(ss.str());
}