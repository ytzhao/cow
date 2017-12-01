## C++ const
### const特性
1. 限定符声明变量只能被读
```cpp
const int i = 5;
int j = 0;
i = j;  // fail
```
2. 必须初始化
```cpp
const int i = 5;    // ok
const int j;        // fail
```

3. 在C++中const默认具有内部链接性
在a.h文件中：
```cpp
const int i = 10;
```
在b.h文件中引用时用：
```cpp
extern const int i;
```

### 常见用法
1. const常量: const常量有效数据类型，而宏常量没有数据类型。编译器可以对前者进行安全检查，而对后者只能进行字符替换，没有类型安全检查。

2. const修饰类的数据成员
```cpp
class A 
{
    const int size;
}
```
const数据成员的初始化只能在类的**构造函数**的初始化表中进行。

3. const修饰指针的情况
```cpp
int b = 500;

const int *a = &b;
int const *a = &b;
int* const a = &b;
const int* const a = &b;
```
- const位于\*的**左**边：const就是修饰指针所指向的变量，即指针指向为常量
- const位于\*的**右**边：const就是修饰指针本身，即指针本身是常量

### const初始化
```cpp
const int a = 10;

int* b = new int;
const int* c = b;

const int* d = new int;

int e;
const int& f = e;   // 这样f只能访问声明为const的函数，而不能访问一般的成员函数。
```

### const在函数声明中的运用
```cpp
void A(const int* a);   // [1]
void B(const int& b);   // [2]
void C() const;         // [3]
const int D();          // [4]
```
[1][2]: 修饰参数的const：在函数体中，按照const所修饰的部分进行常量化，不能对传递进来的指针内容/引用对象进行改变，保护了原指针所指向的内容/原对象的属性。   
[3]：任何不会修改数据成员的函数都应该声明为const类型，如果在编写const成员函数时，不小心修改了数据成员，或者调用了其他非const成员函数，编译器将报错，大大提高了程序的鲁棒性。
```cpp
class Stack
{
    public:
        void Push(int elem);
        int  Pop(void);
        int  GetCount(void) const;  // const成员函数
    private:
        int m_num;
        int m_data[100];
};

int Stack::GetCount(void) const {
    m_num++;    // 编译错误，企图修改数据成员m_num
    Pop();      // 编译错误，企图调用非const函数
    return m_num;
}
```
[4]：一般情况下，函数的的返回值为某个对象时，如果将其声明为const时，多用于操作符的重载。
