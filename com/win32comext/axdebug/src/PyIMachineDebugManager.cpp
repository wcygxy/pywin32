// This file implements the IMachineDebugManager Interface and Gateway for Python.
// Generated by makegw.py

#include "stdafx.h"

#include "PyIMachineDebugManager.h"

// @doc - This file contains autoduck documentation
// ---------------------------------------------------
//
// Interface Implementation

PyIMachineDebugManager::PyIMachineDebugManager(IUnknown *pdisp) : PyIUnknown(pdisp) { ob_type = &type; }

PyIMachineDebugManager::~PyIMachineDebugManager() {}

/* static */ IMachineDebugManager *PyIMachineDebugManager::GetI(PyObject *self)
{
    return (IMachineDebugManager *)PyIUnknown::GetI(self);
}

// @pymethod |PyIMachineDebugManager|AddApplication|Description of AddApplication.
PyObject *PyIMachineDebugManager::AddApplication(PyObject *self, PyObject *args)
{
    IMachineDebugManager *pIMDM = GetI(self);
    if (pIMDM == NULL)
        return NULL;
    // @pyparm <o PyIRemoteDebugApplication>|pda||Description for pda
    PyObject *obpda;
    if (!PyArg_ParseTuple(args, "O:AddApplication", &obpda))
        return NULL;
    IRemoteDebugApplication *pda;
    BOOL bPythonIsHappy = TRUE;
    if (!PyCom_InterfaceFromPyInstanceOrObject(obpda, IID_IRemoteDebugApplication, (void **)&pda, FALSE /* bNoneOK */))
        bPythonIsHappy = FALSE;
    if (!bPythonIsHappy)
        return NULL;
    DWORD dwAppCookie;
    PY_INTERFACE_PRECALL;
    HRESULT hr = pIMDM->AddApplication(pda, &dwAppCookie);
    pda->Release();
    PY_INTERFACE_POSTCALL;
    if (FAILED(hr))
        return SetPythonCOMError(self, hr);

    PyObject *pyretval = Py_BuildValue("i", dwAppCookie);
    return pyretval;
}

// @pymethod |PyIMachineDebugManager|RemoveApplication|Description of RemoveApplication.
PyObject *PyIMachineDebugManager::RemoveApplication(PyObject *self, PyObject *args)
{
    IMachineDebugManager *pIMDM = GetI(self);
    if (pIMDM == NULL)
        return NULL;
    // @pyparm int|dwAppCookie||Description for dwAppCookie
    DWORD dwAppCookie;
    if (!PyArg_ParseTuple(args, "i:RemoveApplication", &dwAppCookie))
        return NULL;
    PY_INTERFACE_PRECALL;
    HRESULT hr = pIMDM->RemoveApplication(dwAppCookie);
    PY_INTERFACE_POSTCALL;
    if (FAILED(hr))
        return SetPythonCOMError(self, hr);
    Py_INCREF(Py_None);
    return Py_None;
}

// @pymethod |PyIMachineDebugManager|EnumApplications|Description of EnumApplications.
PyObject *PyIMachineDebugManager::EnumApplications(PyObject *self, PyObject *args)
{
    IMachineDebugManager *pIMDM = GetI(self);
    if (pIMDM == NULL)
        return NULL;
    if (!PyArg_ParseTuple(args, ":EnumApplications"))
        return NULL;
    IEnumRemoteDebugApplications *ppeda;
    PY_INTERFACE_PRECALL;
    HRESULT hr = pIMDM->EnumApplications(&ppeda);
    PY_INTERFACE_POSTCALL;
    if (FAILED(hr))
        return SetPythonCOMError(self, hr);

    return PyCom_PyObjectFromIUnknown(ppeda, IID_IEnumRemoteDebugApplications, FALSE);
}

// @object PyIMachineDebugManager|Description of the interface
static struct PyMethodDef PyIMachineDebugManager_methods[] = {
    {"AddApplication", PyIMachineDebugManager::AddApplication,
     1},  // @pymeth AddApplication|Description of AddApplication
    {"RemoveApplication", PyIMachineDebugManager::RemoveApplication,
     1},  // @pymeth RemoveApplication|Description of RemoveApplication
    {"EnumApplications", PyIMachineDebugManager::EnumApplications,
     1},  // @pymeth EnumApplications|Description of EnumApplications
    {NULL}};

PyComTypeObject PyIMachineDebugManager::type("PyIMachineDebugManager", &PyIUnknown::type,
                                             sizeof(PyIMachineDebugManager), PyIMachineDebugManager_methods,
                                             GET_PYCOM_CTOR(PyIMachineDebugManager));
// ---------------------------------------------------
//
// Gateway Implementation

STDMETHODIMP PyGMachineDebugManager::AddApplication(
    /* [in] */ IRemoteDebugApplication __RPC_FAR *pda,
    /* [out] */ DWORD __RPC_FAR *pdwAppCookie)
{
    PY_GATEWAY_METHOD;
    PyObject *obpda = PyCom_PyObjectFromIUnknown(pda, IID_IRemoteDebugApplication, TRUE);
    PyObject *result;
    HRESULT hr = InvokeViaPolicy("AddApplication", &result, "O", obpda);
    Py_XDECREF(obpda);
    if (FAILED(hr))
        return hr;
    // Process the Python results, and convert back to the real params
    if (!PyArg_Parse(result, "i", pdwAppCookie))
        return PyCom_HandlePythonFailureToCOM(/*pexcepinfo*/);
    Py_DECREF(result);
    return hr;
}

STDMETHODIMP PyGMachineDebugManager::RemoveApplication(
    /* [in] */ DWORD dwAppCookie)
{
    PY_GATEWAY_METHOD;
    HRESULT hr = InvokeViaPolicy("RemoveApplication", NULL, "i", dwAppCookie);
    return hr;
}

STDMETHODIMP PyGMachineDebugManager::EnumApplications(
    /* [out] */ IEnumRemoteDebugApplications __RPC_FAR *__RPC_FAR *ppeda)
{
    PY_GATEWAY_METHOD;
    if (ppeda == NULL)
        return E_POINTER;
    PyObject *result;
    HRESULT hr = InvokeViaPolicy("EnumApplications", &result);
    if (FAILED(hr))
        return hr;
    // Process the Python results, and convert back to the real params
    PyObject *obppeda;
    if (!PyArg_Parse(result, "O", &obppeda))
        return PyCom_HandlePythonFailureToCOM(/*pexcepinfo*/);
    BOOL bPythonIsHappy = TRUE;
    if (!PyCom_InterfaceFromPyInstanceOrObject(obppeda, IID_IEnumRemoteDebugApplications, (void **)ppeda,
                                               FALSE /* bNoneOK */))
        bPythonIsHappy = FALSE;
    if (!bPythonIsHappy)
        hr = PyCom_HandlePythonFailureToCOM(/*pexcepinfo*/);
    Py_DECREF(result);
    return hr;
}
