#include <audio/buffer.h>

Buffer::Buffer()
{
    unsigned int bufferSize;
    // Initialize internal attributes
    this->erase();
    // Define size of the buffer.
    // You can change it by changing the values inside <audio/core.h>
    bufferSize = BUFFER_MAX_OPERATIONS * INTERNAL_AUDIO_BUFFER_SIZE;
    // Allocate buffer
    this->buffer = new SAMPLE_TYPE[bufferSize];
}

Buffer::~Buffer()
{
    delete[] this->buffer;
}

char Buffer::insert(void* data, unsigned int size)
{
    SAMPLE_TYPE* data_ptr = (SAMPLE_TYPE*) data;
    // Copy data to the buffer
    for (unsigned int i = 0; i < size; ++i)
        this->buffer[currentIndex++] = *data_ptr++;
    // Increament number of new chunks of data
    ++this->newChunks;
    // If buffer is full, return its flag.
    if (++this->operationsCounter == BUFFER_MAX_OPERATIONS) {
        this->operationsCounter = 0;
        this->currentIndex = 0;
        return Buffer::BUFFER_FULL;
    }
    // Continue using the buffer, it is not full.
    return Buffer::BUFFER_NOT_FULL;
}

void Buffer::erase()
{
    this->currentIndex = 0;
    this->operationsCounter = 0;
    this->newChunks = 0;
    this->lastChunk = 0;
}

SAMPLE_TYPE* Buffer::getNextChunk()
{
    unsigned long int position = INTERNAL_AUDIO_BUFFER_SIZE * this->lastChunk;
    this->lastChunk = (lastChunk+1) % BUFFER_MAX_OPERATIONS;
    --this->newChunks;
    return &(this->buffer[position]);
}