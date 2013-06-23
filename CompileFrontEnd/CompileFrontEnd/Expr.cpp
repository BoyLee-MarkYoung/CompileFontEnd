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
//    char *temp = new char[test.length()+string("if ").length()+string(" goto L").length()];
    ostringstream ss;
    if( t != 0 && f != 0 )
    {
        ss << "if " << test<< " goto L" << t;
        //sprintf(temp, "if %s goto L%d",test.c_str(), t);
        emit(ss.str());
        ss = ostringstream();
        ss << "goto L" << f;
//        sprintf(temp, "goto L%d",f);
        emit(ss.str());
    }
    else if( t != 0 )
    {
//        sprintf(temp, "if %s goto L%d",test.c_str(), t);
        ss << "if " << test << " goto L" << t;
        emit(ss.str());
    }
    else if( f != 0 )
    {
        ss << "iffalse " << test << " goto L" <<f;
//        sprintf(temp, "iffalse %s goto L%d",test.c_str(), f);
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
    this->type == rhs.type &&
    (Node)(*this) == (Node)(rhs))
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

