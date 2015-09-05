#include <audio/effects/fxsystem.h>
#include <iostream>
#include <cstdlib>

using namespace AudioFX;

FxSystem::FxSystem(AudioSystem& audioSystem)
{
    this->audioSystem = &audioSystem;
    this->buffer = new Buffer();
    this->activeProfile = new Profile("Metallica");
    this->fourierTransform = new FourierTransform();
}

FxSystem::~FxSystem() {
    delete this->activeProfile;
    delete this->buffer;
    delete this->fourierTransform;
}

void FxSystem::start()
{
    while (this->running) {
        // Only process new data
        if (this->buffer->hasNewData()) {
            this->activeProfile->applyEffects(this->buffer->getNextChunk(), &FxSystem::onDataProcessed, this);
        }
    }
}

void FxSystem::append(SAMPLE_TYPE* input)
{
    SAMPLE_TYPE* output;
    // Transform audio into frequency-based information
    this->fourierTransform->time2frequency(input, &output);
    delete[] input;
    this->buffer->insert(output, INTERNAL_AUDIO_BUFFER_SIZE);
}

void FxSystem::onDataProcessed(SAMPLE_TYPE* output)
{
    SAMPLE_TYPE *audio;
    // Transform output into time-based information
    this->fourierTransform->frequency2time(output, &audio);
    delete[] output;
    this->audioSystem->onAudioProcessed(audio);
}