#include <plugins/option.h>
#include <cstring>

using namespace AudioFX;

PluginOption::PluginOption(const char* opName, long min, long max, OptionType opType):
    name(opName), minValue(min), maxValue(max), type(opType)
{
    this->currentValue = 0;
}

PluginOption* PluginOption::create(PyObject* data)
{
    const char *name, *type;
    long min, max;
    OptionType opType;

    // Extract tuple information
    // (name, min, max, type)
    PyObject* optionName = PyDict_GetItem(data, PyUnicode_FromString("name"));
    PyObject* optionMin = PyDict_GetItem(data, PyUnicode_FromString("min"));
    PyObject* optionMax = PyDict_GetItem(data, PyUnicode_FromString("max"));
    PyObject* optionType = PyDict_GetItem(data, PyUnicode_FromString("type"));
    // Convert to C++ types
    // name as char*
    name = PyUnicode_AsUTF8(optionName);
    // min as long
    min = PyLong_AsLong(optionMin);
    // max as long
    max = PyLong_AsLong(optionMax);
    // type as char*
    type = PyUnicode_AsUTF8(optionType);
    // Now, we have to create an instance of PluginOption using
    // the information that we got from Python
    // First of all, lets convert the last string to an OptionType

    if (strcmp("boolean", type) == 0) {
        opType = ON_OFF;
    } else if (strcmp("int_scale", type) == 0) {
        opType = INT_SCALE;
    } else {
        // Error
    }
    return new PluginOption(name, min, max, opType);
}

PyObject* PluginOption::toPython()
{
    // Create a dict
    PyObject* dict = PyDict_New();
    // Convert C++ types to python types
    // Name
    PyObject* name = PyUnicode_FromString(this->name);
    // Min
    PyObject* min = PyLong_FromLong(this->minValue);
    // Max
    PyObject* max = PyLong_FromLong(this->maxValue);
    // Current value
    PyObject* current = PyLong_FromLong(this->currentValue);
    // type
    const char* typeString;
    if (this->type == ON_OFF)
        typeString = "boolean";
    else if (this->type == INT_SCALE)
        typeString = "int_scale";
    PyObject* type = PyUnicode_FromString(typeString);
    // Add items to the tuple
    PyDict_SetItemString(dict, "name", name);
    PyDict_SetItemString(dict, "min", min);
    PyDict_SetItemString(dict, "max", max);
    PyDict_SetItemString(dict, "type", type);
    PyDict_SetItemString(dict, "value", current);
    return dict;
}