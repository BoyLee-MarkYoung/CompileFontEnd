//
//  Parser.h
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-19.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#ifndef __CompileFrontEnd__Parser__
#define __CompileFrontEnd__Parser__

#include <iostream>
#include "Lexer.h"
#include "Token.h"
#include "Env.h"
#include "Stmt.h"
#include "Access.h"
#include "Set.h"
#include "SetElem.h"
#include "Expr.h"
#include "Type.h"
#include "And.h"
#include "Or.h"
#include "Rel.h"
#include "Arith.h"
#include "Not.h"
#include "Env.h"
#include "Real.h"
#include "Num.h"
#include "Unary.h"
#include "Constant.h"
#include "Access.h"
#include "Array.h"
#include "If.h"
#include "While.h"
#include "Seq.h"
#include "Do.h"
#include "Else.h"
#include "Break.h"



using namespace std;

class Parser {
private:
    Lexer lex;    // lexical analyzer for this parser
    Token *look;   // lookahead tagen
    string objFileName;
    
    
public:
    Env *top;       // current or top symbol table
    int used = 0;         // storage used for declarations
    Parser(Lexer l)
    {
        top = new Env();
        lex = l;
        objFileName = l.getObjFileName();
        
        move();
    }
    
    void move() { look = lex.scan(); }
    void error(string s) { cout << "near line " << Lexer::lineMultiFile[objFileName] << ": " <<s; }
    void match(int t);
    void program();
    Stmt* block();
    void decls();
    Type* type();
    Type* dims(Type* p);
    Stmt* stmts();
    Stmt* stmt();
    Stmt* assign();
    Expr* booll();
    Expr* join();
    Expr* equality();
    Expr* rel();
    Expr* expr();
    Expr* unary();
    Expr* term();
    Expr* factor();
    Access* offset(Id);
};
#endif /* defined(__CompileFrontEnd__Parser__) */
