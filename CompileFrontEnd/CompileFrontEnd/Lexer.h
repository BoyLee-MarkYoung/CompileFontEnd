//
//  Lexer.h
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-19.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#ifndef __CompileFrontEnd__Lexer__
#define __CompileFrontEnd__Lexer__

#include <iostream>
#include "Word.h"
#include "Type.h"
#include <map>
#include "Num.h"
#include "Real.h"

#define MAX_FILE_NAME_LENGTH 256

using namespace std;

class Lexer {
private:
    FILE *fp;
    char fn[MAX_FILE_NAME_LENGTH];
public:
    static int line;
    char peek;
    map<string, Word*> words;
    void reserve( Word* w) { words.insert(make_pair(w->lexeme, w)); }
    
    Lexer();
    Lexer(const char *filename);
    void readch() {
        peek = getchar();
        //        cout << endl << peek << ' ';
    }
    bool readch(char c);
    Token* scan();
    
    Lexer& operator=(const Lexer& rhs);
    
};
#endif /* defined(__CompileFrontEnd__Lexer__) */
