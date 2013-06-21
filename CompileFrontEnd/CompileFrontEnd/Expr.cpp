//
//  Expr.cpp
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-19.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#include "Expr.h"

void Expr::emitjumps(string test, int t, int f) {
    char *temp = new char[test.length()+string("if ").length()+string(" goto L").length()];
    if( t != 0 && f != 0 )
    {
        sprintf(temp, "if %s goto L%d",test.c_str(), t);
        emit(temp);
        sprintf(temp, "goto L%d",f);
        emit(temp);
    }
    else if( t != 0 )
    {
        sprintf(temp, "if %s goto L%d",test.c_str(), t);
        emit(temp);
    }
    else if( f != 0 )
    {
        sprintf(temp, "iffalse %s goto L%d",test.c_str(), f);
        emit(temp);
    }
    else ; // nothing since both t and f fall through
}

Expr& Expr::operator=(const Expr &rhs) {
    this->lexline = rhs.lexline;
    this->op = rhs.op;
    this->type = rhs.type;
    return *this;
}

bool Expr::operator==(const Expr& rhs)
{
    return this->op == rhs.op &&
    this->type == rhs.type &&
    (Node)(*this) == (Node)(rhs);
}

