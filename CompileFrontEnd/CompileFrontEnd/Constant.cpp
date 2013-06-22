//
//  Constant.cpp
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-20.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#include "Constant.h"

Constant
Constant::True  = Constant(&Word::True,  &Type::Bool),
Constant::False = Constant(&Word::False, &Type::Bool);



bool Constant::operator==(const Constant &rhs)
{
    return (this->type == rhs.type) && (this->op == rhs.op) && (this->lexline == rhs.lexline);
}