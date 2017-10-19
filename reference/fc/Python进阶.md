# Python进阶

## 类

### 定义

```python
class Dog():
    def __init__(self, name, age):
        """初始化属性"""
        self.name = name
        self.age = age 
        
    def sit(self):
        print(self.name.title() + "is now sitting")
        
    def roll_over(self):
        print(self.name.title() + "rolled over!")
```

`__init__`是一个特殊的方法，每次创建类的实例就会自动执行这个方法。

`self`是实参，类本身的引用，让实例能够访问类中的属性和方法。

`self.xx`表示其中变量都可以供类中所有方法使用。还可以用类的任何实例来访问这些变量。

### 创建实例

和变量赋值，函数赋值一致。

### 使用实例

#### 给属性指定默认值

类对的每个属性都**必须**有默认值，哪怕这个值是0或者空字符串。在方法`__init__()`中设置这种初始值是可行的，但如果对某个属性这样做了，就无需包含为它提供初始值得形参。

#### 修改属性的值

- 直接修改

  创建实例后访问修改

- 通过方法修改属性

  在类中创建一个修改此属性的方法

  ```python
  class Dog():
      def __init__(self, name, age):
          """初始化属性"""
          self.name = name
          self.age = age 
          self.character = 'kind'
         
      def update_charcater(self, char):
          self.character = char
          
  """创建实例后调用up..函数修改character参数"""
  ```



### 继承

#### 定义子类

一个类继承另一个类时，它将会自动的获得另一个类的所有属性和方法；原有的类称为父类，而新类称为子类。

子类继承了父类额所有属性和方法，同时还可以定义自己的属性和方法。

```python
class book():
    def __init__(self, make, use):
        self.make = make
        self.use = use

    def description(self):
        print("The Book is maked by"+self.make+" I use it to "+self.use)


class Learning_python(book):
    def __init__(self, make, use):
        super().__init__(make, use)
       
    
>>> my_book = Learning_python('paper', 'learning program language')
>>> my_book.description()
The Book is maked bypaper I use it to learning program language
```

- 创建子类时，父类必须位于子类之前。`python`是脚本语言，会一行行的解释。
- 定义子类时，必须在括号内指定父类名称。
- `super()`这个特殊函数，能联系父类和子类，使子类使用父类的所有属性和方法。


#### 给子类定义属性和方法

给子类添加新属性和方法同于给类添加

#### 重写父类方法

在子类中写重名的父类方法即可。







## 文件

### 读取整个文件

```python
with open('url') as file_object:
    contents = file_object.read()
    print()
```

- `with`是在不再需要需要访问文件后将其关闭
- `read`在读取文件时，读取到文件末尾会返回一个空字符串，将其打印时会显示为一个空行。

### 写入文件

```python
with open(filename, 'w') as file_object:
    file_object.write("I love programming.")
```

- `w`以写入模式打开文件
- `r`读取模式
- `a`附加模式
#### 存储数据

采用`json`文件来存储数据

- 使用`json.dump(data, filename)`
- 使用`json.load()`读取到内存






## 异常

使用`try-except`，例如使用它处理`ZeroDivisionError`异常。

```python
try:
    print(5/0)
except ZeroDivisionError:
    print("You can't divide by zero")
```

还可添加`else`部分，使依赖`try`成功执行的代码在`else`中执行。







# 测试

### 单元测试（针对函数进行测试）

```python
import unittest
from city_functions import  location


class CitiesTestCase(unittest.TestCase):

    def test_city_country(self):         #必须使用test开头
        city_name = location('shanghai', 'china')
        self.assertEqual(city_name, 'Shanghai,China') #断言方法


unittest.main()


```

|           方法            |      用途      |
| :---------------------: | :----------: |
|    assertEqual(a,b)     |  核实 a == b   |
|   assertNotEqual(a,b)   |  核实 a != b   |
|      assertTrue(x)      |   核实x为True   |
|     assertFalse(x)      |  核实x为False   |
|  assertIn(item, list)   | 核实item在list  |
| assertNotIn(item, list) | 核实item不在list |

​        

