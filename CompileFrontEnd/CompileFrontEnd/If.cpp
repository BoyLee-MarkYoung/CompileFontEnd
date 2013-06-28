//
//  If.cpp
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-21.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#include "If.h"

If::If(Expr *x, Stmt *s, string fn)
:expr(x), stmt(s), Stmt(fn)
{
    expr = x;  stmt = s;
    if( *(expr->type) != Type::Bool )
        expr->error("boolean required in if");
}


void If::gen(int b, int a) {
    int label = newlabel(); // stmt 的代码的标号
    expr->jumping(0, a);     // 为真时控制流穿越，为假时转向a
    emitlabel(label);
    stmt->gen(label, a);
}