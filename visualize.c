//
// Created by 肖骁 on 2021/5/30.
//
#include "visualize.h"
#include <stdio.h>
#include <python.h>

void visualize(char file[],char path[])
{
    PyObject *pName, *pModule, *pFunc;
    PyObject *pArgs, *pValue;
    Py_Initialize();//开始Python解释器
    pName = PyUnicode_DecodeFSDefault("draw_map");//python的文件名为draw_map.py
    pModule = PyImport_Import(pName);//import the file
    pFunc = PyObject_GetAttrString(pModule,"draw_map");//*pFunc指向draw_map.py中的draw_map函数
    pArgs = PyTuple_New(2);//函数调用的参数传递均是以元组的形式打包的,2表示参数个数
    PyTuple_SetItem(pArgs, 0, Py_BuildValue("s", file));//0--序号,i表示创建int型变量
    PyTuple_SetItem(pArgs, 1, Py_BuildValue("i", path));//1--序号
    PyObject_CallObject(pFunc, pArgs);//调用函数
    Py_Finalize();
}
