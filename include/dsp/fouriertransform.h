/**
 * \file fouriertransform.h
 * \brief Structure used to transform audio tracks using fourier transforms.
 *
 * This structure will transform audio tracks (time-magnitude) into sound
 * spectrum (frequency-magnitude) and vice-versa.
 */
#pragma once

namespace AudioFX {

#include <audio/core.h>
#include <fftw3.h>

/**
 * \class FourierTransform <dsp/fouriertransform.h>
 * \brief Class used to transform audio signals
 *
 * Transform an audio track into its spectrum, so the effects can be
 * applied using the frequencies of the track. 
 *
 * \author Matheus Nogueira
 * \version 1.0
 */
class FourierTransform
{
public:

    /**
     * Create a new fourier transform interface.
     */
    FourierTransform();

    /**
     * Destroy the fourier transform interface.
     */
    ~FourierTransform();

    /**
     * Transform an audio track into its frequency-magnitude representation.
     * \param input audio data to be transformed.
     * \param output pointer to the output data
     */
    void time2frequency(SAMPLE_TYPE* input, SAMPLE_TYPE** output);

    /**
     * Transform an audio track that is frequency-magnitude into time-magnitude.
     * \param input audio frequency-based to be transformed
     * \param output pointer to the output audio.
     */
    void frequency2time(SAMPLE_TYPE* input, SAMPLE_TYPE** output);

private:

    /**
     * Plan that will be used to do the transform time into frequency.
     */
    fftwf_plan plan_t2f;

    /**
     * Plan that will be used to do the transform frequency into time.
     */
    fftwf_plan plan_f2t;

};

}; // namespace