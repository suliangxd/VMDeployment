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
    // 总值
    int _all;
    // 已使用
    int _use;
    // 服务器预留值
    int _reserve;
    
    Property() {}
    
    Property(int a, int b, int c) : _all(a), _use(b), _reserve(c) {}
    
    // 增加新的vm
    void add(int num) {
        _use += num;
        update(_use);
    }
    
    // update use and other args from new use number.
    void update(int use) {
        _use = use;
    }
    
    // 特征[formula] : q = 1 - use/(all-reserve)
    double get_feature() {
        double ret;
        ret = 1.0 - _use/(_all - _reserve + 0.0);
        return ret;
    }
    
    // 使用率
    double get_usePercent() {
        double ret;
        ret = _use*1.0/(_all - _reserve);
        return ret;
    }
    
    int get_unUsed() {
        return _all - _use - _reserve;
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
