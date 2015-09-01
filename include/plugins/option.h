/**
 * \file option.h
 * \brief C++ structure to represent an option of a plugin.
 *
 */
#pragma once

// Require python 3.4
#include <python3.4/Python.h>

namespace AudioFX {

/**
 * Enumerate that represents the type of option.
 * For example, some options are ON/OFF, while others are based on scales.
 * So, this enumerate is used to represent that.
 *
 * \author Matheus Nogueira
 * \version 1.0
 */
enum OptionType
{
    ON_OFF,         ///< Represent a boolean option
    INT_SCALE,      ///< Represent an integer scale (0,1,2,...,999,1000)
};

/**
 * \class PluginOption <plugins/option.h>
 * \brief Structure to store an option of a plugin.
 *
 * Plugins options are numeric values that change the behavior of the plugin.
 *
 * \author Matheus Nogueira.
 * \version 1.0
 */
class PluginOption
{
public:

    /**
     * Name of the option.
     */
    const char* name;

    /**
     * Inferior limit for the option.
     */
    const long minValue;

    /**
     * Superior limit for the option.
     */
    const long maxValue;

    /**
     * Type of the option.
     */
    const OptionType type;

    /**
     * Create a new option.
     *
     * \param opName option name
     * \param min minimum value
     * \param max maximum value
     * \param opType type of option
     */
    PluginOption(const char* opName, long min, long max, OptionType opType);

    /**
     * Define value for the option.
     * \param value new value for the option.
     */
    void setValue(long value)
    {
        this->currentValue = value;
    }

    /**
     * Get the current value for the option.
     * \return value for the option.
     */
    long getValue()
    {
        return this->currentValue;
    }

    /**
     * Create an option using a Python Object as data.
     * 
     * \param data python object that contains the option data.
     * \return pointer to option filled with data.
     */
    static PluginOption* create(PyObject* data);

    /**
     * Create a Python object from its content.
     *
     * \return python tuple.
     */
    PyObject* toPython();
    
private:

    /**
     * Current value for the option.
     */
    long currentValue;

};

}; // namespace