//
//  Not.h
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-20.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#ifndef __CompileFrontEnd__Not__
#define __CompileFrontEnd__Not__

#include <iostream>
#include "Logical.h"


class Not : public Logical {
public:
    Not(Token *tok, Expr *x2)
    :Logical(tok, x2, x2)
    {}
    
    void jumping(int t, int f) { expr2->jumping(f, t); }
    
    string toString() { return op->toString()+" "+expr2->toString(); }
};
#endif /* defined(__CompileFrontEnd__Not__) */
