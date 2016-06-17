# VMDeployment
## 虚拟机部署算法仿真

------

虚拟机部署算法仿真实验平台，模拟批量虚拟机部署请求，并在数据中心部署。    
给出相应的数据结构，可根据不同算法，实现不同部署逻辑

###代码目录
├── CMakeLists.txt  cmake脚本   
├── Makefile        makefile脚本，由cmake生成   
├── Server.cpp      服务器数据结构    
├── Server.hpp    
├── VM.cpp          虚拟机数据结构    
├── VM.hpp    
├── comm.cpp        算法模块需要的公共函数    
├── dataMaker.py    数据生成器脚本    
└── main.cpp        执行程序，在这里面写算法逻辑    

### 程序流程图
![流程图](http://i.niupic.com/images/2016/06/17/F1RiDa.png)

### 示例代码中算法的参考文献
1. [云计算下基于匹配距离的虚拟机批量部署算法](http://www.chinacloud.cn/upload/2014-05/14050209528743.pdf)
