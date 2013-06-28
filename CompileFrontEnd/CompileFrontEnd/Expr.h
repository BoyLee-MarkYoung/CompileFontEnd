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


//表达式类
class Expr : public Node {
public:
    //表达式单元
    Token *op;
    
    //表达式类型
    Type *type;
    
    // constructor...
    Expr(Token *tok, Type *p, string objFileName)
    :op(tok), type(p), Node(objFileName)
    {}
    
    Expr(Token *tok, Type *p)
    :op(tok), type(p)
    {}
    
    Expr()
    :op(&Token::Null), type(&Type::Null)
    {}
    
    //生成语句函数
    virtual Expr* gen() { return this; }
    
    //规约函数
    virtual Expr* reduce() { return this; }
    
    //bool 语句跳转
    virtual void jumping(int t, int f) { emitjumps(toString(), t, f); }
    virtual void emitjumps(string test, int t, int f);

    
    virtual string toString() { return op->toString(); }
    
    static Expr Null;
    
    Expr& operator=(const Expr& rhs);
    bool operator==(const Expr& rhs);
    
};

#endif /* defined(__CompileFrontEnd__Expr__) */
