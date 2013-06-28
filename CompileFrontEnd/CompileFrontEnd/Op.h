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

//提供一个 reduce 的一个实现。这个类的字累包括：表示算数运算符的子类　Arith,表示单目运算符的子类 Unary和表示数组访问的子类 Access。
class Op : public Expr {
public:
    Op(Token *tok, Type *p, string objFileName)
    :Expr(tok, p, objFileName)
    {}
    
    Op(){}
    
//reduce先调用gen生成临时变量，以便后面使用
    Expr *reduce();
};
#endif /* defined(__CompileFrontEnd__Op__) */
