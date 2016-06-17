//
//  comm.cpp
//  VMDeployment
//
//  Created by Liang on 16/5/25.
//  Copyright © 2016年 Liang. All rights reserved.
//

/*
 *
 *                       _oo0oo_
 *                      o8888888o
 *                      88" . "88
 *                      (| -_- |)
 *                      0\  =  /0
 *                    ___/`---'\___
 *                  .' \\|     |// '.
 *                 / \\|||  :  |||// \
 *                / _||||| -:- |||||- \
 *               |   | \\\  -  /// |   |
 *               | \_|  ''\---/''  |_/ |
 *               \  .-\__  '-'  ___/-. /
 *             ___'. .'  /--.--\  `. .'___
 *          ."" '<  `.___\_<|>_/___.' >' "".
 *         | | :  `- \`.;`\ _ /`;.`/ - ` : | |
 *         \  \ `_.   \_ __\ /__ _/   .-` /  /
 *     =====`-.____`.___ \_____/___.-`___.-'=====
 *                       `=---='
 *
 *
 *     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *               佛祖保佑         永无BUG
 */

#include "comm.hpp"
#include "Server.hpp"
#include "VM.hpp"

#include <cstring>
#include <vector>
#include <iostream>
#include <cmath>
#include <climits>


// 读取VM, 每次读取num个
void read_vm(std::vector<VM> & vmList, int num) {
    
    for(int i = 0; i < num; i++) {
        // 需求量
        int needs[4];
        // 期望
        double exps[4];
        // 每次读取4个VMAges, 分别是CPU, RAM, STOR, BW
        
        for (int j = 0; j < 4; j++) {
            std::cin >> needs[j] >> exps[j];
        }
        
        VMArgs CPUArgs(needs[CPU], exps[CPU]);
        VMArgs RAMArgs(needs[RAM], exps[RAM]);
        VMArgs STORArgs(needs[STOR], exps[STOR]);
        VMArgs BWArgs(needs[BW], exps[BW]);
        
        VM tmpVM(CPUArgs, RAMArgs, STORArgs, BWArgs);
        vmList.push_back(tmpVM);
    }
}

// 读取server
void read_svr(std::vector<Server> & svrList, int num) {
    for (int i = 0; i < num; i++) {
        // 总值
        int alls[4];
        // 服务器预留值
        int reserves[4];
        
        // 每次读取4个Property, 分别是服务器的CPU, RAM, STOR, BW
        for (int j = 0; j < 4; j++) {
            std::cin >> alls[j] >> reserves[j];
        }
        
        // 初始化使用量 use=0
        Property CPUPro(alls[CPU], 0, reserves[CPU]);
        Property RAMPro(alls[RAM], 0, reserves[RAM]);
        Property STORPro(alls[STOR], 0, reserves[STOR]);
        Property BWPro(alls[BW], 0, reserves[BW]);
        
        Server tmpSvr(CPUPro, RAMPro, STORPro, BWPro);
        svrList.push_back(tmpSvr);
    }
}

// CPU使用率
void getCPUPercent(std::vector<Server> svrList, std::vector<double> & cpuPercentList) {
    cpuPercentList.clear();
    for (auto svr : svrList) {
        double percent = svr.CPU.get_usePercent();
        cpuPercentList.push_back(percent);
    }
}

// RAM使用率
void getRAMPercent(std::vector<Server> svrList, std::vector<double> & ramPercentList) {
    ramPercentList.clear();
    for (auto svr : svrList) {
        double percent = svr.RAM.get_usePercent();
        ramPercentList.push_back(percent);
    }
}

// STOR使用率
void getSTORPercent(std::vector<Server> svrList, std::vector<double> & storPercentList) {
    storPercentList.clear();
    for (auto svr : svrList) {
        double percent = svr.STOR.get_usePercent();
        storPercentList.push_back(percent);
    }
}

// BW使用率
void getBWPercent(std::vector<Server> svrList, std::vector<double> & bwPercentList) {
    bwPercentList.clear();
    for (auto svr : svrList) {
        double percent = svr.BW.get_usePercent();
        bwPercentList.push_back(percent);
    }
}

// 判断vm是否可部署在svr上
bool isUseFul(Server svr, VM vm) {
    
    if (svr.CPU.get_unUsed() < vm.CPU._need)
        return false;
    if (svr.RAM.get_unUsed() < vm.RAM._need)
        return false;
    if (svr.STOR.get_unUsed() < vm.STOR._need)
        return false;
    if (svr.BW.get_unUsed() < vm.BW._need)
        return false;
    
    return true;
}

// svr与vm的欧拉距离
double getEulerDis(Server svr, VM vm) {
    double ret = 0.0;
    ret += pow((svr.CPU.get_unUsed() - vm.CPU._need), 2);
    ret += pow((svr.RAM.get_unUsed() - vm.RAM._need), 2);
    ret += pow((svr.STOR.get_unUsed() - vm.STOR._need), 2);
    ret += pow((svr.BW.get_unUsed() - vm.BW._need), 2);
    ret = sqrt(ret);
    
    return ret;
}

// 批量虚机部署成功率
double getVmSuccPercent(std::vector<VM> vmList, int allVm) {
    int succNum = 0;
    for (auto vm : vmList) {
        if (vm.isSetSucc() == true) {
            succNum ++ ;
        }
    }
    
    return succNum*1.0/allVm;
}

// 归一化计算公式
double getNormaliza(int num, int minNum, int maxNum) {
    return (num - minNum + 0.0)/(maxNum - minNum);
}

// svr的各特征归一化
void svrNormaliza(Server svr, int *svrMinArr, int *svrMaxArr, double *svrNormArr) {
    svrNormArr[CPU] = getNormaliza(svr.CPU.get_unUsed(), svrMinArr[CPU], svrMaxArr[CPU]);
    svrNormArr[RAM] = getNormaliza(svr.RAM.get_unUsed(), svrMinArr[RAM], svrMaxArr[RAM]);
    svrNormArr[STOR] = getNormaliza(svr.STOR.get_unUsed(), svrMinArr[STOR], svrMaxArr[STOR]);
    svrNormArr[BW] = getNormaliza(svr.BW.get_unUsed(), svrMinArr[BW], svrMaxArr[BW]);
}

// vm的各特征需求归一化
void vmNormaliza(VM vm, int *vmMinArr, int *vmMaxArr, double *vmNormArr) {
    vmNormArr[CPU] = getNormaliza(vm.CPU._need, vmMinArr[CPU], vmMaxArr[CPU]);
    vmNormArr[RAM] = getNormaliza(vm.RAM._need, vmMinArr[RAM], vmMaxArr[RAM]);
    vmNormArr[STOR] = getNormaliza(vm.STOR._need, vmMinArr[STOR], vmMaxArr[STOR]);
    vmNormArr[BW] = getNormaliza(vm.BW._need, vmMinArr[BW], vmMaxArr[BW]);
}

// 求所有服务器各特征的峰值
void getSvrMinAndMaxArr(std::vector<Server> svrList, int *svrMinArr, int *svrMaxArr) {
    
    svrMinArr[CPU] = svrMinArr[RAM] = svrMinArr[STOR] = svrMinArr[BW] = INT_MAX;
    svrMaxArr[CPU] = svrMaxArr[RAM] = svrMaxArr[STOR] = svrMaxArr[BW] = -1;
    
    for (auto svr : svrList) {
        svrMinArr[CPU]  = std::min(svr.CPU.get_unUsed(), svrMinArr[CPU]);
        svrMinArr[RAM]  = std::min(svr.RAM.get_unUsed(), svrMinArr[RAM]);
        svrMinArr[STOR] = std::min(svr.STOR.get_unUsed(), svrMinArr[STOR]);
        svrMinArr[BW]   = std::min(svr.BW.get_unUsed(), svrMinArr[BW]);
        
        svrMaxArr[CPU]  = std::max(svr.CPU.get_unUsed(), svrMaxArr[CPU]);
        svrMaxArr[RAM]  = std::max(svr.RAM.get_unUsed(), svrMaxArr[RAM]);
        svrMaxArr[STOR] = std::max(svr.RAM.get_unUsed(), svrMaxArr[STOR]);
        svrMaxArr[BW]   = std::max(svr.BW.get_unUsed(), svrMaxArr[BW]);
    }
}

// 求所有vm各特征的峰值
void getVmMinAndMaxArr(std::vector<VM> vmList, int *vmMinArr, int *vmMaxArr) {
    vmMinArr[CPU] = vmMinArr[RAM] = vmMinArr[STOR] = vmMinArr[BW] = INT_MAX;
    vmMaxArr[CPU] = vmMaxArr[RAM] = vmMaxArr[STOR] = vmMaxArr[BW] = -1;
    
    for (auto vm : vmList) {
        vmMinArr[CPU]  = std::min(vm.CPU._need, vmMinArr[CPU]);
        vmMinArr[RAM]  = std::min(vm.RAM._need, vmMinArr[RAM]);
        vmMinArr[STOR] = std::min(vm.STOR._need, vmMinArr[STOR]);
        vmMinArr[BW]   = std::min(vm.BW._need, vmMinArr[BW]);
        
        vmMaxArr[CPU]  = std::max(vm.CPU._need, vmMaxArr[CPU]);
        vmMaxArr[RAM]  = std::max(vm.RAM._need, vmMaxArr[RAM]);
        vmMaxArr[STOR] = std::max(vm.STOR._need, vmMaxArr[STOR]);
        vmMaxArr[BW]   = std::max(vm.BW._need, vmMaxArr[BW]);
    }
}

// svr的特征向量与vm的期待向量的匹配距离mat1
double getMat1(Server svr, VM vm) {
    double ret = 0.0;
    ret += pow((svr.CPU.get_feature() - vm.CPU._exp), 2);
    ret += pow((svr.RAM.get_feature() - vm.RAM._exp), 2);
    ret += pow((svr.STOR.get_feature() - vm.STOR._exp), 2);
    ret += pow((svr.BW.get_feature() - vm.BW._exp), 2);
    ret = sqrt(ret);
    
    return ret;
    
}

// 求svr剩余性能和vm所需性能匹配距离mat2
double getMat2(double *svrNormArr, double *vmNormArr) {
    double ret = 0.0;
    ret += pow((svrNormArr[CPU] - vmNormArr[CPU]), 2);
    ret += pow((svrNormArr[RAM] - vmNormArr[RAM]), 2);
    ret += pow((svrNormArr[STOR] - vmNormArr[STOR]), 2);
    ret += pow((svrNormArr[BW] - vmNormArr[BW]), 2);
    ret = sqrt(ret);
    
    return ret;
}

// 综合匹配距离
double getMinMatDis(double r1, double r2, double mat1, double mat2) {
    return r1*mat1 + r2*mat2;
}
