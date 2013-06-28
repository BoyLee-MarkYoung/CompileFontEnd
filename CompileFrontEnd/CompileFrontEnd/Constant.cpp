//
//  Constant.cpp
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-20.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#include "Constant.h"



bool Constant::operator==(const Constant &rhs)
{
    return (this->type == rhs.type) && (this->op == rhs.op) && (this->lexline == rhs.lexline);
}

//对于常量的跳转，直接生成goto语句
void Constant::jumping(int t, int f) {
    ostringstream str;
    
    if ( *this == Constant(&Word::True, &Type::Bool, objFileName)
        && t != 0 )
    {
        str << "goto L" << t;
        emit(str.str());
    }
    else if ( *this == Constant(&Word::False, &Type::Bool, objFileName) && f != 0)
    {
        str << "goto L" << f;
        emit(str.str());
    }
}