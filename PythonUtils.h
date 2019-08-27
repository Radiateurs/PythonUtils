/**
 **************************************************************************
 * SIREHNA
 **************************************************************************
 * \brief	This file contain definition of mutliple classes for the Python 
 *			Wrapping library.
 * \author Pierre-Marie Danieau
 **************************************************************************
 * \brief \b History
 *	- 15/05/2017 BSO Creation
 **************************************************************************
 * Copyright     SIREHNA
 * 1 Rue de la Noe
 * 44321 Nantes Cedex 3
 */

#ifndef	__SIR_PYTHON_UTILS__
#define	__SIR_DBCCLASSIFIER__

 /******************************************************************************/
 /* INCLUDE FILES */
 /******************************************************************************/
#include "Python.h"
#include <varargs.h>
#include <string>
#include <vector>
#include <map>

/******************************************************************************/
/* CONSTANT DEFINITION */
/******************************************************************************/

/******************************************************************************/
/* CLASS DEFINITION */
/******************************************************************************/
class PythonModule;
class PythonClass;
class PythonFunction;
class PythonUtils;

/******************************************************************************/
/* CLASS DEFINITION PythonModule */ 
/******************************************************************************/
class PythonModule
{
private:
	PyObject			*m_pInstance;
	std::string			m_Name;
	std::vector<PythonClass*> m_Classes;
	std::vector<PythonFunction*>	m_Functions;

public:
	/* GETTER */
	PyObject			*GetInstance() const;
	const std::string	GetName() const;
	const std::vector<PythonClass*>	GetClasses() const;
	const PythonClass	*GetClass(const std::string &p_rClass) const;
	const std::vector<PythonFunction*>	GetFunctions() const;
	const PythonFunction	*GetFunction(const std::string &p_rFunction) const;
	bool				IsValid() const;

	/* SETTER */
	void				SetInstance(PyObject *p_pInstance);
	void				SetName(const std::string &p_pName);
	void				SetClasses(const std::vector<PythonClass*> p_Classes);

	PythonClass			*LoadClass(const std::string &p_rClassName);
	bool				Import(const std::string &p_rModuleName);
	PythonFunction		*LoadFunction(const std::string &p_rFunctionName);

	/* CTOR */
	PythonModule(const std::string &p_rName);
	PythonModule();

	/* DTOR */
	virtual ~PythonModule();

	/* COPY CTOR */
	PythonModule(const PythonModule &p_rOther);

	/* Operation overload = */
	PythonModule		&operator=(const PythonModule &p_rOther);
};

/******************************************************************************/
/* CLASS DEFINITION PythonClass */
/******************************************************************************/
class PythonClass
{
private:
	PyObject			*m_pClass;
	PyObject			*m_pInstance;
	std::string			m_Name;
	std::vector<PythonFunction*>	m_Methods;

public:	
	/* GETTER */
	PyObject			*GetClass() const;
	PyObject			*GetInstance() const;
	const std::string	GetName() const;
	const std::vector<PythonFunction*>	GetMethods() const;
	const PythonFunction	*GetMethod(const std::string &p_rMethod) const;
	bool				IsValid() const;

	/* SETTER */
	void				SetClass(PyObject *p_pClass);
	void				SetInstance(PyObject *p_pInstance);
	void				SetName(const std::string &p_pName);
	void				SetMethods(const std::vector<PythonFunction*> p_Methods);

	void				Construct(const char *p_pExpr, ...);
	void				Construct(PyObject *p_pArgs);
	void				Destruct();
	PythonFunction		*LoadMethod(const std::string &p_rClassMethod);

	/* CTOR */
	PythonClass();
	PythonClass(PyObject *p_pModule, const std::string &p_rName);

	/* DTOR */
	virtual ~PythonClass();

	/* COPY CTOR */
	PythonClass(const PythonClass &p_rOther);

	/* Operation overload = */
	PythonClass			&operator=(const PythonClass &p_rOther);
};

/******************************************************************************/
/* CLASS DEFINITION PythonFunction */
/******************************************************************************/
class PythonFunction
{
private:
	PyObject			*m_pInstance;
	std::string			m_Name;

public:
	/* GETTER */
	PyObject			*GetInstance() const;
	const std::string	GetName() const;
	bool				IsValid() const;

	/* SETTER */
	void				SetInstance(PyObject *p_pInstance);
	void				SetName(const std::string &p_pName);

	PyObject			*Execute(PyObject *p_pArgs);
	PyObject			*Execute(const char *p_pExpr, ...);

	/* CONSTRUCTOR - COPLIEN */

	/* CTOR */
	PythonFunction();
	PythonFunction(PyObject *p_pModule, const std::string &p_rName);

	/* DTOR */
	virtual ~PythonFunction();

	/* COPY CTOR */
	PythonFunction(const PythonFunction &p_rOther);

	/* Operation overload = */
	PythonFunction		&operator=(const PythonFunction &p_rOther);
};

/******************************************************************************/
/* CLASS DEFINITION PythonUtils */
/******************************************************************************/
class PythonUtils
{
public:
	static void			start();
	static void			end();
	static PyObject		*ImportModule(const std::string &p_rModule);
	static PyObject		*ImportClassFromLoadedModule(PyObject *p_Module, const std::string &p_rClass);
	static PyObject		*ImportClassFromModule(const std::string &p_rModule, const std::string &p_rClass);
	static PyObject		*ImportMethodFromLoadedModule(PyObject *p_pMethod, const std::string &p_rMethod);
	static PyObject		*ImportMethodFromModule(const std::string &p_rModule, const std::string &p_rMethod);
	static PyObject		*ImportMethodFromLoadedClass(PyObject *p_pClass, const std::string &p_rMethod);
	static PyObject		*CallMethod(PyObject *p_pMethod, const char *p_pExpr, ...);
	static PyObject		*CallMethod(PyObject *p_pMethod, const char *p_pExpr, va_list p_VarArgs);
	static PyObject		*CallMethod(PyObject *p_pMethod, PyObject *p_pArgs);
	static PyObject		*CallMethodFromClassFromModule(const std::string &p_rModule, const std::string &p_rClass, const std::string &p_rMethod, const char *p_pExpr, ...);
	static PyObject		*CallMethodFromClassFromLoadedMethod(PyObject *p_pModule, const std::string &p_rClass, const std::string &p_rMethod, const char *p_pExpr, ...);
	static PyObject		*CallMethodFromLoadedClass(PyObject *p_pClass, const std::string &p_rMethod, const char *p_pExpr,...);

	PythonUtils();
	~PythonUtils();
};

#endif /*__SIR_PYTHON_UTILS__ */