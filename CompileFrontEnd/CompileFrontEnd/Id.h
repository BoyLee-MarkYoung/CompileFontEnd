//
//  Id.h
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-19.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#ifndef __CompileFrontEnd__Id__
#define __CompileFrontEnd__Id__

#include <iostream>
#include "Word.h"
#include "Type.h"
#include "Expr.h"

using namespace std;


//标示符类
class Id :public Expr
{
public:
    
    //标示符在符号表中的偏移量
    int offset;     // relative address
    
    
    Id(Word *idd, Type *p, int b, string objFileName)
    :Expr(idd, p, objFileName), offset(b)
    {}
    
    Id(){offset = 0;}
    
    
    const static Id Null;
    bool operator==(const Id& rhs);
    bool operator!=(const Id& rhs);
    Id& operator=(const Id& rhs);


};
#endif /* defined(__CompileFrontEnd__Id__) */
