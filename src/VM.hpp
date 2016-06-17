//
//  VM.hpp
//  VMDeployment
//
//  Created by Liang on 16/5/24.
//  Copyright © 2016年 Liang. All rights reserved.
//

#ifndef VM_hpp
#define VM_hpp

#include <stdio.h>

struct VMArgs {
    int _need;
    double _exp;
    
    VMArgs() {}
    
    VMArgs(int need, double exp) : _need(need), _exp(exp) {}
    
    VMArgs& operator = (const VMArgs & args) {
        _need = args._need;
        _exp = args._exp;
        
        return *this;
    }
    
};

class VM {
public:
    VM();
    
    VM(VMArgs cpu, VMArgs ram, VMArgs stor, VMArgs bw);
    
    ~VM();
    
    bool isSetSucc();
    
    VMArgs CPU;
    VMArgs RAM;
    VMArgs STOR;
    VMArgs BW;
    int svrSetIndex;
    
};
#endif /* VM_hpp */
