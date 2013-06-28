//
//  Break.h
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-21.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#ifndef __CompileFrontEnd__Break__
#define __CompileFrontEnd__Break__

#include <iostream>
#include "Stmt.h"

#include <sstream>

class Break :public Stmt{
    
    
public:
    Stmt *stmt;
    
    Break(string objFileName);
    
    void gen(int b, int a);
};
#endif /* defined(__CompileFrontEnd__Break__) */
