//
//  Else.cpp
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-21.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#include "Else.h"


void Else::gen(int b, int a) {
    int label1 = newlabel();   // label1 for stmt1
    int label2 = newlabel();   // label2 for stmt2
    expr->jumping(0,label2);    // fall through to stmt1 on true
    emitlabel(label1); stmt1->gen(label1, a);
    ostringstream ss;
    ss << "goto L" << a;
    emit(ss.str());
    emitlabel(label2); stmt2->gen(label2, a);
}

Else::Else(Expr *x, Stmt *s1, Stmt *s2) {
    expr = x; stmt1 = s1; stmt2 = s2;
    if( *(expr->type) != Type::Bool ) expr->error("boolean required in if");
}