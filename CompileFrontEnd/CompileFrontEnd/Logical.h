//
//  Logical.h
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-19.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#ifndef __CompileFrontEnd__Logical__
#define __CompileFrontEnd__Logical__

#define lengthOfInt 64
#include <iostream>
#include "Expr.h"
#include "Temp.h"

using namespace std;

class Logical :public Expr {
    
public:
    Expr expr1, expr2;
    
    Logical(Token tok, Expr x1, Expr x2)
    :Expr(tok, Type::Null), expr1(x1), expr2(x2)
    {
        type = check(expr1.type, expr2.type);
        if (type == Type::Null ) error("type error");
    }
    
    Type check(Type p1, Type p2) {
        if ( p1 == Type::Bool && p2 == Type::Bool ) return Type::Bool;
        else return Type::Null;
    }
    
    Expr gen() {
        int f = newlabel();
        int a = newlabel();
        Temp temp(type);
        this->jumping(0,f);
        emit(temp.toString() + " = true");
        char * p_temp_char = new char[string("goto L").length()+lengthOfInt];
        sprintf(p_temp_char, "goto L%d", a);
        emit(p_temp_char);
        emitlabel(f); emit(temp.toString() + " = false");
        emitlabel(a);
        return temp;
    }
    
    string toString() {
        return expr1.toString()+" "+op.toString()+" "+expr2.toString();
    }
};
#endif /* defined(__CompileFrontEnd__Logical__) */
