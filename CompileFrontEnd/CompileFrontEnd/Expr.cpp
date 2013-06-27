//
//  Expr.cpp
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-19.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#include "Expr.h"
#include <sstream>

void Expr::emitjumps(string test, int t, int f) {

    ostringstream ss;
    if( t != 0 && f != 0 )
    {
        ss << "if " << test<< " goto L" << t;

        emit(ss.str());
        ss = ostringstream();
        ss << "goto L" << f;

        emit(ss.str());
    }
    else if( t != 0 )
    {

        ss << "if " << test << " goto L" << t;
        emit(ss.str());
    }
    else if( f != 0 )
    {
        ss << "iffalse " << test << " goto L" <<f;

        emit(ss.str());
    }
    else ; // nothing since both t and f fall through
}

Expr& Expr::operator=(const Expr &rhs) {
    this->lexline = rhs.lexline;
    this->op = rhs.op;
    this->type = rhs.type;
    return *this;
}

bool Expr::operator==(const Expr& rhs)
{
    if ( this->op == rhs.op &&
    this->type == rhs.type)
    {
//        cout << "same Expr"  << endl;
        return true;
    }
    else {
//        cout << "diff Expr" << endl;
        return false;
    }
}


Expr Expr::Null = Expr();

