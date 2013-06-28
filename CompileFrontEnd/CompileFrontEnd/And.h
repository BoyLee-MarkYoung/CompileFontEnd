//
//  And.h
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-19.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#ifndef __CompileFrontEnd__And__
#define __CompileFrontEnd__And__

#include <iostream>
#include "Logical.h"

class And :public Logical{

    
public:
    And(Token *tok, Expr *x1, Expr *x2, string fn)
    :Logical(tok,x1,x2, fn)
    {}
    
    void jumping(int t, int f) {
        int label = f != 0 ? f : newlabel();
        expr1->jumping(0, label);
        expr2->jumping(t,f);
        if( f == 0 ) emitlabel(label);
    }
};

#endif /* defined(__CompileFrontEnd__And__) */
