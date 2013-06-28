//
//  Stmt.h
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-19.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#ifndef __CompileFrontEnd__Stmt__
#define __CompileFrontEnd__Stmt__

#include <iostream>

#include "Node.h"

using namespace std;


//语句类
class Stmt : public Node
{
public:
    Stmt(string objFileName)
    :Node(objFileName)
    {}
    
    Stmt()
    {}
    
    static Stmt Null;

    // 调用时的参数是语句的开始处标号和语句的下一条标号
    virtual void gen(int b, int a) {}  
    int after = 0;                   // while & Do 用它来break
    static Stmt *Enclosing;  // 在语法分析时被用于跟踪外层构造

};
#endif /* defined(__CompileFrontEnd__Stmt__) */
