#include <plugins/pyPlugin.h>
#include <iostream>

using namespace AudioFX;

PyPlugin::PyPlugin(const char* script)
{
    this->scriptFile = (char*) script;
}

PyPlugin::~PyPlugin()
{
    
}

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

void PyPlugin::importOptions()
{
    PyObject* pyOptions = PyObject_CallObject(this->fOptions, PyTuple_New(0));
    PyErr_Print();
    int numOptions = (int) PyList_Size(pyOptions);
    // Iterates through the list of options
    for (int i = 0; i < numOptions; ++i) {
        // Get item from the list
        PyObject* pyOption = PyList_GetItem(pyOptions, i);
        this->options.push_back(PluginOption::create(pyOption));
    }
}

void PyPlugin::applyOptions()
{
    unsigned int size = this->options.size();
    // Convert vector to list of tuples
    PyObject* list = PyList_New(0);
    // Convert each PluginOption into a tuple
    for (unsigned int i = 0; i < size; ++i) {
        PyList_Insert(list, i, this->options[i]->toPython());
    }
    PyObject* args = PyTuple_New(1);
    PyTuple_SetItem(args, 0, list);
    // Call configure method
    this->pyOptions = PyObject_CallObject(this->fConfigure, args);
    PyErr_Print();
}

void PyPlugin::execute()
{
    // Arguments for the function call
    PyObject* args = PyTuple_New(1);
    PyTuple_SetItem(args, 0, this->pyOptions);
    // Call the execute method from the python script
    PyObject_CallObject(this->fExecute, args);
    PyObject* args2 = PyTuple_New(1);
    PyTuple_SetItem(args2, 0, this->pyOptions);
    PyObject_CallObject(this->fExecute, args2);
    PyErr_Print();
};