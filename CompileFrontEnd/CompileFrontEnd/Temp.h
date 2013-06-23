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
class Temp :public Expr{
public:
    static int count;
    int number;
    
    Temp(Type *p)
    : Expr(&Word::temp, p), number(++count)
    {
    }
    

    string toString()
    {
        ostringstream str;
        str << "t" << number;
        return str.str();
    }
    
};
#endif /* defined(__CompileFrontEnd__Temp__) */
