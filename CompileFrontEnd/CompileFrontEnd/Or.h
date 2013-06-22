//
//  Or.h
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-19.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#ifndef __CompileFrontEnd__Or__
#define __CompileFrontEnd__Or__

#include <iostream>
#include "Logical.h"

class Or :public Logical {
public:
    Or(Token *tok, Expr *x1, Expr *x2)
    :Logical(tok, x1, x2)
    {}
    
    void jumping(int t, int f) {
        int label = t != 0 ? t : newlabel();
        expr1->jumping(label, 0);
        expr2->jumping(t,f);
        if( t == 0 ) emitlabel(label);
    }
    
};


#endif /* defined(__CompileFrontEnd__Or__) */
