//
//  Node.cpp
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-19.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#include "Node.h"


void Node::error(string s) {
    cerr << "near line "
    <<lexline
    <<": "
    << s;
}

int Node::newlabel() {
     return ++labels;
}


void Node::emitlabel(int i) {
    cout << "L"
    << i
    << ":";
}

void Node::emit(string s) {
    cout << "\t"
        << s;
}

bool Node::operator==(const Node& rhs)
{
    return this->lexline == rhs.lexline;
}