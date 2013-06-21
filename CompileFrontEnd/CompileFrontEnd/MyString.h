//
//  MyString.h
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-19.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#ifndef __CompileFrontEnd__MyString__
#define __CompileFrontEnd__MyString__

#include <iostream>


using namespace std;

class MyString {

    
public:
    static string create(char *c)
    {
        string str(c);
        return str;
    }
};
#endif /* defined(__CompileFrontEnd__MyString__) */
