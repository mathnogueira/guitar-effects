/**
 * \file audiosystem.h
 * \brief Component that controls the audio flow.
 *
 * File containing the component responsible for controlling all the audio
 * functions of the system. It will delegate all the operations to other
 * components.
 */
#pragma once

#include <audio/buffer.h>
#include <audio/core.h>
#include <audio/inputstream.h>
#include <audio/outputstream.h>
#include <audio/effects/fxsystem.h>
#include <thread>

namespace AudioFX {

class FxSystem;

/**
 * \class AudioSystem <audio/audiosystem.h>
 * \brief Component that controls the audio flow in the system.
 *
 * The audio system is a component that will use other components (sub-systems)
 * to do things for it. Basically, we are going to use it as an easy interface
 * to manipulate the audio in the software.
 *
 * This system is responsible for turning on/off the recording, controlling
 * the order of effects that will be used in the audio sample, and will also
 * play the output audio and call other systems to store this data in a disk.
 *
 * \author Matheus Nogueira
 * \version 1.0
 */
class AudioSystem
{
public:

    /**
     * Create a new instance of the AudioSystem.
     */
    AudioSystem();

    /**
     * Destroy the AudioSystem and all of its components.
     */
    ~AudioSystem();

    /**
     * Start recording audio from the input device.
     */
    void startRecording();

    /**
     * Stop recording audio from the innput device.
     */
    void stopRecording();

    /**
     * Start playing the audio.
     */
    void startPlaying();

    /**
     * Stop playing the audio.
     */
    void stopPlaying();

    /**
     * Start recording and playing at the same time.
     */
    void start();

    /**
     * Function that is used as callback for the Effects System.
     */
    void onAudioProcessed(SAMPLE_TYPE* input);

private:

    /**
     * Input stream used to capture audio coming from an input device.
     */
    InputStream *inputStream;

    /**
     * Thread to run the input stream.
     */
    std::thread *inputThread;

    /**
     * Output stream used to reproduce audio samples from the software.
     */
    OutputStream *outputStream;

    /**
     * Thread to run the output stream.
     */
    std::thread *outputThread;

    /**
     * System that will apply effects to the audio captured by the input
     * stream.
     */
    FxSystem *effectSystem;

    /**
     * Thread to run the effects system.
     */
    std::thread *fxThread;

    /**
     * Buffer used to store the data to be played and stored.
     */
    Buffer buffer;

    /**
     * Function that is used as callback for the input stream.
     * \param buffer recorded samples.
     */
    void onAudioBufferReceived(SAMPLE_TYPE* buffer);
};

}; // namespace