#include <audio/audiosystem.h>
#include <iostream>

AudioSystem::AudioSystem()
{
    this->inputStream = new InputStream(*this);
    this->outputStream = new OutputStream(this->buffer);
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

    inputThread->join();
    outputThread->join();
}

void AudioSystem::onAudioBufferReceived(SAMPLE_TYPE* buffer)
{
    //std::cout << buffer[0] << " --> " << buffer[INTERNAL_AUDIO_BUFFER_SIZE-1] << std::endl;
    this->outputStream->addOutput(buffer);
}