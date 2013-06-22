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

class Seq : public Stmt {
    
    
public:
    Stmt *stmt1; Stmt *stmt2;
    
    Seq(Stmt *s1, Stmt *s2)
    :stmt1(s1), stmt2(s2)
    {}
    
    Seq()
    :stmt1(NULL), stmt2(NULL)
    {}
    
    void gen(int b, int a) {
        if ( stmt1 == NULL ) stmt2->gen(b, a);
        else if ( stmt2 == NULL ) stmt1->gen(b, a);
        else {
            int label = newlabel();
            stmt1->gen(b,label);
            emitlabel(label);
            stmt2->gen(label,a);
        }
    }
};
#endif /* defined(__CompileFrontEnd__Seq__) */
