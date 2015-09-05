#include <audio/effects/effect.h>

using namespace AudioFX;

Effect::Effect(void (Profile::*callback)(SAMPLE_TYPE*)) {}

Effect::~Effect() {}

void Effect::start()
{
    this->running = true;
    while (this->running) {
        // Check if there is data to process
        if (this->buffer->hasNewData()) {
            // Call external plugin to process this data
            this->callPlugin(this->buffer->getNextChunk());
        }
    }
}

void Effect::apply(SAMPLE_TYPE* input)
{

}

void Effect::callPlugin(SAMPLE_TYPE* input)
{
    
}