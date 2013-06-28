//
//  Temp.cpp
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-19.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#include "Temp.h"

map<string, int> Temp::countMultiFile;

//int Temp::count = 0;

string Temp::toString()
{
    ostringstream str;
    str << "t" << number;
    return str.str();
}