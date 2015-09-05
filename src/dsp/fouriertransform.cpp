#include <dsp/fouriertransform.h>

using namespace AudioFX;

FourierTransform::FourierTransform()
{
    
}

FourierTransform::~FourierTransform() {}

void FourierTransform::time2frequency(SAMPLE_TYPE* input, SAMPLE_TYPE** output)
{
    // Allocate output memory
    *output = new SAMPLE_TYPE[INTERNAL_AUDIO_BUFFER_SIZE];
    SAMPLE_TYPE *fourierOut = (SAMPLE_TYPE*) fftwf_malloc(sizeof(SAMPLE_TYPE) * INTERNAL_AUDIO_BUFFER_SIZE);
    // Create the plan
    plan_t2f = fftwf_plan_r2r_1d(INTERNAL_AUDIO_BUFFER_SIZE, (float*) input, (float*) fourierOut, FFTW_R2HC, FFTW_ESTIMATE);
    // Execute plan
    fftwf_execute(plan_t2f);
    // Normalize the output
    for (unsigned int i = 0; i < INTERNAL_AUDIO_BUFFER_SIZE; ++i)
        // Copy normalized output
        (*output)[i] = fourierOut[i] / INTERNAL_AUDIO_BUFFER_SIZE;
    // Destroy output
    fftwf_free(fourierOut);
    // Destroy the plan
    fftwf_destroy_plan(plan_t2f);
}

void FourierTransform::frequency2time(SAMPLE_TYPE* input, SAMPLE_TYPE** output)
{
    // Allocate output memory
    *output = new SAMPLE_TYPE[INTERNAL_AUDIO_BUFFER_SIZE];
    SAMPLE_TYPE *fourierOut = (SAMPLE_TYPE*) fftwf_malloc(sizeof(SAMPLE_TYPE) * INTERNAL_AUDIO_BUFFER_SIZE);
    // Create the plan
    plan_f2t = fftwf_plan_r2r_1d(INTERNAL_AUDIO_BUFFER_SIZE, (float*) input, (float*) fourierOut, FFTW_HC2R, FFTW_ESTIMATE);
    // Execute plan
    fftwf_execute(plan_f2t);
    // Normalize the output
    for (unsigned int i = 0; i < INTERNAL_AUDIO_BUFFER_SIZE; ++i)
        (*output)[i] = fourierOut[i] / INTERNAL_AUDIO_BUFFER_SIZE;
    // Destroy output
    fftwf_free(fourierOut);
    // Destroy the plan
    fftwf_destroy_plan(plan_f2t);
}