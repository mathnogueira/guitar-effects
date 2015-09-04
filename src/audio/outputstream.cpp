#include <audio/outputstream.h>

using namespace AudioFX;

OutputStream::OutputStream(Buffer& buffer)
{
    // Set buffer
    this->buffer = &buffer;
    // Initialize portaudio
    this->setup();
}

OutputStream::~OutputStream()
{
    // Close steam
    PaError err = Pa_CloseStream(stream);
    if (err != paNoError)
    {
        std::cout << "Pa_CloseStream error: " << Pa_GetErrorText(err) << std::endl;
        return;
    }
}

void OutputStream::setup()
{
    // Initialize portaudio
    PaError err = Pa_Initialize();
    if (err != paNoError)
    {
        std::cout << "Pa_Initialize error: " << Pa_GetErrorText(err) << std::endl;
        return;
    }
    // Setup output device
    outputParameters.device = Pa_GetDefaultOutputDevice();
    // Check for error
    if (outputParameters.device == paNoDevice)
    {
        std::cout << "Error: No default output defice found" << std::endl;
        return;
    }
    outputParameters.channelCount = NUMBER_CHANNELS;
    outputParameters.sampleFormat = paFloat32;
    outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;
}

void OutputStream::addOutput(SAMPLE_TYPE* data)
{
    // Add data to the buffer
    this->buffer->insert(data, INTERNAL_AUDIO_BUFFER_SIZE);
}

void OutputStream::play()
{
    std::cout << "Audio playing!" << std::endl;
    this->playing = true;
    PaError err;
    err = Pa_OpenStream(&stream, NULL, &outputParameters, SAMPLES_PER_SECOND, INTERNAL_AUDIO_BUFFER_SIZE, paClipOff, playingCallback, this);
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

    while ( (err = Pa_IsStreamActive(stream) ) == 1 ) Pa_Sleep(1000);
}

void OutputStream::pause()
{
    this->playing = false;
}

int OutputStream::playingCallback(
            const void* inputBuffer,
            void* outputBuffer,
            unsigned long framesPerBuffer,
            const PaStreamCallbackTimeInfo* timeinfo,
            PaStreamCallbackFlags statusFlags,
            void* userData)
{
    OutputStream* outputStream = (OutputStream*) userData;
    Buffer* buffer = outputStream->getBuffer();
    SAMPLE_TYPE* output = (SAMPLE_TYPE*) outputBuffer;
    // Play audio while we still new data in the buffer
    if (buffer->hasNewData()) {
        // Get a chunk of data
        SAMPLE_TYPE* data = buffer->getNextChunk();
        // Copy data from buffer to output
        for (unsigned int i = 0; i < INTERNAL_AUDIO_BUFFER_SIZE; ++i)
            output[i] = data[i];
    }
    // Check if it is still playing
    if (outputStream->isPlaying())
        return paContinue;
    return paComplete;
}