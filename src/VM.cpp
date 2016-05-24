//
//  VM.cpp
//  VMDeployment
//
//  Created by Liang on 16/5/24.
//  Copyright © 2016年 Liang. All rights reserved.
//

#include "VM.hpp"

VM::VM() {};

VM::VM(VMArgs cpu, VMArgs ram, VMArgs stor, VMArgs bw) {
    CPU = cpu;
    RAM  = ram;
    STOR = stor;
    BW = bw;
}

VM::~VM() {};