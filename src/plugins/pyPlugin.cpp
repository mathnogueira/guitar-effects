#include <plugins/pyPlugin.h>
#include <iostream>

using namespace AudioFX;

PyPlugin::PyPlugin(const char* script)
{
    this->scriptFile = (char*) script;
}

PyPlugin::~PyPlugin() {}

void PyPlugin::initialize()
{
    PyObject *pName, *pModule;
    // Initialize python interpretor
    Py_Initialize();
    // Update sys.path
    // Add folder plugins to it.
    PyRun_SimpleString("import sys\nsys.path.append('./plugins/')");
    pName = PyUnicode_FromString(this->scriptFile);
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);
    // Check if module was loaded ok.
    if (pModule != NULL) {
        // Try to find the functions of the module.
        this->fOptions = PyObject_GetAttrString(pModule, "options");
        this->fConfigure = PyObject_GetAttrString(pModule, "configure");
        this->fExecute = PyObject_GetAttrString(pModule, "execute");
        if (!this->fOptions || !this->fConfigure || !this->fExecute)
            PyErr_Print();
    } else {
        std::cout << "Module " << this->scriptFile << " not found!" << std::endl;
    }
}

void PyPlugin::getOptions()
{
    this->options = PyObject_CallObject(this->fOptions, PyTuple_New(0));
    // Convert the python object to a C++ object
    // TODO:
    //        - Convert the list of tuples to a C++ structure (array of a class)
    //        - Return this structure.
}

void PyPlugin::applyOptions() {}

void PyPlugin::execute() {};