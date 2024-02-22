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
## 第1章 C++回顾
### 1.5 自有数据类型
* [Currency类](ch01/Currency.h)

## 第5章 线性表——数组描述
* [Linear_list](ADT/Linear_list.h)：线性表抽象基类
* [Array_list](ADT/Array_list.h)：线性表的数组实现
* [Vector_list](ADT/Vector_list.h)：线性表的vector实现
* [Linked_list](ADT/Linked_list.h)：不带头节点的单向链表
* [Circular_linked_list](ADT/Circular_linked_list.h)：带头节点的单向循环链表

## 第6章 线性表——链式描述
* [箱子排序](ch06/bin_sort.h)
* [基数排序](ch06/radix_sort.h)

## 第7章 数组和矩阵
* [Matrix](ADT/Matrix.h)：矩阵

## 第8章 栈
### 数据结构
* [Stack](ADT/Stack.h)：栈抽象基类
* [Array_stack](ADT/Array_stack.h)：栈的数组实现
* [Linked_stack](ADT/Linked_stack.h)：栈的链表实现

### 应用
* [括号匹配](ch08/parenthesis_matching.cpp)
* [汉诺塔](ch08/towers_of_hanoi.cpp)
* [列车车厢重排](ch08/rearranging_railroad_cars.cpp)
* [开关盒布线](ch08/switch_box_routing.cpp)
* [离线等价类](ch08/offline_equivalence_class.cpp)

## 第9章 队列
* [Queue](ADT/Queue.h)：队列抽象基类
* [Array_queue](ADT/Array_queue.h)：队列的数组实现
