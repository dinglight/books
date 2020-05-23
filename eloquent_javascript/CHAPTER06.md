# The secret life of objects

第4章介绍了JavaScript的对象。 在编程文化中，我们有一种称为面向对象的编程的东西，这是一组使用对象（及相关概念）作为程序组织中心原理的技术。 尽管没有人真的同意它的精确定义，但是面向对象的编程已经影响了包括JavaScript在内的许多编程语言的设计。 本章将描述这些想法在JavaScript中的应用方式。

## Encapsulation

面向对象编程的核心思想是将程序分成较小的部分，并使每个部分负责管理自己的状态。这样，可以将有关程序部分工作方式的一些知识保留在该部分中。从事该程序其余部分的人员不必记住，甚至不必知道这些知识。每当这些本地详细信息更改时，仅需要更新其周围的代码。此类程序的不同部分通过接口，功能有限的集合或绑定相互交互，这些接口或绑定在更抽象的级别提供有用的功能，从而隐藏了它们的精确实现。使用对象对此类程序段进行建模。它们的界面由一组特定的方法和属性组成。属于接口的属性称为public。外部代码不应接触的其他部分称为私有。许多语言提供了一种区分公共属性和私有属性并防止外部代码完全访问私有属性的方法。 JavaScript再次采用了极简主义的方法，现在还没有-至少现在还没有。目前正在进行将其添加到语言中的工作。即使该语言没有内置这种区别，JavaScript程序员也已经成功地使用了这种想法。通常，可用接口在文档或注释中描述。通常在属性名称的开头添加下划线（_）字符以指示这些属性是私有的。将接口与实现分开是一个好主意。通常称为封装。

## Methods

方法不过是保存函数值的属性而已。 这是一个简单的方法：

```javascript
let rabbit = {};
rabbit.speak = function(line) {
  console.log(`The rabbit says '${line}'`);
};
rabbit.speak("I'm alive.");
// → The rabbit says 'I'm alive.'
```

通常，方法需要对调用它的对象做一些事情。 当一个函数被调用为方法时（如在object.method（）中那样被视为一个属性并立即被调用），在其主体中称为this的绑定会自动指向被调用的对象。

```javascript
function speak(line) {
  console.log(`The ${this.type} rabbit says '${line}'`);
}
let whiteRabbit = {type: "white", speak};
let hungryRabbit = {type: "hungry", speak};
whiteRabbit.speak("Oh my ears and whiskers, " +
                  "how late it's getting!");
// → The white rabbit says 'Oh my ears and whiskers, how
// late it's getting!'
hungryRabbit.speak("I could use a carrot right now.");
// → The hungry rabbit says 'I could use a carrot right now.'
```

您可以将其视为以其他方式传递的额外参数。 如果要显式传递它，则可以使用函数的call方法，该方法将this值作为其第一个参数，并将其他参数视为普通参数。

```javascript
speak.call(hungryRabbit, "Burp!");
// → The hungry rabbit says 'Burp!'
```

由于每个函数都有自己的this绑定，其值取决于调用方式，因此您不能在使用function关键字定义的常规函数中引用包装范围的this。 箭头函数是不同的-它们不绑定自己的this，但是可以看到它们周围范围的this绑定。 因此，您可以执行类似以下代码的操作，该代码从本地函数内部进行引用：

```javascript
function normalize() {
  console.log(this.coords.map(n => n / this.length));
}
normalize.call({coords: [0, 2, 3], length: 5});
// → [0, 0.4, 0.6]
```

如果我使用function关键字编写了要映射的参数，则该代码将无效。

## Prototypes

看这个

```javascript
let empty = {};
console.log(empty.toString);
// → function toString()…{}
console.log(empty.toString());
// → [object Object]
```

我从一个空对象中拉出了一个属性。 魔法！ 好吧，不是真的。 我只是隐瞒有关JavaScript对象工作方式的信息。 除了其属性集外，大多数对象还具有原型。 原型是另一个用作属性的备用源的对象。 当一个对象获得对它没有的属性的请求时，将在其原型中搜索该属性，然后搜索该原型的原型，依此类推。 那么谁是那个空物体的原型呢？ 它是伟大的祖先原型，几乎所有对象背后的实体Object.prototype

```javascript
console.log(Object.getPrototypeOf({}) == Object.prototype);
// → true
console.log(Object.getPrototypeOf(Object.prototype));
// → null
```

如您所料，Object.getPrototypeOf返回对象的原型。 JavaScript对象的原型关系形成一个树形结构，该结构的根位于Object.prototype。 它提供了一些在所有对象中显示的方法，例如toString，它将对象转换为字符串表示形式。 许多对象并不直接将Object.prototype作为其原型，而是使用另一个提供不同默认属性集的对象。 函数派生自Function.prototype，而数组派生自Array.prototype

```javascript
console.log(Object.getPrototypeOf(Math.max) == Function.prototype);
// → true
console.log(Object.getPrototypeOf([]) == Array.prototype);
// → true
```

这样的原型对象本身将具有原型，通常是Object.prototype，因此它仍间接提供诸如toString之类的方法。 您可以使用Object.create创建具有特定原型的对象。

```javascript
let protoRabbit = {
  speak(line) {
    console.log(`The ${this.type} rabbit says '${line}'`);
  }
};
let killerRabbit = Object.create(protoRabbit);
killerRabbit.type = "killer";
killerRabbit.speak("SKREEEE!");
// → The killer rabbit says 'SKREEEE!'
```

对象表达式中的诸如talk（line）之类的属性是定义方法的简便方法。 它创建了一个称为语音的属性，并为其赋予了功能。 “原始”兔子充当所有兔子共享的属性的容器。 单个兔子对象（如杀手兔子）包含仅适用于自身的属性（在本例中为类型），并从其原型派生共享属性。

## Classes

JavaScript的原型系统可以解释为对称为类的面向对象概念的某种非正式形式。 类定义一种对象类型的形状，即它具有什么方法和属性。 这样的对象称为类的实例。 原型可用于定义类的所有实例共享相同值的属性，例如方法。 每个实例不同的属性（例如我们的Rabbit的type属性）需要直接存储在对象本身中。 因此，要创建给定类的实例，您必须创建一个从正确的原型派生的对象，但还必须确保它本身具有该类实例应具有的属性。 这就是构造函数的作用。

```javascript
function makeRabbit(type) {
  let rabbit = Object.create(protoRabbit);
  rabbit.type = type;
  return rabbit;
}
```

JavaScript提供了一种使定义此类函数更容易的方法。 如果将关键字new放在函数调用的前面，则该函数将被视为构造函数。 这意味着将自动创建具有正确原型的对象，并将其绑定到函数中，并在函数末尾返回。 通过采用构造函数的prototype属性可以找到构造对象时使用的原型对象。

```javascript
function Rabbit(type) {
  this.type = type;
}
Rabbit.prototype.speak = function(line) {
  console.log(`The ${this.type} rabbit says '${line}'`);
};
let weirdRabbit = new Rabbit("weird");
```

构造函数（实际上是所有函数）会自动获取一个名为prototype的属性，默认情况下，该属性包含一个从Object.prototype派生的普通空对象。 您可以根据需要用新对象覆盖它。 也可以像示例一样向现有对象添加属性。 按照约定，构造函数的名称要大写，以便可以轻松将它们与其他函数区分开。 重要的是要了解原型与构造函数的关联方式（通过其prototype属性）与对象具有原型的方式（可以通过Object.getPrototypeOf找到）之间的区别。 构造函数的实际原型是Function.prototype，因为构造函数是函数。 它的prototype属性保存用于通过它创建的实例的原型。

```javascript
console.log(Object.getPrototypeOf(Rabbit) == Function.prototype);
// → true
console.log(Object.getPrototypeOf(weirdRabbit) == Rabbit.prototype);
// → true
```

## Class notation

因此，JavaScript类是具有原型属性的构造函数。 它们就是这样工作的，直到2015年，您才必须编写它们。 这些天，我们有了一个不太尴尬的表示法。

```javascript
class Rabbit {
  constructor(type) {
    this.type = type;
  }
  speak(line) {
    console.log(`The ${this.type} rabbit says '${line}'`);
  }
}
let killerRabbit = new Rabbit("killer");
let blackRabbit = new Rabbit("black");
```

class关键字启动一个类声明，它使我们可以在一个地方定义一个构造函数和一组方法。声明的花括号内可以写入任意数量的方法。一个命名构造函数被特殊对待。它提供了实际的构造函数，该函数将绑定到名称Rabbit。其他的则打包到该构造函数的原型中。因此，较早的类声明等效于上一节中的构造函数定义。看起来更好。当前，类声明仅允许将方法（包含函数的属性）添加到原型中。当您要在其中保存非功能值时，这可能会带来一些不便。该语言的下一个版本可能会对此有所改善。目前，您可以通过在定义类后直接操作原型来创建此类属性。像function一样，class可以在语句和表达式中使用。当用作表达式时，它不定义绑定，而只是将构造函数生成为值。您可以在类表达式中省略类名。

```javascript
let object = new class { getWord() { return "hello"; } };
console.log(object.getWord());
// → hello
```

## Overriding derived properties

将属性添加到对象时，无论该属性是否存在于原型中，该属性都会添加到对象本身。 如果原型中已经存在一个具有相同名称的属性，那么该属性将不再影响该对象，因为它现在已隐藏在该对象自己的属性后面。

```javascript
Rabbit.prototype.teeth = "small";
console.log(killerRabbit.teeth);
// → small
killerRabbit.teeth = "long, sharp, and bloody";
console.log(killerRabbit.teeth);
// → long, sharp, and bloody
console.log(blackRabbit.teeth);
// → small
console.log(Rabbit.prototype.teeth);
// → smallconsole.log([1, 2, 3, 4].reduce((a, b) => a + b));
// → 10
```

下图概述了此代码运行后的情况。 Rabbit和Object原型作为一种背景位于killerRabbit后面，可以在其中查找对象本身未找到的属性。

覆盖原型中存在的属性可能是一件有用的事情。 如兔齿示例所示，在更普通的对象类别的实例中，可以使用覆盖来表示特殊属性，同时让非例外对象从其原型中获取标准值。 覆盖还用于为标准函数和数组原型提供与基本对象原型不同的toString方法。

```javascript
console.log(Array.prototype.toString ==
Object.prototype.toString);
// → false
console.log([1, 2].toString());
// → 1,2
```

在数组上调用toString会产生与在其上调用.join（“，”）类似的结果-将逗号放在数组中的值之间。 直接调用对象。 带数组的prototype.toString会生成另一个字符串。 该函数不了解数组，因此仅将单词对象和类型名称放在方括号之间。

```javascript
console.log(Object.prototype.toString.call([1, 2]));
// → [object Array]
```

## Maps

我们在上一章中看到了单词映射，该单词映射用于通过对元素应用函数来转换数据结构的操作。 尽管令人困惑，但在编程中，相同的词也用于相关但完全不同的事物。 映射（名词）是将值（键）与其他值关联的数据结构。 例如，您可能想将名称映射到年龄。 为此可以使用对象。

```javascript
let ages = {
  Boris: 39,
  Liang: 22,
  Júlia: 62
};
console.log(`Júlia is ${ages["Júlia"]}`);
// → Júlia is 62
console.log("Is Jack's age known?", "Jack" in ages);
// → Is Jack's age known? false
console.log("Is toString's age known?", "toString" in ages);
// → Is toString's age known? true
```

在这里，对象的属性名称是人们的名字，属性值是他们的年龄。 但是我们当然没有在我们的Map中列出任何名为toString的人。 但是，由于普通对象是从Object.prototype派生的，因此看起来该属性在那里。因此，将普通对象用作Map很危险。 有几种可能的方法来避免此问题。 首先，可以创建没有原型的对象。 如果将null传递给Object.create，则生成的对象将不会派生自Object.prototype，并且可以安全地用作Map。

```javascript
console.log("toString" in Object.create(null));
// → false
```

对象属性名称必须是字符串。 如果您需要一个Map，其键不能轻松转换为字符串（例如对象），则不能将对象用作Map。 幸运的是，JavaScript附带了一个名为Map的类，正是为此目的而编写的。 它存储一个映射并允许任何类型的键。

```javascript
let ages = new Map();
ages.set("Boris", 39);
ages.set("Liang", 22);
ages.set("Júlia", 62);
console.log(`Júlia is ${ages.get("Júlia")}`);
// → Júlia is 62
console.log("Is Jack's age known?", ages.has("Jack"));
// → Is Jack's age known? false
console.log(ages.has("toString"));
// → false
```

set，get和has方法是Map对象的接口的一部分。 编写一个可以快速更新和搜索大量值的数据结构并不容易，但是我们不必为此担心。 有人为我们做了，我们可以通过这个简单的界面来使用他们的工作。 如果确实有一个出于某种原因需要作为地图处理的普通对象，那么知道Object.keys仅返回对象自己的键，而不返回原型中的键会很有用。 作为in运算符的替代方法，您可以使用hasOwnProperty方法，该方法将忽略对象的原型。

```javascript
console.log({x: 1}.hasOwnProperty("x"));
// → true
console.log({x: 1}.hasOwnProperty("toString"));
// → false
```

## Polymorphism

当您在对象上调用String函数（将值转换为字符串）时，它将在该对象上调用toString方法，以尝试从该对象创建有意义的字符串。 我提到过，一些标准原型定义了自己的toString版本，因此它们可以创建一个字符串，该字符串包含比“ [object Object]”更多的有用信息。 您也可以自己做。

```javascript
Rabbit.prototype.toString = function() {
  return `a ${this.type} rabbit`;
};
console.log(String(blackRabbit));
// → a black rabbit
```

这是一个强大想法的简单实例。 当编写一段代码来使用具有特定接口的对象（在本例中为toString方法）时，可以将支持该接口的任何类型的对象插入代码中，这样就可以正常工作。 这种技术称为多态性。 多态代码可以使用不同形状的值，只要它们支持其期望的接口即可。 我在第4章中提到过for / of循环可以循环几种数据结构。 这是多态性的另一种情况-此类循环希望数据结构公开特定的接口，而数组和字符串则会这样做。 我们还可以将此接口添加到您自己的对象中！ 但是在我们这样做之前，我们需要知道什么是符号。

## Symbols

多个接口可能将相同的属性名称用于不同的事物。 例如，我可以定义一个接口，在其中应该使用toString方法将对象转换为字符串。 一个对象不可能既符合该接口又符合toString的标准用法。 那将是一个坏主意，而且这个问题并不常见。 大多数JavaScript程序员根本不会考虑这一点。 但是无论如何，语言设计师的工作就是考虑这些东西，他们还是为我们提供了解决方案。 当我声称属性名称是字符串时，这并不完全正确。 它们通常是，但也可以是符号。 符号是使用符号功能创建的值。 与字符串不同，新创建的符号是唯一的-您不能两次创建相同的符号。

```javascript
let sym = Symbol("name");
console.log(sym == Symbol("name"));
// → false
Rabbit.prototype[sym] = 55;
console.log(blackRabbit[sym]);
// → 55
```

传递给Symbol的字符串在转换为字符串时会包括在内，例如，在控制台中显示它时，可以使识别符号更加容易。 但这没有其他意义-多个符号可能具有相同的名称。 既具有唯一性又可用作属性名称，使符号适合于定义可以与其他属性和平共处的接口，无论它们的名称是什么。

```javascript
const toStringSymbol = Symbol("toString");
Array.prototype[toStringSymbol] = function() {
return `${this.length} cm of blue yarn`;
};
console.log([1, 2].toString());
// → 1,2
console.log([1, 2][toStringSymbol]());
// → 2 cm of blue yarn
```

通过在属性名称周围使用方括号，可以在对象表达式和类中包括符号属性。 这导致对属性名称进行求值，就像方括号属性访问符号一样，它使我们可以引用包含符号的绑定。

```javascript
let stringObject = {
  [toStringSymbol]() { return "a jute rope"; }
};
console.log(stringObject[toStringSymbol]());
// → a jute rope
```

## The iterator interface

## Getters, setters, and statics

## Inheritance

## The instanceof operator

## Summary

能够将函数值传递给其他函数是JavaScript的一个非常有用的方面。 它使我们能够编写函数来对计算进行建模，并在其中带有“空白”。 调用这些函数的代码可以通过提供函数值来填补空白。
数组提供了许多有用的高阶方法。 您可以使用forEach遍历数组中的元素。 filter方法返回一个新数组，该数组仅包含通过谓词函数的元素。
通过将每个元素放入函数中来转换数组是通过map进行的。 您可以使用reduce将数组中的所有元素组合为一个值。 some方法测试是否有任何元素匹配给定的谓词函数。 findIndex查找与谓词匹配的第一个元素的位置。

## Exercises

### Flattening

将reduce方法与concat方法结合使用，可以将数组数组“拉平”为具有原始数组所有元素的单个数组。

```javascript
let arrays = [[1, 2, 3], [4, 5], [6]];

console.log(arrays.reduce((flat, current) => flat.concat(current), []));
// → [1, 2, 3, 4, 5, 6]
```

### Your own loop

编写一个高阶函数循环，该循环提供类似for循环的语句。 它需要一个值，一个测试函数，一个更新函数和一个主体函数。 每次迭代时，它首先在当前循环值上运行测试函数，并在返回false时停止。 然后，它调用body函数，并为其提供当前值。 最后，它调用update函数创建一个新值，并从头开始。 定义函数时，可以使用常规循环进行实际循环。

```javascript
function loop(start, test, update, body) {
  for (let value = start; test(value); value = update(value)) {
    body(value);
  }
}

loop(3, n => n > 0, n => n - 1, console.log);
// → 3
// → 2
// → 1
```

### Everything

类似于某些方法，数组也具有每种方法。 当给定的函数对数组中的每个元素返回true时，此返回true。 从某种意义上说，有些是||的版本。 操作数组的运算符，每个运算符都类似于&&运算符。 将每个函数都实现为以数组和谓词函数为参数的函数。 编写两个版本，一个使用循环，一个使用some方法。

```javascript
function every(array, predicate) {
  for (let element of array) {
    if (!predicate(element)) return false;
  }
  return true;
}

function every2(array, predicate) {
  return !array.some(element => !predicate(element));
}

console.log(every([1, 3, 5], n => n < 10));
// → true
console.log(every([2, 4, 16], n => n < 10));
// → false
console.log(every([], n => n < 10));
// → true
```

### Dominant writing direction

编写一个函数来计算文本字符串中的主要书写方向。 请记住，每个脚本对象都有一个Direction属性，可以是“ ltr”（从左到右），“ rtl”（从右到左）或“ ttb”（从上到下）。 主导方向是具有与之相关联的脚本的大多数字符的方向。 本章前面定义的characterScript和countBy函数在这里可能很有用。

```javascript
function dominantDirection(text) {
  let counted = countBy(text, char => {
    let script = characterScript(char.codePointAt(0));
    return script ? script.direction : "none";
  }).filter(({name}) => name != "none");

  if (counted.length == 0) return "ltr";

  return counted.reduce((a, b) => a.count > b.count ? a : b).name;
}

console.log(dominantDirection("Hello!"));
// → ltr
console.log(dominantDirection("Hey, مساء الخير"));
// → rtl
```

