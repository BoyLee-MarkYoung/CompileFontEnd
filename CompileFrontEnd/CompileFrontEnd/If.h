//
//  If.h
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-21.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#ifndef __CompileFrontEnd__If__
#define __CompileFrontEnd__If__

#include <iostream>
#include "Stmt.h"
#include "Expr.h"

class If : public Stmt {
    
    
public:
    Expr expr; Stmt stmt;
    
    If(Expr x, Stmt s)
    :expr(x), stmt(s)
    {
        expr = x;  stmt = s;
        if( expr.type != Type::Bool ) expr.error("boolean required in if");
    }
    
    void gen(int b, int a) {
        int label = newlabel(); // label for the code for stmt
        expr.jumping(0, a);     // fall through on true, goto a on false
        emitlabel(label); stmt.gen(label, a);
    }
};
#endif /* defined(__CompileFrontEnd__If__) */
