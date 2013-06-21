//
//  Access.h
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-19.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#ifndef __CompileFrontEnd__Access__
#define __CompileFrontEnd__Access__

#include <iostream>
#include "Op.h"
#include "Id.h"
#
using namespace std;

class Access : public Op {
public:
    Id array;
    Expr index;
    
    Access(Id a, Expr i, Type p)
    : Op(Word("[]",Tag::INDEX), p), array(a), index(i)
    {    // p is element type after
          // flattening the array
    }
    
    Access()
    :array(Id::Null), index(Expr::Null)
    {}
    
    Expr gen() { return Access(array, index.reduce(), type); }
    
    void jumping(int t,int f) { emitjumps(reduce().toString(),t,f); }
    
    string toString() {
        return array.toString() + " [ " + index.toString() + " ]";
    }
};
#endif /* defined(__CompileFrontEnd__Access__) */
