//
//  Tag.h
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-19.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#ifndef __CompileFrontEnd__Tag__
#define __CompileFrontEnd__Tag__

#include <iostream>

using namespace std;

class Tag {
public:
    const static int
    AND   = 256,  BASIC = 257,  BREAK = 258,  DO   = 259, ELSE  = 260,
    EQ    = 261,  FALSEE = 262,  GE    = 263,  ID   = 264, IF    = 265,
    INDEX = 266,  LE    = 267,  MINUS = 268,  NE   = 269, NUM   = 270,
    OR    = 271,  REAL  = 272,  TEMP  = 273,  TRUEE = 274, WHILE = 275,
    Null = -1;

};
#endif /* defined(__CompileFrontEnd__Tag__) */
