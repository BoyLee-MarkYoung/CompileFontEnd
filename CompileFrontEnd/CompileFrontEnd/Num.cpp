//
//  Num.cpp
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-20.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#include "Num.h"
#include <sstream>

string Num::toString()
{
    std::ostringstream str;
    str << value;
    return str.str();
}