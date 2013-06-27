//
//  Seq.cpp
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-21.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#include "Seq.h"
void Seq::gen(int b, int a) {
    if ( stmt1 == NULL || *stmt1 == Stmt::Null) stmt2->gen(b, a);
    else if ( stmt2 == NULL || *stmt2 == Stmt::Null) stmt1->gen(b, a);
    else {
        int label = newlabel();
        stmt1->gen(b,label);
        emitlabel(label);
        stmt2->gen(label,a);
    }
}