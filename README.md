# cosvr
    基于c++20协程实现的一套高效易用的actor服务器引擎框架；
    使用者可以基于框架提供的基础模块搭建自己想要的服务器框架，也可以直接开箱即用(后续会提供相关工具，根据配置生成基础框架)；
    提供云上，云下部署方案(会提供对应的工具链)；
    后续也会制定一套api规范，方便框架基础功能模块的替换；
    各功能模块都提供了简单易用的协程接口，彻底告别callback编程。

因为个人时间比较少，更新可能比较慢，但是有时间会持续更新，也欢迎大家参与一起开发；
文档后续会继续完善，代码仍需打磨，相关方案需要继续完善及改进，当前进度大致完成70%.

# 目录结构：
```
.
├── cmake           cmake文件
├── dep             依赖库
├── examples        相关模块示例
└── modules         引擎框架基础模块
    ├── agent       actor机制实现模块
    ├── app         app模块
    ├── cluster     集群模块
    ├── coder       编码器，支持protobuf，json，pod struct等协议
    ├── common      
    ├── config      yaml配置模块
    ├── error       错误处理机制模块
    ├── log         日志
    ├── net         网络相关模块
    ├── protocol    协议
    ├── redis       不依赖任何第三方库的redis客户端
    ├── rpc         rpc机制模块
    ├── timer       计时器模块
    ├── util        工具接口
    └── uuid        uuid
```

# 编译：
```
git clone https://github.com/wujiebocai/cosvr.git --recursive
cd cosvr
mkdir build
cd build
cmake ..
make -j
```