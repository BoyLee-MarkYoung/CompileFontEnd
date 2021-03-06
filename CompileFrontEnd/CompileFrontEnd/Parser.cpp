//
//  Parser.cpp
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-19.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#include "Parser.h"
#include <typeinfo>


void Parser::match(int t) {
    try {
        if( look->tag == t ) {
            //            cout <<endl << look->tag << endl;
            move();
        }
        else
            error("syntax err6");
    } catch (exception e) {
        cerr << e.what();
    }
}

void Parser::program()
{
    Stmt* s = block(); 
    int begin = s->newlabel();
    int after = s->newlabel();
    s->emitlabel(begin);
    s->gen(begin, after);
    s->emitlabel(after);
}

Stmt* Parser::block() {  // block -> { decls stmts }
    match('{');
    Env *savedEnv = top;
    top = new Env(top);
    decls();
    Stmt* s = stmts();
    match('}');
    top = savedEnv;
    return s;
}

void Parser::decls()
{
    while( look->tag == Tag::BASIC ) {   // D -> type ID ;
        Type* p = type();
        Word *wd = dynamic_cast<Word*>(look);
        if (p == NULL) return;
        match(Tag::ID);
        match(';');
        if (wd) {
            Id id = Id(wd, p, used, objFileName);
            top->put( wd, id );
        }
        used = used + p->width;
    }
}

Type* Parser::type()
{
    
    Type *tp = dynamic_cast<Type*>(look);//    Type p = dynamic_cast<Type&>(look);
    // expect look.tag == Tag.BASIC
    match(Tag::BASIC);// && typeid(look) == typeid(Type)
    if (tp) {
        if( look->tag != '[') {
            return tp; // T -> basic
        }
        else return dims(tp);            // return array type
    } else {
        cerr << "sytax err1";
        return NULL;
    }
}

Type* Parser::dims(Type *p)
{
    if (p == NULL) {
        cerr << "compile err2";
        return NULL;
    }
    match('[');
    Num* num = dynamic_cast<Num*>(look);
    match(Tag::NUM);
    match(']');
    if( look->tag == '[' )
        p = dims(p);
    if (num)
        return new Array(num->value, p);//?????
    else {
        cerr << "sytax err3";
        return NULL;
    }
}

Stmt* Parser::stmts()
{
    if ( look->tag == '}' )
        return & Stmt::Null;
    else
        return new Seq(stmt(), stmts(), objFileName);
}

Stmt* Parser::stmt()
{
    Expr *x;
    Stmt *s1, *s2;
    Stmt *savedStmt;         // save enclosing loop for breaks
    
    switch( look->tag ) {
            
        case ';':
            move();
            return &Stmt::Null;
            
        case Tag::IF:
            match(Tag::IF);
            match('(');
            x = booll();
            match(')');
            s1 = stmt();
            if( look->tag != Tag::ELSE )
                return new If(x, s1, objFileName);
            match(Tag::ELSE);
            s2 = stmt();
            return new Else(x, s1, s2, objFileName);
            
        case Tag::WHILE:
        {
            While *whilenode = new While(objFileName);
            savedStmt = Stmt::Enclosing; Stmt::Enclosing = whilenode;
            match(Tag::WHILE); match('('); x = booll(); match(')');
            s1 = stmt();
            whilenode->init(x, s1);
            Stmt::Enclosing = savedStmt;  // reset Stmt.Enclosing
            return whilenode;
        }
            
        case Tag::DO:
        {
            Do *donode = new Do(objFileName);
            savedStmt = Stmt::Enclosing; Stmt::Enclosing = donode;
            match(Tag::DO);
            s1 = stmt();
            match(Tag::WHILE); match('('); x = booll(); match(')'); match(';');
            donode->init(s1, x);
            Stmt::Enclosing = savedStmt;  // reset Stmt.Enclosing
            return donode;
        }
            
        case Tag::BREAK:
        {
            match(Tag::BREAK); match(';');
            return new Break(objFileName);
        }
            
        case '{':
            return block();
        default:
            return assign();
    }
}

Stmt* Parser::assign()
{
    Stmt* stmt;
    Id id;
    //    Word *wd = dynamic_cast<Word*>(look);
    //    if (wd)
    id = top->get(look);

    
    //    else {
    //        cerr << "sytax err4";
    //        return Stmt::Null;
    //    }
    if( id == Id::Null )
        error(look->toString() + " undeclared");
    match(Tag::ID);
    if( look->tag == '=' ) {       // S -> id = E ;
        move();
        stmt = new Set(id, booll(), objFileName);
    }
    else {                        // S -> L = E ;
        Access *x = offset(id);
        match('=');  stmt = new SetElem(x, booll(), objFileName);
    }
    match(';');
    return stmt;
}

Expr* Parser::booll()
{
    Expr* x = join();
    while( look->tag == Tag::OR ) {
        Token *tok = look;
        move();
        x = new Or(tok, x, join(), objFileName);
    }
    return x;
}

Expr* Parser::join(){
    Expr* x = equality();
    while( look->tag == Tag::AND ) {
        Token *tok = look;
        move();
        x = new And(tok, x, equality(), objFileName);
    }
    return x;
}

Expr* Parser::equality()
{
    Expr* x = rel();
    while( look->tag == Tag::EQ || look->tag == Tag::NE ) {
        Token *tok = look;
        move();
        x = new Rel(tok, x, rel(), objFileName);
    }
    return x;
}

Expr* Parser::rel() {
    Expr* x = expr();
    switch( look->tag ) {
        case '<': case Tag::LE: case Tag::GE: case '>':
        {
            Token *tok = look;
            move();
            return new Rel(tok, x, expr(),objFileName);
        }
        default:
            return x;
    }
}

Expr* Parser::expr() {
    Expr *x = term();
    while( look->tag == '+' || look->tag == '-' ) {
        Token *tok = look;
        move();
        x = new Arith(tok, x, term(), objFileName);
    }
    return x;
}

Expr* Parser::term(){
    Expr *x = unary();
    while(look->tag == '*' || look->tag == '/' ) {
        Token *tok = look;
        move();
        x = new Arith(tok, x, unary(),objFileName);
    }
    return x;
}

Expr* Parser::unary() {
    if( look->tag == '-' ) {
        move();
        return new Unary(&Word::minus, unary(), objFileName);
    }
    else if( look->tag == '!' ) {
        Token *tok = look;
        move();
        return new Not(tok, unary(), objFileName);
    }
    else
        return factor();
}

Expr* Parser::factor() {
    Expr* x = &Expr::Null;
    switch( look->tag ) {
        case '(':
            move();
            x = booll();
            match(')');
            return x;
        case Tag::NUM:
            x = new Constant(look,& Type::Int, objFileName);
            move();
            return x;
        case Tag::REAL:
            x = new Constant(look, &Type::Float, objFileName);
            move();
            return x;
        case Tag::TRUEE:
            x = new Constant(&Word::True, &Type::Bool, objFileName);
            move();
            return x;
        case Tag::FALSEE:
            x = new Constant(&Word::False, &Type::Bool, objFileName);
            move();
            return x;
        case Tag::ID:
        {
            string s = look->toString();
            Id *id = new Id(top->get(look));
            if( *id == Id::Null )
                error(look->toString() + " undeclared");
            move();
            if( look->tag != '[' ) return id;
            else return offset(*id);
        }
        default:
            error("syntax error5");
            return x;
    }
}

Access* Parser::offset(Id a)
{   // I -> [E] | [E] I
    Expr *i; Expr *w; Expr *t1, *t2; Expr *loc;  // inherit id
    
    
    match('[');
    i = booll();
    match(']');     // first index, I -> [ E ]
    
    //需要异常处理
    Array *temptype = dynamic_cast<Array*>(a.type);
    if (temptype) {
        Type* type = temptype->of;
        
        w = new Constant(type->width, objFileName);
        t1 = new Arith(new Token('*'), i, w, objFileName);
        loc = t1;
        while( look->tag == '[' ) {      // multi-dimensional I -> [ E ] I
            match('[');
            i = booll();
            match(']');
            type = dynamic_cast<Array*>(type)->of;
            Type* type = new Type(*temptype->of);
            w = new Constant(type->width, objFileName);
            t1 = new Arith( new Token('*'), i, w, objFileName);
            t2 = new Arith( new Token('+'), loc, t1, objFileName);
            loc = t2;
        }
        
        return new Access(a, loc, type, objFileName);
    } else {
        return NULL;
    }
}

void Parser::error(string s) {
    FILE *f = fopen("log.txt", "a+");
    //    ofstream fstrm(objFileName);
    //    fstrm.open(objFileName);
    
    
    //输出到文件
    fprintf(f, "near line %d: %s\n", Lexer::lineMultiFile[objFileName], s.c_str());
    //
    //        cout << "near line " << Lexer::lineMultiFile[objFileName] << ": " <<s;
}

