/**
 * \file fxsystem.h
 * \brief System that controls the effects of the software.
 *
 * The effects system is the component that receives an audio track as input
 * and is responsible for applying all the effects specified by the user.
 *
 * Each effect is a plugin written in Python language, so this system is
 * responsible for making some convertions to allow the Python script to
 * process the audio input and generate a valid output.
 *
 * Each plugin output is the next plugin's input, until there is no other
 * effect in the list. In that case, it will return the ouput audio to the
 * audio system, so it can be played back to the user.
 */
#pragma once

#include <audio/audiosystem.h>
#include <audio/buffer.h>
#include <audio/core.h>
#include <audio/effects/profile.h>
#include <dsp/fouriertransform.h>

namespace AudioFX {

/**
 * \class FxSystem <audio/effects/fxsystem.h>
 * \brief System that controls the effects of the software.
 *
 * The effects system is the component that receives an audio track as input
 * and is responsible for applying all the effects specified by the user.
 *
 * Each effect is a plugin written in Python language, so this system is
 * responsible for making some convertions to allow the Python script to
 * process the audio input and generate a valid output.
 *
 * Each plugin output is the next plugin's input, until there is no other
 * effect in the list. In that case, it will return the ouput audio to the
 * audio system, so it can be played back to the user.
 *
 * \author Matheus Nogueira
 * \version 1.0
 */
class FxSystem
{
public:

    /**
     * Create a new effects system.
     */
    FxSystem(AudioSystem& audioSystem);

    /**
     * Destroy the effects system.
     */
    ~FxSystem();

    /**
     * Start the fx system.
     */
    void start();

    /**
     * Set data to be processed by the effects system.
     * \param input audio to be processed.
     */
    void append(SAMPLE_TYPE* input);

    /**
     * Function that will notify the audio system that all the samples passed
     * through the effects pipeline.
     * 
     * \param output audio output after the effects.
     */
    void onDataProcessed(SAMPLE_TYPE* output);


private:

    /**
     * Audio system that will be called when the effect process is over.
     */
    AudioSystem *audioSystem;

    /**
     * Object resposible for transform the audio before processing and
     * before returning it to the audio system.
     */
    FourierTransform *fourierTransform;

    /**
     * Indicate that the system is running.
     */
    bool running;

    /**
     * Buffer used to store data before it gets processed.
     */
    Buffer *buffer;

    /**
     * Active profile at the moment.
     */
    Profile *activeProfile;
};

}; // namespace