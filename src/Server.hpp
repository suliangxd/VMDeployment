//
//  Server.hpp
//  VMDeployment
//
//  Created by Liang on 16/5/24.
//  Copyright © 2016年 Liang. All rights reserved.
//

#ifndef Server_hpp
#define Server_hpp

#include <stdio.h>

struct Property {
    int _all;
    int _use;
    int _reserve;
    
    Property() {}
    
    Property(int a, int b, int c) : _all(a), _use(b), _reserve(c) {}
    
    // update use and other args from new use number.
    void uptate(int use) {
        _use = use;
        _reserve = _all - _use;
    }
    
    // [formula] : q = 1 - use/(all-reserve)
    double get_feature() {
        double ret;
        ret = 1.0 - _use/(_all - _reserve + 0.0);
        return ret;
    }
    
    Property& operator = (const Property & pro) {
        _all = pro._all;
        _use = pro._use;
        _reserve = pro._reserve;
        
        return *this;
    }
    
    
};

class Server {
public :
    Server();
    
    Server(Property cpu, Property ram, Property stor, Property bw);
    
    ~Server();
    
    Property CPU;
    Property RAM;
    Property STOR;
    Property BW;
};
#endif /* Server_hpp */
