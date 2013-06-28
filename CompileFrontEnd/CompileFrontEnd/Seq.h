//
//  Seq.h
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-21.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#ifndef __CompileFrontEnd__Seq__
#define __CompileFrontEnd__Seq__

#include <iostream>
#include "Stmt.h"


//语句序列
class Seq : public Stmt {
    
    
public:
    Stmt *stmt1; Stmt *stmt2;
    
    Seq(Stmt *s1, Stmt *s2, string fn)
    :stmt1(s1), stmt2(s2), Stmt(fn)
    {}
    
    Seq()
    :stmt1(NULL), stmt2(NULL)
    {}
    
    void gen(int b, int a);
};
#endif /* defined(__CompileFrontEnd__Seq__) */
