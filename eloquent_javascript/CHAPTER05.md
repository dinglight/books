# Higher-order functions

大型程序是一个昂贵的程序，而不仅仅是因为要花费时间。 大小几乎总是涉及复杂性，而复杂性会使程序员感到困惑。 反过来，困惑的程序员会将错误（bugs）引入程序中。 大型程序为隐藏这些错误提供了很多空间，使它们很难被发现。 让我们简要地回到简介中的最后两个示例程序。 第一个是自包含的，有六行。

```javascript
let total = 0, count = 1;
while (count <= 10) {
  total += count;
  count += 1;
}
console.log(total);
```

第二个依赖于两个外部功能，长度为一行。

```javascript
console.log(sum(range(1, 10)));
```

哪一个更可能包含错误？ 如果我们计算sum和range定义的大小，则第二个程序也很大，甚至比第一个更大。 但是，我仍然认为这很可能是正确的。 因为解决方案用与要解决的问题相对应的词汇表表达，所以更可能是正确的。 对一系列数字求和与循环和计数器无关。 这是关于范围和总和。 该词汇表（功能sum和range）的定义仍将涉及循环，计数器和其他附带细节。 但是，由于它们所表达的概念要比整个程序简单，因此更容易正确。

## Abstraction

在编程的上下文中，这类词汇通常称为抽象。 抽象隐藏细节，使我们能够在更高（或更抽象）的层次上讨论问题。

打个比方，比较这两种豌豆汤的食谱。 第一个是这样的：

> 将每人1杯干豌豆放入容器中。 加水直到豌豆盖好。 将豌豆放在水中至少12小时。 将豌豆从水中取出，放入锅中。 每人加4杯水。 盖上锅，将豌豆煮沸两个小时。 每人取一半洋葱。 用刀切成碎片。 将其添加到豌豆。 每人取一茎芹菜。 用刀切成碎片。 将其添加到豌豆。 每人拿一根胡萝卜。 切成块。 用刀！ 将其添加到豌豆。 再煮10分钟。

这是第二个秘诀：

> 每人：1杯干豌豆，一半切碎的洋葱，芹菜杆和胡萝卜。 将豌豆浸泡12小时。 在4杯水中煮2小时（每人）。 切碎并加入蔬菜。 再煮10分钟。

第二个更短，更容易解释。 但是您确实需要理解一些与烹饪相关的词，例如浸泡，慢炖，剁碎以及我想是蔬菜。 进行编程时，我们不能完全依赖字典中需要等待的所有单词。 因此，我们可能会陷入第一个配方的模式—弄清楚计算机必须一步一步执行的精确步骤，而忽略了它们所表达的更高层次的概念。 在编程中，当您以太低的抽象级别工作时，可以注意到它是一项有用的技能。

## Abstracting repetition

到目前为止，我们已经看到普通函数是构建抽象的好方法。 但有时它们达不到要求。 程序通常执行给定次数的操作。 您可以为此编写一个for循环：

```javascript
for (let i = 0; i < 10; i++) {
  console.log(i);
}
```

我们可以将“ N次做某事”抽象为一个函数吗？ 嗯，编写一个调用N次console.log的函数很容易。

```javascript
function repeatLog(n) {
  for (let i = 0; i < n; i++) {
    console.log(i);
  }
}
```

但是，如果我们想做一些除记录数字之外的事情怎么办？ 由于“做某事”可以表示为一个函数，而函数只是值，因此我们可以将操作作为一个函数值传递。

```javascript
function repeat(n, action) {
  for (let i = 0; i < n; i++) {
    action(i);
  }
}
repeat(3, console.log);
// → 0
// → 1
// → 2
```

我们不必传递预定义的函数即可重复。 通常，当场创建函数值会更容易。

```javascript
let labels = [];
repeat(5, i => {
  labels.push(`Unit ${i + 1}`);
});
console.log(labels);
// → ["Unit 1", "Unit 2", "Unit 3", "Unit 4", "Unit 5"]
```

它的结构有点像for循环-首先描述循环的类型，然后提供主体。 但是，主体现在被写为一个函数值，该函数值包装在调用repeat的括号中。 这就是为什么必须使用大括号和大括号将其关闭。 在本例这样的情况下，主体是单个小表达式，您也可以省略花括号并将循环写在一行上。

## Higher-order functions

通过将其他函数作为参数或通过将其返回来对其他函数进行操作的函数称为高阶函数。 既然我们已经看到函数是规则值，那么关于这些函数存在的事实并没有特别引人注目。 该术语来自数学，在数学中，函数和其他值之间的区别更加重要。

高阶函数使我们可以抽象动作，而不仅仅是值。 它们有几种形式。 例如，我们可以具有创建新功能的功能。

```javascript
function greaterThan(n) {
  return m => m > n;
}
let greaterThan10 = greaterThan(10);
console.log(greaterThan10(11));
// → true
```

并且我们可以具有更改其他功能的功能。

```javascript
function noisy(f) {
  return (...args) => {
    console.log("calling with", args);
    let result = f(...args);
    console.log("called with", args, ", returned", result);
    return result;
  };
}
noisy(Math.min)(3, 2, 1);
// → calling with [3, 2, 1]
// → called with [3, 2, 1] , returned 1
```

我们甚至可以编写提供新型控制流的函数。

```javascript
function unless(test, then) {
  if (!test) then();
}
repeat(3, n => {
  unless(n % 2 == 1, () => {
    console.log(n, "is even");
  });
});
// → 0 is even
// → 2 is even
```

有一个内置的数组方法forEach，它提供诸如for / of循环之类的高阶函数。

```javascript
["A", "B"].forEach(l => console.log(l));
// → A
// → B
```

## Script data set

高阶功能的亮点之一是数据处理。 要处理数据，我们需要一些实际数据。 本章将使用有关脚本的数据集-书写系统，如拉丁文，西里尔文或阿拉伯文。 还记得第1章中的Unicode吗，该系统以书面语言为每个字符分配一个数字？ 这些字符大多数与特定脚本关联。 该标准包含140个不同的脚本-至今仍在使用81个脚本，其中59个具有历史意义。 尽管我只能流利地阅读拉丁字符，但我欣赏人们至少在其他80种书写系统中书写文本的事实，其中许多系统我什至都不认识。 例如，以下是泰米尔文手写示例：

示例数据集包含有关以Unicode定义的140个脚本的一些信息。 可在本章的编码沙箱（https://eloquentjavascript.net/code#5）中将其作为SCRIPTS绑定。 绑定包含一个对象数组，每个对象描述一个脚本。

```javascript
{
name: "Coptic",
ranges: [[994, 1008], [11392, 11508], [11513, 11520]],
direction: "ltr",
year: -200,
living: false,
link: "https://en.wikipedia.org/wiki/Coptic_alphabet"
}
```

这样的对象告诉我们脚本的名称，分配给它的Unicode范围，写入的方向，（大约）原始时间，是否仍在使用以及指向更多信息的链接。 方向可能是“ ltr”（从左到右），“ rtl”（从右到左）（阿拉伯和希伯来文字的书写方式）或“ ttb”（从上到下）（与蒙古文书写一样）。 ranges属性包含一个Unicode字符范围数组，每个字符范围都是一个包含下限和上限的两个元素的数组。 这些范围内的任何字符代码都分配给脚本。 下限是包含的（代码994是科普特字符），上限是非包含的（代码1008不是）。

## Filtering arrays

要在数据集中查找仍在使用的脚本，以下功能可能会有所帮助。 它过滤掉数组中未通过测试的元素。

```javascript
function filter(array, test) {
  let passed = [];
  for (let element of array) {
    if (test(element)) {
      passed.push(element);
    }
  }
  return passed;
}
console.log(filter(SCRIPTS, script => script.living));
// → [{name: "Adlam", …}, …]
```

该函数使用名为test的参数（函数值）来填补计算中的“空白”，即确定要收集哪些元素的过程。 请注意，筛选器功能如何（而不是从现有数组中删除元素）如何仅通过测试的元素来构建新数组。 此功能是纯函数。 它不会修改给定的数组。 像forEach一样，filter是一种标准的数组方法。 该示例定义该函数只是为了显示其内部功能。 从现在开始，我们将像这样使用它：

```javascript
console.log(SCRIPTS.filter(s => s.direction == "ttb"));
// → [{name: "Mongolian", …}, …]
```

## Transforming with map

假设我们有一个表示脚本的对象数组，这些对象是通过以某种方式过滤SCRIPTS数组而生成的。 但是我们需要一个名称数组，以便于检查。 map方法通过将函数应用于所有元素并根据返回的值构建新数组来变换数组。 新数组的长度与输入数组的长度相同，但是该函数的内容将被映射为新格式。

```javascript
function map(array, transform) {
  let mapped = [];
  for (let element of array) {
    mapped.push(transform(element));
  }
  return mapped;
}
let rtlScripts = SCRIPTS.filter(s => s.direction == "rtl");
console.log(map(rtlScripts, s => s.name));
// → ["Adlam", "Arabic", "Imperial Aramaic", …]let objectA = {a: 1, b: 2};
Object.assign(objectA, {b: 3, c: 4});
console.log(objectA);
// → {a: 1, b: 3, c: 4}
```

像forEach和filter一样，map是一种标准的数组方法。

## Summarizing with reduce

与数组有关的另一件事是从数组中计算一个值。 我们重复出现的例子，将一个数字集合加起来，就是一个例子。 另一个示例是查找字符数最多的脚本。 表示此模式的高阶操作称为reduce（有时也称为fold）。 它通过重复从数组中获取单个元素并将其与当前值组合来构建值。 在对数字求和时，您将从数字零开始，然后将每个元素加到总和中。 除数组外，要减少的参数是组合函数和起始值。 此函数比filter和map少一些直接，因此请仔细看一下此函数：

```javascript
function reduce(array, combine, start) {
  let current = start;
  for (let element of array) {
    current = combine(current, element);
  }
  return current;
}
console.log(reduce([1, 2, 3, 4], (a, b) => a + b, 0));
// → 10
```

标准数组方法reduce，当然与该函数相对应，具有更多的便利。 如果数组中至少包含一个元素，则可以不使用start参数。 该方法将数组的第一个元素作为其起始值，并从第二个元素开始减少。

```javascript
console.log([1, 2, 3, 4].reduce((a, b) => a + b));
// → 10
```

要使用reduce（两次）来查找字符数最多的脚本，我们可以编写如下内容：

```javascript
function characterCount(script) {
  return script.ranges.reduce((count, [from, to]) => {
    return count + (to - from);
  }, 0);
}
console.log(SCRIPTS.reduce((a, b) => {
  return characterCount(a) < characterCount(b) ? b : a;
}));
// → {name: "Han", …}
```

characterCount函数通过求和它们的大小来减小分配给脚本的范围。 请注意在reducer函数的参数列表中使用解构。 第二个reduce调用然后通过重复比较两个脚本并返回较大的脚本来使用它来找到最大的脚本。

在Unicode标准中，Han脚本分配了超过89,000个字符，是迄今为止该数据集中最大的书写系统。 汉字（有时）是用于中文，日文和韩文文本的脚本。 这些语言共享许多字符，尽管它们倾向于以不同的方式编写它们。 （基于美国的）Unicode联盟决定将它们视为保存字符代码的单个书写系统。 这被称为汉统一，仍然使一些人非常生气。

## Composability

考虑一下我们如何编写没有高阶函数的前面的示例（查找最大的脚本）。 代码并没有那么糟糕。

```javascript
let biggest = null;
for (let script of SCRIPTS) {
  if (biggest == null ||
      characterCount(biggest) < characterCount(script)) {
    biggest = script;
  }
}
console.log(biggest);
// → {name: "Han", …}
```

还有更多的绑定，程序长了四行。 但是它仍然非常可读。 当需要编写操作时，高阶函数开始发光。 举例来说，让我们编写代码来查找数据集中活着和死亡脚本的平均起源年。

```javascript
function average(array) {
  return array.reduce((a, b) => a + b) / array.length;
}
console.log(Math.round(average(
SCRIPTS.filter(s => s.living).map(s => s.year))));
// → 1188
console.log(Math.round(average(
SCRIPTS.filter(s => !s.living).map(s => s.year))));
// → 188
```

因此，Unicode中的无效脚本平均比活动脚本更旧。 这不是一个非常有意义或令人惊讶的统计数据。 但我希望您会同意，用于计算它的代码并不难读。 您可以将其视为一条管道：我们从所有脚本开始，过滤掉活着的（或死掉的）脚本，从这些脚本中提取年限，取平均值，然后四舍五入。 您当然也可以将此计算写为一个大循环。

```javascript
let total = 0, count = 0;
for (let script of SCRIPTS) {
  if (script.living) {
    total += script.year;
    count += 1;
  }
}
console.log(Math.round(total / count));
// → 1188
```

但是，很难看到正在计算什么以及如何计算。 而且由于中间结果未表示为连贯的值，因此将平均值等内容提取到单独的函数中需要进行大量工作。 在计算机实际运行方面，这两种方法也有很大不同。 第一个将在运行filter和map时建立新的数组，而第二个仅计算一些数字，从而减少工作量。 通常，您可以负担得起可读的方法，但是如果您要处理大量数组并且进行多次，那么抽象度较低的样式可能值得增加速度。

## Strings and character codes

数据集的一种用途是弄清楚一段文本正在使用什么脚本。 让我们来看一个执行此操作的程序。 请记住，每个脚本都有一个与之关联的字符代码范围数组。 因此，给定字符码，我们可以使用类似这样的函数来找到相应的脚本（如果有）：

```javascript
function characterScript(code) {
  for (let script of SCRIPTS) {
    if (script.ranges.some(([from, to]) => {
      return code >= from && code < to;
    })) {
      return script;
    }
  }
  return null;
}
console.log(characterScript(121));
// → {name: "Latin", …}
```

some方法是另一个高阶函数。 它带有一个测试函数，并告诉您该函数是否对数组中的任何元素返回true。但是，如何获取字符串中的字符代码？

在第1章中，我提到过JavaScript字符串被编码为16位数字的序列。这些称为代码单元。最初应该将Unicode字符代码放入这样的单位内（这会使您略多于65,000个字符）。当事实证明这还不够时，许多人对每个角色使用更多内存的需求感到沮丧。为了解决这些问题，发明了JavaScript字符串使用的UTF-16格式。它使用单个16位代码单元描述最常见的字符，但对其他两个则使用两个这样的单元对。今天，UTF-16通常被认为是一个坏主意。似乎几乎是故意设计来引起错误。假装代码单元和字符是同一件事的程序很容易编写。而且，如果您的语言不使用两个单位的字符，那么看起来就可以正常工作。但是，一旦有人尝试使用带有一些不太常见的汉字的程序，它就会中断。幸运的是，随着表情符号的出现，每个人都开始使用两单元字符，并且处理此类问题的负担也更加公平。不幸的是，对JavaScript字符串的明显操作（例如通过length属性获取其长度并使用方括号访问其内容）仅处理代码单元。

```javascript
// Two emoji characters, horse and shoe
let horseShoe = " ?? ";
console.log(horseShoe.length);
// → 4
console.log(horseShoe[0]);
// → (Invalid half-character)
console.log(horseShoe.charCodeAt(0));
// → 55357 (Code of the half-character)
console.log(horseShoe.codePointAt(0));
// → 128052 (Actual code for horse emoji)
```

JavaScript的charCodeAt方法为您提供一个代码单位，而不是完整的字符代码。 稍后添加的codePointAt方法确实提供了完整的Unicode字符。 因此，我们可以使用它来获取字符串中的字符。 但是传递给codePointAt的参数仍然是代码单元序列的索引。 因此，要遍历字符串中的所有字符，我们仍然需要处理一个字符占用一个或两个代码单元的问题。 在上一章中，我提到了for / of循环也可以在字符串上使用。 像codePointAt一样，这种循环是在人们敏锐地意识到UTF-16问题的时候引入的。 当您使用它在字符串上循环时，它将为您提供真实的字符，而不是代码单位。

```javascript
let roseDragon = " ?? ";
for (let char of roseDragon) {
  console.log(char);
}
// → ?
// → ?
```

如果您有一个字符（将是一两个或两个代码单元的字符串），则可以使用codePointAt（0）来获取其代码。

## Recognizing text

我们有一个characterScript函数和一种正确循环字符的方法。 下一步是计算属于每个脚本的字符。 以下计数抽象在此处将非常有用：

```javascript
function countBy(items, groupName) {
  let counts = [];
  for (let item of items) {
    let name = groupName(item);
    let known = counts.findIndex(c => c.name == name);
    if (known == -1) {
      counts.push({name, count: 1});
    } else {
      counts[known].count++;
    }
  }
  return counts;
}
console.log(countBy([1, 2, 3, 4, 5], n => n > 2));
// → [{name: false, count: 2}, {name: true, count: 3}]
```

countBy函数需要一个集合（可以使用for / of进行循环的任何对象）和一个为给定元素计算组名的函数。 它返回一个对象数组，每个对象都命名一个组并告诉您在该组中找到的元素数。 它使用另一个数组方法findIndex。 此方法有点类似于indexOf，但是它不查找特定值，而是查找给定函数为其返回true的第一个值。 像indexOf一样，当找不到这样的元素时，它返回-1。 使用countBy，我们可以编写函数来告诉我们在一段文本中使用了哪些脚本。

```javascript
function textScripts(text) {
  let scripts = countBy(text, char => {
    let script = characterScript(char.codePointAt(0));
    return script ? script.name : "none";
  }).filter(({name}) => name != "none");

  let total = scripts.reduce((n, {count}) => n + count, 0);
  if (total == 0) return "No scripts found";
  return scripts.map(({name, count}) => {
    return `${Math.round(count * 100 / total)}% ${name}`;
  }).join(", ");
}
console.log(textScripts(' 英国的狗说 "woof", 俄罗斯的狗说 "тяв"'));
// → 61% Han, 22% Latin, 17% Cyrillic
```

该函数首先按名称对字符进行计数，使用characterScript为它们分配名称，然后对不属于任何脚本的字符退回到字符串“ none”。 筛选器调用会从结果数组中删除“无”的条目，因为我们对这些字符不感兴趣。 为了能够计算百分比，我们首先需要属于脚本的字符总数，可以使用reduce进行计算。 如果找不到这样的字符，该函数将返回一个特定的字符串。 否则，它将计数条目转换为带有map的可读字符串，然后将它们与join组合。

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

