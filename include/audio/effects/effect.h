/**
 * \file effect.h
 * \brief Effect to be applied to the audio.
 *
 * Effect that will be applied to an audio track.
 */
#pragma once

#include <audio/buffer.h>
#include <audio/core.h>
#include <plugins/pyPlugin.h>

namespace AudioFX {

class Profile;

/**
 * \class Effect <audio/effects/effect.h>
 * \brief Audio effect that will be applied to the input audio.
 *
 * This is a class that will load a Python script (audio effect) that
 * will apply the changes to the audio track.
 *
 * \author Matheus Nogueira
 * \version 1.0
 */
class Effect
{

public:

    /**
     * Create a new effect.
     * \param callback function that will be called when the effect is applied.
     */
    Effect(void (Profile::*callback)(SAMPLE_TYPE*));

    /**
     * Destroy the effect..
     */
    ~Effect();

    /**
     * Start running the effect.
     */
    void start();

    /**
     * Apply effect to an audio track.
     * \param input audio track.
     */
    void apply(SAMPLE_TYPE* input);

private:

    /**
     * Python plugin that will apply the effect.
     */
    PyPlugin *plugin;

    /**
     * Buffer that is used by the effect.
     */
    Buffer *buffer;

    /**
     * Indicates that the effect is still active.
     */
    bool running;

    /**
     * Call python plugin to apply the effect on the audio track.
     * \param input audio data.
     */
    void callPlugin(SAMPLE_TYPE* input);
};

}; // namespace