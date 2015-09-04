#include <audio/inputstream.h>
#include <cstdlib>
#include <iostream>

using namespace AudioFX;

InputStream::InputStream(AudioSystem &audioSystem)
{
    this->setup();
    this->audioSystem = &audioSystem;
}

InputStream::~InputStream()
{
    // Close steam
    PaError err = Pa_CloseStream(stream);
    if (err != paNoError)
    {
        std::cout << "Pa_CloseStream error: " << Pa_GetErrorText(err) << std::endl;
    }
}

void InputStream::record(void (AudioSystem::*callback)(SAMPLE_TYPE*))
{
    this->callback = callback;
    this->recording = true;

    PaError err;
    // Open stream
    err = Pa_OpenStream(&stream, &inputParameters, NULL, SAMPLES_PER_SECOND, INTERNAL_AUDIO_BUFFER_SIZE, paClipOff, recordingCallback, this);
    if (err != paNoError)
    {
        std::cout << "Pa_OpenStream error: " << Pa_GetErrorText(err) << std::endl;
        return;
    }

    err = Pa_StartStream(stream);
    if (err != paNoError)
    {
        std::cout << "Pa_StartStream error: " << Pa_GetErrorText(err) << std::endl;
        return;
    }
    // Record all samples
    while ( (err = Pa_IsStreamActive(stream) ) == 1)
    {
        Pa_Sleep(1000);
    }
}

void InputStream::pause()
{
    this->recording = false;
}

bool InputStream::setup()
{
    // Initialize portaudio
    PaError err = Pa_Initialize();
    if (err != paNoError)
    {
        std::cout << "Pa_Initialize error: " << Pa_GetErrorText(err) << std::endl;
        return false;
    }
    // Setup input device
    inputParameters.device = Pa_GetDefaultInputDevice();
    // Check for error
    if (inputParameters.device == paNoDevice)
    {
        std::cout << "Error: No default input defice found" << std::endl;
        return false;
    }
    inputParameters.channelCount = NUMBER_CHANNELS;
    inputParameters.sampleFormat = paFloat32;
    inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputParameters.device)->defaultLowInputLatency;
    inputParameters.hostApiSpecificStreamInfo = NULL;

    return true;
}

int InputStream::recordingCallback(
            const void* inputBuffer,
            void* outputBuffer,
            unsigned long framesPerBuffer,
            const PaStreamCallbackTimeInfo* timeinfo,
            PaStreamCallbackFlags statusFlags,
            void* userData)
{
    // userData is the "this" reference to the stream that is recording
    InputStream* inputStream = (InputStream*) userData;
    // Copy buffer into another variable
    SAMPLE_TYPE* buffer = new SAMPLE_TYPE[framesPerBuffer];
    SAMPLE_TYPE* input = (SAMPLE_TYPE*) inputBuffer;
    for (unsigned int i = 0; i < framesPerBuffer; ++i)
        buffer[i] = input[i];
    // Call callback function with the buffer
    void (AudioSystem::*callback)(SAMPLE_TYPE*) = inputStream->getCallback();
    AudioSystem *audioSystem = inputStream->getAudioSystem();
    // Call the callback function from the audioSystem object
    (*audioSystem.*callback)(buffer);
    // If we are still recording, return continue flag
    // otherwise, return complete flag
    return inputStream->isRecording() ? paContinue : paComplete;
}