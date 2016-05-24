//
//  Server.cpp
//  VMDeployment
//
//  Created by Liang on 16/5/24.
//  Copyright © 2016年 Liang. All rights reserved.
//

#include "Server.hpp"

Server::Server() {
    
};

Server::Server(Property cpu, Property ram, Property stor, Property bw) {
    CPU = cpu;
    RAM = ram;
    STOR = stor;
    BW = bw;
};

Server::~Server() {
    
};


