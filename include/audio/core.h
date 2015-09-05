/**
 * \file core.h
 * \brief File containing all the common structures to work with audio.
 *
 * Inside this file, you will find all the configuration about audio, and
 * the declaration of structures used by the audio system of the software.
 *
 */
#pragma once

namespace AudioFX {

/**
 * Number of samples per second.
 */
#define SAMPLES_PER_SECOND  44100

/**
 * Type used to store each sample.
 */
#define SAMPLE_TYPE         double

/**
 * Number of channels that will be used.
 * 1 channel is MONO audio.
 * 2 channels is STEREO audio.
 */
#define NUMBER_CHANNELS     2

/**
 * Number of operations that an audio buffer will support before it is full.
 * This is related to <audio/buffer.h>. This number defines the size of the
 * buffer itself, which is described as:
 *
 * BUFFER_MAX_OPERATIONS * INTERNAL_AUDIO_BUFFER_SIZE * sizeof(SAMPLE_TYPE).
 *
 * The buffer will be stored in disk when the number of operations reach this
 * max value. So, the bigger it is, the longer the disk access intervals will
 * be.
 *
 * To make it better, try to set the buffer_size as multiple of a block size.
 */
#define BUFFER_MAX_OPERATIONS       64

/**
 * Size of the audio buffer.
 *
 * This buffer size has nothing to do with <audio/buffer.h>. This buffer is
 * used internally by the recorder.
 *
 * It shouldnt be too small, because it makes the CPU work a lot,
 * but it cannot be too big, otherwise, you will notice some lag
 * between the input and output.
 */
#define INTERNAL_AUDIO_BUFFER_SIZE   32

/**
 * Value used to indicate a silent sample.
 */
#define SILENT_SAMPLE       (0.0f)

}; // namespace