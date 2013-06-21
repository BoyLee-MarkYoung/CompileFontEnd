//
//  Node.h
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-19.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#ifndef __CompileFrontEnd__Node__
#define __CompileFrontEnd__Node__

#include <iostream>
#include <String.h>
#include "Lexer.h"

using namespace std;


class Node {
public:
    int lexline;
    static int labels;
    void error(string s);
    
    
    int newlabel();
    
    void emitlabel(int i);
    
    void emit(string s);
    
    Node() {
        lexline = Lexer::line; lexline = 0;
    }
    
    bool operator==(const Node& rhs);

};
#endif /* defined(__CompileFrontEnd__Node__) */
