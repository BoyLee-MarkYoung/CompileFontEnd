//
//  Logical.h
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-19.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#ifndef __CompileFrontEnd__Logical__
#define __CompileFrontEnd__Logical__

#define lengthOfInt 64
#include <iostream>
#include "Expr.h"
#include "Temp.h"

using namespace std;


//bool 逻辑表达式类
class Logical :public Expr {
    
public:
    //含两个子表达式
    Expr *expr1, *expr2;
    
    //在创建对象时检查两个子表达式的 Type类型时候都是 bool
    Logical(Token *tok, Expr *x1, Expr *x2, string objFileName);
    Logical(){}
    
    //检查两表达式的类型时候都是 Bool 不是则返回 Type::Null
    virtual Type* check(Type *p1, Type *p2);
    
    //生成中间代码
    Expr* gen();
    
    string toString();
};
#endif /* defined(__CompileFrontEnd__Logical__) */
