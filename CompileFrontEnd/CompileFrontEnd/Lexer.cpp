//
//  Lexer.cpp
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-19.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#include "Lexer.h"
#include "Tag.h"



Lexer& Lexer::operator=(const Lexer& rhs) {
    this->peek = rhs.peek;
    this->line = rhs.line;
    this->words = rhs.words;
    return *this;
}

Lexer::Lexer ()
{
    reserve( Word("if",    Tag::IF)    );
    reserve( Word("else",  Tag::ELSE)  );
    reserve( Word("while", Tag::WHILE) );
    reserve( Word("do",    Tag::DO)    );
    reserve( Word("break", Tag::BREAK) );
    
    reserve( Word::True );  reserve( Word::False );
    
    reserve( Type::Int  );  reserve( Type::Char  );
    reserve( Type::Bool );  reserve( Type::Float );
}


bool Lexer::readch(char c) {

    readch();
    if( peek != c ) return false;
    peek = ' ';
    return true;

}


Token Lexer::scan() {
    for( ; ; readch() ) {
        if( peek == ' ' || peek == '\t' ) continue;
        else if( peek == '\n' ) line = line + 1;
        else break;
    }
    switch( peek ) {
        case '&':
            if( readch('&') ) return Word::andd;  else return Token('&');
        case '|':
            if( readch('|') ) return Word::orr;   else return  Token('|');
        case '=':
            if( readch('=') ) return Word::eq;   else return  Token('=');
        case '!':
            if( readch('=') ) return Word::ne;   else return  Token('!');
        case '<':
            if( readch('=') ) return Word::le;   else return  Token('<');
        case '>':
            if( readch('=') ) return Word::ge;   else return  Token('>');
    }
    if( isdigit(peek) ) {
        int v = 0;
        do {
            v = 10*v + atoi(&peek);
            readch();
        } while( isdigit(peek) );
        
        if( peek != '.' )
            return  Num(v);
        float x = v; float d = 10;
        for(;;) {
            readch();
            if( ! isdigit(peek) ) break;
            x = x + atoi(&peek) / d;
            d = d*10;
        }
        return  Real(x);
    }
    if( isalpha(peek) or peek=='_') {
        string b;
        do {
            b.append(&peek);
            readch();
        } while( isalnum(peek) );
        Word w = (Word)words[b];
        if( w != Word::Null )
            return w;
        w =  Word(b, Tag::ID);
//        words.insert(pair<string, Word>(b, w));
        return w;
    }
    Token tok =  Token(peek);
    peek = ' ';
    return tok;
}
