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

给for / of循环的对象应该是可迭代的。 这意味着它具有一个以Symbol.iterator符号命名的方法（该语言定义的符号值，存储为Symbol函数的属性）。 调用该方法时，该方法应返回一个提供第二个接口Iterator的对象。 这是实际的迭代过程。 它具有next方法，该方法返回下一个结果。 该结果应该是一个对象，该对象的value属性提供下一个值（如果有），并具有done属性（当没有更多结果时应为true，否则为false）。
请注意，next，value和done属性名称是纯字符串，而不是符号。 只有Symbol.iterator（可能会添加到许多不同的对象中）才是实际的符号。 我们可以自己直接使用此接口。

```javascript
let okIterator = "OK"[Symbol.iterator]();
console.log(okIterator.next());
// → {value: "O", done: false}
console.log(okIterator.next());
// → {value: "K", done: false}
console.log(okIterator.next());
// → {value: undefined, done: true}
```

让我们实现一个可迭代的数据结构。 我们将构建一个矩阵类，作为二维数组。

```javascript
class Matrix {
  constructor(width, height, element = (x, y) => undefined) {
    this.width = width;
    this.height = height;
    this.content = [];
    for (let y = 0; y < height; y++) {
      for (let x = 0; x < width; x++) {
        this.content[y * width + x] = element(x, y);
      }
    }
  }
  get(x, y) {
    return this.content[y * this.width + x];
  }
  set(x, y, value) {
    this.content[y * this.width + x] = value;
  }
}
```

该类将其内容存储在width×height元素的单个数组中。 元素逐行存储，因此，例如，第五行中的第三个元素（使用基于零的索引）存储在位置4×宽度+ 2。
构造函数具有宽度，高度和可选的内容函数，这些函数将用于填充初始值。 有get和set方法可检索和更新矩阵中的元素。
在矩阵上循环时，通常您会对元素的位置以及元素本身感兴趣，因此，我们将让迭代器生成具有x，y和value属性的对象。

```javascript
class MatrixIterator {
  constructor(matrix) {
    this.x = 0;
    this.y = 0;
    this.matrix = matrix;
  }
  next() {
    if (this.y == this.matrix.height) return {done: true};
    let value = {x: this.x,
      y: this.y,
      value: this.matrix.get(this.x, this.y)};
    this.x++;
    if (this.x == this.matrix.width) {
      this.x = 0;
      this.y++;
    }
    return {value, done: false};
  }
}
```

该类在其x和y属性中跟踪对矩阵进行迭代的进度。 下一个方法开始于检查是否已达到矩阵的底部。 如果没有，它将首先创建保存当前值的对象，然后更新其位置，并在必要时移至下一行。
让我们将Matrix类设置为可迭代的。 在整本书中，我偶尔会使用事后原型操作将方法添加到类中，以使各个代码段保持较小且独立。 在不需要将代码分成小块的常规程序中，您可以直接在类中声明这些方法。

```javascript
Matrix.prototype[Symbol.iterator] = function() {
  return new MatrixIterator(this);
};
```

现在，我们可以循环使用for / of矩阵。

```javascript
let matrix = new Matrix(2, 2, (x, y) => `value ${x},${y}`);
for (let {x, y, value} of matrix) {
  console.log(x, y, value);
}
// → 0 0 value 0,0
// → 1 0 value 1,0
// → 0 1 value 0,1
// → 1 1 value 1,1
```

## Getters, setters, and statics

接口通常主要由方法组成，但是也可以包括保存非函数值的属性。 例如，Map对象具有size属性，该属性告诉您其中存储了多少个键。 这样的对象甚至不必直接在实例中计算和存储这样的属性。 甚至直接访问的属性也可能隐藏方法调用。 此类方法称为getter，它们是通过在对象表达式或类声明中的方法名称之前编写get来定义的

```javascript
let varyingSize = {
  get size() {
    return Math.floor(Math.random() * 100);
  }
};
console.log(varyingSize.size);
// → 73
console.log(varyingSize.size);
// → 49
```

每当有人从该对象的size属性中读取内容时，就会调用关联的方法。 使用setter将属性写入属性时，您可以执行类似的操作。

```javascript
class Temperature {
  constructor(celsius) {
    this.celsius = celsius;
  }
  get fahrenheit() {
    return this.celsius * 1.8 + 32;
  }
  set fahrenheit(value) {
    this.celsius = (value - 32) / 1.8;
  }
  static fromFahrenheit(value) {
    return new Temperature((value - 32) / 1.8);
  }
}
let temp = new Temperature(22);
console.log(temp.fahrenheit);
// → 71.6
temp.fahrenheit = 86;
console.log(temp.celsius);
// → 30
```

Temperature类允许您以摄氏度或华氏度读取和写入温度，但是在内部它仅存储摄氏温度，并在华氏吸气剂和设定器中自动与摄氏温度进行转换。
有时您想将某些属性直接附加到构造函数，而不是原型。 此类方法将无权访问类实例，但可以用于提供创建实例的其他方式。
在类声明中，名称之前写有静态的方法存储在构造函数中。 因此，温度类允许您编写Temperature.fromFahrenheit（100）以使用华氏度创建温度。

## Inheritance

已知某些矩阵是对称的。 如果在对称矩阵的左上到右下对角线镜像，则它保持不变。 换句话说，存储在x，y处的值始终与y，x处的值相同。
想象一下，我们需要一种像Matrix这样的数据结构，但是却需要一个事实，即矩阵是并且保持对称。 我们可以从头开始编写它，但这将涉及到重复一些与我们已经编写的代码非常相似的代码。
JavaScript的原型系统可以创建一个新类，就像旧类一样，但是可以为其某些属性添加新的定义。 新类的原型源自旧的原型，但是为set方法添加了新的定义。
用面向对象的编程术语，这称为继承。 新类继承了旧类的属性和行为。

```javascript
class SymmetricMatrix extends Matrix {
  constructor(size, element = (x, y) => undefined) {
    super(size, size, (x, y) => {
      if (x < y) return element(y, x);
      else return element(x, y);
    });
  }
  set(x, y, value) {
    super.set(x, y, value);
    if (x != y) {
      super.set(y, x, value);
    }
  }
}
let matrix = new SymmetricMatrix(5, (x, y) => `${x},${y}`);
console.log(matrix.get(2, 3));
// → 3,2
```

使用扩展一词表示该类不应直接基于默认的Object原型，而应基于其他某个类。这称为超类。派生类是子类。
要初始化SymmetricMatrix实例，构造函数将通过super关键字调用其超类的构造函数。这是必需的，因为如果此新对象的行为（大致）类似于Matrix，则它将需要矩阵具有的实例属性。为确保矩阵对称，构造函数包装content方法以将坐标交换为对角线以下的值。
set方法再次使用super，但是这次不是调用构造函数，而是从超类的方法集中调用特定的方法。我们正在重新定义集合，但确实要使用原始行为。由于this.set引用了新的set方法，因此调用将无效。在类方法内部，super提供了一种调用方法的方法，这些方法是在超类中定义的。
继承使我们能够以相对较少的工作来构建与现有数据类型略有不同的数据类型。除封装和多态性外，它是面向对象传统的基本组成部分。但是，尽管后两者现在通常被认为是绝妙的主意，但是继承却更具争议性。
封装和多态性可用于将代码段彼此分离，从而减少整个程序的混乱，而继承从根本上将类联系在一起，从而产生更多的纠结。从类继承时，与仅使用类相比，通常必须了解更多有关其工作方式的信息。继承可能是一个有用的工具，我在自己的程序中不时使用它，但它不应该是您所追求的第一个工具，并且您可能不应该积极地寻求构建类层次结构（家族树）的机会。

## The instanceof operator

有时了解对象是否源自特定类很有用。 为此，JavaScript提供了一个名为instanceof的二进制运算符

```javascript
console.log(new SymmetricMatrix(2) instanceof SymmetricMatrix);
// → true
console.log(new SymmetricMatrix(2) instanceof Matrix);
// → true
console.log(new Matrix(2, 2) instanceof SymmetricMatrix);
// → false
console.log([1] instanceof Array);
// → true
```

该运算符将查看继承的类型，因此SymmetricMatrix是Matrix的实例。 该运算符还可以应用于Array之类的标准构造函数。 几乎每个对象都是对象的一个实例

## Summary

因此，对象所做的不仅仅是保留自己的属性。他们有原型，这是其他对象。只要它们的原型具有该属性，它们就好像它们具有的属性一样。简单对象有对象。
原型作为他们的原型。
构造函数是其名称通常以大写字母开头的函数，可以与new运算符一起使用以创建新对象。新对象的原型将是在构造函数的prototype属性中找到的对象。您可以通过将给定类型的所有值共享的属性放入其原型中来充分利用这一点。有一个类标记，提供了一种清晰的方法来定义构造函数及其原型。
您可以定义getter和setter以在每次访问对象的属性时秘密调用方法。静态方法是存储在类的构造函数中的方法，而不是其原型。
给定一个对象和一个构造函数，instanceof运算符可以告诉您该对象是否是该构造函数的实例。
与对象有关的一件有用的事情是为它们指定一个接口，并告诉每个人仅应通过该接口与您的对象对话。构成对象的其余细节现在已封装，隐藏在接口后面。
一个以上的类型可以实现相同的接口。使用接口编写的代码会自动知道如何使用提供接口的许多不同对象。这称为多态。
当实现仅在某些细节上有所不同的多个类时，将新类编写为现有类的子类可能会有所帮助，从而继承其部分行为。

## Exercises

### A vector type

编写代表二维空间中向量的Vec类。 它带有x和y参数（数字），应将其保存到相同名称的属性中。
给Vec原型两个方法plus和minus，它们将另一个向量作为参数，并返回一个新向量，该向量具有两个向量（此和参数）的x和y值之和或差。
在原型中添加一个getter属性长度，该长度可以计算向量的长度-即，点（x，y）与原点（0，0）的距离。

```javascript
class Vec {
  constructor(x, y) {
    this.x = x;
    this.y = y;
  }

  plus(other) {
    return new Vec(this.x + other.x, this.y + other.y);
  }

  minus(other) {
    return new Vec(this.x - other.x, this.y - other.y);
  }

  get length() {
    return Math.sqrt(this.x * this.x + this.y * this.y);
  }
}

console.log(new Vec(1, 2).plus(new Vec(2, 3)));
// → Vec{x: 3, y: 5}
console.log(new Vec(1, 2).minus(new Vec(2, 3)));
// → Vec{x: -1, y: -1}
console.log(new Vec(3, 4).length);
// → 5
```

### Group

标准JavaScript环境提供了另一个名为Set的数据结构。 就像Map的实例一样，集合包含值的集合。 与Map不同，它不会将其他值与这些值相关联，而只是跟踪哪些值是集合的一部分。 一个值只能是一个集合的一部分，再次添加不会产生任何效果。
编写一个名为Group的类（因为已经使用Set）。 与Set一样，它具有add，delete和has方法。 它的构造函数创建一个空组，add向该组添加一个值（但前提是它还不是成员），delete从该组中删除其参数（如果它是一个成员），has返回一个布尔值，指示它的参数是否为该组的成员。
使用===运算符或诸如indexOf之类的等效项来确定两个值是否相同。
给该类一个静态from方法，该方法使用一个可迭代的对象作为参数，并创建一个包含通过迭代产生的所有值的组。

```javascript
class Group {
  constructor() {
    this.members = [];
  }

  add(value) {
    if (!this.has(value)) {
      this.members.push(value);
    }
  }

  delete(value) {
    this.members = this.members.filter(v => v !== value);
  }

  has(value) {
    return this.members.includes(value);
  }

  static from(collection) {
    let group = new Group;
    for (let value of collection) {
      group.add(value);
    }
    return group;
  }
}

let group = Group.from([10, 20]);
console.log(group.has(10));
// → true
console.log(group.has(30));
// → false
group.add(10);
group.delete(10);
console.log(group.has(10));
```

### Iterable groups

使上一个练习中的Group类可迭代。 如果您不清楚接口的确切形式，请参阅本章前面有关迭代器接口的部分。
如果您使用数组表示组的成员，则不要仅返回通过调用数组上的Symbol.iterator方法创建的迭代器。 那会行得通，但它违背了此练习的目的。
如果在迭代过程中修改组时迭代器的行为异常，则可以。

```javascript
class Group {
  constructor() {
    this.members = [];
  }

  add(value) {
    if (!this.has(value)) {
      this.members.push(value);
    }
  }

  delete(value) {
    this.members = this.members.filter(v => v !== value);
  }

  has(value) {
    return this.members.includes(value);
  }

  static from(collection) {
    let group = new Group;
    for (let value of collection) {
      group.add(value);
    }
    return group;
  }

  [Symbol.iterator]() {
    return new GroupIterator(this);
  }
}

class GroupIterator {
  constructor(group) {
    this.group = group;
    this.position = 0;
  }

  next() {
    if (this.position >= this.group.members.length) {
      return {done: true};
    } else {
      let result = {value: this.group.members[this.position],
                    done: false};
      this.position++;
      return result;
    }
  }
}

for (let value of Group.from(["a", "b", "c"])) {
  console.log(value);
}
// → a
// → b
// → c
```

### Borrowing a method

在本章的前面，我曾提到，当您想忽略原型的属性时，可以将对象的hasOwnProperty用作in运算符的更可靠替代。 但是，如果您的地图需要包含单词“ hasOwnProperty”怎么办？ 您将无法再调用该方法，因为对象自身的属性会隐藏该方法的值。
您能想到一种通过该名称具有自己的属性的对象调用hasOwnProperty的方法吗？

```javascript
let map = {one: true, two: true, hasOwnProperty: true};

console.log(Object.prototype.hasOwnProperty.call(map, "one"));
// → true
```

