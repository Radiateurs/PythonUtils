# NID DBC EMBEDDED

## Microsoft
-------------------------

#### Compiling

You must change the include paths and lib paths in the project. Most importantly the python paths.
ex : [LIB] C:\Users\User\AppData\Local\Programs\Python\Python37\libs
     [INCLUDES] C:\Users\User\AppData\Local\Programs\Python\Python37\include

#### Executing
Visual studio doesn't works and cannot handle properly the project. Execute it through a CMD to successfully use it.

To compile through a command use MSBuild.exe.

## PYTHON UTILS
---------------

#### SUMMARY
Python Utils is a small library that wrap the Python library to make it easier, and faster to use. On its current version it wraps modules, classes (and their methods) and functions import, creation and execution.

#### GETTING STARTED
To use the library, you will have to call `PythonUtils::start()` before any function for this library or the native Python Library. Once done and the programm won't use any other functions of those two library, call `PythonUtils::end()`.

##### MODULE


``` python
import module
```
To import modules just like in python, simply refer to the class PythonModule. This class will always have an instance to the selected module. You can either import the module through the constructor or through the method `Import`.
```C++
PythonModule    *firstModule = new PythonModule("module");
PythonModule    *otherModule() = new PythonModule();
PyObject        *lastModule = PythonUtils::ImportModuke("module");

otherModule->Import("module");
```
If you want to get the PyObject object for the module, either use the getter of PythonModule or call the import from PythonUtils.
``` C++
PyObject        *myModule, *myOtherModule;
PythonModule    *otherModule = new PythonModule("module");

/* 1st method passing by the static method of PythonUtils */
myModule = PythonUtils::ImportModule("module")
/* 2nd method using the getter of PythonModule */
myOtherModule = otherModule->GetInstance();
```

##### CLASS

``` python
from module import klass
```
To import a class from a module, simply call the method `LoadClass` from a PythonModule class, or use the `ImportClassFromModule` from PythonUtils.

```C++
PyObject        *klass = PythonUtils::ImportClassFromModule("module", "klass");
PythonModule    *otherModule = new PythonModule("module");
PythonClass     *otherKlass = otherModule->LoadClass("klass");
```

##### FUNCTION

IMPORTING A FUNCTION
```python
from module import funktion
```

To import a function from a module, just like the class, you can use the PythonUtils method `ImportMethodFromModule` or the `LoadFunction` from a PythonModule class.
```C++
PyObject        *funktion = PythonUtils::ImportMethodFromModule("module", "funktion");
PythonModule    *otherModule = new PythonModule("module");
PythonFunction  *otherFunktion = otherModule->LoadFunction("funktion");
PythonFunction  *lastFunktion = new PythonFunction("module", "funktion");
```

EXECUTING A FUNCTION
```python
funktion(a, b)
```
Here is the list of method you can use to call a function:
Using PythonFunction :
- Execute(PyObject *p_pArgs);
- Execute(const std::string &p_rExpr, ...);

Using PythonUtils :
- CallMethod(PyObject *p_pMethod, const std::string &p_rExpr, ...);
- CallMethod(PyObject *p_pMethod, PyObject *p_pArgs);
- CallMethodFromClassFromModule(const std::string &p_rModule, const std::string &p_rClass, const std::string &p_rMethod, const std::string &p_rExpr, ...);
- CallMethodFromLoadedClassPythonUtils::(PyObject *p_pClass, const std::string &p_rMethod, ...);

As you can see there's most of the time a string `p_rExpr` and a va_list `...`. Those two are used for the arguments. Using the string, you will have to formulate the types for the next coming arguments. let's say that `a` and `b` are numbers. To give the value to the python function, I will have to fomat them this way : 
```C++
int             a = 0;
int             b = 1;
PythonFunction  myFunction("module", "funktion");
myFunction.Execute("(ii)", a, b);
``` 
#### /!\ IMPORTANT :
When passing one or more arguments to a function, you MUST always put them in a tuple. In the previous example it is shown by the two parenthesis in `(ii)` .
Learn more about the argument formatting [here](https://docs.python.org/3/c-api/arg.html).

Unlike the previous examples, `Execute(PyObject *p_pArgs)` has directly a `PyObject *` which represents the formatted arguments. This can be done using native Python library's function such as `Py_BuildValue`.
```C++
int             a = 0;
int             b = 1;
PyObject        *myArgs = Py_BuildValue("(ii)", a, b);
PythonFunction  *myFunction = new PythonFunction("module", "funktion");
myFunction->Execute(myArgs);
```



##### REFERENCES
[1] https://learning-python.com/class/Workbook/unit16.htm
[2] https://www.oreilly.com/library/view/python-cookbook/0596001673/ch16s03.html
[3] https://docs.python.org/3/c-api/
[4] http://books.gigatux.nl/mirror/pythonprogramming/0596000855_python2-CHP-20-SECT-5.html