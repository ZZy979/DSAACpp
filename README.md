# DSAACpp
《数据结构、算法与应用C++语言描述》书中ADT代码
原书链接：<https://www.cise.ufl.edu/~sahni/dsaac/>

## 环境
Visual Studio 2019

## 目录结构
解决方案包含ADT, Tests和Applications三个项目
* ADT：包含所有数据结构类的代码
* Tests：ADT对应的单元测试（使用[Microsoft Unit Testing框架](https://docs.microsoft.com/zh-cn/visualstudio/test/how-to-use-microsoft-test-framework-for-cpp?view=vs-2019)）
* Applications：ADT的应用（也是单元测试项目）

## 数据结构
ADT项目包含的数据结构类如下
* Linear_list：线性表
    * [Linear_list](ADT/Linear_list/Linear_list.h)：线性表抽象基类
    * [Array_list](ADT/Linear_list/Array_list.h)：线性表的数组实现
    * [Vector_list](ADT/Linear_list/Vector_list.h)：线性表的vector实现
    * [Linked_list](ADT/Linear_list/Linked_list.h)：不带头节点的单向链表
    * [Circular_linked_list](ADT/Linear_list/Circular_linked_list.h)：带头节点的单向循环链表
* Matrix：矩阵
    * [Matrix](ADT/Matrix/Matrix.h)：矩阵
* Stack：栈
    * [Stack](ADT/Stack/Stack.h)：栈抽象基类
    * [Array_stack](ADT/Stack/Array_stack.h)：栈的数组实现
    * [Linked_stack](ADT/Stack/Linked_stack.h)：栈的链表实现
* [utils.h](ADT/utils.h)：辅助函数

## 应用
Applications项目包含的数据结构应用如下
* Linear_list：线性表
    * [bin_sort](Applications/Linear_list/bin_sort.h)：箱子排序
    * [radix_sort](Applications/Linear_list/radix_sort.h)：基数排序
