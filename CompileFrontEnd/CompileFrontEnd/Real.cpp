//
//  Real.cpp
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-20.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#include "Real.h"
#include <sstream>

string Real::toString()
{
    std::ostringstream str;
    str << value;
    return str.str();
}