//
//  Op.cpp
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-19.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#include "Op.h"


Expr* Op::reduce()
{
    Expr *x = gen();
    Temp *t = new Temp(type, objFileName);
    emit( t->toString() + " = " + x->toString() );
    return t;
}