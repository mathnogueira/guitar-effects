/**
 * \file pyPlugin.h
 * \brief Plugin that is writen in python language.
 *
 * Module that will call plugins written in Python.
 */
#pragma once

// Requires Python 3.4
#include <python3.4/Python.h>
#include <plugins/plugin.h>

namespace AudioFX {

/**
 * \class PyPlugin <plugins/pyPlugin.h>
 * \brief Plugin that is writen in Python 3.4.
 * 
 * Plugin that will load a python script to do something. This is an easy way
 * to write plugins to the software. Using Python, we make it even easier to
 * write new sound effects and the new collaborators don't need to learn a new
 * language to do so.
 *
 * \author Matheus Nogueira.
 * \version 1.0
 */
class PyPlugin : public Plugin
{

public:

    /**
     * Create a new plugin.
     * \param script path to the script that has the plugin implementation.
     */
    PyPlugin(const char* script);

    ~PyPlugin();

    /**
     * Initialize the plugin.
     */
    void initialize();

    /**
     * Get options of plugin.
     */
    void getOptions();

    /**
     * Define values for each option of the plguin.
     */
    void applyOptions();

    /**
     * Execute plugin.
     */
    void execute();

private:

    /**
     * Script that is being used by the plugin.
     */
    char* scriptFile = NULL;

    /**
     * Plugin options.
     */
    PyObject *options;

    /**
     * Function that says the options of the plugin.
     *
     * You must be asking: what are these options? Each sound effect have
     * different options. For example, for an AMP, you will have Low, Mid and
     * High, while, in a delay pedal, you have time delay.
     *
     * This is used to configure the effect in the way the user wants.
     */
    PyObject *fOptions;

    /**
     * Function that will be used to define the options choosen by the user.
     * This function will change the way the plugin will execute.
     */ 
    PyObject *fConfigure;

    /**
     * Function that will be called when the user request an effect in the
     * sound. 
     *
     * It will receive the options choosen by the user and a sound track to
     * be changed based on the choosen options.
     *
     */
    PyObject *fExecute;
};

}; // Namespace