//
//  Break.cpp
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-21.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#include "Break.h"


void Break::gen(int b, int a) {
    ostringstream ss;
    ss << "goto L" << stmt->after;
    emit(ss.str());
}

Break::Break() {
    if( *Stmt::Enclosing == Stmt::Null ) error("unenclosed break");
    stmt = Stmt::Enclosing;
}