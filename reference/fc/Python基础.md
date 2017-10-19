---
title: Python基础
date: 2017-05-16 20:30:11
categories: Python
tags: [Python, 基础语法]
---



## Python 之美

```markdown
Beautiful is better than ugly.

Explicit is better than implicit.

Simple is better than complex.

Complex is better than complicated.

Flat is better than nested.

Sparse is better than dense.

Readability counts.

Special cases aren't special enough to break the rules.

Although practicality beats purity.

Errors should never pass silently.

Unless explicitly silenced.

In the face of ambiguity, refuse the temptation to guess.

There should be one-- and preferably only one --obvious way to do it.

Although that way may not be obvious at first unless you're Dutch.

Now is better than never.

Although never is often better than *right* now.

If the implementation is hard to explain, it's a bad idea.

If the implementation is easy to explain, it may be a good idea.

Namespaces are one honking great idea -- let's do more of those!
```




## 变量和简单数据类型

#### 输入输出

```python
#输出
print("Hello, World!")
#输入
text = input("Please input something")
```

#### 变量

- 变量名只能包含字母、数字和下划线
- 变量名不能包含空格
- 不能将`Python`关键字当做变量名


#### 字符串
用`''`或者`""`都可以包含字符串。对字符串中单词有常见的几种方法：
- `.title()` 以首字母大写显示每个单词

- `.upper()` 字符串全为大写

- `.lower()` 字符串全为小写

- `.capitalize()` 字符串首字母大写

- `.swapcase()`字母大小写转换

- `+` 合并字符串

- `\t`和`\n`制造空白

- `.strip()`删除所有空白（删除的空白并没有保存到原字符串，下同）

- `.rstrip()`删除尾部空白

- `.lstrip()`删除首部空白

- `三重引号`在三重引号内字符串会把转义、制表符、换行都认定为字符串的一部分

- `in` `not in`

- `isX`
  - `.isupper()` `.islower()`
  - `.isalpha()`如果字符串只包含字母，而且非空
  - `.isalnum()`如果字符串只包含字母和数字，并且非空
  - `.isdecimal()`如果字符串只包含数字字符，并且非空
  - `.isspace()`如果字符串只包含空格、制表符和换行，并且非空
  - `.istitle()`
  - `.startswith()` `.endswith()`

- `.find()`

- `.count()`

- `.split()` 分割

- `''.join()` 合并

#### 数字
- `0b/0B`二进制

- `0o/0O`八进制

- `0x/0X`十六进制

#### 浮点数（遵循`IEEE754`标准）

`int() float() str()`进行类型转换

`None`----`NoneType`

#### 注释

`python`中使用`#`来表示注释





## 列表(引用操作)

列表是由一系列按特定顺序排列的元素组成的**值**。

列表用下标取值。（从`0`开始，可取负值，从倒数开始`-1,-2`）

#### 列表基础操作
- `+`列表连接

- `.index()`列表索引

- 列表添加元素

  - `.append()`列表末尾添加元素
  - `.insert(index, obj)`特定位置添加元素


- 列表删除元素

  - 索引删除
    - `del list[index]`删除元素，需指定元素索引，永久删除
    - `.pop(boj=list[-1])`默认弹出最后一个元素，也可弹出指定索引元素
  - 值删除
    - `.remove()`

- 列表元素复制

  - `import copy      copy.copy() 浅拷贝 只拷贝父对象，不会拷贝对象的内部的子对象。  `
  - `import copy     copy.deepcopy() 深拷贝 拷贝对象及其子对象 `

- 排序
  - `.sort()`对列表进行永久性排序

    `.sort(reverse=True)`逆序排序
  - `sorted()`不影响原始排列顺序的

- 列表反转`.reverse()`永久反转,反转的是**列表元素的排列顺序**

#### 遍历

`for x in list`

#### 创建数值列表
`range(start, end, scan)`输出数值为`[start, start+1,...,end-1]`

#### 列表解析

>列表解析式是将一个列表（实际上适用于任何可迭代对象（iterable））转换成另一个列表的工具。在转换过程中，可以指定元素必须符合一定的条件，才能添加至新的列表中，这样每个元素都可以按需要进行转换。

```python
result = []
for x in range(1,10):
  result = x*2
#列表解析式  
result = [x*2 for x in range(1,10)]
```
#### 切片

`[:]`提取从开头到结尾的整个字符串

`[start:]`从start提取到结尾

`[:end]`从开头提取到结尾-1

`[start:end]`从`start`提取到`end-1`

`[start:end:step]`从`start`提取到`end-1`，每`step`个字符提取一个
```python
>>> spam = ['cat', 'bat', 'rat', 'elephant']
>>> spam[0:3]  #从索引0开始到索引2，不包含3，共3个元素
['cat', 'bat', 'rat']
>>> spam[1:3]
['bat', 'rat']
>>> spam[0:-1] #从索引0到最后一个元素，不包含最后一个索引为-1的元素
['cat', 'bat', 'rat']
>>> spam[:2] #从索引0到1
['cat', 'bat']
>>> spam[1:] #从索引1到end
['bat', 'rat', 'elephant']
>>> spam[:] #列表复制
['cat', 'bat', 'rat', 'elephant']
```
#### 元组

特殊的列表（不可变列表）

修改元组只能重新赋值





## 流程

`True` `False`

`and` `or` `not` `in` `==`

`if - else`

`if - elif - else`

`while`

`for in`





## 字典

`d = {key1: value1, key2: value2}`

字典是**不排序**的

#### 对字典的基本操作

```python
#访问字典中的值
print(d[key1]） #value1

#添加键值
d['like'] = 'cat'

#创建空字典
mycat = {}

#修改值
d['like'] = 'dog'

#删除键-值对
del d['like']
```

#### 字典的遍历

```python

# 遍历键
>>> a = {'like': 'cat', 'heat' : 'dog'}
>>> for k in a:
	   print(k)

heat
like

>>> for k in a.keys():
	print(k.title())
# keys() 并非只能用于遍历，实际上它返回的是一个列表，其中包含字典中的所有键

Heat
Like
# 遍历值
>>> for v in a.values():
	print(v.upper())


DOG
CAT

# 遍历键-值
>>> for k, v in a.items():
	   print(k+ ' '+ v)


heat dog
like cat
```

用`in`检查字典中是否存在键或值

`.get(s1, s2)`
- `s1`要取得的值得键

- `s2`如果键不存在返回的备用值

`.setdefault(x1, x2)`
- `x1`要检查的键

- `x2`如果该键不存在时要设置的值（如果该键确实存在，方法会返回键的值）




## 函数

```python
def fun_name(参数...):
  return #如果函数没有return，python会自动在函数末尾加 return None
```

####  参数传递

-  关键字实参

```python
def fun1(para1, para2):
	...
    
fun1(para1 = 'xx', para2 = 'xx')
fun1(para2 = 'xx', para1 = 'xx')
```

指定函数参数的值，直接在实参中将名称和值关联起来

- 默认值

```python
def fun2(para1, para2 = 'xx'):
	...
    
fun2(x1,)
```

在使用默认值时，在形参列表中必须先列出没有默认值的形参，再列出有默认值的实参。

#### 让实参变为可选

```python
def get_formatted_name(first_name, last_name, middle_name=''):
    ...
```

空字符串为`False`，但如果调用过中提供了`middle_name`，那么它将为`True`。

#### 禁止函数修改列表

`function_name(list_name[:])`

#### 传递任意数量的实参

- 使用`*para_name`作为形参接受任意数量实参

```python
>>> def fun1(*names):
	print(names)

	
>>> fun1("fc")
('fc',)
>>> fun1("aa","bb","cc")
('aa', 'bb', 'cc')
```

- 使用任意数量的关键字实参

```python
>>> def build_profile(first, last, **user_info):
	profile = {}
	profile['first_name'] = first
	profile['last_name'] = last
	for key, value in user_info.items():
		profile[key] = value
	return profile

>>> user_profile = build_profile('albert', 'einstein',
			     location='preiceton',
			     field='physics')
>>> print(user_profile)
{'first_name': 'albert', 'location': 'preiceton', 'field': 'physics', 'last_name': 'einstein'}
```





##  模块

导入整个模块：

```python
import module_name

modul_name.function_name()
```

导入特定函数：

```python
from module_name import function_name(,function_name2,...)

function_name()
```
用`as`指定别名

```python
from module_name import function_name(,function_name2,...) as fn(,fn1,...)

fn()
```
用`as`给模块指定别名

```python
import module_name as mn

mn.function_name()
```

导入模块中所有函数

```python
from module_name import *

Every_function()
```
导入类

- 导入单个类

  ```python
  from pyfile_name import class_name
  ```

- 从一个模块中导入多个类

  ```python
  from pyfile_name import class_name1, class_name2
  ```

- 导入整个模块

  ```python
  import pyfile_name
  ```

- 导入模块中的所有类

  ```python
  import module_name import *
  ```

  ​