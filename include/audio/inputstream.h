/**
 * \file inputstream.h
 * \brief Stream of audio capture.
 *
 * Stream used to capture audio from an input device.
 */
#pragma once

#include <audio/core.h>
// Requires portaudio to work
#include <portaudio.h>

namespace AudioFX {

class AudioSystem;

/**
 * \class InputStream <audio/inputstream.h>
 * \brief Stream used to capture audio from an input device.
 *
 * An input stream is a structure used to initialize an input device that
 * will capture audio from the user. It will not do anything other than that. So,
 * it will work with callbacks that will communicate with the audio system. 
 *
 * The audio system is responsible for doing things with the captured audio.
 *
 * \author Matheus Nogueira
 * \version 1.0
 */
class InputStream
{
public:

    /**
     * Create a new input stream.
     */
    InputStream(AudioSystem &audioSystem);

    /**
     * Destroy the input stream.
     */
    ~InputStream();

    /**
     * Start recording audio with the input stream.
     *
     * \param callback function that will be called when the buffer is full.
     */
    void record(void (AudioSystem::*callback)(SAMPLE_TYPE*));

    /**
     * Pause recording.
     */
    void pause();

    /**
     * Function that will receive the data recorded by the input device.
     *
     * \param inputBuffer input audio buffer
     * \param outputBuffer output audio buffer (it will not be used)
     * \param framesPerBuffer number of frames contained in the audio sample
     * \param timeinfo not used by this callback
     * \param statusFlags not used by this callback
     * \param userData pointer to the "this" reference of the class.
     *
     * \return recording status
     */
    static int recordingCallback(
            const void* inputBuffer,
            void* outputBuffer,
            unsigned long framesPerBuffer,
            const PaStreamCallbackTimeInfo* timeinfo,
            PaStreamCallbackFlags statusFlags,
            void* userData);

    /**
     * Check if the stream is recording data.
     * \return recording status
     */
    bool isRecording() { return this->recording; }

    /**
     * Return the callback function pointer.
     * \return callback function.
     */
    void (AudioSystem::*getCallback())(SAMPLE_TYPE*) { return this->callback; }

    /**
     * Get pointer to the audio system
     * \return pointer to audio system.
     */
    AudioSystem* getAudioSystem() { return this->audioSystem; }

private:

    /// Flag that indicates that we are recording audio at the moment.
    bool recording;

    /// Callback function that will be called while recording.
    void (AudioSystem::*callback)(SAMPLE_TYPE*);

    /// Input parameters used by PortAudio
    PaStreamParameters inputParameters;

    /// PortAudio stream
    PaStream* stream;

    /// Audio system reference
    AudioSystem *audioSystem;

    /**
     * Setup the portaudio library, so it can start recording.
     */
    bool setup();
};

}; // namespace