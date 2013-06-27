//
//  Else.h
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-21.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#ifndef __CompileFrontEnd__Else__
#define __CompileFrontEnd__Else__

#include <iostream>
#include "Stmt.h"
#include "Expr.h"
#include <sstream>

class Else :public Stmt{
    
    
public:
    Expr *expr; Stmt *stmt1, *stmt2;
    
    Else(Expr *x, Stmt *s1, Stmt *s2);
    
    void gen(int b, int a);
};
#endif /* defined(__CompileFrontEnd__Else__) */
