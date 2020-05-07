# Functions

函数是JavaScript编程的基础。 将程序包装成一个值的概念有很多用途。 它为我们提供了一种构造大型程序，减少重复，将名称与子程序关联以及将这些子程序彼此隔离的方法。

函数最明显的应用是定义新词汇。 用散文创造新词通常是不好的风格。 但是在编程中，它是必不可少的。

典型的成年英语使用者的词汇量约为20,000个单词。 很少有内置20,000个命令的编程语言。与人类语言相比，可用词汇往往更精确地定义，因此不够灵活。 因此，我们通常必须引入新的概念，以避免重复过多。

## Defining a function

函数定义是常规绑定，其中绑定的值是函数。 例如，此代码定义平方，以引用产生给定数字平方的函数：

```javascript
const square = function(x) {
  return x * x;
};
console.log(square(12));
// → 144
```

使用以关键字function开头的表达式创建函数。 函数具有一组参数（在这种情况下，只有x）和一个主体，其中包含要在调用函数时执行的语句。 以这种方式创建的函数的函数主体必须始终用大括号括起来，即使它仅由单个语句组成。

一个函数可以有多个参数，也可以根本没有参数。 在以下示例中，makeNoise不列出任何参数名称，而power列出两个参数名称：

```javascript
const makeNoise = function() {
  console.log("Pling!");
};
makeNoise();
// → Pling!
const power = function(base, exponent) {
  let result = 1;
  for (let count = 0; count < exponent; count++) {
    result *= base;
  }
  return result;
};
console.log(power(2, 10));
// → 1024
```

有些函数会产生一个值，例如power和square，而有些函数不会产生一个值，例如makeNoise，其唯一结果是产生副作用。 return语句确定函数返回的值。 当控件遇到这样的语句时，它立即跳出当前函数，并将返回的值提供给调用该函数的代码。如果return关键字后面没有表达式，将导致函数返回undefined。 根本没有return语句的函数，例如makeNoise，同样返回undefined.

函数的参数的行为类似于常规绑定，但是它们的初始值是由函数的调用者而不是函数本身中的代码给出的。

## Bindings and scopes

每个绑定都有一个范围，该范围是该绑定在程序中可见的一部分。 对于在任何函数或块之外定义的绑定，范围是整个程序-您可以在任何需要的位置引用此类绑定。 这些称为全局。

但是为函数参数创建的绑定或在函数内部声明的绑定只能在该函数中引用，因此它们被称为局部绑定。 每次调用该函数时，都会创建这些绑定的新实例。 这提供了功能之间的某种隔离-每个函数调用都在自己的小世界（其本地环境）中运行，并且通常无需了解很多有关全局环境中发生的事情就可以理解。

实际上，用let和const声明的绑定在声明它们的块中是本地的，因此，如果您在循环内部创建一个绑定，则循环前后的代码将无法“看到”它。 在2015年前的JavaScript中，除非函数创建了新的作用域，否则使用var关键字创建的旧式绑定在它们出现的整个函数中（如果不在函数中）在整个作用域中都是可见的。

```javascript
let x = 10;
if (true) {
  let y = 20;
  var z = 30;
  console.log(x + y + z);
  // → 60
}
// y is not visible here
console.log(x + z);
// → 40
```

每个范围都可以“观察”周围的范围，因此x在示例中的块内可见。 唯一的例外是多个绑定具有相同的名称-在这种情况下，代码只能看到最里面的一个。 例如，当halve函数中的代码引用n时，它将看到自己的n而不是全局n。

```javascript
const halve = function(n) {
  return n / 2;
};
let n = 10;
console.log(halve(100));
// → 50
console.log(n);
// → 10
```

### Nested Scope

JavaScript不仅区分全局绑定和局部绑定。 可以在其他块和功能内创建块和功能，从而产生多个程度的局部性。

例如，此函数（输出制作一批鹰嘴豆泥所需的成分）内部具有另一个函数：

```javascript
const hummus = function(factor) {
  const ingredient = function(amount, unit, name) {
    let ingredientAmount = amount * factor;
    if (ingredientAmount > 1) {
      unit += "s";
    }
    console.log(`${ingredientAmount} ${unit} ${name}`);
  };
  ingredient(1, "can", "chickpeas");
  ingredient(0.25, "cup", "tahini");
  ingredient(0.25, "cup", "lemon juice");
  ingredient(1, "clove", "garlic");
  ingredient(2, "tablespoon", "olive oil");
  ingredient(0.5, "teaspoon", "cumin");
};
```

成分函数内部的代码可以从外部函数看到因子绑定。 但是它的局部绑定（例如unit或IngredientAmount）在外部函数中不可见。

简而言之，每个本地范围也可以看到包含它的所有本地范围。 块内部可见的绑定集由该块在程序文本中的位置确定。 每个本地范围也可以看到包含它的所有本地范围，并且所有范围都可以看到全局范围。 这种绑定可见性的方法称为词法作用域。

## Functions As Values

函数绑定通常只是充当程序特定部分的名称。 这样的绑定定义一次，并且永远不会改变。 很容易混淆函数及其名称。

但是两者是不同的。 函数值可以完成其他值可以做的所有事情-您可以在任意表达式中使用它，而不仅仅是调用它。 可以将函数值存储在新的绑定中，将其作为参数传递给函数，依此类推。 同样，拥有函数的绑定仍然只是常规绑定，并且如果不是常量，则可以分配一个新值，如下所示：

```javascript
let launchMissiles = function() {
  missileSystem.launch("now");
};
if (safeMode) {
  launchMissiles = function() {/* do nothing */};
}
```

在第5章中，我们将讨论可以通过将函数值传递给其他函数来完成的有趣事情。

## Declaration notation

存在更简短的方式来创建函数绑定。以function关键字在语句的开头，其工作原理有所不同。

```javascript
function square(x) {
  return x * x;
}
```

这是一个函数声明。 该语句定义绑定square并将其指向给定的函数。 该函数编写起来稍微容易一些，并且在函数后不需要分号。

这种形式的函数定义有一个微妙之处。

```javascript
console.log("The future says:", future());
function future() {
  return "You'll never have flying cars";
}
```

即使在使用该功能的代码下定义了该功能，上述代码也可以使用。 函数声明不属于常规的自上而下的控制流。 从概念上讲，它们已移到其作用域的顶部，并且可以被该作用域中的所有代码使用。 有时这很有用，因为它提供了以有意义的方式对代码进行排序的自由，而不必担心在使用所有函数之前必须先定义它们。

## Arrow Functions

对于函数，还有第三种表示法，看起来与其他符号有很大不同。 它使用由等号和大于字符组成的箭头（=>）代替function关键字（不要与大于或等于运算符（写为> =）混淆）。

```javascript
const power = (base, exponent) => {
  let result = 1;
  for (let count = 0; count < exponent; count++) {
    result *= base;
  }
  return result;
};
```

箭头位于参数列表之后，其后是函数的正文。 它表示类似“此输入（参数）产生此结果（主体）”的内容。

如果只有一个参数名称，则可以省略参数列表周围的括号。 如果主体是单个表达式，而不是大括号中的块，则该表达式将从函数中返回。 因此，正方形的这两个定义具有相同的作用：

```javascript
const square1 = (x) => { return x * x; };
const square2 = x => x * x;
```

当箭头函数根本没有参数时，其参数列表只是一组空括号。

```javascript
const horn = () => {
  console.log("Toot");
};
```

没有必要同时使用该语言的箭头函数和函数表达式。 除了次要的细节（我们将在第6章中讨论）之外，它们的作用相同。 2015年添加了Arrow函数，主要是为了以较小的冗长方式编写小的函数表达式。 我们将在第5章中大量使用它们。

## The Call Stack

控制流经功能的方式有些涉及。 让我们仔细看看。 这是一个简单的程序，可以进行一些函数调用：

```javascript
function greet(who) {
  console.log("Hello " + who);
}
greet("Harry");
console.log("Bye");
```

运行该程序的过程大致如下：对greet的调用导致控件跳至该函数的开头（第2行）。 该函数调用console.log，它进行控制，执行其工作，然后将控制权返回到第2行。在此到达greet函数的末尾，因此它返回到调用它的位置，即第4行。 之后再次调用console.log。 返回之后，程序结束。

我们可以像这样示意性地显示控制流：

```
not in function
  in greet
    in console.log
  in greet
not in function
  in console.log
not in function
```

因为函数必须在返回时跳回到调用它的位置，所以计算机必须记住调用发生的上下文。 在一种情况下，console.log必须在完成后返回到greet函数。 在其他情况下，它返回到程序的末尾。

计算机存储该上下文的位置是调用堆栈。 每次调用函数时，当前上下文都存储在此堆栈的顶部。 当函数返回时，它将从堆栈中删除顶部上下文，并使用该上下文继续执行。

存储该堆栈需要计算机内存中的空间。 当堆栈太大时，计算机将失败，并显示诸如“堆栈空间不足”或“递归过多”之类的消息。 下面的代码通过向计算机提出一个非常棘手的问题来说明这一点，该问题会导致两个函数之间的无限往返。 相反，如果计算机具有无限的堆栈，它将是无限的。 照原样，我们将用完空间，或“破坏堆栈”。

```javascript
function chicken() {
  return egg();
}
function egg() {
  return chicken();
}
console.log(chicken() + " came first.");
// → ??
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

