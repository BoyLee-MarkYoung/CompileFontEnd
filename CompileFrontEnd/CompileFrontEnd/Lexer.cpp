//
//  Lexer.cpp
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-19.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#include "Lexer.h"
#include "Tag.h"

int Lexer::line = 1;

Lexer& Lexer::operator=(const Lexer& rhs) {
    this->fp = rhs.fp;
    this->peek = rhs.peek;
    this->line = rhs.line;
    this->words = rhs.words;
    return *this;
}

Lexer::Lexer() {
    fn[0] = '\0';
    fp = NULL;
    reserve( new Word("if",    Tag::IF)    );
    reserve( new Word("else",  Tag::ELSE)  );
    reserve( new Word("while", Tag::WHILE) );
    reserve( new Word("do",    Tag::DO)    );
    reserve( new Word("break", Tag::BREAK) );
    
    reserve(& Word::True );  reserve( &(Word::False) );
    
    reserve(& Type::Int  );  reserve( & Type::Char  );
    reserve(& Type::Bool );  reserve( & Type::Float );
    peek = ' ';
}

Lexer::Lexer (const char *filename)
{
    strcpy(fn, filename);
    fp = fopen(filename, "r");
    if (fp == NULL) {
#pragma mark 文件打开失败的处理
        printf("File not found!\n");
    }
    reserve( new Word("if",    Tag::IF)    );
    reserve( new Word("else",  Tag::ELSE)  );
    reserve( new Word("while", Tag::WHILE) );
    reserve( new Word("do",    Tag::DO)    );
    reserve( new Word("break", Tag::BREAK) );
    
    reserve(& Word::True );  reserve( &(Word::False) );
    
    reserve(& Type::Int  );  reserve( & Type::Char  );
    reserve(& Type::Bool );  reserve( & Type::Float );
    peek = ' ';
}


bool Lexer::readch(char c) {
    
    readch();
    if( peek != c ) return false;
    peek = ' ';
    return true;
    
}


Token* Lexer::scan() {
    for( ; ; readch() ) {
        if( peek == ' ' || peek == '\t' ) continue;
        else if( peek == '\n' ) line = line + 1;
        else break;
    }
    switch( peek ) {
        case '&':
            if( readch('&') ) return new Word(Word::andd);  else return new Token('&');
        case '|':
            if( readch('|') ) return new Word(Word::orr);   else return new Token('|');
        case '=':
            if( readch('=') ) return new Word(Word::eq);   else return new Token('=');
        case '!':
            if( readch('=') ) return new Word(Word::ne);   else return new Token('!');
        case '<':
            if( readch('=') ) return new Word(Word::le);   else return new Token('<');
        case '>':
            if( readch('=') ) return new Word(Word::ge);   else return new Token('>');
    }
    if( isdigit(peek) ) {
        int v = 0;
        do {
            v = 10*v + atoi(&peek);
            readch();
        } while( isdigit(peek) );
        
        if( peek != '.' )
            return  new Num(v);
        float x = v; float d = 10;
        for(;;) {
            readch();
            if( ! isdigit(peek) ) break;
            x = x + atoi(&peek) / d;
            d = d*10;
        }
        return  new Real(x);
    }
    if( isalnum(peek) or peek=='_') {
        string b;
        do {
            b.append(&peek);
            readch();
        } while( isalnum(peek) );
        Word *w = words[b];
        if( w != NULL )
            return w;
        w =  new Word(b, Tag::ID);
        words.insert(make_pair(b, w));
        return w;
    }
    Token *tok =  new Token(peek);
    peek = ' ';
    return tok;
}
