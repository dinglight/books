# 项目：机器人

在“项目”一章中，我将在短时间内不再向您介绍新理论，而是我们将一起完成一个程序。 理论是学习编程的必要条件，但阅读和理解实际程序也同样重要。
本章中的项目是构建一个自动机，一个在虚拟世界中执行任务的小程序。 我们的自动机将是一个邮递机器人，负责接送包裹。

## 梅多菲尔德村


梅多菲尔德村不是很大。 它由11个地方组成，中间有14条道路。 可以用以下道路来描述：

```javascript
const roads = [
  "Alice's House-Bob's House", "Alice's House-Cabin",
  "Alice's House-Post Office", "Bob's House-Town Hall",
  "Daria's House-Ernie's House", "Daria's House-Town Hall",
  "Ernie's House-Grete's House", "Grete's House-Farm",
  "Grete's House-Shop", "Marketplace-Farm",
  "Marketplace-Post Office", "Marketplace-Shop",
  "Marketplace-Town Hall", "Shop-Town Hall"
];
```

村庄中的道路网形成了一个图形。 图形是点（村庄中的地点）和点之间的线（道路）的集合。 此图将是我们的机器人穿越的世界。
字符串数组不是很容易使用。 我们感兴趣的是可以从给定位置到达的目的地。 让我们将道路列表转换为一个数据结构，该数据结构可以告诉我们从那里可以到达的地方。

```javascript
function buildGraph(edges) {
  let graph = Object.create(null);
  function addEdge(from, to) {
    if (graph[from] == null) {
      graph[from] = [to];
    } else {
      graph[from].push(to);
    }
  }
  for (let [from, to] of edges.map(r => r.split("-"))) {
    addEdge(from, to);
    addEdge(to, from);
  }
  return graph;
}
const roadGraph = buildGraph(roads);
```

给定一组边线，buildGraph将创建一个地图对象，该地图对象为每个节点存储一组连接的节点。
它使用split方法从形式为“Start-End”的道路字符串到包含开始和结束作为单独字符串的两个元素的数组。

## 任务

我们的机器人将在村庄中移动。在各个地方都有包裹，每个包裹都寄到其他地方。机器人将包裹捡起来，并在到达目的地时将其交付。
自动机必须在每个点上确定下一步要去哪里。所有包裹交付完毕，它已经完成了任务。
为了能够模拟此过程，我们必须定义一个可以描述它的虚拟世界。这个模型告诉我们机器人在哪里，包裹在哪里。
当机器人决定移动到某个地方时，我们需要更新模型以反映新情况。
如果您考虑使用面向对象的编程方法，那么您的第一个冲动可能就是开始为世界上各种元素定义对象：机器人类，包裹类或地方类。然后，这些属性可以保留描述其当前状态的属性，例如某个位置的包裹堆，我们可以在更新世界时更改这些属性。
错了
至少通常是这样。听起来像对象的事实并不自动意味着它应该是程序中的对象。为应用程序中的每个概念反射性地编写类往往会给您留下一组互连的对象，每个对象都有自己的内部变化状态。这样的程序通常很难理解，因此很容易破解。取而代之的是，让我们将村庄的状态压缩为定义该状态的最小一组值。这里有机器人的当前位置以及未交付包裹的集合，每个包裹都有一个当前位置和一个目标地址。而已。而且，在进行调整时，我们要做的是不要在机器人移动时更改此状态，而是为移动后的情况计算新的状态。

```javascript
class VillageState {
  constructor(place, parcels) {
    this.place = place;
    this.parcels = parcels;
  }
  move(destination) {
    if (!roadGraph[this.place].includes(destination)) {
      return this;
    } else {
      let parcels = this.parcels.map(p => {
        if (p.place != this.place) return p;
        return {place: destination, address: p.address};
      }).filter(p => p.place != p.address);
      return new VillageState(destination, parcels);
    }
  }
}
```

移动方法是动作发生的地方。 它首先检查是否存在从当前位置到目的地的道路，如果没有，则返回旧状态，因为这不是有效的举动。
然后，它以目的地为机器人的新地点来创建一个新状态。 但是它还需要创建一组新的包裹-机器人所携带的包裹（位于机器人当前位置）需要一起移动到新位置。
并且需要递送到新地点的包裹-即，需要从未交付的包裹中将其删除。 map调用负责移动，而filter调用则负责传送。
包裹对象在移动时不会更改，但会重新创建。 移动方法为我们提供了一个新的乡村状态，但旧的状态却完好无损。

```javascript
let first = new VillageState(
  "Post Office",
  [{place: "Post Office", address: "Alice's House"}]
);
let next = first.move("Alice's House");
console.log(next.place);
// → Alice's House
console.log(next.parcels);
// → []
console.log(first.place);
// → Post Office
```

该移动导致包裹被递送，这反映在下一个状态中。 但是初始状态仍然描述了机器人在邮局且包裹未送达的情况。

## 持久数据

不变的数据结构称为不可变的或持久的。 它们的行为很像字符串和数字，因为它们是真实的人并保持原样，而不是在不同的时间包含不同的事物。
在JavaScript中，几乎所有内容都可以更改，因此使用假定为永久性的值需要一定的约束。 有一个名为Object.freeze的函数，该函数更改对象，以便忽略对其属性的写入。可以使用它来确保不更改对象。 冻结确实需要计算机做一些额外的工作，而忽略更新就象使他们做错事一样容易使人困惑。 因此，我通常更愿意告诉人们不要将给定的物体弄乱，并希望他们记住它。

```javascript
let object = Object.freeze({value: 5});
object.value = 10;
console.log(object.value);
// → 5
```

当语言显然希望我这样做时，为什么我会竭尽所能不更改对象？
因为它可以帮助我理解我的程序。这又是关于复杂性管理。当系统中的对象是固定的，稳定的东西时，我可以孤立地考虑对它们的操作-从给定的开始状态移到爱丽丝的房子总是会产生相同的新状态。当对象随时间变化时，这为这种推理增加了一个全新的复杂度。
对于像本章中构建的那样的小型系统，我们可以处理一点额外的复杂性。但是，我们可以构建哪种系统的最重要限制是我们可以理解多少。任何使您的代码更易于理解的东西都可以构建更雄心勃勃的系统。
不幸的是，尽管了解基于持久性数据结构的系统比较容易，但是设计一个系统（尤其是在您的编程语言无济于事的情况下）可能会有些困难。我们会在本书中寻找使用持久性数据结构的机会，但也会使用可变的结构。

## 模拟

送货机器人观察世界，并决定要朝哪个方向移动。 这样，我们可以说机器人是一个函数，它接受VillageState对象并返回附近地点的名称。
因为我们希望机器人能够记住事物，以便它们能够制定和执行计划，所以我们也将它们的内存传递给他们，并允许它们返回新的内存。 因此，机器人返回的东西是一个既包含其要移动的方向又包含一个存储值的对象，该存储值将在下次调用时返回给它。

```javascript
function runRobot(state, robot, memory) {
  for (let turn = 0;; turn++) {
    if (state.parcels.length == 0) {
      console.log(`Done in ${turn} turns`);
      break;
    }
    let action = robot(state, memory);
    state = state.move(action.direction);
    memory = action.memory;
    console.log(`Moved to ${action.direction}`);
  }
}
```

考虑一下机器人必须做什么才能“解决”给定状态。 它必须通过访问具有包裹的每个位置来拾取所有包裹，并通过访问包裹所到达的每个位置来运送它们，但必须在拾取包裹之后。
可能有效的最愚蠢的策略是什么？ 机器人每转一圈都可以朝随机方向行走。 这意味着它很有可能最终会碰到所有包裹，然后在某个时候到达应该交付的地方。
可能是这样的：

```javascript
function randomPick(array) {
  let choice = Math.floor(Math.random() * array.length);
  return array[choice];
}
function randomRobot(state) {
  return {direction: randomPick(roadGraph[state.place])};
}
```

请记住，Math.random（）返回一个介于0和1之间的数字，但始终小于1。 将这个数字乘以数组的长度，然后将Math.floor应用于该数字，即可得到该数组的随机索引。
由于该机器人不需要记住任何内容，因此它会忽略其第二个参数（请记住，可以使用额外的参数调用JavaScript函数而不会产生不良影响），并且忽略了其返回对象中的memory属性。
为了使这个先进的机器人正常工作，我们首先需要一种使用一些地块创建新状态的方法。 静态方法（在此处通过直接向构造函数添加属性来编写）是放置该功能的好地方。

```javascript
VillageState.random = function(parcelCount = 5) {
  let parcels = [];
  for (let i = 0; i < parcelCount; i++) {
    let address = randomPick(Object.keys(roadGraph));
    let place;
    do {
      place = randomPick(Object.keys(roadGraph));
    } while (place == address);
    parcels.push({place, address});
  }
  return new VillageState("Post Office", parcels);
};
```

我们不希望从发往同一地点的任何包裹发送。 因此，do循环在获得等于地址的位置时会继续选择新的位置。
让我们开始一个虚拟世界。

```javascript
runRobot(VillageState.random(), randomRobot);
// → Moved to Marketplace
// → Moved to Town Hall
// →…
// → Done in 63 turns
```

机器人运送包裹需要花费很多时间，因为它没有很好地计划。 我们会尽快解决。

## 邮车的路线
我们应该能够比随机机器人做得更好。 一个简单的改进就是从现实世界中的邮件传递方式中获取提示。 如果我们找到一条通过村庄所有地方的路线，则机器人可以运行该路线两次，这时可以保证完成。 这是一条这样的路线（从邮局开始）：

```javascript
const mailRoute = [
  "Alice's House", "Cabin", "Alice's House", "Bob's House",
  "Town Hall", "Daria's House", "Ernie's House",
  "Grete's House", "Shop", "Grete's House", "Farm",
  "Marketplace", "Post Office"
];
```

要实施跟踪机器人，我们需要利用机器人内存。 机器人将其剩余路线保留在内存中，并且每转一圈都会丢弃第一个元素。

```javascript
function routeRobot(state, memory) {
  if (memory.length == 0) {
    memory = mailRoute;
  }
  return {direction: memory[0], memory: memory.slice(1)};
}
```

这个机器人已经快很多了。 最多需要转26圈（是13步路线的两倍），但通常会少一些。

## 寻找路径

不过，我不会真正按照固定路线的智能行为盲目打电话。如果机器人将其行为调整为需要完成的实际工作，则其工作效率可能更高。
为此，它必须能够有意地移至给定的包裹或必须交付包裹的位置。这样做，即使目标不止一个，也需要某种寻路功能。
通过图形查找路线的问题是典型的搜索问题。我们可以判断给定的解决方案（路线）是否有效，但是我们无法以2 + 2的方式直接计算该解决方案。相反，我们必须继续创建潜在的解决方案，直到找到可行的解决方案为止。
通过图形的可能路线数是无限的。但是，当您搜索从A到B的路线时，我们只对始于A的那些路线感兴趣。我们也不在乎两次访问同一地点的路线-那些路线绝对不是最有效的路线。这样可以减少路线查找器必须考虑的路线数量。
实际上，我们对最短路线最感兴趣。因此，我们希望确保在看较长的路线之前先看短路线。一个好的方法是从起点“增长”路线，探索尚未到达的每个可到达地点，直到路线到达目标为止。这样，我们将仅探索可能有趣的路线，并找到到达目标的最短路线（如果有多个，则为最短路线之一）。
这是执行此操作的函数：

```javascript
function findRoute(graph, from, to) {
  let work = [{at: from, route: []}];
  for (let i = 0; i < work.length; i++) {
    let {at, route} = work[i];
    for (let place of graph[at]) {
      if (place == to) return route.concat(place);
      if (!work.some(w => w.at == place)) {
        work.push({at: place, route: route.concat(place)});
      }
    }
  }
}
```

必须以正确的顺序进行探索-首先要探索的地方。我们无法在到达某个位置后立即对其进行探索，因为这意味着从该位置到达的位置也将被立即探索，依此类推，即使可能还有其他更短的路径尚未被探索。
因此，该功能保留工作清单。这是接下来应该探索的一系列地方，以及到达我们那里的路线。它仅从起始位置和空路径开始。
然后，搜索将通过选择列表中的下一个项目并进行探索来进行，这意味着将查看从该位置出发的所有道路。如果目标之一是目标，则可以返回完成的路线。否则，如果我们以前没有看过这个地方，则会在列表中添加一个新项目。如果我们以前曾看过它，则因为我们首先看的是短途路线，所以我们发现到该地点的路线更长或与现有路线的长度一样长，因此我们无需进行探索。
您可以从视觉上想象这是一条已知路线的网络，该路线从起始位置爬出，在所有方向上均等增长（但从不纠结于自身）。
一旦第一个线程到达目标位置，该线程就会追溯到起点，为我们提供路线。
我们的代码无法处理工作列表上没有更多工作项的情况，因为我们知道我们的图表已连接，这意味着可以从所有其他位置访问每个位置。我们将始终能够找到两点之间的路线，并且搜索不会失败。

```javascript
function goalOrientedRobot({place, parcels}, route) {
  if (route.length == 0) {
    let parcel = parcels[0];
    if (parcel.place != place) {
      route = findRoute(roadGraph, place, parcel.place);
    } else {
      route = findRoute(roadGraph, place, parcel.address);
    }
  }
  return {direction: route[0], memory: route.slice(1)};
}
```

该机器人将其内存值用作前进方向的列表，就像跟随路线的机器人一样。 只要该列表为空，就必须弄清楚下一步该怎么做。 它会获取集合中的第一个未送达包裹，如果尚未取走该包裹，则向其绘制路线。 如果包裹已被拾起，则仍需要将其交付，因此，机器人会自动创建一条指向交付地址的路线。
该机器人通常完成大约16圈的5个包裹交付任务。 这比routeRobot略好，但绝对不是最佳选择。

## 练习

### 测量机器人

仅通过让机器人解决几种情况就很难客观地比较机器人。 也许一个机器人只是碰巧获得了更轻松的任务或它擅长的那种任务，而另一个却没有。
编写一个带有两个机器人（及其起始内存）的功能compareRobots。 它应该生成100个任务，并让每个机器人解决这些任务。 完成后，它应该输出每个机器人完成每个任务的平均步骤数。
为了公平起见，请确保将每个任务都分配给两个机器人，而不是每个机器人都生成不同的任务。

```javascript
function countSteps(state, robot, memory) {
  for (let steps = 0;; steps++) {
    if (state.parcels.length == 0) return steps;
    let action = robot(state, memory);
    state = state.move(action.direction);
    memory = action.memory;
  }
}

function compareRobots(robot1, memory1, robot2, memory2) {
  let total1 = 0, total2 = 0;
  for (let i = 0; i < 100; i++) {
    let state = VillageState.random();
    total1 += countSteps(state, robot1, memory1);
    total2 += countSteps(state, robot2, memory2);
  }
  console.log(`Robot 1 needed ${total1 / 100} steps per task`)
  console.log(`Robot 2 needed ${total2 / 100}`)
}

compareRobots(routeRobot, [], goalOrientedRobot, []);
```

### 机器人效率

您是否可以编写一个比targetOrientedRobot更快完成交付任务的机器人？ 如果您观察到该机器人的行为，那么它显然有什么愚蠢的事情？ 如何改善这些？
如果您解决了上一个练习，则可能要使用compareRobots函数来验证是否对机器人进行了改进。

```javascript
function lazyRobot({place, parcels}, route) {
  if (route.length == 0) {
    // Describe a route for every parcel
    let routes = parcels.map(parcel => {
      if (parcel.place != place) {
        return {route: findRoute(roadGraph, place, parcel.place),
                pickUp: true};
      } else {
        return {route: findRoute(roadGraph, place, parcel.address),
                pickUp: false};
      }
    });

    // This determines the precedence a route gets when choosing.
    // Route length counts negatively, routes that pick up a package
    // get a small bonus.
    function score({route, pickUp}) {
      return (pickUp ? 0.5 : 0) - route.length;
    }
    route = routes.reduce((a, b) => score(a) > score(b) ? a : b).route;
  }

  return {direction: route[0], memory: route.slice(1)};
}

runRobotAnimation(VillageState.random(), lazyRobot, []);
```

### 持久组

标准JavaScript环境中提供的大多数数据结构都不太适合持久使用。数组具有slice和concat方法，这使我们能够轻松创建新数组而不损坏旧数组。但是，例如Set，没有创建带有添加或删除项的新集合的方法。
编写一个新类PGroup，类似于第6章中的Group类，它存储一组值。像Group一样，它具有add，delete和has方法。
但是，它的add方法应该返回添加了给定成员的新PGroup实例，并使旧成员不变。同样，delete创建一个没有给定成员的新实例。
该类应适用于任何类型的值，而不仅仅是字符串。当与大量值一起使用时，它不一定高效。
构造函数不应成为类界面的一部分（尽管您肯定会在内部使用它）。而是有一个空实例PGroup.empty可以用作起始值。为什么只需要一个PGroup.empty值，而不是每次都有一个创建新的空映射的函数？

```javascript
class PGroup {
  constructor(members) {
    this.members = members;
  }

  add(value) {
    if (this.has(value)) return this;
    return new PGroup(this.members.concat([value]));
  }

  delete(value) {
    if (!this.has(value)) return this;
    return new PGroup(this.members.filter(m => m !== value));
  }

  has(value) {
    return this.members.includes(value);
  }
}

PGroup.empty = new PGroup([]);

let a = PGroup.empty.add("a");
let ab = a.add("b");
let b = ab.delete("a");

console.log(b.has("b"));
// → true
console.log(a.has("b"));
// → false
console.log(b.has("a"));
// → false
```

