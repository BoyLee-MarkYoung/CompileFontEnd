//
//  Temp.h
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-19.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#ifndef __CompileFrontEnd__Temp__
#define __CompileFrontEnd__Temp__

#include <iostream>
#include "Expr.h"
#include <sstream>

using namespace std;

//临时变量类
class Temp :public Expr{
public:
    
    //记录各自输出文件的变量数
    static map<string, int> countMultiFile;
    
    //当前对象的下标
    int number;
    
    Temp(Type *p, string objFileName)
    : Expr(&Word::temp, p, objFileName), number(++countMultiFile[objFileName])
    {}
    

    string toString();
    
};
#endif /* defined(__CompileFrontEnd__Temp__) */
