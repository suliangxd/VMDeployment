# -*- coding: utf-8 -*-

import random, os

def rand_int(a, b):
    '''
    Return the integer From [a,b].
    '''
    return random.randint(a, b);

conf_svr = dict(svr_num = 20, cpu_max = 8000, cpu_min = 2000, ram_max = 256, ram_min = 64,
                stor_max = 5000, stor_min = 1000, bw_max = 5000, bw_min = 2000)

conf_vm = dict(vm_case_num = 20, vm_num = 10, cpu_max = 600, cpu_min = 200,
               ram_max = 16, ram_min = 1, stor_max = 400, stor_min = 100, bw_max = 400, bw_min = 150)

if __name__ == '__main__':

    file_handle = open("/Users/baidu/Desktop/VMDeployment/VMDeployment/data.txt", 'w')
    # 服务器数量
    svr_num = conf_svr['svr_num']
    write_str = str(svr_num) + '\n'
    file_handle.write(write_str)
    
    for i in range(0, svr_num):
        cpu_all = rand_int(conf_svr['cpu_min'], conf_svr['cpu_max'])
        cpu_rev = 0
        ram_all = rand_int(conf_svr['ram_min'], conf_svr['ram_max'])
        ram_rev = 0
        stor_all = rand_int(conf_svr['stor_min'], conf_svr['stor_max'])
        stor_rev = 0
        bw_all = rand_int(conf_svr['bw_min'], conf_svr['bw_max'])
        bw_rev = 0
    
        write_str = str(cpu_all) + ' ' + str(cpu_rev) + '\n'
        write_str += str(ram_all) + ' ' + str(ram_rev) + '\n'
        write_str += str(stor_all) + ' ' + str(stor_rev) + '\n'
        write_str += str(bw_all) + ' ' + str(bw_rev) + '\n'

        file_handle.write(write_str)
    
    # vm批次
    vm_case_num = conf_vm['vm_case_num']
    write_str = str(vm_case_num) + '\n'
    file_handle.write(write_str)

    for cas in range(0, vm_case_num):
        # 虚机个数
        vm_num = conf_vm['vm_num']
        write_str = str(vm_num) + '\n'
        file_handle.write(write_str)

        for i in range(0, vm_num):
            cpu_need = rand_int(conf_vm['cpu_min'], conf_vm['cpu_max'])
            cpu_exp = 0.25
            ram_need = rand_int(conf_vm['ram_min'], conf_vm['ram_max'])
            ram_exp = 0.25
            stor_need = rand_int(conf_vm['stor_min'], conf_vm['stor_max'])
            stor_exp = 0.25
            bw_need = rand_int(conf_vm['bw_min'], conf_vm['bw_max'])
            bw_exp = 0.25
            
            write_str = str(cpu_need) + ' ' + str(cpu_exp) + '\n'
            write_str += str(ram_need) + ' ' + str(ram_exp) + '\n'
            write_str += str(stor_need) + ' ' + str(stor_exp) + '\n'
            write_str += str(bw_need) + ' ' + str(bw_exp) + '\n'
            file_handle.write(write_str)
                
                
    file_handle.close()
