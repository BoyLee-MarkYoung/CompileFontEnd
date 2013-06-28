//
//  Constant.h
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-20.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#ifndef __CompileFrontEnd__Constant__
#define __CompileFrontEnd__Constant__

#include <iostream>
#include "Expr.h"
#include "Num.h"
#include "Type.h"
#include "Word.h"
#include <sstream>
#include "Token.h"  

class Constant :public Expr {
    
    
public:
    Constant(Token *tok, Type *p, string fn)
    :Expr(tok, p, fn)
    {}
    
    Constant(Token *tok, Type *p)
    :Expr(tok, p)
    {}
    
    Constant(int i, string objFileName)
    :Expr(new Num(i), &Type::Int, objFileName)
    {}
    
    void jumping(int t, int f);
    
    bool operator==(const Constant &rhs);

};
#endif /* defined(__CompileFrontEnd__Constant__) */
