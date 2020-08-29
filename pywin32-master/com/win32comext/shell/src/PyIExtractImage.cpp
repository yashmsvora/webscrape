// This file implements the IExtractImage Interface for Python.
// Generated by makegw.py

#include "shell_pch.h"
#include "PyWinTypes.h"
#include "PyIExtractImage.h"

#define elementsof(array) (sizeof(array) / sizeof((array)[0]))

BOOL PyWinObject_AsSIZE(PyObject *obsize, SIZE *psize);
PyObject *PyWinObject_FromSIZE(PSIZE psize);

PyObject *PyWinObject_FromSIZE(PSIZE psize) { return Py_BuildValue("ll", psize->cx, psize->cy); }

BOOL PyWinObject_AsSIZE(PyObject *obsize, SIZE *psize)
{
    if (!PyTuple_Check(obsize)) {
        PyErr_SetString(PyExc_TypeError, "SIZE must be a tuple of 2 ints (x,y)");
        return FALSE;
    }
    return PyArg_ParseTuple(obsize, "ll;SIZE must be a tuple of 2 ints (x,y)", &psize->cx, &psize->cy);
}

// @doc - This file contains autoduck documentation
// ---------------------------------------------------
//
// Interface Implementation

PyIExtractImage::PyIExtractImage(IUnknown *pdisp) : PyIUnknown(pdisp) { ob_type = &type; }

PyIExtractImage::~PyIExtractImage() {}

/* static */ IExtractImage *PyIExtractImage::GetI(PyObject *self) { return (IExtractImage *)PyIUnknown::GetI(self); }

// @pymethod |PyIExtractImage|GetLocation|Description of GetLocation.
PyObject *PyIExtractImage::GetLocation(PyObject *self, PyObject *args)
{
    IExtractImage *pIEI = GetI(self);
    if (pIEI == NULL)
        return NULL;
    DWORD dwPriority;
    // @pyparm int|dwPriority||Description for dwPriority
    SIZE rgSize;
    PyObject *obrgSize;
    // @pyparm (int, int)|size||Description for prgSize
    // @pyparm int|dwRecClrDepth||Description for dwRecClrDepth
    DWORD dwFlags;
    // @pyparm int|pdwFlags||Description for pdwFlags
    WCHAR pszPathBuffer[255];
    DWORD dwRecClrDepth;
    if (!PyArg_ParseTuple(args, "lOll:GetLocation", &dwPriority, &obrgSize, &dwRecClrDepth, &dwFlags))
        return NULL;
    BOOL bPythonIsHappy = TRUE;
    // if (bPythonIsHappy && !PyInt_Check(obdwPriority)) bPythonIsHappy = FALSE;
    if (bPythonIsHappy && !PyWinObject_AsSIZE(obrgSize, &rgSize))
        bPythonIsHappy = FALSE;
    // if (bPythonIsHappy && !PyInt_Check(obdwFlags)) bPythonIsHappy = FALSE;
    if (!bPythonIsHappy)
        return NULL;
    // dwPriority = PyInt_AsLong(obdwPriority);
    // dwFlags = PyInt_AsLong(obdwFlags);
    HRESULT hr;
    PY_INTERFACE_PRECALL;
    hr = pIEI->GetLocation(pszPathBuffer, elementsof(pszPathBuffer), &dwPriority, &rgSize, dwRecClrDepth, &dwFlags);

    PY_INTERFACE_POSTCALL;

    if (FAILED(hr))
        return PyCom_BuildPyException(hr, pIEI, IID_IExtractImage);
    PyObject *obpszPathBuffer;

    obpszPathBuffer = MakeOLECHARToObj(pszPathBuffer);
    PyObject *pyretval = Py_BuildValue("O", obpszPathBuffer);
    CoTaskMemFree(pszPathBuffer);
    Py_XDECREF(obpszPathBuffer);
    return pyretval;
}

// @pymethod |PyIExtractImage|Extract|Description of Extract.
PyObject *PyIExtractImage::Extract(PyObject *self, PyObject *args)
{
    IExtractImage *pIEI = GetI(self);
    if (pIEI == NULL)
        return NULL;
    HBITMAP hBmpThumbnail;
    HRESULT hr;
    PY_INTERFACE_PRECALL;
    hr = pIEI->Extract(&hBmpThumbnail);

    PY_INTERFACE_POSTCALL;

    if (FAILED(hr))
        return PyCom_BuildPyException(hr, pIEI, IID_IExtractImage);

    return PyWinObject_FromHANDLE((HANDLE)hBmpThumbnail);
    // return Py_BuildValue("i", hBmpThumbnail);
    // return PyLong_FromVoidPtr((void*)hBmpThumbnail);
    // return PyString_FromString((char*)hBmpThumbnail);
}

// @object PyIExtractImage|Description of the interface
static struct PyMethodDef PyIExtractImage_methods[] = {
    {"GetLocation", PyIExtractImage::GetLocation, 1},  // @pymeth GetLocation|Description of GetLocation
    {"Extract", PyIExtractImage::Extract, 1},          // @pymeth Extract|Description of Extract
    {NULL}};

PyComTypeObject PyIExtractImage::type("PyIExtractImage", &PyIUnknown::type, sizeof(PyIExtractImage),
                                      PyIExtractImage_methods, GET_PYCOM_CTOR(PyIExtractImage));
