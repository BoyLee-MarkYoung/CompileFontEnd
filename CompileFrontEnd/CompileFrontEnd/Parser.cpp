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
            Id id = Id(wd, p, used);
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
    match(Tag::NUM);
    match(']');
    if( look->tag == '[' )
        p = dims(p);
    Num* num = dynamic_cast<Num*>(look);
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
        return new Seq(stmt(), stmts());
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
                return new If(x, s1);
            match(Tag::ELSE);
            s2 = stmt();
            return new Else(x, s1, s2);
            
        case Tag::WHILE:
        {
            While *whilenode = new While();
            savedStmt = Stmt::Enclosing; Stmt::Enclosing = whilenode;
            match(Tag::WHILE); match('('); x = booll(); match(')');
            s1 = stmt();
            whilenode->init(x, s1);
            Stmt::Enclosing = savedStmt;  // reset Stmt.Enclosing
            return whilenode;
        }
            
        case Tag::DO:
        {
            Do *donode = new Do();
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
            return new Break();
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
    match(Tag::ID);
    
//    else {
//        cerr << "sytax err4";
//        return Stmt::Null;
//    }
    if( id == Id::Null )
        error(look->toString() + " undeclared");
    
    if( look->tag == '=' ) {       // S -> id = E ;
        move();
        stmt = new Set(id, booll());
    }
    else {                        // S -> L = E ;
        Access *x = offset(id);
        match('=');  stmt = new SetElem(x, booll());
    }
    match(';');
    return stmt;
}

Expr* Parser::booll()
{
    Expr* x = join();
    while( look->tag == Tag::OR ) {
        move();
        x = new Or(look, x, join());
    }
    return x;
}

Expr* Parser::join(){
    Expr* x = equality();
    while( look->tag == Tag::AND ) {
        move();
        x = new And(look, x, equality());
    }
    return x;
}

Expr* Parser::equality()
{
    Expr* x = rel();
    while( look->tag == Tag::EQ || look->tag == Tag::NE ) {

        move();
        x = new Rel(look, x, rel());
    }
    return x;
}

Expr* Parser::rel() {
    Expr* x = expr();
    switch( look->tag ) {
        case '<': case Tag::LE: case Tag::GE: case '>':
        {
            move();
            return new Rel(look, x, expr());
        }
        default:
            return x;
    }
}

Expr* Parser::expr() {
    Expr *x = term();
    while( look->tag == '+' || look->tag == '-' ) {
        move();
        x = new Arith(look, x, term());
    }
    return x;
}

Expr* Parser::term(){
    Expr *x = unary();
    while(look->tag == '*' || look->tag == '/' ) {
        move();
        x = new Arith(look, x, unary());
    }
    return x;
}

Expr* Parser::unary() {
    if( look->tag == '-' ) {
        move();
        return new Unary(&Word::minus, unary());
    }
    else if( look->tag == '!' ) {
        move();
        return new Not(look, unary());
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
            x = new Constant(look,& Type::Int);
            move();
            return x;
        case Tag::REAL:
            x = new Constant(look, &Type::Float);
            move();
            return x;
        case Tag::TRUEE:
            x = &Constant::True;
            move();
            return x;
        case Tag::FALSEE:
            x = &Constant::False;
            move();
            return x;
        default:
            error("syntax error5");
            return x;
//        case Tag::ID:
//            string s = look.toString();
//            Id id = top[look];
//            if( id == null ) error(look.toString() + " undeclared");
//                move();
//            if( look.tag != '[' ) return id;
//                else return offset(id);
            
    }
}

Access* Parser::offset(Id a)
{   // I -> [E] | [E] I
    Expr *i; Expr *w; Expr *t1, *t2; Expr *loc;  // inherit id
    
    Array* type = dynamic_cast<Array*>(a.type);
    match('['); i = booll(); match(']');     // first index, I -> [ E ]
    w = new Constant(type->of->width);
    t1 = new Arith(new Token('*'), i, w);
    loc = t1;
    while( look->tag == '[' ) {      // multi-dimensional I -> [ E ] I
        match('['); i = booll(); match(']');
        w = new Constant(type->of->width);
        t1 = new Arith( new Token('*'), i, w);
        t2 = new Arith( new Token('+'), loc, t1);
        loc = t2;
    }
    
    return new Access(a, loc, type);
}

