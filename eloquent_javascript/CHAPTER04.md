# Data structures: Objects and arrays

数字，布尔值和字符串是构建数据结构的原子基础。 但是，许多类型的信息都需要多个原子。 对象使我们可以对值（包括其他对象）进行组合，以构建更复杂的结构。

到目前为止，我们构建的程序受到以下限制：它们仅在简单数据类型上运行。 本章将介绍基本数据结构。 到本章结束，您将具备足够知识以便开始编写有用的程序。

本书的在线编码沙箱（https://eloquentjavascript.net/code）提供了一种在特定章节的上下文中运行代码的方法。 如果决定在其他环境中浏览示例，请确保首先从沙盒页面下载本章的完整代码。

## The Weresquirrel

时不时地，通常在晚上8点之间。 晚上10点，雅克发现自己变成了一只尾巴浓密的毛茸茸的小啮齿动物。一方面，雅克（Jacques）很高兴自己没有经典的慈善事业。 与变成狼相比，变成松鼠引起的问题要少得多。 他不必担心会意外地吃掉邻居（那会很尴尬），而不必担心被邻居的猫吃掉。 两次在赤裸裸，迷失方向的橡木树冠上摇摇欲坠的树枝上醒来之后，他不得不在晚上锁上房间的门窗，并在地板上放一些核桃，以保持自己的忙碌。这样可以解决猫和树的问题。 但是雅克宁愿完全摆脱自己的病情。 变换的不规则发生使他怀疑它们可能是由某种东西触发的。 有一段时间，他认为这只是在他靠近橡树的那几天才发生。 但避免橡树并不能解决问题。改用更科学的方法后，雅克（Jacques）已开始每天记录他在某一天所做的一切以及他是否改变了身材。 他希望借助这些数据来缩小触发转换的条件。他需要的第一件事是存储此信息的数据结构。

## Data Sets

要处理大量数字数据，我们首先必须找到一种在计算机内存中表示数据的方法。 举例来说，假设我们要代表数字2、3、5、7和11的集合。

我们可以利用字符串来发挥创造力-毕竟，字符串可以具有任意长度，因此我们可以在其中输入大量数据-并使用“ 2 3 5 7 11”作为表示形式。 但这很尴尬。 您必须以某种方式提取数字并将其转换回数字才能访问它们。

幸运的是，JavaScript提供了一种专门用于存储值序列的数据类型。 它称为数组，并写为方括号之间的值列表，以逗号分隔。

```javascript
let listOfNumbers = [2, 3, 5, 7, 11];
console.log(listOfNumbers[2]);
// → 5
console.log(listOfNumbers[0]);
// → 2
console.log(listOfNumbers[2 - 1]);
// → 3
```

获取数组内元素的符号也使用方括号。 紧接在表达式之后的一对方括号（其中包含另一个表达式）将在左侧表达式中查找与括号中表达式所给出的索引相对应的元素。

数组的第一个索引为零，而不是一。 因此，第一个元素是使用listOfNumbers [0]检索的。 基于零的计数在技术上具有悠久的传统，从某种意义上讲很有意义，但需要一些习惯。 将索引视为从数组开始算起要跳过的项目数。

## Properties

在过去的章节中，我们已经看到了一些看起来很可疑的表达式，例如myString.length（获取字符串的长度）和Math.max（最大函数）。 这些是访问某些值的属性的表达式。 在第一种情况下，我们访问myString中值的length属性。 在第二部分中，我们访问Math对象中的名为max的属性（该属性是与数学相关的常数和函数的集合）。

几乎所有的JavaScript值都有属性。 除了null和undefined。 如果您尝试访问这些非值的属性，你将得到错误信息。

```javascript
null.length;
// → TypeError: null has no properties
```

在JavaScript中访问属性的两种主要方法是使用点和方括号。 value.x和value [x]都访问value的属性，但不一定是同一属性。 区别在于x的解释方式。 使用点时，点后的单词是属性的文字名称。 使用方括号时，将对方括号之间的表达式求值以获取属性名称。 value.x获取名为“ x”的值的属性，而value [x]尝试评估表达式x并使用转换为字符串的结果作为属性名。

因此，如果您知道您感兴趣的属性称为color，则说value.color。 如果要提取由绑定i中保存的值命名的属性，请说value [i]。 属性名称是字符串。 它们可以是任何字符串，但是点符号仅适用于看起来像有效绑定名称的名称。 因此，如果要访问名为2或John Doe的属性，则必须使用方括号：value [2]或value [“ John Doe”]。

数组中的元素存储为数组的属性，使用数字作为属性名称。 因为您不能将点符号与数字一起使用，并且通常希望使用无论如何都可容纳索引的绑定，所以必须使用方括号符号来获取它们。

数组的length属性告诉我们它有多少个元素。 此属性名称是有效的绑定名称，我们已经知道了它的名称，因此通常要写array.length来查找数组的长度，因为它比array [“ length”]容易写。

## Methods

字符串对象和数组对象除了length属性外，还包含许多保存函数值的属性。

```javascript
let doh = "Doh";
console.log(typeof doh.toUpperCase);
// → function
console.log(doh.toUpperCase());
// → DOH
```

每个字符串都有一个toUpperCase属性。 调用时，它将返回字符串的副本，在该字符串中所有字母均已转换为大写。 还有toLowerCase，反之亦然。

有趣的是，即使对toUpperCase的调用未传递任何参数，该函数仍可以访问字符串“ Doh”，即我们调用其属性的值。 第6章介绍了它的工作方式。

包含函数的属性通常称为它们所属的值的方法，例如“ toUpperCase是字符串的方法”。

本示例演示了可用于操作数组的两种方法：

```javascript
let sequence = [1, 2, 3];
sequence.push(4);
sequence.push(5);
console.log(sequence);
// → [1, 2, 3, 4, 5]
console.log(sequence.pop());
// → 5
console.log(sequence);
// → [1, 2, 3, 4]
```

push方法将值添加到数组的末尾，而pop方法执行相反的操作，删除数组中的最后一个值并返回它。

这些有点愚蠢的名称是堆栈操作的传统术语。 堆栈在编程中是一种数据结构，它允许您将值压入其中并以相反的顺序再次弹出它们，以便最后删除最后添加的内容。 这些在编程中很常见-您可能还记得上一章中的函数调用堆栈，这是同一想法的一个实例。

## Objects

回到松鼠。 一组每日日志条目可以表示为一个数组。 但是，这些条目不仅由数字或字符串组成，每个条目都需要存储活动列表和一个布尔值，该布尔值指示雅克是否变成了松鼠。 理想情况下，我们希望将这些分组到一个值中，然后将这些分组的值放入日志条目数组中。

类型对象的值是属性的任意集合。 创建对象的一种方法是使用大括号作为表达式。

```javascript
let day1 = {
  squirrel: false,
  events: ["work", "touched tree", "pizza", "running"]
};
console.log(day1.squirrel);
// → false
console.log(day1.wolf);
// → undefined
day1.wolf = false;
console.log(day1.wolf);
// → false
```

在大括号内，有一个由逗号分隔的属性列表。 每个属性都有一个名称，后跟一个冒号和一个值。 当对象被写在多行上时，像示例中那样缩进可以提高可读性。 名称不是有效绑定名称或有效数字的属性必须加引号。

```javascript
let descriptions = {
  work: "Went to work",
  "touched tree": "Touched a tree"
};
```

这意味着括号在JavaScript中有两个含义。 在语句开始时，它们开始一个语句块。 在任何其他位置，它们描述一个对象。 幸运的是，用大括号括起来的对象来开始语句很少有用，因此，这两者之间的歧义并不是什么大问题。

读取不存在的属性将为您提供undefined值。

可以使用=运算符为属性表达式分配值。 如果该属性的值已经存在，它将替换该属性的值；如果不存在，则将在该对象上创建一个新属性。

回到我们的触手绑定模型，属性绑定是相似的。 他们掌握值，但是其他绑定和属性可能会保留这些相同的值。 您可能会认为对象是带有任意数量触手的章鱼，每个触手上都有一个纹身的名字。

删除操作员从这样的章鱼切下触手。 它是一元运算符，当应用于对象属性时，它将从对象中删除命名的属性。 这不是一件普通的事，但是有可能。

```javascript
let anObject = {left: 1, right: 2};
console.log(anObject.left);
// → 1
delete anObject.left;
console.log(anObject.left);
// → undefined
console.log("left" in anObject);
// → false
console.log("right" in anObject);
// → true
```

二元in运算符应用于字符串和对象时，将告诉您该对象是否具有具有该名称的属性。 将属性设置为undefined与实际删除它的区别在于，在第一种情况下，对象仍然具有该属性（只是没有非常有趣的值），而在第二种情况下，该属性不再存在 并且in将返回false。

要找出对象具有的属性，可以使用Object.keys函数。 您给它一个对象，它返回一个字符串数组-该对象的属性名称。

```javascript
console.log(Object.keys({x: 0, y: 0, z: 2}));
// → ["x", "y", "z"]
```

有一个Object.assign函数，可将所有属性从一个对象复制到另一个对象。

```javascript
let objectA = {a: 1, b: 2};
Object.assign(objectA, {b: 3, c: 4});
console.log(objectA);
// → {a: 1, b: 3, c: 4}
```

因此，数组只是一种专门用于存储事物序列的对象。 如果评估typeof []，它将产生“ object”。 您可以看到它们是长而扁平的章鱼，它们的触手排列整齐，标有数字。

我们将Jacques保留的日志表示为对象数组。

```javascript
let journal = [
  {events: ["work", "touched tree", "pizza", "running", "television"], squirrel: false},
  {events: ["work", "ice cream", "cauliflower", "lasagna", "touched tree", "brushed teeth"], squirrel: false},
  {events: ["weekend", "cycling", "break", "peanuts","beer"], squirrel: true},
  /* and so on... */
];
```

## Mutability

我们将很快开始实际的编程。 首先，还有更多理论要理解。

我们看到对象值可以修改。 在前面的章节中讨论的值的类型（例如数字，字符串和布尔值）都是不可变的，无法更改这些类型的值。 您可以合并它们并从中获取新值，但是当您使用特定的字符串值时，该值将始终保持不变。 其中的文本无法更改。 如果您的字符串包含“ cat”，则其他代码无法更改字符串中的字符以使其拼写为“ rat”。

对象的工作方式不同。 您可以更改它们的属性，从而使单个对象值在不同时间具有不同的内容。

当我们有两个数字120和120时，无论它们是否指代相同的物理位，我们都可以认为它们完全相同。 对于对象，具有对同一对象的两个引用与具有相同属性的两个不同对象之间是有区别的。 考虑以下代码：

```javascript
let object1 = {value: 10};
let object2 = object1;
let object3 = {value: 10};
console.log(object1 == object2);
// → true
console.log(object1 == object3);
// → false
object1.value = 15;
console.log(object2.value);
// → 15
console.log(object3.value);
// → 10
```

object1和object2绑定抓住同一对象，这就是为什么更改object1也会更改object2的值的原因。 据说它们具有相同的身份。 绑定对象3指向不同的对象，该对象最初包含与对象1相同的属性，但寿命不同。

绑定也可以是可变的或恒定的，但这与它们的值的行为方式是分开的。 即使数字值不变，您也可以使用let绑定通过更改绑定点所指向的值来跟踪变化的数字。 同样，尽管绑定到对象的const本身不能更改，并且将继续指向同一对象，但是该对象的内容可能会更改。

```javascript
const score = {visitors: 0, home: 0};
// This is okay
score.visitors = 1;
// This isn't allowed
score = {visitors: 1, home: 1};
```

当您使用JavaScript的==运算符比较对象时，它会按标识进行比较：仅当两个对象的值完全相同时，它才会产生true。 比较不同的对象将返回false，即使它们具有相同的属性。 JavaScript中没有内置的“深度”比较操作，该操作可以按内容比较对象，但是可以自己编写（这是本章最后的练习之一）。

## The Lycanthrope's log

因此，雅克启动了他的JavaScript解释器，并设置了保存日记所需的环境。

```javascript
let journal = [];
function addEntry(events, squirrel) {
  journal.push({events, squirrel});
}
```

请注意，添加到日志的对象看起来有些奇怪。 无需声明诸如events：events之类的属性，它只是提供一个属性名称。 这是简写，意思是相同的东西-如果括号中的属性名称后面没有值，则其值将从具有相同名称的绑定中获取。

因此，雅克每天晚上10时（有时是第二天早晨，从书架的最高架子上爬下来）记录一天。

```javascript
addEntry(["work", "touched tree", "pizza", "running","television"], false);
addEntry(["work", "ice cream", "cauliflower", "lasagna","touched tree", "brushed teeth"], false);
addEntry(["weekend", "cycling", "break", "peanuts","beer"], true);
```

一旦拥有足够的数据点，他打算使用统计信息来找出这些事件中的哪些可能与松散有关。

相关性是统计变量之间依存性的一种度量。 统计变量与编程变量并不完全相同。 在统计数据中，通常会有一组度量值，并且每个变量都会测量每个变量。 变量之间的相关性通常表示为-1到1之间的值。零相关性表示变量不相关。 相关系数为1表示两者是完全相关的-如果您知道一个，那么您也知道另一个。 负数也表示变量是完全相关的，但它们是相反的—当一个为真时，另一个为假。

要计算两个布尔变量之间的相关性，我们可以使用phi系数（φ）。 这是一个公式，其输入是一个频率表，其中包含观察到变量不同组合的次数。 公式的输出是-1和1之间的一个描述相关性的数字。

我们可以考虑吃披萨事件，然后将其放在这样的频率表中，其中每个数字表示在我们的测量中组合发生的次数：

```javascript

```









## Optional Arguments

下面的代码被允许并没有任何问题地执行：

```javascript
function square(x) { return x * x; }
console.log(square(4, true, "hedgehog"));
// → 16
```

我们仅用一个参数定义了square。 但是，当我们用3个参数来调用它时，这种语言不会抱怨。 它忽略多余的参数，并计算第一个参数的平方。

对于传递给函数的参数的数量，JavaScript的观点极为广泛。 如果传递的参数太多，多余的将被忽略。 如果传递的参数太少，则会为缺失的参数分配undefined值。

不利的一面是，甚至有可能您不小心将错误数量的参数传递给函数。 而且没有人会告诉你这件事。

有利的是，此行为可用于允许使用不同数量的参数调用函数。 例如，此减号函数尝试通过作用于一个或两个参数来模仿-运算符：

```javascript
function minus(a, b) {
  if (b === undefined) return -a;
  else return a - b;
}
console.log(minus(10));
// → -10
console.log(minus(10, 5));
// → 5
```

如果在参数后跟一个=运算符和一个表达式，则该表达式的值将在该参数没有传递时替换该参数。

例如，此版本的power使其第二个参数可选。 如果您不提供它或传递值undefined，它将默认为2，并且该函数的行为类似于square。

```javascript
function power(base, exponent = 2) {
  let result = 1;
  for (let count = 0; count < exponent; count++) {
    result *= base;
  }
  return result;
}
console.log(power(4));
// → 16
console.log(power(2, 6));
// → 64
```

在下一章中，我们将介绍一种函数体可以获取传递的参数的完整列表的方法。 这很有用，因为它使函数可以接受任意数量的参数。 例如，console.log做到了这一点-它输出给定的所有值。

```javascript
console.log("C", "O", 2);
// → C O 2
```

## Closure

将函数视为值的能力，再加上每次调用函数都会重新创建局部绑定这一事实，提出了一个有趣的问题。 当创建本地绑定的函数调用不再活动时，本地绑定会怎样？ 以下代码显示了此示例。 它定义一个函数wrapValue，该函数创建本地绑定。 然后，它返回一个函数，该函数访问并返回此本地绑定。

```javascript
function wrapValue(n) {
  let local = n;
  return () => local;
}
let wrap1 = wrapValue(1);
let wrap2 = wrapValue(2);
console.log(wrap1());
// → 1
console.log(wrap2());
// → 2
```

这是允许的，并且可以按您希望的方式工作-仍然可以访问绑定的两个实例。 这种情况很好地说明了以下事实：为每个呼叫重新创建了本地绑定，并且不同的呼叫无法践踏彼此的本地绑定。

能够引用封闭范围内的本地绑定的特定实例的此功能称为封闭。 从本地作用域引用绑定的函数称为闭包。 这种行为不仅使您不必担心绑定的生命周期，而且还可以以某些创造性的方式使用函数值。

稍作更改，我们就可以将前面的示例转换为创建乘以任意数量的函数的方法。

```javascript
function multiplier(factor) {
  return number => number * factor;
}
let twice = multiplier(2);
console.log(twice(5));
// → 10
```

确实不需要wrapValue示例中的显式本地绑定，因为参数本身就是本地绑定。

考虑这样的程序需要一些练习。 一个好的思维模型是将函数值视为包含其主体代码和创建它们的环境的代码。 在调用函数主体时，它会看到在其中创建它的环境，而不是在其中看到它的环境。

在该示例中，将调用multiplier并创建一个环境，该环境中的factor参数绑定到2。它返回的函数值（存储在两次中）会记住该环境。 因此，当调用它时，它将其参数乘以2。

## Recursion

函数调用自身完全可以，只要它不经常执行而使堆栈溢出即可。 调用自身的函数称为递归。 递归允许以不同的样式编写某些函数。 以power的实现为例：

```javascript
function power(base, exponent) {
  if (exponent == 0) {
    return 1;
  } else {
    return base * power(base, exponent - 1);
  }
}
console.log(power(2, 3));
// → 8
```

这与数学家定义幂运算的方式非常接近，并且可以说比循环变量更清楚地描述了该概念。 该函数以越来越小的指数多次调用自身以实现重复乘法。

但是这种实现有一个问题：在典型的JavaScript实现中，它比循环版本慢三倍。通过一个简单的循环运行通常比多次调用一个函数便宜。

速度与优雅的矛盾是一个有趣的问题。您可以将其视为人类友好和机器友好之间的一种连续体。通过使程序更大且更复杂，几乎可以使它更快。程序员必须决定适当的平衡。

在幂函数的情况下，优雅（循环）版本仍然相当简单且易于阅读。用递归版本替换它没有多大意义。但是，程序通常会处理如此复杂的概念，因此为了使程序更简单而放弃一些效率是有帮助的。

担心效率可能会分散注意力。这是使程序设计复杂化的另一个因素，当您执行本来已经很困难的事情时，担心的额外事情可能会瘫痪。

因此，请始终从编写正确且易于理解的内容开始。如果您担心它太慢（通常不会这样做，因为大多数代码只是执行得不够频繁而不会花费大量时间），则可以事后进行评估，并在必要时进行改进。

递归并不总是仅是循环的一种低效替代方法。 使用递归比使用循环更容易解决某些问题。 大多数情况下，这些都是需要探索或处理多个“分支”的问题，每个分支可能会再次分支为更多分支。

考虑一下这个难题：通过从数字1开始并重复加5或乘以3，可以生成无穷多个数字。 您将如何编写一个给定数字的函数，该函数试图查找产生该数字的加法和乘法序列？

例如，数字13可以通过先乘以3，然后再加5两次来获得，而数字15根本无法达到。

这是一个递归解决方案：

```javascript
function findSolution(target) {
  function find(current, history) {
    if (current == target) {
      return history;
    } else if (current > target) {
      return null;
    } else {
      return find(current + 5, `(${history} + 5)`) || find(current * 3, `(${history} * 3)`);
    }
  }
  return find(1, "1");
}
console.log(findSolution(24));
// → (((1 * 3) + 5) * 3)
```

请注意，该程序不一定会找到最短的操作顺序。 当它完全找到任何序列时，它就会满足。

如果您不立即了解它的工作原理，那就可以了。 让我们来研究一下它，因为它可以极大地促进递归思维。

内部函数查找执行实际递归。 它带有两个参数：当前数字和一个记录我们如何达到此数字的字符串。 如果找到解决方案，则返回一个字符串，该字符串显示如何到达目标。 如果从该数字开始找不到解决方案，则返回null。

为此，该功能执行以下三个操作之一。 如果当前号码是目标号码，则当前历史记录是达到该目标的一种方式，因此将其返回。 如果当前数大于目标数，则进一步探索该分支没有任何意义，因为加法和乘法只会增加该数，因此返回null。 最后，如果我们仍未达到目标数字，该函数会通过调用两次自身（一次用于加法，一次用于乘法）来尝试从当前数字开始的两条可能路径。 如果第一个调用返回的内容不为null，则返回该内容。 否则，将返回第二个调用，无论它产生的是字符串还是null。

为了更好地了解此功能如何产生我们想要的效果，让我们看一下在寻找数字13解决方案时进行的所有查找。

```
find(1, "1")
  find(6, "(1 + 5)")
    find(11, "((1 + 5) + 5)")
      find(16, "(((1 + 5) + 5) + 5)")
        too big
      find(33, "(((1 + 5) + 5) * 3)")
        too big
    find(18, "((1 + 5) * 3)")
      too big
  find(3, "(1 * 3)")
    find(8, "((1 * 3) + 5)")
      find(13, "(((1 * 3) + 5) + 5)")
        found!
```

缩进表示调用堆栈的深度。 首次调用find时，它首先调用自身以探索以（1 + 5）开头的解决方案。 该调用将进一步递归以探究产生的结果小于或等于目标数目的每个连续解决方案。 由于找不到要命中目标的人，因此它将空值返回到第一个通话。 那里|| 运算符导致探索（1 * 3）的呼叫发生。 此搜索更有运气-它的第一个递归调用（通过另一个递归调用）命中目标编号。 最里面的调用返回一个字符串，每个|| 中间调用中的运算符将传递该字符串，最终返回解决方案。

## Growing functions

有两种或多种自然的方法可以将函数引入程序。

第一个是您发现自己多次编写类似的代码。 您不希望这样做。 拥有更多的代码意味着更多的空间可以隐藏错误，并为试图理解该程序的人们提供更多的阅读材料。 因此，您可以使用重复的功能，为其找到一个好名字，然后将其放入功能中。

第二种方法是发现您需要一些尚未编写的功能，这听起来应该具有自己的功能。 首先，命名功能，然后编写其主体。 在实际定义函数本身之前，您甚至可能开始编写使用该函数的代码。

为函数找到一个好名字很难，可以很好地表明您要包装的概念有多清晰。 让我们来看一个例子。我们想编写一个打印两个数字的程序：一个农场中的牛和鸡的数目，后跟单词“牛和鸡”，并在两个数字之前填充零，以便它们始终为三位数。

```
007 Cows
011 Chickens
```

这需要两个参数的函数-牛的数量和鸡的数量。 让我们开始编码。

```javascript
function printFarmInventory(cows, chickens) {
  let cowString = String(cows);
  while (cowString.length < 3) {
    cowString = "0" + cowString;
  }
  console.log(`${cowString} Cows`);
  let chickenString = String(chickens);
  while (chickenString.length < 3) {
    chickenString = "0" + chickenString;
  }
  console.log(`${chickenString} Chickens`);
}
printFarmInventory(7, 11);
```

在字符串表达式后写.length将给我们该字符串的长度。 因此，while循环将在数字字符串前添加零，直到它们的长度至少为三个字符。

任务完成！ 但是，就在我们要向农民发送代码（以及大量发票）时，她打电话告诉我们也开始养猪了，难道我们不能将软件扩展到也可以打印猪吗？

我们肯定可以。 但是，就像我们一次又一次复制和粘贴这四行一样，我们停下来重新考虑。 一定有更好的方法。 这是第一次尝试：

```javascript
function printZeroPaddedWithLabel(number, label) {
  let numberString = String(number);
  while (numberString.length < 3) {
    numberString = "0" + numberString;
  }
  console.log(`${numberString} ${label}`);
}
function printFarmInventory(cows, chickens, pigs) {
  printZeroPaddedWithLabel(cows, "Cows");
  printZeroPaddedWithLabel(chickens, "Chickens");
  printZeroPaddedWithLabel(pigs, "Pigs");
}
printFarmInventory(7, 11, 3);
```

有用！ 但是这个名字printZeroPaddedWithLabel有点尴尬。 它将三个内容（打印，零填充和添加标签）合并为一个函数。

除了尝试重复我们的程序批发中重复的部分外，让我们尝试选择一个概念。

```javascript
function zeroPad(number, width) {
  let string = String(number);
  while (string.length < width) {
    string = "0" + string;
  }
  return string;
}
function printFarmInventory(cows, chickens, pigs) {
  console.log(`${zeroPad(cows, 3)} Cows`);
  console.log(`${zeroPad(chickens, 3)} Chickens`);
  console.log(`${zeroPad(pigs, 3)} Pigs`);
}
printFarmInventory(7, 16, 3);
```

具有好名字的函数（例如zeroPad）使阅读代码的人更容易了解其功能。 这样的功能不仅仅是特定程序中而且在更多情况下都很有用。 例如，您可以使用它来帮助打印精确对齐的数字表。

我们的功能应该有多么聪明和多功能？ 我们可以编写任何东西，从非常简单的功能（只能将数字填充为三个字符）到复杂的通用数字格式系统（可处理小数，负数，小数点对齐，以不同字符填充等） 。

一个有用的原则是不要增加聪明，除非您完全确定自己将需要它。 可能会为遇到的每一个功能编写通用的“框架”。 抵制这种冲动。 您将无法完成任何实际的工作，只是编写从未使用过的代码。

## Function and side effects

函数可以大致分为因副作用而调用的函数和因返回值而调用的函数。 （尽管绝对可以同时具有副作用和返回值。）

农场示例中的第一个帮助函数printZeroPaddedWithLabel的副作用是被调用：它打印一行。 第二个版本zeroPad被调用为其返回值。 与第二种情况相比，第二种情况在更多情况下有用，这并非巧合。 与直接产生副作用的函数相比，创造值的函数更容易以新方式进行组合。

纯函数是一种特定类型的值产生函数，它不仅没有副作用，而且不依赖于其他代码的副作用。例如，它不读取其值可能会更改的全局绑定。 纯函数具有令人愉悦的属性，当使用相同的参数调用该函数时，它始终会产生相同的值（并且不会做其他任何事情）。 可以通过返回值替换对此类函数的调用，而无需更改代码的含义。 如果不确定纯函数是否正常工作，可以通过简单地调用它来测试它，并知道如果它在该上下文中有效，那么它将在任何上下文中都能正常工作。 非纯功能往往需要更多的脚手架进行测试。

尽管如此，在编写非纯函数时也无需感到难过，也不必费心去将其从代码中清除。 副作用通常很有用。 例如，无法编写纯版本的console.log，而console.log很好。 当我们使用副作用时，某些操作也更容易以有效的方式表示，因此计算速度可能是避免纯度的原因。

## Summary

本章教您如何编写自己的函数。 函数关键字在用作表达式时可以创建函数值。 当用作语句时，可用于声明绑定并为其提供函数作为其值。 箭头函数是创建函数的另一种方法。

```javascript
// Define f to hold a function value
const f = function(a) {
  console.log(a + 2);
};
// Declare g to be a function
function g(a, b) {
  return a * b * 3.5;
}
// A less verbose function value
let h = a => a % 3;
```

了解函数的一个关键方面是了解范围。 每个块创建一个新的范围。 在给定范围内声明的参数和绑定是局部的，从外部看不到。 用var声明的绑定的行为有所不同-它们最终位于最近的函数作用域或全局作用域中。

将程序执行的任务分成不同的功能会很有帮助。 您无需重复太多，功能可以通过将代码分组为可以完成特定任务的部分来帮助组织程序。

## Exercises

### Minimum

上一章介绍了返回其最小参数的标准函数Math.min。 我们现在可以构建类似的东西。 编写一个函数min，它接受两个参数并返回它们的最小值。

```javascript
function mymin(a,b) {
  return (a<b)? a:b;
}
```

### Recursion

我们已经看到％（余数运算符）可用于测试数字是偶数还是奇数，方法是使用％2来查看其是否可被二整除。 这是定义正整数是偶数还是奇数的另一种方法：

* 零是偶数。
* 一个是奇数。
* 对于任何其他数字N，其均匀度与N-2相同。

定义一个与该描述相对应的递归函数isEven。 该函数应接受单个参数（正整数）并返回布尔值。

```javascript
function isEven(num) {
  if (num < 0) {
    return isEvent(-num);
  } else if (num == 0) {
    return true;  
  } else if (num == 1) {
    return false;
  } else {
    return isEven(num-2);
  }
}
```



在50和75上进行测试。在-1上查看其行为。 为什么？ 您能想到解决此问题的方法吗？

### Bean Counting

您可以通过写“ string” [N]从字符串中获取第N个字符或字母。 返回的值将是一个仅包含一个字符的字符串（例如“ b”）。 第一个字符的位置为0，这导致最后一个字符的位置为string.length-1。 换句话说，两个字符的字符串的长度为2，其字符的位置为0和1。

编写一个函数countBs，该函数将字符串作为唯一参数，并返回一个数字，该数字指示字符串中有多少个大写的“ B”字符。

```javascript
function countBs(string) {
  return countChar(string, "B");
}
```



接下来，编写一个称为countChar的函数，其行为类似于countBs，只是它需要第二个参数来指示要计数的字符（而不是仅计数大写的“ B”字符）。 重写countB以利用此新功能。

```javascript
function countChar(string, ch) {
  let counted = 0;
  for (let i = 0; i < string.length; i++) {
    if (string[i] == ch) {
      counted += 1;
    }
  }
  return counted;
}
```

