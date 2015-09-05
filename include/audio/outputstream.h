/**
 * \file outputstream.h
 * \brief Stream used to play audio tracks.
 *
 * Output streams are used to use the sound output device to play audio
 * tracks.
 */
#pragma once

#include <audio/buffer.h>
#include <audio/core.h>
#include <portaudio.h>
#include <iostream>

namespace AudioFX {

/**
 * \class OutputStream <audio/outputstream.h>
 * \brief Stream used to play audio tracks.
 *
 * Stream used to play audio tracks using data coming from the audio system.
 *
 * \author Matheus Nogueira
 * \version 1.0
 */
class OutputStream
{
public:

    /**
     * Initialize the output stream.
     * \param buffer reference to audio buffer.
     */
    OutputStream(Buffer& buffer);

    /**
     * Destroy the output stream.
     */
    ~OutputStream();

    /**
     * Add data to be played by this stream.
     * \param data data array to be appended to the stream.
     */
    void addOutput(SAMPLE_TYPE* data);

    /**
     * Starts playing the audio appended to the stream.
     */
    void play();

    /**
     * Stop playing the audio.
     */
    void pause();

    /**
     * Callback function that will be used to play the audio data that was
     * added to the stream earlier.
     *
     * \param inputBuffer input audio buffer
     * \param outputBuffer output audio buffer (it will not be used)
     * \param framesPerBuffer number of frames contained in the audio sample
     * \param timeinfo not used by this callback
     * \param statusFlags not used by this callback
     * \param userData pointer to the "this" reference of the class.
     *
     * \return stream status
     */
    static int playingCallback(
            const void* inputBuffer,
            void* outputBuffer,
            unsigned long framesPerBuffer,
            const PaStreamCallbackTimeInfo* timeinfo,
            PaStreamCallbackFlags statusFlags,
            void* userData);

    /**
     * Get buffer pointer.
     * \return pointer to the buffer.
     */
    Buffer* getBuffer() { return this->buffer; }

    /**
     * Get stream status
     * \return true if stream is active.
     */
    bool isPlaying() { return this->playing; }

private:

    /**
     * Setup the stream.
     */
    void setup();

    /*!
     * Portaudio stream
     */
    PaStream* stream;

     /*!
     * Output parameters used to play audio
     */
    PaStreamParameters outputParameters;

    /**
     * Buffer used to store the data that should be played.
     */
    Buffer *buffer;

    /**
     * Flag that indicates that the stream should still play the data
     * coming from the buffer.
     */
    bool playing;
};

}; // namespace