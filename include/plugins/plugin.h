/**
 * \file pyPlugin.h
 * \brief Abstract plugin used by the software.
 */
#pragma once

namespace AudioFX {

/**
 * \class Plugin <plugins/plugin.h>
 * \brief Abstract plugin for the software.
 * 
 * Should write it later.
 *
 * \author Matheus Nogueira.
 * \version 1.0
 */
class Plugin
{

public:

    virtual ~Plugin();

    /**
     * Initialize the plugin.
     */
    virtual void initialize() = 0;

    /**
     * Execute plugin.
     */
    virtual void execute() = 0;

};

}; // namespace