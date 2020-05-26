# 处理事件

某些程序可通过直接用户输入来工作，例如鼠标和键盘操作。 这类输入无法作为组织良好的数据结构使用，它是实时的，逐段的，程序有望在发生时对其进行响应。

## 事件处理程序

想象一下一个界面，找出键盘是否被按下的唯一方法就是读取该键的当前状态。为了能够对按键做出反应，您必须不断读取按键的状态，以便在再次释放按键之前就可以捕捉到它。执行其他耗时的计算会很危险，因为您可能会错过按键操作。
一些原始机器确实会像这样处理输入。硬件或操作系统需要注意的是将按键按下并排入队列。然后，程序可以定期检查队列中是否有新事件，并对在此发现的事件做出反应。
当然，它必须记住要经常查看队列，因为在按下按键和程序通知事件之间的任何时间都会使软件感到无响应。这种方法称为轮询。大多数程序员都喜欢避免这种情况。更好的机制是让系统在事件发生时主动通知我们的代码。浏览器通过允许我们将函数注册为特定事件的处理程序来实现此目的。

```html
<p>Click this document to activate the handler.</p>
<script>
  window.addEventListener("click", () => {
    console.log("You knocked?");
  });
</script>
```

窗口绑定是指浏览器提供的内置对象。 它表示包含文档的浏览器窗口。 每当其第一个参数描述的事件发生时，调用其addEventListener方法都会注册要调用的第二个参数。

## 事件和DOM节点

每个浏览器事件处理程序都在上下文中注册。 在前面的示例中，我们在窗口对象上调用addEventListener来注册整个窗口的处理程序。 也可以在DOM元素和某些其他类型的对象上找到这种方法。 仅当事件发生在其注册对象的上下文中时，才调用事件侦听器。

```html
<button>Click me</button>
<p>No handler here.</p>
<script>
  let button = document.querySelector("button");
  button.addEventListener("click", () => {
    console.log("Button clicked.");
  });
</script>
```

该示例将处理程序附加到按钮节点。 单击按钮将导致该处理程序运行，但是单击该文档的其余部分则不会。
为节点提供onclick属性具有类似的效果。 这适用于大多数类型的事件-您可以通过名称为事件名称的属性附加处理程序，该属性位于事件名称的前面。
但是一个节点只能有一个onclick属性，因此您只能以这种方式在每个节点上注册一个处理程序。 addEventListener方法允许您添加任意数量的处理程序，因此即使元素上已经存在另一个处理程序，也可以安全地添加处理程序。
用类似于addEventListener的参数调用的removeEventListener方法将删除处理程序。

```html
<button>Act-once button</button>
<script>
  let button = document.querySelector("button");
  function once() {
    console.log("Done.");
    button.removeEventListener("click", once);
  }
  button.addEventListener("click", once);
</script>
```

给removeEventListener提供的功能必须与给addEventListener提供的功能值相同。 因此，要取消注册处理程序，您需要为函数命名（示例中为一次），以便能够将相同的函数值传递给这两种方法。

## 事件对象

尽管到目前为止我们都忽略了它，但是事件处理函数被传递了一个参数：事件对象。 该对象保存有关事件的其他信息。 例如，如果我们想知道按下了哪个鼠标按钮，可以查看事件对象的button属性。

```html
<button>Click me any way you want</button>
<script>
  let button = document.querySelector("button");
  button.addEventListener("mousedown", event => {
    if (event.button == 0) {
      console.log("Left button");
    } else if (event.button == 1) {
      console.log("Middle button");
    } else if (event.button == 2) {
      console.log("Right button");
    }
  });
</script>
```

事件对象中存储的信息因事件类型而异。 我们将在本章后面讨论不同的类型。 对象的type属性始终包含标识事件的字符串（例如“ click”或“ mousedown”）。

## 传播

对于大多数事件类型，在具有子节点的节点上注册的处理程序也将接收在子节点中发生的事件。如果单击了段落内的按钮，则该段落上的事件处理程序还将看到click事件。
但是，如果段落和按钮都具有处理程序，则更具体的处理程序（位于按钮上的处理程序）将首先进入。据说该事件是从事件发生的节点传播到该节点的父节点，再到文档的根部向外传播。最终，在特定节点上注册的所有处理程序轮到他们使用后，在整个窗口上注册的处理程序都有机会响应该事件。
事件处理程序可以随时在事件对象上调用stopPropagation方法，以防止处理程序进一步接收该事件。例如，当您在另一个可点击的元素内有一个按钮并且不想单击按钮以激活外部元素的点击行为时，此功能很有用。
下面的示例在按钮及其周围的段落上同时注册“ mousedown”处理程序。当用鼠标右键单击时，该按钮的处理程序将调用stopPropagation，这将阻止该段落上的处理程序运行。当用另一个鼠标按钮单击该按钮时，两个处理程序都将运行。

```html
<p>A paragraph with a <button>button</button>.</p>
<script>
  let para = document.querySelector("p");
  let button = document.querySelector("button");
  para.addEventListener("mousedown", () => {
    console.log("Handler for paragraph.");
  });
  button.addEventListener("mousedown", event => {
    console.log("Handler for button.");
    if (event.button == 2) event.stopPropagation();
  });
</script>
```

大多数事件对象都有一个target属性，该属性引用了它们起源的节点。 您可以使用此属性来确保您不会意外处理从不想处理的节点向上传播的内容。
也可以使用target属性为特定类型的事件投射宽广的网络。 例如，如果您的节点包含一长列按钮，则在外部节点上注册一个单击处理程序，并使其使用target属性来确定是否单击了按钮，而不是单独注册一个按钮，可能会更方便。 所有按钮上的处理程序。

```html
<button>A</button>
<button>B</button>
<button>C</button>
<script>
  document.body.addEventListener("click", event => {
    if (event.target.nodeName == "BUTTON") {
      console.log("Clicked", event.target.textContent);
    }
  });
</script>
```



## 默认动作

许多事件都有与之关联的默认操作。 如果单击链接，则将转到该链接的目标。 如果按下向下箭头，浏览器将向下滚动页面。 如果右键单击，将获得一个上下文菜单。 等等。
对于大多数类型的事件，将在发生默认行为之前调用JavaScript事件处理程序。 如果处理程序不希望发生这种正常行为（通常是因为它已经处理了事件），则可以在事件对象上调用preventDefault方法。
这可以用来实现自己的键盘快捷键或上下文菜单。 它也可以用来讨厌地干扰用户期望的行为。 例如，这是一个无法跟踪的链接：

```html
<a href="https://developer.mozilla.org/">MDN</a>
<script>
  let link = document.querySelector("a");
  link.addEventListener("click", event => {
    console.log("Nope.");
    event.preventDefault();
  });
</script>
```

除非您有充分的理由，否则请不要这样做。 当预期行为被破坏时，这对于使用您的页面的人来说是不愉快的。 视浏览器而定，某些事件根本无法被拦截。 例如，在Chrome上，JavaScript无法处理用于关闭当前标签页的键盘快捷键（control-W或Command-W）。

## 按键事件

当按下键盘上的某个键时，您的浏览器将触发“ keydown”事件。 当它松开时，您会收到一个“ keyup”事件。

```html
<p>This page turns violet when you hold the V key.</p>
<script>
  window.addEventListener("keydown", event => {
    if (event.key == "v") {
      document.body.style.background = "violet";
    }
  });
  window.addEventListener("keyup", event => {
    if (event.key == "v") {
      document.body.style.background = "";
    }
  });
</script>
```

尽管其名称如此，“ keydown”不仅会在物理按下按键时触发。 按住某个键时，每次重复该键都会再次触发该事件。 有时您必须对此小心。 例如，如果您在按下某个键时将一个按钮添加到DOM中，而在释放该键时再次将其删除，则当您按住该键的时间更长时，可能会意外地添加数百个按钮。

该示例查看了事件对象的key属性，以查看事件与哪个键有关。 此属性包含一个字符串，对于大多数键，该字符串与按下该键将要键入的内容相对应。 对于诸如回车之类的特殊键，它包含一个名称为键的字符串（在本例中为“ Enter”）。 如果在按住某个键的同时按住Shift键，则这也可能会影响该键的名称-“ v”变为“ V”，而“ 1”可能变为“！”，这是按shift-1在键盘上产生的。

修改键，例如shift，control，alt和meta（在Mac上为Command），会像普通键一样生成键事件。 但是，在查找键组合时，您还可以通过查看键盘和鼠标事件的shiftKey，ctrlKey，altKey和metaKey属性来确定是否按住了这些键。

```html
<p>Press Control-Space to continue.</p>
<script>
  window.addEventListener("keydown", event => {
    if (event.key == " " && event.ctrlKey) {
      console.log("Continuing!");
    }
  });
</script>
```

按键事件起源的DOM节点取决于按下按键时具有焦点的元素。除非您为它们提供tabindex属性，否则大多数节点都无法获得焦点，但是链接，按钮和表单字段之类的东西却可以。我们将回到第18章中的表格字段。当没有特别注意的地方时，document.body将充当关键事件的目标节点。
当用户键入文本时，使用按键事件找出正在键入的内容是有问题的。某些平台（尤其是Android手机上的虚拟键盘）不会触发按键事件。但是，即使您使用的是老式键盘，某些类型的文本输入也无法以直接的方式与按键匹配，例如脚本不适合键盘的人所使用的输入法编辑器（IME）软件，多个按键组合在一起以创建字符。
为了得到，诸如\<input\>和\<textarea\>标记之类的可以键入的元素，何时键入的通知，只要用户更改内容，“ input”事件就会触发。要获取键入的实际内容，最好直接从焦点领域读取。第18章将说明如何操作。

## 指针事件

当前有两种广泛使用的指向屏幕上事物的方式：鼠标（包括像鼠标一样的设备，如触摸板和轨迹球）和触摸屏。 这些产生不同类型的事件。

### 鼠标事件

按下鼠标按钮会引发许多事件。 “ mousedown”和“ mouseup”事件类似于“ keydown”和“ keyup”事件，并在按下和释放按钮时触发。这些事件发生在事件发生时紧接在鼠标指针下方的DOM节点上。
在“ mouseup”事件之后，将在同时包含按下和释放按钮的最特定节点上触发“ click”事件。例如，如果我在一个段落上按下鼠标按钮，然后将指针移到另一段落并释放按钮，则包含两个段落的元素都会发生“ click”事件。
如果两次单击同时发生，则在第二次单击事件之后也会触发“ dblclick”（双击）事件。
要获取有关鼠标事件发生位置的精确信息，可以查看其clientX和clientY属性，其中包含事件相对于窗口左上角的坐标（以像素为单位），或pageX和pageY，分别是相对于整个文档的左上角（滚动窗口时可能会有所不同）。
以下实现了原始绘图程序。每次单击该文档时，它将在鼠标指针下方添加一个点。参见第19章，获取不太原始的绘图程序。

```html
<style>
  body {
    height: 200px;
    background: beige;
  }
  .dot {
    height: 8px; width: 8px;
    border-radius: 4px; /* rounds corners */
    background: blue;
    position: absolute;
  }
</style>
<script>
  window.addEventListener("click", event => {
    let dot = document.createElement("div");
    dot.className = "dot";
    dot.style.left = (event.pageX - 4) + "px";
    dot.style.top = (event.pageY - 4) + "px";
    document.body.appendChild(dot);
  });
</script>
```

### 鼠标移动

每次鼠标指针移动时，都会触发“ mousemove”事件。 此事件可用于跟踪鼠标的位置。 在实现某种形式的鼠标拖动功能时，这种方法很有用。
例如，以下程序显示一个条形图并设置事件处理程序，以便在该条形图上向左或向右拖动可使其变窄或变宽：

```html
<p>Drag the bar to change its width:</p>
<div style="background: orange; width: 60px; height: 20px">
</div>
<script>
  let lastX; // Tracks the last observed mouse X position
  let bar = document.querySelector("div");
  bar.addEventListener("mousedown", event => {
    if (event.button == 0) {
      lastX = event.clientX;
      window.addEventListener("mousemove", moved);
      event.preventDefault(); // Prevent selection
    }
  });
  function moved(event) {
    if (event.buttons == 0) {
      window.removeEventListener("mousemove", moved);
    } else {
      let dist = event.clientX - lastX;
      let newWidth = Math.max(10, bar.offsetWidth + dist);
      bar.style.width = newWidth + "px";
      lastX = event.clientX;
    }
  }
</script>
```

请注意，“ mousemove”处理程序在整个窗口上注册。 即使在调整大小期间鼠标移到栏的外面，只要按住按钮，我们仍然要更新其大小。
释放鼠标按钮时，我们必须停止调整栏的大小。 为此，我们可以使用button属性（注意复数形式），它告诉我们当前按住的按钮。 当它为零时，没有按钮按下。
按住按钮时，其值是这些按钮的代码之和-左按钮的编码为1，右按钮的编码为2，中间按钮的编码为4。这样，您可以通过这些组合编码知道哪些按钮被按下。
请注意，这些编码的顺序与按钮所使用的顺序不同，后者的中间按钮位于右按钮之前。 如前所述，一致性并不是浏览器编程界面的重点。

### 触摸事件

在很少使用触摸屏的时代，我们使用的图形浏览器在设计时仅仅考虑了鼠标界面。为了使Web在早期的触摸屏手机上“工作”，这些设备的浏览器在一定程度上假装了触摸事件是鼠标事件。如果您点击屏幕，则会出现“mousedown”，“mouseup”和“click”事件。但是这种错觉不是很稳健。触摸屏的工作方式与鼠标不同：触摸屏没有多个按钮，当手指不在屏幕上时，您无法跟踪手指（模拟“ mousemove”），并且触摸屏可以使多个手指在同一时间在触摸屏上。
鼠标事件仅在简单的情况下涵盖触摸交互-如果在按钮上添加“click”处理程序，则触摸用户仍将能够使用它。但是像上例中的可调整大小的条之类的东西在触摸屏上不起作用。
触摸互动会触发特定的事件类型。当手指开始触摸屏幕时，您将收到“ touchstart”事件。触摸时移动它会触发“ touchmove”事件。最后，当它停止触摸屏幕时，您会看到一个“ touchend”事件。
由于许多触摸屏可以同时检测到多个手指，因此这些事件没有与之关联的一组坐标。相反，它们的事件对象具有touches属性，该属性包含点的类似数组的对象，每个点都有其自己的clientX，clientY，pageX和pageY属性。
您可以执行以下操作以在每个触摸的手指周围显示红色圆圈：

```html
<style>
  dot { position: absolute; display: block;
    border: 2px solid red; border-radius: 50px;
    height: 100px; width: 100px; }
</style>
<p>Touch this page</p>
<script>
  function update(event) {
    for (let dot; dot = document.querySelector("dot");) {
      dot.remove();
    }
    for (let i = 0; i < event.touches.length; i++) {
      let {pageX, pageY} = event.touches[i];
      let dot = document.createElement("dot");
      dot.style.left = (pageX - 50) + "px";
      dot.style.top = (pageY - 50) + "px";
      document.body.appendChild(dot);
    }
  }
  window.addEventListener("touchstart", update);
  window.addEventListener("touchmove", update);
  window.addEventListener("touchend", update);
</script>
```

您通常需要在触摸事件处理程序中调用preventDefault来覆盖浏览器的默认行为（可能包括在滑动时滚动页面）并防止触发鼠标事件，为此您可能还具有处理程序。

## 滚动事件

每当滚动元素时，都会在其上触发“滚动”事件。 这有多种用途，例如了解用户当前正在查看的内容（用于禁用屏幕外动画或向您的邪恶总部发送间谍报告）或显示进度指示（通过突出显示目录的一部分或显示页面数）。
下面的示例在文档上方绘制进度条，并在向下滚动时对其进行更新以填充它：

```html
<style>
#progress {
  border-bottom: 2px solid blue;
  width: 0;
  position: fixed;
  top: 0; left: 0;
}
</style>
<div id="progress"></div>
<script>
  // Create some content
  document.body.appendChild(document.createTextNode(
    "supercalifragilisticexpialidocious ".repeat(1000)));
  let bar = document.querySelector("#progress");
  window.addEventListener("scroll", () => {
    let max = document.body.scrollHeight - innerHeight;
    bar.style.width = `${(pageYOffset / max) * 100}%`;
  });
</script>
```

给元素指定固定位置的行为与绝对位置非常相似，但还可以防止其与文档的其余部分一起滚动。 效果是使进度条保持在顶部。 更改其宽度以指示当前进度。 设置宽度时，我们以％而不是px为单位，以使元素相对于页面宽度进行尺寸设置。
全局的innerHeight绑定为我们提供了窗口的高度，我们必须从总可滚动高度中减去该高度-当您点击文档底部时，无法继续滚动。 窗口宽度也有一个innerWidth。 通过将pageYOffset（当前滚动位置）除以最大滚动位置并乘以100，我们可以得到进度条的百分比。
在滚动事件上调用preventDefault不会阻止滚动的发生。 实际上，仅在滚动发生之后才调用事件处理程序。

## 焦点事件

当元素获得焦点时，浏览器将在其上触发“focus”事件。 当失去焦点时，该元素将发生“blur”事件。
与前面讨论的事件不同，这两个事件不会传播。 当子元素获得焦点或失去焦点时，不会通知父元素的处理程序。
以下示例显示当前具有焦点的文本字段的帮助文本：

```html
<p>Name: <input type="text" data-help="Your full name"></p>
<p>Age: <input type="text" data-help="Your age in years"></p>
<p id="help"></p>
<script>
  let help = document.querySelector("#help");
  let fields = document.querySelectorAll("input");
  for (let field of Array.from(fields)) {
    field.addEventListener("focus", event => {
      let text = event.target.getAttribute("data-help");
      help.textContent = text;
    });
    field.addEventListener("blur", event => {
      help.textContent = "";
    });
  }
</script>
```
当用户从显示文档的浏览器选项卡或窗口中移入或移出时，该窗口对象将接收“focus”和“blur”事件。

## 加载事件

页面加载完成后，窗口和文档主体对象上将触发“加载”事件。这通常用于安排需要构建整个文档的初始化操作。请记住，\<script\>标记的内容会在遇到标记时立即运行。这可能为时过早，例如，当脚本需要对出现在\<script\>标记后的文档部分进行某些处理时。
加载外部文件的元素（例如图像和脚本标签）也具有“load”事件，该事件指示它们引用的文件已加载。与焦点相关事件一样，加载事件也不会传播。
当页面关闭或离开页面（例如，通过链接）时，将触发“ beforeunload”事件。此事件的主要用途是防止用户因关闭文档而意外丢失工作。如您所料，阻止页面的卸载不是通过preventDefault方法来完成的。而是通过从处理程序返回非null值来完成此操作。
当您这样做时，浏览器将向用户显示一个对话框，询问他们是否确定要离开该页面。这种机制可确保用户始终能够离开，即使是在恶意网页上，这种网页更希望将其永久保存在那里，并迫使他们查看隐晦的减肥广告。

## 事件和事件循环

在事件循环的上下文中，如第11章所述，浏览器事件处理程序的行为类似于其他异步通知。它们是在事件发生时安排的，但是必须等待其他正在运行的脚本完成，然后才能运行。只有在没有其他任何运行时才可以处理事件的事实，这意味着，如果事件循环与其他工作捆绑在一起，则与页面的任何交互（通过事件发生）都将被延迟，直到有时间进行处理为止。因此，如果您安排了太多的工作，或者使用长时间运行的事件处理程序，或者使用大量短期运行的事件处理程序，则该页面将变得缓慢且使用起来很麻烦。
对于确实要在后台执行一些耗时的操作而不冻结页面的情况，浏览器提供了称为Web Worker的功能。工作程序是一个JavaScript进程，它在其自己的时间轴上与主脚本一起运行。
想象一下，对数字进行平方是一个沉重的，长期运行的计算，我们希望在单独的线程中执行该计算。我们可以编写一个名为code / squareworker.js的文件，该文件通过计算平方并向后发送消息来响应消息。

```javascript
addEventListener("message", event => {
  postMessage(event.data * event.data);
});
```

为避免多个线程接触同一数据的问题，工作人员请勿与主脚本的环境共享全局范围或任何其他数据。 相反，您必须通过来回发送消息来与他们进行通信。
此代码产生一个运行该脚本的工作程序，向其发送一些消息，然后输出响应。

```javascript
let squareWorker = new Worker("code/squareworker.js");
squareWorker.addEventListener("message", event => {
  console.log("The worker responded:", event.data);
});
squareWorker.postMessage(10);
squareWorker.postMessage(24);
```

postMessage函数发送一条消息，这将在接收器中引发“message”事件。 创建工作程序的脚本通过工作程序对象发送和接收消息，而工作程序则通过直接在其全局范围内发送和侦听来与创建该工作程序的脚本进行对话。 只有可以表示为JSON的值才能作为消息发送-另一端将收到它们的副本，而不是值本身。

## 定时器

我们在第11章中看到了setTimeout函数。它安排了另一个函数，在给定的毫秒数后将被调用。 有时您需要取消预定的功能。 这是通过存储setTimeout返回的值并对其调用clearTimeout来完成的。

```javascript
let bombTimer = setTimeout(() => {
  console.log("BOOM!");
}, 500);
if (Math.random() < 0.5) { // 50% chance
  console.log("Defused.");
  clearTimeout(bombTimer);
}
```

cancelAnimationFrame函数的工作方式与clearTimeout相同，即在requestAnimationFrame返回的值上调用它会取消该帧（假设尚未调用）。 一组类似的函数setInterval和clearInterval用于设置应每X毫秒重复一次的计时器。

```javascript
let ticks = 0;
let clock = setInterval(() => {
  console.log("tick", ticks++);
  if (ticks == 10) {
    clearInterval(clock);
    console.log("stop.");
  }
}, 200);
```

## 防弹跳

某些类型的事件有可能连续多次快速触发（例如，“ mousemove”和“ scroll”事件）。处理此类事件时，必须注意不要做太耗时的操作，否则处理程序将占用大量时间，以至于与文档的交互开始变得缓慢。
如果确实需要在此类处理程序中执行一些不平凡的操作，则可以使用setTimeout来确保您不经常执行此操作。这通常称为对事件进行反弹。有几种方法略有不同。
在第一个示例中，我们希望在用户键入内容时做出反应，但我们不想在每个输入事件中立即执行操作。当他们快速打字时，我们只想等到暂停出现。我们设置了超时，而不是立即在事件处理程序中执行操作。我们还会清除上一个超时（如果有），以便当事件并发发生（比我们的超时延迟更近）时，上一个事件的超时将被取消。

```html
<textarea>Type something here...</textarea>
<script>
  let textarea = document.querySelector("textarea");
  let timeout;
  textarea.addEventListener("input", () => {
    clearTimeout(timeout);
    timeout = setTimeout(() => console.log("Typed!"), 500);
  });
</script>
```

给clearTimeout提供一个未定义的值或在已经触发的超时上调用它无效。 因此，我们不必担心何时调用它，而只需为每个事件调用它。
如果我们希望将响应间隔开，以使响应间隔至少一定的时间，但又希望在一系列事件中（而不是仅在事后触发）触发它们，则可以使用略有不同的模式。 例如，我们可能想通过显示鼠标的当前坐标（仅每250毫秒）来响应“ ousemove”事件。

```html
<script>
  let scheduled = null;
  window.addEventListener("mousemove", event => {
    if (!scheduled) {
      setTimeout(() => {
        document.body.textContent =
          `Mouse at ${scheduled.pageX}, ${scheduled.pageY}`;
        scheduled = null;
      }, 250);
    }
    scheduled = event;
  });
</script>
```

## 总结

通过事件处理程序，可以检测和响应网页中发生的事件。 addEventListener方法用于注册此类处理程序。
每个事件都有一个标识它的类型（“ keydown”，“ focus”等）。
大多数事件都是在特定的DOM元素上调用的，然后传播到该元素的祖先，从而使与这些元素相关联的处理程序能够处理它们。
调用事件处理程序时，会向其传递事件对象以及有关该事件的其他信息。该对象还具有允许我们停止进一步传播（stopPropagation）并阻止浏览器对事件进行默认处理（preventDefault）的方法。
按下一个键会触发“ keydown”和“ keyup”事件。按下鼠标按钮会触发“mousedown”，“mouseup”和“click”事件。移动鼠标会触发“ mousemove”事件。触摸屏交互将导致“touchstart”，“touchmove”和“touchend”事件。可以通过“scroll”事件检测滚动，而可以通过“focus”和“blur”事件检测焦点变化。文档加载完成后，窗口上将触发“load”事件。

## 练习

### 气球

编写一个显示气球的页面（使用气球表情符号🎈）。 当您按下向上箭头时，它应使10％膨胀（增长），而当您按下向下箭头时，其应使10％缩小（收缩）。 您可以通过在其父元素上设置font-size CSS属性（style.fontSize）来控制文本（表情符号为文本）的大小。 请记住，在值中包括一个单位，例如，像素（10px）。
箭头键的键名是“ ArrowUp”和“ ArrowDown”。 确保按键仅更改气球，而不滚动页面。
当这种方法起作用时，添加一个功能，如果将气球膨胀超过一定大小，它将爆炸。 在这种情况下，爆炸意味着将其替换为💥表情符号，然后事件处理程序将被删除（因此您无法使爆炸膨胀或收缩）。

```html
<!doctype html>
<html>
  <head>
    <meta charset="utf-8">
    <title>My home page</title>
  </head>
  <body>
    <p>🎈</p>
    <script>
      let p = document.querySelector("p");
      let size;
      function setSize(newSize) {
        size = newSize;
        p.style.fontSize = size + "px";
      }
      setSize(20);
      
      function handleArrow(event) {
        if (event.key == "ArrowUp") {
          if (size > 70) {
            p.textContent = "💥";
            document.body.removeEventListener("keydown", handleArrow);
          } else {
            setSize(size * 1.1);
            event.preventDefault();
          }
        } else if (event.key = "ArrowDown") {
          setSize(size*0.9);
          event.preventDefault();
        }
      }
      document.body.addEventListener("keydown", handleArrow);
    </script>
  </body>
</html>
```

### 鼠标轨迹

在JavaScript的早期，那是花哨的主页充斥大量动画图像的高潮时期，人们想到了一些真正鼓舞人心的方法来使用该语言。
其中之一是鼠标轨迹-在页面上移动鼠标指针时会跟随的一系列元素。
在本练习中，我希望您实现鼠标跟踪。 使用具有固定大小和背景颜色的绝对定位的<div>元素（有关示例，请参阅“鼠标单击”部分中的代码）。 创建一堆这样的元素，并在鼠标移动时将它们显示在鼠标指针之后。
这里有各种可能的方法。 您可以根据需要使解决方案简单或复杂。 首先，一个简单的解决方案是保持固定数量的线索元素并在它们之间循环，每次发生“移动事件”事件时，将下一个元素移动到鼠标的当前位置。

```html
<!doctype html>
<html>
  <head>
    <meta charset="utf-8">
    <title>My home page</title>
  </head>
  <style>
    .trail {
      position: absolute;
      height: 6px;
      width: 6px;
      border-radius: 3px;
      background: teal;
    }
    body {
      height: 300px;
    }
  </style>
  <body>
    <script>
      let dots = [];
      for (let i = 0; i < 12; ++i) {
        let node = document.createElement("div");
        node.className = "trail";
        document.body.appendChild(node);
        dots.push(node);
      }
      let currentDot = 0;
      window.addEventListener("mousemove", event => {
        let dot = dots[currentDot];
        dot.style.left = (event.pageX - 3) + "px";
        dot.style.top = (event.pageY - 3) + "px";
        currentDot = (currentDot + 1) % dots.length;
      });
    </script>
  </body>
</html>
```

### 标签页

选项卡式面板广泛用于用户界面。 它们允许您通过从元素上方“突出”的多个选项卡中进行选择来选择界面面板。
在本练习中，您必须实现一个简单的选项卡式界面。 编写一个函数asTabs，该函数接受一个DOM节点并创建一个选项卡式界面，显示该节点的子元素。 它应在节点顶部插入一个<button>元素列表，每个子元素一个，其中包含从子元素的data-tabname属性检索的文本。 除了一个原始孩子外，所有其他孩子都应该被隐藏（显示样式为none）。 单击按钮可以选择当前可见的节点。
在这种情况下，请对其进行扩展，以对当前所选选项卡的按钮进行不同样式的设置，以便于选择哪个选项卡。

```html
<!doctype html>
<html>
  <head>
    <meta charset="utf-8">
    <title>My home page</title>
  </head>
  <body>
    <tab-panel>
      <div data-tabname="one">Tab one</div>
      <div data-tabname="two">Tab two</div>
      <div data-tabname="three">Tab three</div>
    </tab-panel>
    <script>
      function asTabs(node) {
        let tabs = Array.from(node.children).map(node => {
          let button = document.createElement("button");
          button.textContent = node.getAttribute("data-tabname");
          let tab = {node, button};
          button.addEventListener("click", () => selectTab(tab));
          return tab;
        });

        let tabList = document.createElement("div");
        for (let {button} of tabs) tabList.appendChild(button);
        node.insertBefore(tabList, node.firstChild);

        function selectTab(selectedTab) {
          for (let tab of tabs) {
            let selected = tab == selectedTab;
            tab.node.style.display = selected ? "" : "none";
            tab.button.style.color = selected ? "red" : "";
          }
        }
        selectTab(tabs[0]);
      }

      asTabs(document.querySelector("tab-panel"));
    </script>
  </body>
</html>
```

