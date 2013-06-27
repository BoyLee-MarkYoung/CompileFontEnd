//
//  Do.h
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-21.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#ifndef __CompileFrontEnd__Do__
#define __CompileFrontEnd__Do__

#include <iostream>
#include "Stmt.h"
#include "Expr.h"

class Do :public Stmt {
    
    
public:
    Expr *expr; Stmt *stmt;
    
    Do() { expr = &Expr::Null; stmt = &Stmt::Null; }
    
    void init(Stmt *s, Expr *x);
    
    void gen(int b, int a);
};
#endif /* defined(__CompileFrontEnd__Do__) */
