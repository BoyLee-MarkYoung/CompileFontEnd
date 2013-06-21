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
    Stmt stmt;
    Break() {
        if( Stmt::Enclosing == Stmt::Null ) error("unenclosed break");
        stmt = Stmt::Enclosing;
    }
    
    void gen(int b, int a) {
        ostringstream ss;
        ss << "goto L" << stmt.after;
        emit(ss.str());
    }
};
#endif /* defined(__CompileFrontEnd__Break__) */
