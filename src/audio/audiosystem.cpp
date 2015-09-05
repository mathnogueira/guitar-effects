#include <audio/audiosystem.h>
#include <iostream>

using namespace AudioFX;

AudioSystem::AudioSystem()
{
    this->inputStream = new InputStream(*this);
    this->outputStream = new OutputStream(this->buffer);
    this->effectSystem = new FxSystem(*this);
}

AudioSystem::~AudioSystem()
{
    delete this->inputStream;
    delete this->outputStream;
    delete this->inputThread;
}

void AudioSystem::startRecording()
{
    inputThread = new std::thread(&InputStream::record, inputStream, &AudioSystem::onAudioBufferReceived);
    inputThread->join();
}

void AudioSystem::stopRecording()
{
    inputStream->pause();
}

void AudioSystem::startPlaying()
{
    outputThread = new std::thread(&OutputStream::play, outputStream);
    outputThread->join();
}

void AudioSystem::stopPlaying()
{
    outputStream->pause();
}

void AudioSystem::start()
{
    inputThread = new std::thread(&InputStream::record, inputStream, &AudioSystem::onAudioBufferReceived);
    outputThread = new std::thread(&OutputStream::play, outputStream);
    fxThread = new std::thread(&FxSystem::start, effectSystem);

    inputThread->join();
    outputThread->join();
    fxThread->join();
}

void AudioSystem::onAudioBufferReceived(SAMPLE_TYPE* buffer)
{
    //std::cout << buffer[0] << " --> " << buffer[INTERNAL_AUDIO_BUFFER_SIZE-1] << std::endl;
    this->effectSystem->append(buffer);
}

void AudioSystem::onAudioProcessed(SAMPLE_TYPE* input) 
{
    this->outputStream->addOutput(input);
}