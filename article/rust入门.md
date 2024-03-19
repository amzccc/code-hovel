# rust 入门

## 开发环境

[官网](https://www.rust-lang.org/zh-CN/)

更新 `rustup update`
卸载 `reustup self uninstall`
添加组件 `rustup component add component_name`
查看版本 `rustup --version`

### 编译器 rustc

查看版本 `rustc --version`

编译生成的二级制文件 `rustc -o output_name filename.rs`

编译生成库文件 `rustc --create-type lib filename.rs`

### 包管理工具 cargo

一般不直接使用编译器rustc，而是使用包管理工具cargo，cargo会隐式的使用rustc进行编译。

* 创建 `cargo new project_name`
* 创建库项目 `cargo new --lib project_name`
* 构建项目 `cargo build`
`cargo build --release`会生成release版本
* 检测 `cargo check`
* 运行/测试 `cargo run/test`

#### 项目结构

##### 库

project_name/
|-- Cargo.tomal
|-- src/
  |-- lib.rs

##### 可执行二进制文件 

project_name/
|-- Cargo.toml
|-- src/
  |-- main.js

##### Cargo.toml文件

**package**
设置项目名、版本号等

**dependencies**
设置全局依赖项

[build-dependencies] 列出只在构建项目时需要的依赖项
[dev-dependencies] 列出只在开发时需要的依赖项

## 三方库和换源

### 三方库管理

第三方库的查找网址: [https:// create.io](https:// create.io)

找到所需的三方库，粘贴到dependencies下即可。

还可以使用插件`cargo-edit`
* 安装插件 `cargo install cargo-edit`
* 添加库 `cargo add dependency_name`
* 安装指定版本 `cargo add dependency_name@1.2.3`
* 添加开发时依赖 `cargo add --dev dev_dependency_name`
* 添加构建时依赖 `cargo add --build build_dependency_name`
* 删除依赖 `cargo rm dependency_name`

### 国内源

修改文件 ~/.cargo/config

## 变量与数据类型

### 变量与不可变性

* 使用`let`声明变量，也可以显式指定变量类型
```rust
let x: i32=5;
```
* 变量名遵循蛇形命名法(下划线命名法), 枚举和结构遵顼帕斯卡命名法。如果变量没有用到可以添加前置下划线来消除警告。

* 强制类型转换
``` rust
let a = 3.1;
let b = a as i32;
```

* 打印变量
``` rust
println!("val: {}", x);
println!("val: {x}");
```

* rust中的变量默认是不可变的，不可变性也是rust实现可靠性和安全性的关键。如果希望一个变量是可变的，需要显示地用`mut`关键字进行声明。
```rust
let mut y = 10;
y = 20;
```

* rust可以通过声明一个同名的变量来将前一个变量隐藏掉。这不是重新赋值，而是产生了一个新的变量。

### const 常量

* 常量的值必须是在编译时已知的常量表达式，必须指定类型和值。
* 与C的宏定义不同，Rust的const常量被直接嵌入到底层的机器码之中，而不是简单的字符替换。
* 常量名与静态变量名命名推荐全部大写，单词间通过下划线相连。
* 常量的作用域是块级作用域，只在声明它们的作用域内可见。

### static 静态变量

* 与const不同，static变量是在运行时分配内存的。
* 并不是不可变的，可以使用unfase修改
* 静态变量的生命周期是整个程序的运行时间。

### 基础数据类型

* 有符号整型 i8 i16 i32 i64 i128，默认推断是i32
* 无符号整型 u8 u16 u32 u64 u128
* 平台决定的整型 usize isize
* 浮点型 f32 f64
* 布尔值 bool
* 字符类型 char


### 元组与数组

相同点：
1. 元组和数组都是复合类型，而Vec和Map都是集合类型(容器)。
2. 元组和数组的长度都是固定的。

不同点：
Tuples是不同数据类型组成的；
Arrays是相同数据类型组成的。

#### 数组

创建方式
* [a, b, c]
* [value; size]

获取元素 arr[index]
获取长度 arr.len()

#### 元组

获取元素 tup.index

### copy和move

和C++类似，Rust有copy和move两种拷贝方式，基础类型会使用copy行为，而对于String等复杂的和自定义的类型会使用move行为，这也就意味着，在将复杂类型作为其他的参数时，那么会失去所有权。
``` rust
let str = String::from("hello world");
let str_new = str;
println!("{str}");  // error，str在上一步失去了所有权，这是一个非法的访问
```

### 内存管理模型

Rust会在编译期做一系列的检查，如果检查出内存有问题的话，会直接报错。主要通过所有权机制(ownership rules)、引用检查(borrow checker)、生命周期(lifetime)、引用计数，使得在不牺牲性能的情况下（和C/C++是一个级别的），保证了内存的安全。

Rust和其他语言最不同的就是所有权的转移，当把变量传递给别的变量后，会被立刻销毁，无论是作为其他的构造参数，还是作为函数的入参。
如果不想要转移所有权，就需要使用`clone()`深拷贝一份。

Rust不允许函数直接返回一个引用，因为这样无法判断引用变量的生命周期。

### String和&str

String是一个堆分配的可变字符串类型
&str是指字符串切片引用，是在栈上分配的。
&str是个不可变引用，指向存储在其他地方的utf-8编码的字符串数据。

String是具有所有权的，&str没有。

Struct中属性使用String，如果不使用显式声明生命周期无法使用&str，麻烦而又有隐患。

函数参数推荐使用&str，不用交出所有权。&str为参数，可以传递&str和&String；&String为参数，只能传&String。

```rs
fn foo(str: &str) {
    println!("{str}");
}

fn main() {
  let name = String::from("value c++");

  let name2 = "Rust".to_string();

  let str3 = "hello".to_owned();

  let new_name = name.replace("c++", "cpp");

  println!("{name} {name2} {str3}");

  foo(&new_name);
}
```