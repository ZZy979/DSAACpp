# DSAACpp
《数据结构、算法与应用C++语言描述》书中代码和习题解答

原书链接：<https://www.cise.ufl.edu/~sahni/dsaac/>

# 构建
使用CMake构建

```shell
cmake -G "Unix Makefiles" -B cmake-build
cmake --build cmake-build
```

# 单元测试
使用CTest运行单元测试

```shell
cd cmake-build/
ctest
```

# 代码目录
## ADT
ADT目录包含的数据结构类如下
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
* Queue：队列
    * [Queue](ADT/Queue/Queue.h)：队列抽象基类
    * [Array_queue](ADT/Queue/Array_queue.h)：队列的数组实现
* [utils.h](ADT/utils.h)：辅助函数

## 应用
Applications项目包含的数据结构应用如下
* Linear_list：线性表
    * [箱子排序](Applications/Linear_list/bin_sort.h)
    * [基数排序](Applications/Linear_list/radix_sort.h)
* Stack：栈
    * [括号匹配](Applications/Stack/parenthesis_matching.cpp)
    * [汉诺塔](Applications/Stack/towers_of_hanoi.cpp)
    * [列车车厢重排](Applications/Stack/rearranging_railroad_cars.cpp)
    * [开关盒布线](Applications/Stack/switch_box_routing.cpp)
    * [离线等价类](Applications/Stack/offline_equivalence_class.cpp)
