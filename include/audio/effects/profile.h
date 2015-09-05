/**
 * \file profile.h
 * \brief Set of combined effects that will be applied to the audio.
 *
 * File containing the Profile class.
 */
#pragma once

#include <audio/core.h>
#include <audio/effects/effect.h>
#include <vector>
#include <thread>

namespace AudioFX {

class FxSystem;

/**
 * \class Profile <audio/effects/profile.h>
 * \brief Set of effects that will be applied to the audio.
 *
 * Profiles are an easy way to combine effects. A profile is a combination
 * of effects that have different configurations and are identified by a
 * name.
 *
 * So, lets say you have awesome effects installed and you want to play
 * Metallica, you will create a profile called "Metallica" and configure
 * each of those effects to make it sound like Metallica.
 *
 * \author Matheus Nogueira
 * \version 1.0
 */
class Profile
{
public:

    /**
     * Create a new profile.
     * \param name name of the profile.
     */
    Profile(const char* name);

    /**
     * Destroy the profile instance.
     */
    ~Profile();

    /**
     * Apply all the effects in an audio track.
     * \param input audio track.
     * \param callback function that will be called when the finished.
     */
    void applyEffects(SAMPLE_TYPE* input, void (FxSystem::*callback)(SAMPLE_TYPE*), FxSystem* fxSystem);

    /**
     * Apply one effect on an audio track.
     * \param input audio track
     */
    void applyEffect(SAMPLE_TYPE* input);

private:

    /**
     * Name of the profile.
     */
    char* name;

    /**
     * List of threads that will apply effects to the audio.
     */
    std::vector<std::thread*> fxThreads;

    /**
     * List of effects that will be applied to the audio.
     */
    std::vector<Effect*> effects;

    /**
     * Index of the next effect to be applied.
     */
    unsigned int nextEffectIndex;

    /**
     * Instance of FxSystem that is controlling this profile.
     */
    FxSystem* fxSystem;

    /**
     * Callback function that will be called when the profile finishes
     * applying all the effects on an audio sample.
     */
    void (FxSystem::*callback)(SAMPLE_TYPE*);
};

} // namespace