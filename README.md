# CPPTools

![C++ Solutions](https://img.shields.io/badge/STD-C++17-blue.svg?style=flat&logo=c%2B%2B)![GitHub last commit](https://img.shields.io/github/last-commit/divad1196/CPPTools)![example workflow](https://github.com/divad1196/CPPTools/actions/workflows/ccpp.yml/badge.svg)![GitHub](https://img.shields.io/github/license/divad1196/CPPTools)

### Tests

Tests are done using [Catch2 v2.13.6](https://github.com/catchorg/Catch2/releases/tag/v2.13.6)



## Set of CPP tools

* Header only
* Simple to use
* Standalone: only rely on std



[TOC]



##### Maintainer remarks:

* Those are a few projects of mine combined altogether for convenience. They **may** be splitted in separate repositories again later.

* This is a bunch of utilitaries, but i am looking forward to add more complex tools

* Some part are still in draft, i really take to heart to have a good api and it is hard to challenge myself to find the best one.
  I would appreciate any suggestion/opinion.
  
* I still have to write tests and documentation and i promise it will be done as soon as the api is fixed for any part of the project.

* I want this code to be cross platform, but first implementation may always be on linux (since i work on it)

  

**Any comment, advice/recommendation is welcome!** I specially struggle with naming or design decisions (e.g.: should i use a constexpr function or a template structure)



## Tuple

```c++
auto x = std::make_tuple(3, 4, std::string("foo"), 5, 6, std::string("bar"));
auto seq = cond_index_seq<std::is_integral>(x);  // Generate an index_sequence based on a condition
auto sub = extract(x, seq);
print_tuple(sub);  // (3, 4, 5, 6)

// We can do it with one line only
auto sub = cond_extract<std::is_integral>(x);
```

I personally use tuple a lot to handle types, for example those who are passed to a function.
This currently only works with `Cond` being a struct with static boolean `value` attribute, as `std::is_integral`.

In the same way, there is also `slice` which works with **references** (based on `std::tie`)



## String

Utilitaries for std::basic_string classes and const char* (null terminated)

* **instring**: Return true if a string contains the given char, false otherwise
  It is used for convenience (not returning an iterator) and genericity (use for both std::string or const char\*)

* **icomp**: case insensitive comparison  between strings

* **strip**: remove characters at the begining/end of the word<br/>
  Prefixes:

  * **i**: stands for "inplace" => directly modify the string, otherwise makes a copy
  * **l/r**: respectively left and right, otherwise strip both left and right sides

  Condition:

  * A function taking a char(e.g. `isspace`)
  * A string: any char in the string will be removed (e.g.: strip(mystr, "ab") will remove both 'a' and 'b' char at the begining and the end of the string)
  * Nothing: strip whitespaces

  E.g. inplace left strip of characters 'x' and 'y':

  ```c++
  ilstrip(mystr, "xy");
  ```

  

* **Conversions**: namespace "Convert"

  * **to_string**: by default reuse std::to_string but could be override
  * **from_string**: serialize a string to an atomic type (int, double, bool, ...). This is not meant to serialize bigger data!

  Thoses functions are meant to work together:

  ```c++
  value == from_string<decltype(value)>(to_string(value)) // ouput: true
  ```




## CPPEnv

Deal easily with environment variables. They are wrapper for getenv, setenv and unsetenv

* namespace: Env
* Variable name: either `std::string` or `const char*`
* get\<T>: cast using Convert::from_string
* set/unset: return boolean (true if succeeded)



## Function

Tool to handle functions

```c++
void myfunc(int a, int b) {return a + b;}
std::cout << Signature<decltype(myfunc)>::param_count << std::endl;
```

It provides:

* return_type: return type of the function
* argument_type: tuple type with function's arguments type
* param_count
* indexes: std::index_sequence for function

It supports std::function too



## Caller

```c++
void myfunc(int a, int b) {return a + b;}

nlohmann::json myjson = {
    {"foo", 9},
    {"bar", 7}
};
Caller caller(myfunc, "foo", "bar");
std::cout << caller(myjson) << std::endl;  // output: 16
```



## Callback

Partially inspired by RxJS.



#### Wrapper

a wrapper defining getter and setter

```c++
Wrapper<int> a(0,
	[](const int& value){ return value / 2; },
	[](int& value, const int& new_value){ value = new_value * 4;}
);

std::cout << a.get() << std::endl;  // 0
a.set(10);
// we can also use implicit cast
std::cout << a << std::endl;	// 20
a.set(a.get() * 3);
std::cout << a.get() << std::endl;  // 120
```



#### Subject

Call successively all callbacks on value change

```c++
int tmp = 0;

Subject<int> b(0);
b.subscribe([&tmp](const int& value) { tmp = value; });
b.subscribe([](const int& value) { std::cout << "value changed to " << value << std::endl; });

std::cout << tmp << std::endl;
b.set(9);
std::cout << tmp << std::endl;
```



#### Interval

Use the callback after a given period of time (ms)

```c++
// Run for a given period of 5000ms
Interval interval(1000);
    
// Convenient way to use fps
Interval interval2 = Interval::FPS(60);



interval.runFor([](){
	std::cout << "hello world" << std::endl;
}, 5000);

// Run while condition is true
bool condition = true;
interval.runWhile([&condition](Interval::Duration dt){
    ...
    if(some_requirments)
        condition = false;
})
```

* runFor: run for a given period of time (ms)
* runWhile: take a boolean sentinel by const reference. The value must be updated from the callback.
* run: simply run forever.

The callback function can either take:

* No parameter
* Interval::Duration by copy which is the duration since last callback in ms.
  Nb: Use this value instead of the known value of interval, even if they currently are the same.



#### Debounce

Pretty similar to Interval, it return true if its last use was more than the interval time, else return false.

```c++
int count = 0;
Debounce dbounce(1000);
while (count < 5) {
    dbounce && (count += 1) && (
        std::cout << count << std::endl
    );
}
```

Nb: I do not recommend to write it by chaining &&, but it allows this kind of use.



#### Aggregate

Functor to aggregate values.
The contained value can be accessed at any moment. The default value can be provided, otherwise, default constructor is used.

```c++
Aggregate<int> a([](const int& aggr, const int& val){return aggr + val;});
```



#### Futur Works

* Implements data stream
* Take advantage of coroutine.
* Add atomic version and support for threading
* add Pipe class



## CLI [WIP]

CLI tools inspired by [Click.py](https://click.palletsprojects.com/en/7.x/) philosophy.



## Router [WIP]

Meant to be simple to use and generic.

#### Goals

C++ is a great language, but needs a lot of work and knowledge.
For web routing as well as for cli, we have to use different technologies.

This library won't implements directly web server nor cli tools.
It will implement:

* Route matching
* Route call



It should be easy to customise its use.



#### Compilation

Currently officially need at least **C++17** and only need the standard library.
Backward compatibility support may be added.



#### Usage

```c++
Route<int, int, float> route(
    "hello %d world %d final %f",
    [](int a, int b, float c) {
        std::cout << a << " - " << b  << " " << c << std::endl;
    });

route("hello 52 world 34 final 9.0");  // 52 - 34 9
```





Goal

```c++
Router router;
router.route(
    "hello/{}/world/{}/final/{}",
    [](int a, int b, float c) {
        std::cout << a << " - " << b  << " " << c << std::endl;
    }
);

router.route(
    "hello/{}/world",
    [](const std::string& a) {
        std::cout << "test: " << a << std::endl;
    }
);


router("hello/foo/world");  // test: foo
router("hello/32/world/64/final/5.9");  // 32 - 64 5.9
router("abc");  // Error
```

* Not relying on C formatting
* Automatic route match
* Default parameter

##### Todo

1. route template deduction (issue with lambda as argument)
2. router (matching argument types)
   Avoiding all comparisons.
3. better parser tant sscanf ([scnlib](https://github.com/eliaskosunen/scnlib)? Ternary search tries?)



### 

