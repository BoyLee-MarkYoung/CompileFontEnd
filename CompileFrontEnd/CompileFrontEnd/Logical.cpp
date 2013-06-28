//
//  Logical.cpp
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-19.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#include "Logical.h"


Type* Logical::check(Type *p1, Type *p2) {
    if ( *p1 == Type::Bool && *p2 == Type::Bool ) return &Type::Bool;
    else return &Type::Null;
}

Expr* Logical::gen() {
    int f = newlabel();
    int a = newlabel();
    Temp *temp = new Temp(type, objFileName);
    this->jumping(0,f);
    emit(temp->toString() + " = true");
    char * p_temp_char = new char[string("goto L").length()+lengthOfInt];
    sprintf(p_temp_char, "goto L%d", a);
    emit(p_temp_char);
    emitlabel(f); emit(temp->toString() + " = false");
    emitlabel(a);
    return temp;
}


string Logical::toString() {
    return expr1->toString()+" "+op->toString()+" "+expr2->toString();
}

Logical::Logical(Token *tok, Expr *x1, Expr *x2, string objFileName)
:Expr(tok, &Type::Null, objFileName), expr1(x1), expr2(x2)
{
    type = check(expr1->type, expr2->type);
    if (*type == Type::Null )
        error("type error");
}
