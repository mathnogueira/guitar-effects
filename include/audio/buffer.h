/**
 * \file buffer.h
 * \brief A simple audio buffer for recording.
 *
 * File containing the class responsible for handling audio buffering.
 */
#pragma once

#include <audio/core.h>

namespace AudioFX {

/**
 * \class Buffer <audio/buffer.h>
 * \brief A simple audio buffer for recording.
 *
 * Buffer used to store data before it is stored in disk. This buffer reduces
 * the number of disk operations, thus reduces the time needed to record and
 * process an audio signal.
 *
 * This buffer, when full, will throw an event "FULL_BUFFER", that indicates
 * to the audio system that it should store it in disk.
 *
 * \author Matheus Nogueira
 * \version 1.0
 */
class Buffer
{
public:

    /// Indicates that the buffer is full
    static const char BUFFER_FULL = 1;

    /// Indicates that the buffer is not full
    static const char BUFFER_NOT_FULL = 0;

    /**
     * Starts the buffer.
     */
    Buffer();

    /**
     * Destroy the buffer and all its data.
     */
    ~Buffer();

    /**
     * Add data to the buffer.
     * 
     * \param data data that will be appended to the buffer.
     * \param size number of bytes of the data.
     *
     * \return flag that indicates the buffer status after the insertion
     */
    char insert(void* data, unsigned int size);

    /**
     * Erase buffer data.
     *
     * This is a soft erase, it will only change the metadata from the buffer, 
     * but the data itself will be still there, until a next "insert" operation,
     * that will override some of the old data.
     */
    void erase();

    /**
     * Return the next chunk in the buffer.
     * \return pointer to the first position of the chunk.
     */
    SAMPLE_TYPE* getNextChunk();

    /**
     * Check if there is new data in the buffer.
     * \return true if it has new data.
     */
    bool hasNewData() { return (bool) this->newChunks; }

private:

    /**
     * Number of operations done in this buffer.
     */
    unsigned int operationsCounter;

    /**
     * Position when it should be appended the next data array.
     */
    unsigned int currentIndex;

    /**
     * Number of added chunks since last reading operation.
     */
    unsigned int newChunks;

    /**
     * Index of the last chunk retrieved by the user.
     */
    unsigned int lastChunk;

    /**
     * Buffer that will store the data.
     */
    SAMPLE_TYPE *buffer;
};

}; // namespace