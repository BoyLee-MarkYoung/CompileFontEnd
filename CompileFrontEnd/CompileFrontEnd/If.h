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
    Expr *expr; Stmt *stmt;
    
    If(Expr *x, Stmt *s, string fn);
    
    void gen(int b, int a);
};
#endif /* defined(__CompileFrontEnd__If__) */
