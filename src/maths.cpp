#include <Python.h>

// 用 C++ 实现一个加一的函数
double plus_one(double x)
{
    return x + 1;   
}

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
