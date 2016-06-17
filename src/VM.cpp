//
//  VM.cpp
//  VMDeployment
//
//  Created by Liang on 16/5/24.
//  Copyright © 2016年 Liang. All rights reserved.
//

#include "VM.hpp"

VM::VM() {
    svrSetIndex = -1;
};

VM::VM(VMArgs cpu, VMArgs ram, VMArgs stor, VMArgs bw) {
    CPU = cpu;
    RAM  = ram;
    STOR = stor;
    BW = bw;
    svrSetIndex = -1;
}

bool VM::isSetSucc() {
    if (svrSetIndex != -1)
        return true;
    return false;
}

VM::~VM() {};