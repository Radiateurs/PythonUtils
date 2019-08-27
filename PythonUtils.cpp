/**
 *
 **************************************************************************
 * SIREHNA
 **************************************************************************
 * \brief PythonUtils Library definition
 * \author Pierre-Marie Danieau
 **************************************************************************
 * Copyright     SIREHNA
 * Technocampus Océan - 5 rue de l'Halbrane
 * 44340 Bouguenais - France
 */

 //************************************************************************
 // SVN info
 // SVN $Id: $
 // SVN $HeadURL: $
 //************************************************************************

 /******************************************************************************/
 /* INCLUDE FILES */
 /******************************************************************************/
#include "PythonUtils.h"
#include <iostream>

/******************************************************************************/
/* CONSTANT DEFINITION */
/******************************************************************************/

/******************************************************************************/
/* CLASS : PythonModule */
/******************************************************************************/
PythonModule::PythonModule(const std::string &p_rName) :
	m_Name(p_rName)
{
	PyObject		*pName;

	pName = PyUnicode_FromString(p_rName.c_str());
	this->m_pInstance = PyImport_Import(pName);
	Py_DECREF(pName);
}

PythonModule::PythonModule() :
	m_Name()
{
	this->m_pInstance = NULL;
}

PythonModule::~PythonModule()
{
	Py_DECREF(this->m_pInstance);
}

PythonModule::PythonModule(const PythonModule &p_rOther)
{
	this->m_pInstance = p_rOther.GetInstance();
	this->m_Name = p_rOther.GetName();
	this->m_Classes = p_rOther.GetClasses();
	this->m_Functions = p_rOther.GetFunctions();
}

PythonModule		&PythonModule::operator=(const PythonModule &p_rOther)
{
	this->m_pInstance = p_rOther.GetInstance();
	this->m_Name = p_rOther.GetName();
	this->m_Classes = p_rOther.GetClasses();
	this->m_Functions = p_rOther.GetFunctions();
	return (*this);
}

PyObject		*PythonModule::GetInstance() const
{
	return (this->m_pInstance);
}
const std::string	PythonModule::GetName() const
{
	return (this->m_Name);
}

const std::vector<PythonClass*>	PythonModule::GetClasses() const
{
	return (this->m_Classes);
}

const PythonClass	*PythonModule::GetClass(const std::string &p_rClass) const
{
	std::vector<PythonClass*>::const_iterator	it = this->m_Classes.begin();

	while (this->m_Classes.end() != it)
	{
		if ((*it)->GetName() == p_rClass)
			return (*it);
		it++;
	}
	return (NULL);
}

const std::vector<PythonFunction*>	PythonModule::GetFunctions() const
{
	return (this->m_Functions);
}

const PythonFunction	*PythonModule::GetFunction(const std::string &p_rFunction) const
{
	std::vector<PythonFunction*>::const_iterator	it = this->m_Functions.begin();

	while (this->m_Functions.end() != it)
	{
		if ((*it)->GetName() == p_rFunction)
		{
			return (*it);
		}
		it++;
	}
	return (NULL);
}

bool				PythonModule::IsValid() const
{
	return (!(this->m_pInstance == NULL));
}

void				PythonModule::SetInstance(PyObject *p_pInstance)
{
	this->m_pInstance = p_pInstance;
}

void				PythonModule::SetName(const std::string &p_pName)
{
	this->m_Name = p_pName;
}

void				PythonModule::SetClasses(const std::vector<PythonClass*> p_Classes)
{
	this->m_Classes = p_Classes;
}

PythonClass			*PythonModule::LoadClass(const std::string &p_rClassName)
{
	PythonClass		*newClass = new PythonClass(this->m_pInstance, p_rClassName);
	
	this->m_Classes.push_back(newClass);
	return (newClass);
}

bool				PythonModule::Import(const std::string &p_rModuleName)
{
	this->m_pInstance = PythonUtils::ImportModule(p_rModuleName);
	if (!this->m_pInstance)
		return (false);
	this->m_Name = p_rModuleName;
	return (true);
}

PythonFunction		*PythonModule::LoadFunction(const std::string &p_rFunctionName)
{
	PythonFunction	*newFunction = new PythonFunction(this->m_pInstance, p_rFunctionName);
	this->m_Functions.push_back(newFunction);
	return (newFunction);
}

/******************************************************************************/
/* CLASS : PythonClass */
/******************************************************************************/
PythonClass::PythonClass(PyObject *p_pModule, const std::string &p_rName) :
	m_Name(p_rName)
{
	this->m_pClass= PyObject_GetAttrString(p_pModule, p_rName.c_str());
	this->m_pInstance = NULL;
}

PythonClass::PythonClass() :
	m_Name()
{
	this->m_pInstance = NULL;
	this->m_pClass = NULL;
}

PythonClass::~PythonClass()
{
	if (!this->m_pInstance)
		Py_DECREF(this->m_pInstance);
	if (!this->m_pClass)
		Py_DECREF(this->m_pClass);
}

PythonClass::PythonClass(const PythonClass &p_rOther)
{
	this->m_pClass = p_rOther.GetClass();
	this->m_pInstance = p_rOther.GetInstance();
	this->m_Name = p_rOther.GetName();
	this->m_Methods = p_rOther.GetMethods();
}

PythonClass			&PythonClass::operator=(const PythonClass &p_rOther)
{
	this->m_pInstance = p_rOther.GetInstance();
	this->m_Name = p_rOther.GetName();
	this->m_Methods = p_rOther.GetMethods();
	this->m_pClass = p_rOther.GetClass();
	return (*this);
}

PyObject		*PythonClass::GetClass() const
{
	return (this->m_pClass);
}

PyObject		*PythonClass::GetInstance() const
{
	return (this->m_pInstance);
}

const std::string	PythonClass::GetName() const
{
	return (this->m_Name);
}

const std::vector<PythonFunction*>	PythonClass::GetMethods() const
{
	return (this->m_Methods);
}

const PythonFunction	*PythonClass::GetMethod(const std::string &p_rMethod) const
{
	std::vector<PythonFunction*>::const_iterator	it = this->m_Methods.begin();

	while (this->m_Methods.end() != it)
	{
		if ((*it)->GetName() == p_rMethod)
			return (*it);
		it++;
	}
	return (NULL);
}

bool				PythonClass::IsValid() const
{
	return (!(this->m_pClass == NULL));
}

void				PythonClass::SetClass(PyObject *p_pClass)
{
	this->m_pClass = p_pClass;
}

void				PythonClass::SetInstance(PyObject *p_pInstance)
{
	this->m_pInstance = p_pInstance;
}

void				PythonClass::SetName(const std::string &p_pName)
{
	this->m_Name = p_pName;
}

void				PythonClass::SetMethods(const std::vector<PythonFunction*> p_Methods)
{
	this->m_Methods = p_Methods;
}

void				PythonClass::Construct(const char *p_pExpr, ...)
{
	va_list			pVarArgs;

	if (!this->m_pClass)
		return;
	va_start(pVarArgs, p_pExpr);
	this->m_pInstance = PythonUtils::CallMethod(this->m_pClass, p_pExpr, pVarArgs);
	va_end(pVarArgs);
}

void				PythonClass::Construct(PyObject *p_pArgs)
{
	if (!this->m_pClass)
		return;
	this->m_pInstance = PythonUtils::CallMethod(this->m_pClass, p_pArgs);
}

void				PythonClass::Destruct()
{
	Py_DECREF(this->m_pInstance);
	this->m_pInstance = NULL;
}


PythonFunction		*PythonClass::LoadMethod(const std::string &p_rClassMethod)
{
	PythonFunction	*newFunction;

	if (this->m_pInstance != NULL)
		newFunction = new PythonFunction(this->m_pInstance, p_rClassMethod);
	else if (this->m_pClass != NULL)
		newFunction = new PythonFunction(this->m_pClass, p_rClassMethod);
	else 
		return (NULL);
	this->m_Methods.push_back(newFunction);
	return (newFunction);
}

/******************************************************************************/
/* CLASS : PythonFunction */
/******************************************************************************/
PythonFunction::PythonFunction() :
	m_Name()
{
	this->m_pInstance = NULL;
}

PythonFunction::PythonFunction(PyObject *p_pModule, const std::string &p_rName) :
	m_Name(p_rName)
{
	this->m_pInstance = PyObject_GetAttrString(p_pModule, p_rName.c_str());
}

PythonFunction::~PythonFunction()
{
	Py_DECREF(this->m_pInstance);
}

PythonFunction::PythonFunction(const PythonFunction &p_rOther)
{
	this->m_pInstance = p_rOther.GetInstance();
	this->m_Name = p_rOther.GetName();
}

PythonFunction		&PythonFunction::operator=(const PythonFunction &p_rOther)
{
	this->m_pInstance = p_rOther.GetInstance();
	this->m_Name = p_rOther.GetName();
	return (*this);
}

PyObject		*PythonFunction::GetInstance() const
{
	return (this->m_pInstance);
}

const std::string	PythonFunction::GetName() const
{
	return (this->m_Name);
}

bool				PythonFunction::IsValid() const
{
	return (this->m_pInstance != NULL);
}

void				PythonFunction::SetInstance(PyObject *p_pInstance)
{
	this->m_pInstance = p_pInstance;
}

void				PythonFunction::SetName(const std::string &p_rName)
{
	this->m_Name = p_rName;
}

PyObject			*PythonFunction::Execute(PyObject *p_pArgs)
{
	return (PythonUtils::CallMethod(this->m_pInstance, p_pArgs));
}

PyObject			*PythonFunction::Execute(const char *p_pExpr, ...)
{
	PyObject		*pArgs, *pResult;
	va_list			VarArgs;

	va_start(VarArgs, p_pExpr);
	pArgs = Py_VaBuildValue(p_pExpr, VarArgs);
	pResult = PyEval_CallObject(this->m_pInstance, pArgs);
	Py_DECREF(pArgs);
	return (pResult);
}

/******************************************************************************/
/* CLASS : PythonUtils */
/******************************************************************************/
PyObject			*PythonUtils::ImportModule(const std::string &p_rModule)
{
	PyObject		*pName, *pModule;

	pName = PyUnicode_FromString(p_rModule.c_str());
	pModule = PyImport_Import(pName);
	Py_DECREF(pName);
	return (pModule);
}

PyObject			*PythonUtils::ImportClassFromLoadedModule(PyObject *p_pModule, const std::string &p_rClass)
{
	return (PyObject_GetAttrString(p_pModule, p_rClass.c_str()));
}

PyObject			*PythonUtils::ImportClassFromModule(const std::string &p_rModule, const std::string &p_rClass)
{
	PyObject		*pModule, *pClass;

	pModule = PythonUtils::ImportModule(p_rModule);
	if (pModule == NULL)
		return (NULL);
	pClass = PythonUtils::ImportClassFromLoadedModule(pModule, p_rClass);
	Py_DECREF(pModule);
	return (pClass);
}

PyObject			*PythonUtils::ImportMethodFromLoadedModule(PyObject *p_pModule, const std::string &p_rMethod)
{
	return (PyObject_GetAttrString(p_pModule, p_rMethod.c_str()));
}

PyObject			*PythonUtils::ImportMethodFromModule(const std::string &p_rModule, const std::string &p_rMethod)
{
	return (PythonUtils::ImportClassFromModule(p_rModule, p_rMethod));
}

PyObject			*PythonUtils::ImportMethodFromLoadedClass(PyObject *p_pClass, const std::string &p_rMethod)
{
	return (PythonUtils::ImportMethodFromLoadedModule(p_pClass, p_rMethod));
}

PyObject			*PythonUtils::CallMethod(PyObject *p_pMethod, const char *p_pExpr, ...)
{
	PyObject		*pArgs, *pResult;
	va_list			pVarArgs;

	va_start(pVarArgs, p_pExpr);
	pArgs = Py_VaBuildValue(p_pExpr, pVarArgs);
	va_end(pVarArgs);
	pResult = PyEval_CallObject(p_pMethod, pArgs);
	Py_DECREF(pArgs);
	return (pResult);
}

PyObject			*PythonUtils::CallMethod(PyObject *p_pMethod, const char *p_pExpr, va_list p_VarArgs)
{
	PyObject		*pArgs, *pResult;

	pArgs = Py_VaBuildValue(p_pExpr, p_VarArgs);
	pResult = PyEval_CallObject(p_pMethod, pArgs);
	Py_DECREF(pArgs);
	return (pResult);
}

PyObject			*PythonUtils::CallMethod(PyObject *p_pMethod, PyObject *p_pArgs)
{
	return (PyEval_CallObject(p_pMethod, p_pArgs));
}


PyObject			*PythonUtils::CallMethodFromClassFromModule(const std::string &p_rModule, const std::string &p_rClass, const std::string &p_rMethod, const char *p_pExpr, ...)
{
	PyObject		*pClass = PythonUtils::ImportClassFromModule(p_rModule, p_rClass), *pMethod, *pArgs, *pResult;
	va_list			pVarArgs;

	if (pClass == NULL)
		return (NULL);
	pMethod = PythonUtils::ImportMethodFromLoadedClass(pClass, p_rMethod);
	if (pMethod == NULL)
		return (NULL);
	va_start(pVarArgs, p_pExpr);
	pResult = PythonUtils::CallMethod(pMethod, p_pExpr, pVarArgs);
	va_end(pVarArgs);
	Py_DECREF(pClass);
	Py_DECREF(pMethod);
	Py_DECREF(pArgs);
	return (pResult);
}

PyObject			*PythonUtils::CallMethodFromClassFromLoadedMethod(PyObject *p_pModule, const std::string &p_rClass, const std::string &p_rMethod, const char *p_pExpr,...)
{
	PyObject		*pClass = PythonUtils::ImportClassFromLoadedModule(p_pModule, p_rClass), *pResult;
	va_list			pVarArgs;

	if (pClass == NULL)
		return (NULL);
	va_start(pVarArgs, p_pExpr);
	pResult = PythonUtils::CallMethodFromLoadedClass(pClass, p_rMethod, p_pExpr, pVarArgs);
	va_end(pVarArgs);
	return (pResult);
}

PyObject			*PythonUtils::CallMethodFromLoadedClass(PyObject *p_pClass, const std::string &p_rMethod, const char *p_pExpr, ...)
{
	PyObject		*pMethod, *pArgs, *pResult;
	va_list			pVarArgs;

	pMethod = PythonUtils::ImportMethodFromLoadedClass(p_pClass, p_rMethod);
	if (pMethod == NULL)
		return (NULL);
	va_start(pVarArgs, p_pExpr);
	pArgs = Py_BuildValue(p_pExpr, pVarArgs);
	va_end(pVarArgs);
	pResult = PyEval_CallObject(pMethod, pArgs);
	Py_DECREF(pMethod);
	Py_DECREF(pArgs);
	return (pResult);
}

void				PythonUtils::start()
{
	Py_Initialize();
}

void				PythonUtils::end()
{
	Py_Finalize();
}

PythonUtils::PythonUtils()
{
	return;
}

PythonUtils::~PythonUtils()
{
	return;
}
