# DSAACpp
《数据结构、算法与应用C++语言描述》书中ADT代码
原书链接：<https://www.cise.ufl.edu/~sahni/dsaac/>

## 环境
Visual Studio 2019

## 目录结构
解决方案包含ADT和Tests两个项目
* ADT：包含所有数据结构类的代码
* Tests：ADT对应的单元测试（使用[Microsoft Unit Testing框架](https://docs.microsoft.com/zh-cn/visualstudio/test/how-to-use-microsoft-test-framework-for-cpp?view=vs-2019)）

## 数据结构
ADT项目包含的数据结构类如下
* Linear_list：线性表
    * [Linear_list](ADT/Linear_list/Linear_list.h)：线性表抽象基类
    * [Array_list](ADT/Linear_list/Array_list.h)：线性表的数组实现
    * [Vector_list](ADT/Linear_list/Vector_list.h)：线性表的vector实现
    * [Linked_list](ADT/Linear_list/Linked_list.h)：不带头节点的单向链表
    * [Circular_linked_list](ADT/Linear_list/Circular_linked_list.h)：带头节点的单向循环链表
* [utils.h](ADT/utils.h)：辅助函数
