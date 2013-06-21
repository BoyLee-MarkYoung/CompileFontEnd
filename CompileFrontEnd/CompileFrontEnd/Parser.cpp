//
//  Parser.cpp
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-19.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#include "Parser.h"



void Parser::match(int t) {
    try {
        if( look.tag == t ) move();
        else error("syntax error");
    } catch (exception e) {
        cerr << e.what();
    }
}

void Parser::program()
{
    Stmt s = block();
    int begin = s.newlabel();
    int after = s.newlabel();
    s.emitlabel(begin);
    s.gen(begin, after);
    s.emitlabel(after);
}

Stmt Parser::block() {  // block -> { decls stmts }
    match('{');  Env savedEnv = top;  top = Env(top);
    decls(); Stmt s = stmts();
    match('}');  top = savedEnv;
    return s;
}

void Parser::decls()
{
    while( look.tag == Tag::BASIC ) {   // D -> type ID ;
        Type p = type(); Token tok = look; match(Tag::ID); match(';');
        Id id = Id(dynamic_cast<Word&>(tok), p, used);
        top.put( tok, id );
        used = used + p.width;
    }
}

Type Parser::type()
{
    Type p = dynamic_cast<Type&>(look);            // expect look.tag == Tag.BASIC
    match(Tag::BASIC);
    if( look.tag != '[' ) return p; // T -> basic
    else return dims(p);            // return array type
}

Type Parser::dims(Type p)
{
    match('[');  Token tok = look;  match(Tag::NUM);  match(']');
    if( look.tag == '[' )
        p = dims(p);
    return Array((dynamic_cast<Num&>(tok)).value, p);//?????
}

Stmt Parser::stmts()
{
    if ( look.tag == '}' ) return Stmt::Null;
    else return Seq(stmt(), stmts());
}

Stmt Parser::stmt()
{
    Expr x;  Stmt s, s1, s2;
    Stmt savedStmt;         // save enclosing loop for breaks
    
    switch( look.tag ) {
            
        case ';':
            move();
            return Stmt::Null;
            
        case Tag::IF:
            match(Tag::IF); match('('); x = booll(); match(')');
            s1 = stmt();
            if( look.tag != Tag::ELSE ) return If(x, s1);
            match(Tag::ELSE);
            s2 = stmt();
            return Else(x, s1, s2);
            
        case Tag::WHILE:
        {
            While whilenode = While();
            savedStmt = Stmt::Enclosing; Stmt::Enclosing = whilenode;
            match(Tag::WHILE); match('('); x = booll(); match(')');
            s1 = stmt();
            whilenode.init(x, s1);
            Stmt::Enclosing = savedStmt;  // reset Stmt.Enclosing
            return whilenode;
        }
            
        case Tag::DO:
        {
            Do donode = Do();
            savedStmt = Stmt::Enclosing; Stmt::Enclosing = donode;
            match(Tag::DO);
            s1 = stmt();
            match(Tag::WHILE); match('('); x = booll(); match(')'); match(';');
            donode.init(s1, x);
            Stmt::Enclosing = savedStmt;  // reset Stmt.Enclosing
            return donode;
        }
            
        case Tag::BREAK:
        {
            match(Tag::BREAK); match(';');
            return Break();
        }
            
        case '{':
            return block();
            
        default:
            return assign();
    }
}

Stmt Parser::assign()
{
    Stmt stmt;  Token t = look;
    match(Tag::ID);
    Id id = top.get(t);
    if( id == Id::Null )
        error(t.toString() + " undeclared");
    
    if( look.tag == '=' ) {       // S -> id = E ;
        move();
        stmt = Set(id, booll());
    }
    else {                        // S -> L = E ;
        Access x = offset(id);
        match('=');  stmt = SetElem(x, booll());
    }
    match(';');
    return stmt;
}

Expr Parser::booll()
{
    Expr x = join();
    while( look.tag == Tag::OR ) {
        Token tok = look;
        move();
        x = Or(tok, x, join());
    }
    return x;
}

Expr Parser::join(){
    Expr x = equality();
    while( look.tag == Tag::AND ) {
        Token tok = look;
        move();
        x = And(tok, x, equality());
    }
    return x;
}

Expr Parser::equality()
{
    Expr x = rel();
    while( look.tag == Tag::EQ || look.tag == Tag::NE ) {
        Token tok = look;
        move();
        x = Rel(tok, x, rel());
    }
    return x;
}

Expr Parser::rel() {
    Expr x = expr();
    switch( look.tag ) {
        case '<': case Tag::LE: case Tag::GE: case '>':
        {
            Token tok = look;
            move();
            return Rel(tok, x, expr());
        }
        default:
            return x;
    }
}

Expr Parser::expr() {
    Expr x = term();
    while( look.tag == '+' || look.tag == '-' ) {
        Token tok = look;
        move();
        x = Arith(tok, x, term());
    }
    return x;
}

Expr Parser::term(){
    Expr x = unary();
    while(look.tag == '*' || look.tag == '/' ) {
        Token tok = look;  move();   x = Arith(tok, x, unary());
    }
    return x;
}

Expr Parser::unary() {
    if( look.tag == '-' ) {
        move();
        return Unary(Word::minus, unary());
    }
    else if( look.tag == '!' ) {
        Token tok = look;
        move();
        return Not(tok, unary());
    }
    else
        return factor();
}

Expr Parser::factor() {
    Expr x = Expr::Null;
    switch( look.tag ) {
        case '(':
            move();
            x = booll();
            match(')');
            return x;
        case Tag::NUM:
            x = Constant(look, Type::Int);
            move();
            return x;
        case Tag::REAL:
            x = Constant(look, Type::Float);
            move();
            return x;
        case Tag::TRUEE:
            x = Constant::True;
            move();
            return x;
        case Tag::FALSEE:
            x = Constant::False;
            move();
            return x;
        default:
            error("syntax error");
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

Access Parser::offset(Id a)
{   // I -> [E] | [E] I
    Expr i; Expr w; Expr t1, t2; Expr loc;  // inherit id
    
    Type type = a.type;
    match('['); i = booll(); match(']');     // first index, I -> [ E ]
    type = (dynamic_cast<Array&>(type)).of;
    w = Constant(type.width);
    t1 = Arith(Token('*'), i, w);
    loc = t1;
    while( look.tag == '[' ) {      // multi-dimensional I -> [ E ] I
        match('['); i = booll(); match(']');
        type = (dynamic_cast<Array&>(type)).of;
        w = Constant(type.width);
        t1 = Arith( Token('*'), i, w);
        t2 = Arith( Token('+'), loc, t1);
        loc = t2;
    }
    
    return Access(a, loc, type);
}

