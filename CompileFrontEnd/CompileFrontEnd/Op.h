//
//  Op.h
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-19.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#ifndef __CompileFrontEnd__Op__
#define __CompileFrontEnd__Op__

#include <iostream>
#include "Token.h"
#include "Type.h"
#include "Expr.h"
#include "Temp.h"

using namespace std;

class Op : public Expr {
public:
    Op(Token tok, Type p)
    :Expr(tok, p)
    {}
    
    Op(){}
    
    Expr reduce();
};
#endif /* defined(__CompileFrontEnd__Op__) */
