#include <audio/effects/profile.h>
#include <iostream>

using namespace AudioFX;

Profile::Profile(const char* name) {}

Profile::~Profile() {}

void Profile::applyEffects(SAMPLE_TYPE* input, void (FxSystem::*callback)(SAMPLE_TYPE*), FxSystem* fxSystem)
{
    this->callback = callback;
    this->fxSystem = fxSystem;
    // Apply first effect on the audio
    this->nextEffectIndex = 0;
    this->applyEffect(input);
}

void Profile::applyEffect(SAMPLE_TYPE* input)
{
    // Check if index is valid, if not, notify end of effects
    if (nextEffectIndex == this->effects.size()) {
        // Notify FxSystem
        (*fxSystem.*callback)(input);
        return;
    }
    // Apply effect
    this->effects[nextEffectIndex]->apply(input);
}