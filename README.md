# extend-cpython

本项目是一个模板项目，主要完成如下内容

1、使用 C/C++ 来实现部分功能

2、让软件支持 pip install 来安装

3、用 C/C++ 实现的功能支持像原生 Python 模块一样的导入

---

## C/C++ 拓展的原理

Python 的优势在于语法简洁，在一些特定的情况下 Python 的执行效率达不到业务的要求，我们可以通过更加低层的语言(C/C++)来实现这一部分逻辑，进而解决性能问题。就我个人的经历而言 99.9% 的情况下可能通过优化算法来解决。

要想实例用 C/C++ 来拓展 python 总来看分 3 步走

1、用 C/C++ 来实现你的业务逻辑

2、给你的 C/C++ 代码增加一段翻译代码，这个 Python 解释器就能理解了，详细的可以看官方的 [extending](https://docs.python.org/3.8/extending/index.html) 部分。

3、告诉 pip 在安装你的软件包时要编译包里面的 C/C++ 代码为共享库，这个可以通过定制 setup 函数来完成。官方文档看这里 [setup](https://docs.python.org/3/distutils/setupscript.html) 。


---

## 试用
安装包已经上传到了 pypi ，你可以通过 pip3 install extend-cpython 完成安装
``` bash
pip3 install extend-cpython --upgrade

Installing collected packages: extend-cpython
    Running setup.py install for extend-cpython ... done
Successfully installed extend-cpython-0.0.1

```
试用 C/C++ 拓展中的功能。
```python
In [1]: from plugins import maths

In [2]: maths.plus_one(12305)
Out[2]: 12306.0
```

---


## 1 实现业务逻辑
因为这是一个模板项目，所以在这里只实现一个 + 1 的算法。
```C++
// 用 C++ 实现一个加一的函数
double plus_one(double x)
{
    return x + 1;   
}
```

## 2 加上翻译代码

翻译代码负责把你的 C/C++ 代码包装成 *.py 一样的模块。
```C++
// 把 C/C++ 的一个函数包装成一个 Python 函数
static PyObject *py_plus_one(PyObject *self,PyObject *args) 
{
    double x = 0,result = 0;
    PyArg_ParseTuple(args,"d",&x);
    result = plus_one(x);
    return Py_BuildValue("d",result);
}

// 定义模块要包含的函数列表
static PyMethodDef methods[] = {
{"plus_one",py_plus_one,METH_VARARGS,"plus one"},
{0,0,0,0}
};

// 定义模块
static struct PyModuleDef module = {
PyModuleDef_HEAD_INIT,
"plugins",
"extend cpython",
-1,
methods
};

// 定义模块的初始化方法
PyMODINIT_FUNC PyInit_maths(void)
{
    return PyModule_Create(&module);
}

``` 

## 3 告诉 pip 安装时要怎么编译
```python
import os
import re
from setuptools import setup,Extension

setup(name='extend-cpython',
      #省略
      ext_modules = [Extension('plugins/maths',["src/maths.cpp"])],
      #省略
)
```

