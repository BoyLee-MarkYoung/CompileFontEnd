//
//  Stmt.h
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-19.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#ifndef __CompileFrontEnd__Stmt__
#define __CompileFrontEnd__Stmt__

#include <iostream>

#include "Node.h"

using namespace std;

class Stmt : public Node
{
public:
    Stmt() { }
    
    static Stmt Null;
    
    void gen(int b, int a) {} // called with labels begin and after
    
    int after = 0;                   // saves label after
    static Stmt Enclosing;  // used for break stmts

};
#endif /* defined(__CompileFrontEnd__Stmt__) */
