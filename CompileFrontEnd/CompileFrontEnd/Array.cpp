//
//  Array.cpp
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-19.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#include "Array.h"


string Array::toString()
{
    char * p_ch = new char[100];
    sprintf(p_ch, "[%d] ", size);
    
    cout <<"Class Array Test:" << p_ch;
    return p_ch + of.toString();
}