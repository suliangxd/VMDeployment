//
//  main.cpp
//  VMDeployment
//
//  Created by Liang on 16/5/24.
//  Copyright © 2016年 Liang. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cstring>
#include <string>

#include "Server.hpp"
#include "VM.hpp"
#include "comm.hpp"

#define READFILE
#define WRITEFILE
using namespace std;

const int FEATURE_NUM = 5;

vector<VM> vmList[30];
vector<Server> svrList;
vector<double> usePercent[5];
// 每次请求虚机数量
int vmNum[30];
// 虚机批量请求次数
int vmCaseNum;
// 服务器数量
int svrNum;


// 初始化
void init() {
    for (int i = 0; i < 30; i++)
        vmList[i].clear();
    for (int i = 0; i < 5; i++)
        usePercent[i].clear();
    
    svrList.clear();
    memset(vmNum, 0, sizeof(vmNum));
    vmCaseNum = 0;
    svrNum = 0;
}

// 数据输入
void input() {
    
#ifdef READFILE
    freopen("/Users/baidu/Desktop/VMDeployment/VMDeployment/data.txt", "r", stdin);
#endif
    
    cin >> svrNum;
    read_svr(svrList, svrNum);
    cin >> vmCaseNum;
    for(int i = 0; i < vmCaseNum; i++) {
        cin >> vmNum[i];
        read_vm(vmList[i], vmNum[i]);
    }
}

// 虚机部署情况输出
void outVmSetRet() {

#ifdef WRITEFILE
    freopen("", "w", stdout);
#endif
    for (int cas = 0; cas < vmCaseNum; cas++) {
        for (auto vm : vmList[cas]) {
            cout << vm.svrSetIndex;
        }
        cout << endl;
    }
}

void dataResult() {
    
#ifdef WRITEFILE
    freopen("/Users/baidu/Desktop/VMDeployment/VMDeployment/result_2.txt", "w", stdout);
#endif
    for (int i = 0; i < vmCaseNum; i++) {
        cout << "第" << i << "次虚机批量部署结果: " << endl;
        cout << "部署成功率:  " << getVmSuccPercent(vmList[i], vmNum[i]) << endl;
        for (auto vm : vmList[i]) {
            cout << vm.svrSetIndex <<" ";
        }
        cout << endl;
    }
    
    cout << endl << "部署完后服务器负载情况: " << endl;
    getCPUPercent(svrList, usePercent[0]);
    getRAMPercent(svrList, usePercent[1]);
    getSTORPercent(svrList, usePercent[2]);
    getBWPercent(svrList, usePercent[3]);
    
    cout << endl << "CPU: " << endl;
    for (auto percent : usePercent[0])
        cout << percent << " ";
    
    cout << endl << "RAM: " << endl;
    for (auto percent : usePercent[1])
        cout << percent << " ";
    
    cout << endl << "STOR" << endl;
    for (auto percent : usePercent[2])
        cout << percent << " ";
    
    cout << endl << "BW" << endl;
    for (auto percent : usePercent[3])
        cout << percent << " ";
    cout << endl;
}
// 贪心算法
void GreedAlg() {
    
    init();
    input();
    
    /*********************    算法实现部分    *********************/
    // 遍历每一次的批量部署请求
    for (int cas = 0; cas < vmCaseNum; cas++) {
        // 遍历当前请求中所有vm
        for (int vm_index = 0; vm_index < vmList[cas].size(); vm_index++) {
            VM & vm = vmList[cas][vm_index];
            double MaxDis = -1;
            int MaxSvrIndex = 0;
            // 遍历所有svr, 在性能最优的svr上部署
            for (int svr_index = 0; svr_index < svrList.size(); svr_index++) {
                Server & svr = svrList[svr_index];
                if (isUseFul(svr, vm)) {
                    double eulerDis = getEulerDis(svr, vm);
                    if (eulerDis > MaxDis) {
                        MaxDis = eulerDis;
                        MaxSvrIndex = svr_index;
                    }
                }
            }
            
            // 需要更新部署的svr
            if (MaxDis != -1) {
                svrList[MaxSvrIndex].CPU.add(vm.CPU._need);
                svrList[MaxSvrIndex].RAM.add(vm.RAM._need);
                svrList[MaxSvrIndex].STOR.add(vm.STOR._need);
                svrList[MaxSvrIndex].BW.add(vm.BW._need);
                vm.svrSetIndex = MaxSvrIndex;
            }
        }
    }
    /*********************    结果输出与分析    *********************/
    dataResult();
}

// 最小匹配距离算法
void MatchingDisAlg() {
    double r1 = 0.5;
    double r2 = 0.5;
    
    init();
    input();
    
    /*********************    算法实现部分    *********************/
    
    // 遍历每一次的批量部署请求
    for (int cas = 0; cas < vmCaseNum; cas++) {
        // 当前批次下，vm和svr的峰值
        int vmMinArr[FEATURE_NUM], vmMaxArr[FEATURE_NUM];
        int svrMinArr[FEATURE_NUM], svrMaxArr[FEATURE_NUM];
        
        getVmMinAndMaxArr(vmList[cas], vmMinArr, vmMaxArr);
        getSvrMinAndMaxArr(svrList, svrMinArr, svrMaxArr);
        
        // 遍历当前请求中所有vm
        for (int vm_index = 0; vm_index < vmList[cas].size(); vm_index++) {
            VM & vm = vmList[cas][vm_index];
            double bestMatDis = INT_MAX;
            int bestSvrIndex = -1;
            // 遍历所有svr, 在性能最优的svr上部署
            for (int svr_index = 0; svr_index < svrList.size(); svr_index++) {
                Server & svr = svrList[svr_index];
                // 当前svr可部署
                if (isUseFul(svr, vm)) {
                    // 记录svr 和 vm归一化结果
                    double svrNormArr[FEATURE_NUM];
                    double vmNormArr[FEATURE_NUM];
                    vmNormaliza(vm, vmMinArr, vmMaxArr, vmNormArr);
                    svrNormaliza(svr, svrMinArr, svrMaxArr, svrNormArr);
                    
                    double mat1 = getMat1(svr, vm);
                    double mat2 = getMat2(svrNormArr, vmNormArr);
                    
                    double matDis = getMinMatDis(r1, r2, mat1, mat2);
                    if (bestMatDis > matDis) {
                        bestMatDis = matDis;
                        bestSvrIndex = svr_index;
                    }
                    
                }
            }
            // 需要更新部署的svr
            if (bestSvrIndex != -1) {
                svrList[bestSvrIndex].CPU.add(vm.CPU._need);
                svrList[bestSvrIndex].RAM.add(vm.RAM._need);
                svrList[bestSvrIndex].STOR.add(vm.STOR._need);
                svrList[bestSvrIndex].BW.add(vm.BW._need);
                vm.svrSetIndex = bestSvrIndex;
            }
        }
    }
    
    /*********************    结果输出与分析    *********************/
    dataResult();
}


int main(int argc, const char * argv[]) {
      //GreedAlg();
    
     MatchingDisAlg();
    return 0;
}