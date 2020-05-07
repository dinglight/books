# Program Structure

在本章中，我们将开始做实际上可以称为编程的事情。 我们将把JavaScript语言的命令扩展到目前为止所见过的名词和句子片段之外，直至可以表达有意义的散文。

## Expressions and statements （表达式和语句）

在第1章中，我们创建了值并将运算符应用于它们以获取新值。 像这样创建值是任何JavaScript程序的主要内容。 但是该物质必须以较大的结构框起来才能有用。 这就是我们接下来要介绍的内容。

产生值的代码片段称为表达式。 逐个写入的每个值（例如22或“ psychoanalysis”）都是一个表达式。 括号之间的表达式也是一个表达式，应用于两个表达式的二元运算符或应用于一个表达式的一元运算符也是如此。

这显示了基于语言的界面的部分优点。 表达式可以包含其他表达式，其方式类似于人类语言中句子的嵌套方式-句子可以包含自己的句子，依此类推。 这使我们能够构建描述任意复杂计算的表达式。

如果表达式（Expressions ）对应于句子片段，则JavaScript语句（statements）对应于完整句子。 程序是语句列表。

最简单的语句是在其后带有分号的表达式。 这是一个程序：

```javascript
1;
!false;
```

但是，它是一个无用的程序。 表达式可以满足于只产生一个值，然后可以由封闭代码使用。 陈述是独立存在的，因此仅在影响世界时才构成某种意义。 它可以在屏幕上显示某些东西（这可以算是改变世界），也可以改变机器的内部状态，从而影响其后的语句。 这些变化称为副作用。 上一个示例中的语句仅产生值1和true，然后立即将其丢弃。 这一点都没有给世界留下任何印象。 当您运行该程序时，任何可观察的事情都不会发生。

在某些情况下，JavaScript允许您在语句结尾省略分号。 在其他情况下，它必须存在，否则下一行将被视为同一语句的一部分。 何时可以安全地省略它的规则有些复杂并且容易出错。 因此，在本书中，每条需要用分号表示的语句总会得到一个分号。 我建议您进行同样的操作，至少直到您进一步了解分号缺失的精妙之处为止。

## Bindings

程序如何保持内部状态？ 它如何记住事情？ 我们已经看到了如何从旧值中产生新值，但是这不会改变旧值，因此必须立即使用新值，否则它将再次消失。 为了捕获和保留值，JavaScript提供了一种称为绑定或变量的东西：

```javascript
let caught = 5 * 5;
```

这是第二种语句。 特殊单词（关键字）let表示该句子将定义绑定。 它后面是绑定的名称，如果要立即为其提供值，则后面带有=运算符和一个表达式。

前面的语句创建一个名为catch的绑定，并使用它来捕获5乘以5所产生的数字。

定义绑定后，其名称可用作表达式。 这样的表达式的值就是绑定当前持有的值。 这是一个例子：

```javascript
let ten = 10;
console.log(ten * ten);
// → 100
```

当绑定指向某个值时，这并不意味着它将永远与该值绑定。 可以随时在现有绑定上使用=运算符，以将其与当前绑定断开连接，并使它们指向新的绑定。

```javascript
let mood = "light";
console.log(mood);
// → light
mood = "dark";
console.log(mood);
// → dark
```

您应该将绑定想象为触角，而不是盒子。 它们不包含值。 他们掌握了它们-两个绑定可以引用相同的值。 程序只能访问它仍然具有引用的值。 当您需要记住某件事时，可以长出一个触手来抓住它，或者将现有的触手之一重新连接到它上。

让我们看另一个例子。 要记住路易吉仍欠您的钱数，请创建一个绑定。 然后，当他还清$ 35时，您便给此绑定赋予了新值。

```javascript
let luigisDebt = 140;
luigisDebt = luigisDebt - 35;
console.log(luigisDebt);
// → 105
```

当您在没有给定值的情况下定义绑定时，触手没有任何可把握的地方。 如果您要求提供空绑定的值，则将获得undefined值。

```javascript
let empty;
console.log(empty)
// → undefined
```

单个let语句可以定义多个绑定。 定义必须用逗号分隔。

```javascript
let one = 1, two = 2;
console.log(one + two);
// → 3
```

单词var和const也可以用来创建绑定，类似于let。

```javascript
var name = "Ayda";
const greeting = "Hello ";
console.log(greeting + name);
// → Hello Ayda
```

第一个变量var（“变量”的缩写）是在2015年之前的JavaScript中声明绑定的方式。 我将在下一章中讲述它与let的不同点。 目前，请记住它几乎与let具有相同的功能，但是由于它具有一些令人困惑的属性，因此我们在本书中很少使用。

const代表常量。 它定义了一个常量绑定，该常量绑定在其生存期间一直指向相同的值。 这对于为名称赋值的绑定很有用，以便您以后可以轻松引用它。

## Binding Name

绑定名称可以是任何单词。 数字可以是绑定名称的一部分，例如catch22是有效名称，但是名称不能以数字开头。 绑定名称可以包含美元符号（$）或下划线（_），但不能包含其他标点符号或特殊字符。

具有特殊含义的单词（例如let）是关键字，它们不能用作绑定名称。 在将来的JavaScript版本中，还有许多“保留使用”的单词，这些单词也不能用作绑定名称。 关键字和保留字的完整列表相当长。

```javascript
break case catch class const continue debugger default
delete do else enum export extends false finally for
function if implements import interface in instanceof let
new package private protected public return static super
switch this throw true try typeof var void while with yield
```

不用担心记住此列表。 创建绑定时会产生意外的语法错误，请查看您是否要定义保留字。

## The Environment

在给定时间存在的绑定及其值的集合称为环境。 程序启动时，此环境不为空。 它始终包含作为语言标准一部分的绑定，并且在大多数情况下，它还具有提供与周围系统进行交互的方式的绑定。 例如，在浏览器中，具有与当前加载的网站进行交互以及读取鼠标和键盘输入的功能。

## Functions

默认环境中提供的许多值都具有type函数。 函数是包裹在一个值中的一段程序。 可以应用这些值来运行包装的程序。 例如，在浏览器环境中，绑定包含一个prompt函数，该函数显示一个小的对话框，要求用户输入。 它的用法如下：

```javascript
prompt("Enter passcode");
```

![prompt](images/prompt.pNG)

执行一个函数称为调用，调用或应用它。 您可以通过在产生函数值的表达式后加上括号来调用函数。 通常，您将直接使用保存该功能的绑定的名称。 括号之间的值被提供给函数内部的程序。 在示例中，提示函数使用我们提供的字符串作为文本显示在对话框中。 给函数的值称为参数。 不同的函数可能需要不同数量或不同类型的参数。

提示功能在现代的网络编程中很少使用，主要是因为您无法控制对话框的外观，但是在玩具程序和实验中会有所帮助。

## The console.log function

在示例中，我使用console.log输出值。 大多数JavaScript系统（包括所有现代Web浏览器和Node.js）都提供console.log函数，该函数将其参数写到某些文本输出设备中。 在浏览器中，输出到达JavaScript控制台。 默认情况下，浏览器界面的这一部分是隐藏的，但是大多数浏览器会在您按F12键或在Mac上按Command-option-I时将其打开。 如果那不起作用，请在菜单中搜索名为Developer Tools或类似名称的项目。

尽管绑定名称不能包含句点字符，但console.log确实有一个。 这是因为console.log不是简单的绑定。 它实际上是一个表达式，它从控制台绑定持有的值中检索log属性。 我们将在第4章中确切地了解这意味着什么。

## Return values

显示对话框或在屏幕上写文本是一种副作用。 许多功能因其产生的副作用而很有用。 函数也可能产生值，在这种情况下，它们不需要产生副作用即可使用。 例如，函数Math.max接受任意数量的数字参数并返回最大值。

```javascript
console.log(Math.max(2, 4));
// → 4
```

当一个函数产生一个值时，就说要返回该值。 任何产生值的东西都是JavaScript中的表达式，这意味着可以在较大的表达式中使用函数调用。 在这里，与Math.max相反的对Math.min的调用被用作加号表达式的一部分：

```javascript
console.log(Math.min(2, 4) + 100);
// → 102
```

下一章将说明如何编写自己的函数。

## Control flow

当您的程序包含多个语句时，这些语句从上到下都像故事一样执行。 此示例程序有两个语句。 第一个问用户一个数字，第二个在第一个之后执行，显示该数字的平方。

```javascript
let theNumber = Number(prompt("Pick a number"));
console.log("Your number is the square root of " +
             theNumber * theNumber);
```

函数Number将值转换为数字。 我们需要这种转换，因为提示符的结果是一个字符串值，并且我们需要一个数字。 有类似的函数，称为String和Boolean，可将值转换为这些类型。

这是直线控制流程的相当简单的示意图：

## Conditional execution

并非所有程序都是直路。 例如，我们可能想创建一条分支路，程序会根据当前情况选择适当的分支。 这称为条件执行。

使用JavaScript中的if关键字创建条件执行。 在简单的情况下，我们希望仅在满足特定条件的情况下才能执行某些代码。 例如，我们可能只想在输入实际上是数字时才显示输入的平方。

```javascript
let theNumber = Number(prompt("Pick a number"));
if (!Number.isNaN(theNumber)) {
  console.log("Your number is the square root of " +
              theNumber * theNumber);
}
```

进行此修改后，如果输入“ parrot”，则不会显示任何输出。

if关键字根据布尔表达式的值执行或跳过语句。 决定性表达式写在关键字之后，括号之间，然后是要执行的语句。

Number.isNaN函数是标准的JavaScript函数，仅当给定参数为NaN时返回true。 当您输入不代表有效数字的字符串时，Number函数会返回NaN。 因此，条件转化为“除非数字不是数字，否则执行此操作”。

在此示例中，if之后的语句用大括号（{和}）引起来。 大括号可用于将任意数量的语句分组为单个语句，称为块。 在这种情况下，您也可以省略它们，因为它们只包含一个语句，但是为了避免考虑是否需要它们，大多数JavaScript程序员在每个这样的包装语句中都使用它们。 除了偶尔的单线外，我们在本书中通常都会遵循该约定。

```javascript
if (1 + 1 == 2) console.log("It's true");
// → It's true
```

通常，您不仅会拥有在条件成立时执行的代码，而且还会处理其他情况的代码。 此备用路径由图中的第二个箭头表示。 您可以将else关键字与if一起使用，以创建两个单独的替代执行路径。

```javascript
let theNumber = Number(prompt("Pick a number"));
if (!Number.isNaN(theNumber)) {
  console.log("Your number is the square root of " +
              theNumber * theNumber);
} else {
  console.log("Hey. Why didn't you give me a number?");
}
```

如果您有两个以上可供选择的路径，则可以“链接”多个if / else对。 这是一个例子：

```javascript
let num = Number(prompt("Pick a number"));
if (num < 10) {
  console.log("Small");
} else if (num < 100) {
  console.log("Medium");
} else {
  console.log("Large");
}
```

该程序将首先检查num是否小于10。如果是，则选择该分支，显示“ Small”，然后完成。 如果不是，则使用else分支，该分支本身包含第二个if。 如果第二个条件（<100）成立，则表示该数字在10到100之间，并显示“中”。 如果不是，则选择第二个也是最后一个else分支。

## While and Do loops

考虑一个程序，该程序输出从0到12的所有偶数。一种编写方法如下：

```javascript
console.log(0);
console.log(2);
console.log(4);
console.log(6);
console.log(8);
console.log(10);
console.log(12);
```

可以，但是编写程序的想法是减少工作量，而不是增加工作量。 如果我们需要所有小于1000的偶数，则此方法将行不通。 我们需要的是多次运行一段代码的方法。 这种控制流形式称为循环。

循环控制流使我们可以返回到程序之前的某个位置，并以我们当前的程序状态对其进行重复。 如果我们将此与具有约束力的绑定结合在一起，我们可以执行以下操作：

```javascript
let number = 0;
while (number <= 12) {
  console.log(number);
  number = number + 2;
}
// → 0
// → 2
// … etcetera
```

以关键字while开头的语句将创建循环。 单词while之后是括号中的表达式，然后是语句，就像if一样。 只要表达式生成的值转换为布尔值时为true，循环就一直输入该语句。

数字绑定演示了绑定可以跟踪程序进度的方式。 每次循环重复，数字将得到一个比其先前值大2的值。 在每次重复的开始，它都会与数字12进行比较，以确定程序的工作是否完成。

举个实际起作用的例子，我们现在可以编写一个程序来计算并显示2 10的值（2的10次方）。 我们使用两个绑定：一个用于跟踪结果，另一个用于计数将结果乘以2的频率。循环测试第二个绑定是否已达到10，如果没有，则更新两个绑定。

```javascript
let result = 1;
let counter = 0;
while (counter < 10) {
  result = result * 2;
  counter = counter + 1;
}
console.log(result);
// → 1024
```

计数器也可以从1开始并检查<= 10，但是由于在第4章中将变得显而易见的原因，习惯于从0开始计数是一个好主意。

do循环是类似于while循环的控制结构。 它仅在一点上有所不同：do循环始终至少执行一次其主体，并且开始测试是否仅应在第一次执行后才停止。 为了反映这一点，该测试出现在循环的主体之后。

```javascript
let yourName;
do {
  yourName = prompt("Who are you?");
} while (!yourName);
console.log(yourName);
```

该程序将强制您输入名称。 它将反复询问直到得到不是空字符串的东西。 应用！ 运算符将在将值取反之前将其转换为布尔类型，并且除“”外的所有字符串都将转换为true。 这意味着循环将继续进行，直到您提供非空名称为止。

## indenting code

在示例中，我一直在一些较大的语句的一部分的语句前添加空格。 这些空格不是必需的-没有它们，计算机也将接受程序。 实际上，程序中的换行符也是可选的。 如果您愿意，可以将程序编写为单个长行。

块内缩进的作用是使代码的结构突出。 在新的块在其他块内打开的代码中，很难看到一个块在哪里结束而另一个在哪里开始。 通过适当的缩进，程序的视觉形状与程序内部块的形状相对应。 我喜欢为每个打开的块使用两个空格，但是口味有所不同-有些人使用四个空格，有些人使用制表符。 重要的是每个新块都增加了相同的空间。

```javascript
if (false != true) {
  console.log("That makes sense.");
  if (1 < 2) {
    console.log("No surprise there.");
  }
}
```

大多数代码编辑器程序都会通过自动缩进适当的行数来帮助您。

## For loops

许多循环遵循while示例中显示的模式。 首先，创建一个“计数器”绑定来跟踪循环的进度。 然后是while循环，通常带有一个测试表达式，用于检查计数器是否已达到其结束值。 在循环主体的末尾，计数器将更新以跟踪进度。

由于这种模式非常普遍，因此JavaScript和类似的语言提供了一种略短，更全面的形式，即for循环。

```javascript
for (let number = 0; number <= 12; number = number + 2) {
  console.log(number);
}
// → 0
// → 2
// … etcetera
```

该程序与先前的偶数打印示例完全等效。 唯一的变化是，与循环的“状态”相关的所有语句在for之后分组在一起。

for关键字后的括号必须包含两个分号。 第一个分号之前的部分通常通过定义绑定来初始化循环。 第二部分是检查循环是否必须继续的表达式。 最后一部分在每次迭代后更新循环的状态。 在大多数情况下，它比while结构更短，更清晰。

这是使用for而不是while计算2^10的代码:

```javascript
let result = 1;
for (let counter = 0; counter < 10; counter = counter + 1) {
  result = result * 2;
}
console.log(result);
// → 1024
```

## Breaking out of a loop

使循环条件产生假不是循环可以完成的唯一方法。 有一个特殊的语句称为break，它具有立即跳出封闭循环的作用。该程序说明了break语句。 它会找到第一个大于或等于20且可被7整除的数字。

```javascript
for (let current = 20; ; current = current + 1) {
  if (current % 7 == 0) {
    console.log(current);
    break;
  }
}
// → 21
```

使用余数（％）运算符是测试一个数字是否可被另一个数字整除的简便方法。 如果是，则它们的除法余数为零。示例中的for构造没有检查循环结束的部分。 这意味着除非执行了break语句，否则循环永远不会停止。如果要删除该break语句，或者不小心编写了始终产生true的结束条件，则程序将陷入无限循环。 陷入无限循环的程序将永远无法完成运行，这通常是一件坏事。

continue关键字与break相似，因为它影响循环的进度。 如果在循环主体中遇到continue，控件将跳出主体并继续循环的下一个迭代。

## Updating bindings succinctly

特别是在循环时，程序通常需要“更新”绑定以根据该绑定的先前值保存该值。

```javascript
counter = counter + 1;
```

JavaScript为此提供了快捷方式。

```javascript
counter += 1;
```

类似的快捷方式也适用于许多其他运算符，例如result * = 2使结果加倍或counter-= 1使计数递减。这使我们可以稍微缩短计数示例。

```javascript
for (let number = 0; number <= 12; number += 2) {
  console.log(number);
}
```

对于counter + = 1和counter-= 1，甚至还有更短的等效项：counter ++和counter--。

## Dispatching on a value with switch

代码看起来像这样并不罕见：

```javascript
if (x == "value1") action1();
else if (x == "value2") action2();
else if (x == "value3") action3();
else defaultAction();
```

有一种名为switch的构造，旨在以更直接的方式表达这种“调度”。 不幸的是，JavaScript为此使用的语法（它是从C / Java语言的编程语言中继承的）有点尴尬-一系列if语句看起来更好。 这是一个例子：

```javascript
switch (prompt("What is the weather like?")) {
  case "rainy":
    console.log("Remember to bring an umbrella.");
    break;
  case "sunny":
    console.log("Dress lightly.");
  case "cloudy":
    console.log("Go outside.");
    break;
  default:
    console.log("Unknown weather type!");
    break;
}
```

您可以在switch打开的块中放置任意数量的案例标签。 程序将在与给定开关的值相对应的标签处开始执行，如果没有找到匹配的值，则默认情况下开始执行。 它会继续执行，甚至跨其他标签，直到到达break语句。 在某些情况下，例如示例中的“晴天”案例，可以在案例之间共享一些代码（建议在晴天和阴天都出门）。 但是要小心-容易忘记这样的中断，它会导致程序执行您不想执行的代码。

## Capitalization

绑定名称不可能包含空格，但是使用多个单词来清楚地描述绑定表示什么通常会有所帮助。 您几乎可以选择以下几种方式来编写绑定名称：

```javascript
fuzzylittleturtle
fuzzy_little_turtle
FuzzyLittleTurtle
fuzzyLittleTurtle
```

第一种风格可能很难阅读。 我更喜欢下划线的外观，尽管键入该样式有点麻烦。 标准的JavaScript函数和大多数JavaScript程序员遵循最后一个的样式，除了第一个以外，它们均大写每个单词。 习惯这样的小事情并不难，混合命名方式的代码可能会让人难以理解，因此我们遵循此约定。

在某些情况下，例如Number函数，绑定的第一个字母也会大写。 这样做是为了将此函数标记为构造函数。 在第6章中将清楚说明构造函数是什么。目前，重要的是不要被明显缺乏一致性所困扰。

## Comments

通常，原始代码不会将您希望程序传达的所有信息传达给人类读者，或者以一种人们可能不理解的秘密方式传达。 在其他时候，您可能只想在程序中包含一些相关的想法。 这就是注释的目的。

注释是一段文本，它是程序的一部分，但计算机完全将其忽略。 JavaScript有两种编写注释的方法。 要编写单行注释，可以使用两个斜杠字符（//），然后使用注释文本。

```javascript
let accountBalance = calculateBalance(account);
// It's a green hollow where a river sings
accountBalance.adjust();
// Madly catching white tatters in the grass.
let report = new Report();
// Where the sun on the proud mountain rings:
addToReport(accountBalance, report);
// It's a little valley, foaming like light in a glass.
```

//注释仅到行尾。 / *和* /之间的一段文本将被完全忽略，无论它是否包含换行符。 这对于添加有关文件或程序块的信息块很有用。

```javascript
/*
I first found this number scrawled on the back of an old notebook.
Since then, it has often dropped by, showing up in phone numbers
and the serial numbers of products that I've bought. It obviously
likes me, so I've decided to keep it.
*/
const myNumber = 11213;
```

## Summary

您现在知道程序是由语句构建的，而语句本身有时包含更多的语句。 语句倾向于包含表达式，而表达式本身可以由较小的表达式构建。

将语句彼此放在一起可以使您从上到下执行一个程序。 通过使用条件语句（if，else和switch）和循环语句（while，do和for），可以在控制流中引入干扰。

绑定可用于以名称命名文件数据，它们对于跟踪程序中的状态很有用。 环境是定义的绑定集。 JavaScript系统始终在您的环境中放置许多有用的标准绑定。

函数是封装程序的特殊值。 您可以通过编写functionName（argument1，arguments2）来调用它们。 这样的函数调用是一个表达式，并可能产生一个值。

## Exercises

如果不确定如何测试练习的解决方案，请参阅“简介”。

每个练习都以问题描述开始。 阅读此说明并尝试解决该练习。 如果遇到问题，请考虑阅读本书结尾处的提示。 本书没有提供练习的完整解决方案，但您可以在https://eloquentjavascript.net/code上在线找到它们。 如果您想从练习中学到一些东西，我建议您仅在解决练习之后，或者至少在经过长时间艰苦的练习以至于头疼之后再看一下解决方案。

### Looping a triangle

编写一个循环，该循环对console.log进行七个调用，以输出以下三角形：

```javascript
#
##
###
####
#####
######
#######
```

知道可以通过在字符串后加上.length来找到字符串的长度可能很有用。

```javascript
let abc = "abc";
console.log(abc.length);
// → 3
```

#### Answer

```javascript
for (let line = "#"; line.length < 8; line += "#") {
  console.log(line);
}
```

### Fizzbuzz

编写一个程序，使用console.log打印从1到100的所有数字，但有两个例外。 对于可被3整除的数字，请打印“ Fizz”而不是数字；对于可被5整除的数字（而不是3），请打印“ Buzz”。

工作正常后，修改程序以将“ FizzBuzz”打印为可被3和5整除的数字（并仍将“ Fizz”或“ Buzz”打印为只能被其中一个数字整除的数字）。

（实际上，这是一个面试问题，据说已经淘汰了很大一部分程序员候选人。因此，如果您解决了这个问题，您的劳动力市场价值就会上升。）

#### Answer

```javascript
for (let n = 1; n <= 100; n += 1) {
  let output = "";
  if (n % 3 == 0) output += "Fizz";
  if (n % 5 == 0) output += "Buzz";
  console.log(output || n);
}
```

### Chessboard

编写一个程序，该程序创建一个表示8×8网格的字符串，并使用换行符分隔各行。 在网格的每个位置都有一个空格或一个“＃”字符。 角色应构成一个棋盘。

将此字符串传递给console.log应该显示如下内容：

当您有一个生成该模式的程序时，定义一个装订大小= 8并更改该程序，使其适用于任何大小，并输出给定宽度和高度的网格。

```javascript
let n = 8;
let board = "";
for (let i = 0; i < n; i += 1) {
  for (let j = 0; j < n; j += 1) {
    if ((i+j) % 2 == 0) {
      board += " ";
    } else {
      board += "#";
    }
  }
  board += "\n";
}
console.log(board);
```

