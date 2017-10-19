# Markdown 简介及进阶

[TOC]

## Markdown简介

**Markdown** 是一种[轻量级标记语言](https://zh.wikipedia.org/wiki/%E8%BD%BB%E9%87%8F%E7%BA%A7%E6%A0%87%E8%AE%B0%E8%AF%AD%E8%A8%80)，创始人为[约翰·格鲁伯](https://zh.wikipedia.org/wiki/%E7%B4%84%E7%BF%B0%C2%B7%E6%A0%BC%E9%AD%AF%E4%BC%AF)（John Gruber）。它允许人们“使用易读易写的纯文本格式编写文档，然后转换成有效的[XHTML](https://zh.wikipedia.org/wiki/XHTML)(或者[HTML](https://zh.wikipedia.org/wiki/HTML))文档”。这种语言吸收了很多在[电子邮件](https://zh.wikipedia.org/wiki/%E7%94%B5%E5%AD%90%E9%82%AE%E4%BB%B6)中已有的纯文本标记的特性[^0]。

本文所用**Markdown** 语法基于[GitHub Flavored Markdown](https://help.github.com/articles/github-flavored-markdown/) 。

[^0]: 维基百科中Markdown的介绍。




## Markdown语法

### 标题

  ```markdown
  # 一级标题
  ## 二级标题
  ### 三级标题
  #### 四级标题
  ##### 五级标题
  ###### 六级标题
  ```
示例：
![标题](C:\Users\fc\Pictures\markd\标题.png)

也可以加`=====`和`-----`来生成标题。

```markdown
这是一个一级标题
==============


这是一个二级标题
----------------
```





### 字体

```markdown
使用**粗体**表示粗体

使用*斜体*表示斜体

使用***加粗斜体***表示加粗斜体

使用~~删除线~~表示删除线
```
示例：

**粗体**

*斜体*

***加粗斜体***

~~删除线~~





### 列表

- 无序列表

  使用`+ * -`表示无序列表

  示例：
  ```markdown
  - Unordered list1
  - Unordered list2
  - Unordered list3
  ```

  - Unordered list1
  - Unordered list2
  - Unordered list3

- 有序列表

  使用`数字和点生成`生成有序列表

  ```markdown
  1. Ordered list1
  2. Ordered list2
  3. Ordered list3
  ```

  1. Ordered list1
  2. Ordered list2
  3. Ordered list3




### 链接

- 行内链接
  - 文字链接

    使用`[描述](链接地址)`为文字加外链接。

    示例：

    这是[B站](http://www.bilibili.com/)的官网。

  - 图片链接
    使用`![描述](链接地址)`添加图片.

    ![本地图片](C:\Users\fc\Pictures\Camera Roll\5462876_150854046500_2.jpg "beautiful picture")

    > 注：**图片最好还是存到云上,比如放到Github上,然后用其链接作图片地址.**

  - 自动链接

     ```markdown
     <http://www.baidu.com/>
     ```
     <http://www.baidu.com/>

- 引用链接

  ```markdown
  上面的图片是我从[视觉中国][1]中找的素材，我想把它存到[Github][2]上。

  [1]:https://www.vcg.com "vcg"
  [2]:https://github.com "Github"
  ```

   上面的图片是我从[视觉中国][1]中找的素材，我想把它存到[Github][2]上。	

  [1]:https://www.vcg.com "vcg"
  [2]:https://github.com "Github"







### 文字引用

使用`>`表示文字引用

示例：

> 苟利国家生死以，岂因祸福避趋之。





### 代码块

- 行内代码块

  使用` ``  `表示行内代码

  示例：

  `print("hello,world")`

- 加强的代码块
  ```
  ​```编程语言类型(python/java/.....)
  	code
  ​```
  ```

  示例：

  ```c++
  /**
  ​```c++
  	code
  ​```
  **/
  #include <iostream>
  using namespace std;
  int main()
  {
      cout << "Hello, world!" << endl;
      return 0;
  }
  ```






### 表格

```markdown
| Item       |    Value | Qty  |
| :--------- | -------: | :--: |
| 短线分隔了表头和表身 |    |      |
| :在左边表示此列左对齐| :在右边表示此列右对齐 |  两边都有冒号表示此列居中   |
| Phone      |   12 USD |  12  |
| Pipe       |    1 USD | 234  |
```

| Item          |         Value |      Qty      |
| :------------ | ------------: | :-----------: |
| 短线分隔了表头和表身    |               |               |
| `:`在左边表示此列左对齐 | `:`在右边表示此列右对齐 | 两边都有`:`表示此列居中 |
| Phone         |        12 USD |      12       |
| Pipe          |         1 USD |      234      |





 ### 注脚

```markdown
使用 Markdown[^1]可以效率的书写文档, 直接转换成 HTML[^2], 你可以使用 Typora[^Le] 编辑器进行书写。

[^1]:Markdown是一种纯文本标记语言

[^2]:HyperText Markup Language 超文本标记语言

[^Le]:免费Markdown编辑软件.
```

使用 Markdown[^1]可以效率的书写文档, 直接转换成 HTML[^2], 你可以使用 Typora[^Le] 编辑器进行书写。

[^1]: Markdown是一种纯文本标记语言
[^2]: HyperText Markup Language 超文本标记语言
[^Le]: 免费Markdown编辑软件.

> 注： **脚注自动被搬运到最后面，请到文章末尾查看，并且脚注后方的链接可以直接跳转回到加注的地方。**





### 目录

在想生成目录的地方输入`[TOC]`





### LaTex 公式

#### 基础



##### 行中公式

`$ 数学公式$`

示例：

`质能守恒方式为：$E = mc^2$`

 质能守恒方式为：$E = mc^2$



##### 独立公式

`$$ 数学公式 $$`

示例：

`这是一个不在行内的公式:$$\sum_{i=1}^n a_i=0$$`

这是一个在行内的公式:$\sum_{i=1}^n a_i=0$

这是一个不在行中的公式：

$$
\sum_{i=1}^n a_i=0
$$



##### 自动编号的公式

```
\begin{equation}
数学公式
\label{eq:当前公式名}
\end{equation}
```

```markdown
\begin{equation}
x = \int _{x} ^\infty \frac {x}{x+1}
\label{eq:examp}
\end{equation}
```

$$
\begin{equation}
x = \int _{x} ^\infty \frac {x}{x+1}
\label{eq:1}
\end{equation}
$$



##### 空格

有四种宽度的空格可以使用： `\,`、`\;`、`\quad` 和 `\qquad` 。

```latex
$$ a \, b \mid a \; b \mid a \quad b \mid a \qquad b $$
```


$$
a \, b \mid a \; b \mid a \quad b \mid a \qquad b
$$


##### 希腊字母


| 名称      | 大写   | Tex      | 小写   | Tex      |
| ------- | ---- | -------- | ---- | -------- |
| alpha   | AA   | A        | αα   | \alpha   |
| beta    | BB   | B        | ββ   | \beta    |
| gamma   | ΓΓ   | \Gamma   | γγ   | \gamma   |
| delta   | ΔΔ   | \Delta   | δδ   | \delta   |
| epsilon | EE   | E        | ϵϵ   | \epsilon |
| zeta    | ZZ   | Z        | ζζ   | \zeta    |
| eta     | HH   | H        | ηη   | \eta     |
| theta   | ΘΘ   | \Theta   | θθ   | \theta   |
| iota    | II   | I        | ιι   | \iota    |
| kappa   | KK   | K        | κκ   | \kappa   |
| lambda  | ΛΛ   | \Lambda  | λλ   | \lambda  |
| mu      | MM   | M        | μμ   | \mu      |
| nu      | NN   | N        | νν   | \nu      |
| xi      | ΞΞ   | \Xi      | ξξ   | \xi      |
| omicron | OO   | O        | οο   | \omicron |
| pi      | ΠΠ   | \Pi      | ππ   | \pi      |
| rho     | PP   | P        | ρρ   | \rho     |
| sigma   | ΣΣ   | \Sigma   | σσ   | \sigma   |
| tau     | TT   | T        | ττ   | \tau     |
| upsilon | ΥΥ   | \Upsilon | υυ   | \upsilon |
| phi     | ΦΦ   | \Phi     | ϕϕ   | \phi     |
| chi     | XX   | X        | χχ   | \chi     |
| psi     | ΨΨ   | \Psi     | ψψ   | \psi     |
| omega   | ΩΩ   | \Omega   | ωω   | \omega   |



##### 上标和下标

上标和下标分别使用`^`和`_`,例如`$x_z^y$` ：$$x_z^y$$. 但是上下标仅仅对下一个组起作用。一个组即单个字符或者`{...}`包围起来的内容。如上面的公式，我要得到 $$x_{z^y}$$ 这个公式就必须用括号`$x_{z^y}$`。对于单个字符也要用括号，要得到公式 $$x^{10}$$ ,就必须带大括号`$x^{10}$ `，否则`$x^10$ `：$$x^10$$，那就贻笑大方了。



##### 括号

1. 小括号和方括号：`() []`

2. 大括号：大括号用来分组，因此要用`\{和\}`表示大括号,也可以用`\lbrace和\rbrace`。如`$x = \{1,2,3,4,...n\}$` ：  $$x = \{1,2,3,4,...n\}$$

3. 使用`\langle` 和`\rangle`表示左，右尖括号。$\langle$  $\rangle$

4. 上取整 `\lceil x \rceil` ： $$\lceil x \rceil$$

5. 下取整`\lfloor x \rfloor` ：$$\lfloor x \rfloor$$

6. 显示大号的括号或分隔符时，用`\left`和`\right`命令。

   示例：

   `$$f(x,y,z) = x^2 + x^y \left(3+\frac{7x+5}{1+y^z} \right)$$`

   ​
   $$
   f(x,y,z) = x^2 + x^y \left( 3+\frac{7x+5}{1+y^z} \right)
   $$
   ​
   ​



##### 累加，累乘，交集，并集

`\sum_{下标表达式}^{上标表达式}{累加表达式}`和`\prod` `\bigcup` `\bigcap` 用来表示累加，累乘，病机，交集。

示例：

`$$\sum_1^n {i^2}$$`：$$\sum_1^n{i^2}$$

`$$\prod_{i=0}^n \frac 1 a $$`：$$\prod_{i=0}^n \frac 1 a$$  

`$$\bigcup _i \infty n$$` ：$$\bigcup _i^\infty n$$

`$$\bigccp _i \infty n$$` ：$$\bigcap _i^\infty n$$



##### 极限和积分符号

`\int`用来表示积分符号，同样地，其上下标表示积分的上下限。如，`$\int_1^\infty dx$`：$$\int_1^\infty dx$$。

与此类似的符号还有`\iint`：$$\iint$$ ，`\iiint` ：$$\iiint$$



##### 分式和根式

- 分式

  `$\frac 1 3$` ： $$\frac 1 3$$

  `$\frac {1+x^2}{1-x^3}$`  ： $$\frac {1+x^2}{1-x^3}$$

  `$a+b\over c+d$`： ：$$a+b\over c+d$$

- 根式

  `$\sqrt[3]{x^2\overy}$` ：$$\sqrt[3]{x^2\over y}$$



##### 省略号

`\ldots`表示与文本线对齐的省略号，`\cdots`表示与文本中线对齐的省略号。

示例：

`$f(x_1,x_2,x_3,\ldots,x_n) = x_1^2 + x_2^2 + x_3^2 + \cdots + x_n^2$`

$$
f(x_1,x_2,x_3,\ldots,x_n) = x_1^2 + x_2^2 + x_3^2 + \cdots + x_n^2
$$



#####  矢量符号

`\vec`

示例：

`$\vec{a} \cdot \vec{b} = 0$`

$$\vec{a} \cdot \vec{b} = 0$$



##### 其他特使字符

###### 关系运算符

| 输入       |     显示     | 输入         |      显示      | 输入        |     显示      | 输入         |      显示      |
| -------- | :--------: | ---------- | :----------: | --------- | :---------: | ---------- | :----------: |
| \pm      |   $\pm$    | \times     |   $\times$   | \div      |   $\div$    | \mid       |    $\mid$    |
| \nmid    |  $\nmid$   | \cdot      |   $\cdot$    | \circ     |   $\circ$   | \ast       |    $\ast$    |
| \bigodot | $\bigodot$ | \bigotimes | $\bigotimes$ | \bigoplus | $\bigoplus$ | \leq       |    $\leq$    |
| \geq     |   $\geq$   | \neq       |    $\neq$    | \approx   |  $\approx$  | \equiv     |   $\equiv$   |
| \sum     |   $\sum$   | \prod      |   $\prod$    | \coprod   |  $\coprod$  | \backslash | $\backslash$ |

###### 集合运算符

| 输入        |     显示      | 输入        |     显示      | 输入        |     显示      |
| --------- | :---------: | --------- | :---------: | --------- | :---------: |
| \emptyset | $\emptyset$ | \in       |    $\in$    | \notin    |  $\notin$   |
| \subset   |  $\subset$  | \supset   |  $\supset$  | \subseteq | $\subseteq$ |
| \supseteq | $\supseteq$ | \bigcap   |  $\bigcap$  | \bigcup   |  $\bigcup$  |
| \bigvee   |  $\bigvee$  | \bigwedge | $\bigwedge$ | \biguplus | $\biguplus$ |

###### 对数运算符

| 输入   |   显示   | 输入   |  显示   | 输入   |  显示   |
| ---- | :----: | ---- | :---: | ---- | :---: |
| \log | $\log$ | \lg  | $\lg$ | \ln  | $\ln$ |

###### 三角运算符

| 输入       |     显示     | 输入   |   显示   | 输入       |     显示     |
| -------- | :--------: | :--- | :----: | -------- | :--------: |
| 30^\circ | $30^\circ$ | \bot | $\bot$ | \angle A | $\angle A$ |
| \sin     |   $\sin$   | \cos | $\cos$ | \tan     |   $\tan$   |
| \csc     |   $\csc$   | \sec | $\sec$ | \cot     |   $\cot$   |

###### 微积分运算符

| 输入      |    显示     | 输入     |    显示    | 输入     |    显示    |
| ------- | :-------: | ------ | :------: | ------ | :------: |
| \int    |  $\int$   | \iint  | $\iint$  | \iiint | $\iiint$ |
| \iiiint | $\iiiint$ | \oint  | $\oint$  | \prime | $\prime$ |
| \lim    |  $\lim$   | \infty | $\infty$ | \nabla | $\nabla$ |

###### 逻辑运算符

| 输入       |     显示     | 输入         |      显示      | 输入          |      显示       |
| -------- | :--------: | ---------- | :----------: | ----------- | :-----------: |
| \because | $\because$ | \therefore | $\therefore$ |             |               |
| \forall  | $\forall$  | \exists    |  $\exists$   | \not\subset | $\not\subset$ |
| \not<    |  $\not<$   | \not>      |   $\not>$    | \not=       |    $\not=$    |

###### 戴帽符号

| 输入         |      显示      | 输入              |        显示         |
| ---------- | :----------: | --------------- | :---------------: |
| \hat{xy}   |  $\hat{xy}$  | \widehat{xyz}   |  $\widehat{xyz}$  |
| \tilde{xy} | $\tilde{xy}$ | \widetilde{xyz} | $\widetilde{xyz}$ |
| \check{x}  | $\check{x}$  | \breve{y}       |    $\breve{y}$    |
| \grave{x}  | $\grave{x}$  | \acute{y}       |    $\acute{y}$    |

###### 连线符号

| 输入                                       |                    显示                    |
| ---------------------------------------- | :--------------------------------------: |
| \fbox{a+b+c+d}                           |             $\fbox{a+b+c+d}$             |
| \overleftarrow{a+b+c+d}                  |        $\overleftarrow{a+b+c+d}$         |
| \overrightarrow{a+b+c+d}                 |        $\overrightarrow{a+b+c+d}$        |
| \overleftrightarrow{a+b+c+d}             |      $\overleftrightarrow{a+b+c+d}$      |
| \underleftarrow{a+b+c+d}                 |        $\underleftarrow{a+b+c+d}$        |
| \underrightarrow{a+b+c+d}                |       $\underrightarrow{a+b+c+d}$        |
| \underleftrightarrow{a+b+c+d}            |     $\underleftrightarrow{a+b+c+d}$      |
| \overline{a+b+c+d}                       |           $\overline{a+b+c+d}$           |
| \underline{a+b+c+d}                      |          $\underline{a+b+c+d}$           |
| \overbrace{a+b+c+d}^{Sample}             |      $\overbrace{a+b+c+d}^{Sample}$      |
| \underbrace{a+b+c+d}_{Sample}            |     $\underbrace{a+b+c+d}_{Sample}$      |
| \overbrace{a+\underbrace{b+c}_{1.0}+d}^{2.0} | $\overbrace{a+\underbrace{b+c}_{1.0}+d}^{2.0}$ |
| \underbrace{a\cdot a\cdots a}_{b\text{ times}} | $\underbrace{a\cdot a\cdots a}_{b\text{ times}}$ |

###### 箭头符号

- 推荐使用符号：

| 输入       |     显示     | 输入      |    显示     | 输入         |      显示      |
| -------- | :--------: | ------- | :-------: | ---------- | :----------: |
| \to      |   $\to$    | \mapsto | $\mapsto$ |            |              |
| \implies | $\implies$ | \iff    |  $\iff$   | \impliedby | $\impliedby$ |

- 其它可用符号：

| 输入                  |          显示           | 输入                  |          显示           |
| ------------------- | :-------------------: | ------------------- | :-------------------: |
| \uparrow            |      $\uparrow$       | \Uparrow            |      $\Uparrow$       |
| \downarrow          |     $\downarrow$      | \Downarrow          |     $\Downarrow$      |
| \leftarrow          |     $ \leftarrow$     | \Leftarrow          |     $\Leftarrow$      |
| \rightarrow         |     $\rightarrow$     | \Rightarrow         |     $\Rightarrow$     |
| \leftrightarrow     |   $\leftrightarrow$   | \Leftrightarrow     |   $\Leftrightarrow$   |
| \longleftarrow      |   $\longleftarrow$    | \Longleftarrow      |   $\Longleftarrow$    |
| \longrightarrow     |   $\longrightarrow$   | \Longrightarrow     |   $\Longrightarrow$   |
| \longleftrightarrow | $\longleftrightarrow$ | \Longleftrightarrow | $\Longleftrightarrow$ |









#### 高级




##### 如何进行字体转换

若要对公式的某一部分字符进行字体转换，可以用 `{\字体 {需转换的部分字符}}` 命令，其中 `\字体` 部分可以参照下表选择合适的字体。一般情况下，公式默认为意大利体  。

示例中 **全部大写** 的字体仅大写可用。

| 输入    | 说明    |           显示           | 输入   | 说明   |           显示           |
| ----- | ----- | :--------------------: | ---- | ---- | :--------------------: |
| \rm   | 罗马体   |  $\large\rm {sample}$  | \cal | 花体   | $\large\cal {sample}$  |
| \it   | 意大利体  |  $\large\it {sample}$  | \Bbb | 黑板粗体 | $\large\Bbb {sample}$  |
| \bf   | 粗体    |  $\large \bf{sample}$  | \mit | 数学斜体 | $\large \mit {sample}$ |
| \sf   | 等线体   | $\large \sf {sample}$  | \scr | 手写体  | $\large \scr{sample}$  |
| \tt   | 打字机体  | $\large \tt {sample}$  |      |      |                        |
| \frak | 旧德式字体 | $\large \frak{sample}$ |      |      |                        |

转换字体十分常用，例如在积分中：

- 例子：

  ```latex
  \begin{array}{cc}
  \mathrm{Bad} & \mathrm{Better} \\
  \hline \\
  \int_0^1 x^2 dx & \int_0^1 x^2 \,{\rm d}x
  \end{array}
  ```

- 显示： 
  $$
  \begin{array}{cc}
  \mathrm{Bad} & \mathrm{Better} \\
  \hline \\
  \int_0^1 x^2 dx & \int_0^1 x^2 \,{\rm d}x
  \end{array}
  $$






注意比较两个式子间$dx$ 与 ${\rm d}x$ 的不同。 
使用 `\operatorname` 命令也可以达到相同的效果，详见 [定义新的符号 \operatorname](https://www.zybuluo.com/codeep/note/163962#1定义新的符号-operatorname) 。



##### 大括号

使用 `\left` 和 `\right` 来创建自动匹配高度的 (圆括号)，[方括号] 和 {花括号} 。 
在每个公式末尾前使用 `\tag{行标}` 来实现行标。

```latex
$$
F^{HLLC}=\left\{
\begin{array}{rl}
F_L       &      & {0      <      S_L}\\
F^*_L     &      & {S_L \leq 0 < S_M}\\
F^*_R     &      & {S_M \leq 0 < S_R}\\
F_R       &      & {S_R \leq 0}
\end{array} \right.
$$
```


$$
F^{HLLC}=\left\{
\begin{array}{rl}
F_L       &            & {0      <      S_L}\\
F^*_L     &      &  {S_L \leq 0 < S_M}   \\
F^*_R     &      & {S_M \leq 0 < S_R}\\
F_R       &      & {S_R \leq 0}
\end{array} \right.
$$









##### 表格

使用`$$\begin{array}{列样式}…\end{array}$$`这样的形式来创建表格，列样式可以是`c` `l` `r`表示居中，左，右对齐，还可以使用`|`表示一条竖线。表格中 各行使用`\\`分隔，各列使用`&`分隔。使用`\hline`在本行前加入一条直线。 

示例：

```latex
$$
\begin{array}{c|lcr}
n & \text{Left} & \text{Center} & \text{Right} \\
\hline
1 & 0.24 & 1 & 125 \\
2 & -1 & 189 & -8 \\
3 & -20 & 2000 & 1+10i \\
\end{array}
$$
```

$$
\large
\begin{array}{c|clr}
n & \text{Left} & \text{Center} & \text{Right} \\
\hline
1 & 0.24 & 1 & 125 \\
2 & -1 & 189 & -8 \\
3 & -20 & 2000 & 1+10i \\
\end{array}
$$



##### 方程组

使用 `\begin{array}…\end{array}` 和 `\left\{…\right.` 来创建一个方程组。

```latex
$$
\left\{
\begin{array}{l}
x + y + z = 1 \\
x^2 + z =2	  \\
y*z = 10    \\
\end{array}
\right.
$$
```

$$
\large
\left\{
\begin{array}{l}
x + y + z = 1 \\
x^2 + z =2	  \\
y*z = 10    \\
\end{array}
\right.
$$

使用条件表达式组 `\begin{cases}…\end{cases}` 更方便：

```latex
$$
\begin{cases}
a_1x+b_1y+c_1z=d_1 \\ 
a_2x+b_2y+c_2z=d_2 \\ 
a_3x+b_3y+c_3z=d_3
\end{cases}
$$
```

$$
\large
\begin{cases}
a_1x+b_1y+c_1z=d_1 \\ 
a_2x+b_2y+c_2z=d_2 \\ 
a_3x+b_3y+c_3z=d_3
\end{cases}
$$



##### 矩阵

###### 无框矩阵

在开头使用 `begin{matrix}`，在结尾使用 `end{matrix}`，在中间插入矩阵元素，每个元素之间插入 `&` ，并在每行结尾处使用 `\\` 。 
使用矩阵时必须声明 `$` 或 `$$` 符号。

```latex
$$
        \begin{matrix}
        1 & x & x^2 \\
        1 & y & y^2 \\
        1 & z & z^2 \\
        \end{matrix}
$$
```

$$
        \begin{matrix}
        1 & x & x^2 \\
        1 & y & y^2 \\
        1 & z & z^2 \\
        \end{matrix}
$$

###### 边框矩阵

在开头将 `matrix` 替换为 `pmatrix` `bmatrix` `Bmatrix` `vmatrix` `Vmatrix` 。

```latex
$ \begin{matrix} 1 & 2 \\ 3 & 4 \\ \end{matrix} $
$ \begin{pmatrix} 1 & 2 \\ 3 & 4 \\ \end{pmatrix} $
$ \begin{bmatrix} 1 & 2 \\ 3 & 4 \\ \end{bmatrix} $
$ \begin{Bmatrix} 1 & 2 \\ 3 & 4 \\ \end{Bmatrix} $
$ \begin{vmatrix} 1 & 2 \\ 3 & 4 \\ \end{vmatrix} $
$ \begin{Vmatrix} 1 & 2 \\ 3 & 4 \\ \end{Vmatrix} $
```


$$
\begin{matrix} 1 & 2 \\ 3 & 4 \\ \end{matrix} 
\begin{pmatrix} 1 & 2 \\ 3 & 4 \\ \end{pmatrix} 
 \begin{bmatrix} 1 & 2 \\ 3 & 4 \\ \end{bmatrix} 
 \begin{Bmatrix} 1 & 2 \\ 3 & 4 \\ \end{Bmatrix} 
 \begin{vmatrix} 1 & 2 \\ 3 & 4 \\ \end{vmatrix} 
 \begin{Vmatrix} 1 & 2 \\ 3 & 4 \\ \end{Vmatrix} 
$$

###### 带省略符号的矩阵

使用 `\cdots`   $\cdots$   , `\ddots`  $\ddots$   , `\vdots `   $\vdots$   来输入省略符号。

```latex
$$
        \begin{pmatrix}
        1 & a_1 & a_1^2 & \cdots & a_1^n \\
        1 & a_2 & a_2^2 & \cdots & a_2^n \\
        \vdots & \vdots & \vdots & \ddots & \vdots \\
        1 & a_m & a_m^2 & \cdots & a_m^n \\
        \end{pmatrix}
$$
```

$$
\begin{pmatrix}
        1 & a_1 & a_1^2 & \cdots & a_1^n \\
        1 & a_2 & a_2^2 & \cdots & a_2^n \\
        \vdots & \vdots & \vdots & \ddots & \vdots \\
        1 & a_m & a_m^2 & \cdots & a_m^n \\
        \end{pmatrix}
$$

###### 增广矩阵

```latex
$$
\left[
    \begin{array}{cc|c}
      1&2&3\\
      4&5&6
    \end{array}
\right]
$$
```

$$
\left[
    \begin{array}{cc|c}
      1&2&3\\
      4&5&6
    \end{array}
\right]
$$

##### 分类表达式

定义函数的时候经常需要分情况给出表达式，可使用`\begin{cases}…\end{cases}`。其中，使用\来分类，使用&指示需要对齐的位置。如：

```latex
$$
f(n) = 
\begin{cases}
n &\text{if $n$ is even}\\
3n+1, & \text{if $n$ is odd}\\
\end{cases}
$$
```


$$
f(n) = 
\begin{cases}
n &\text{if $n$ is even}\\
3n+1, & \text{if $n$ is odd}\\
 \end{cases}
$$


```latex
$$
        \left.
        \begin{array}{l}
        \text{if $n$ is even:}& \frac n 2 \\
        \text{if $n$ is odd:}&3n+1
        \end{array}
        \right\}
        =f(n)
$$
```


$$
\left.
        \begin{array}{l}
        \text{if $n$ is even:}& \frac n 2   \\[3ex]
        \text{if $n$ is odd:}&3n+1 \\[2ex]
        \end{array}
        \right\}
        =f(n)
$$



### 流程图



```flow
st=>start: Start:>https://www.zybuluo.com
io=>inputoutput: verification
op=>operation: Your Operation
cond=>condition: Yes or No?
sub=>subroutine: Your Subroutine
e=>end

st->io->op->cond
cond(yes)->e
cond(no)->sub->io
```

> 更多语法参考：[流程图语法参考](http://adrai.github.io/flowchart.js/) [序列图语法参考](http://bramp.github.io/js-sequence-diagrams/) [甘特图语法参考](https://knsv.github.io/mermaid/#gant-diagrams) [Mermaid 序列图语法参考](https://knsv.github.io/mermaid/#sequence-diagrams)





## Markdown编译器

- [atom](https://atom.io/)
- [Typora](https://typora.io/)
- [Cmd Markdown](https://www.zybuluo.com/cmd/)

