//
//  Expr.h
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-19.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#ifndef __CompileFrontEnd__Expr__
#define __CompileFrontEnd__Expr__

#include <iostream>
#include "Node.h"
#include "Token.h"
#include "Type.h"

using namespace std;

class Expr : public Node {
public:
    Token op;
    Type type;
    
    Expr(Token tok, Type p)
    :op(tok), type(p)
    {}
    
    Expr()
    :op(Token::Null), type(Type::Null)
    {}
    
    Expr gen() { return *this; }
    Expr reduce() { return *this; }
    
    void jumping(int t, int f) { emitjumps(toString(), t, f); }
    void emitjumps(string test, int t, int f);

    string toString() { return op.toString(); }
    
    static const Expr Null;
    
    Expr& operator=(const Expr& rhs);
    bool operator==(const Expr& rhs);
    
};

#endif /* defined(__CompileFrontEnd__Expr__) */
