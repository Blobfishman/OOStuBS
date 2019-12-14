#ifndef __bounded_buffer_include
#define __bounded_buffer_include

template <typename T, int size>
class BoundedBuffer {
    T m_buffer[size];
    int m_nextin, m_nextout;

   public:
    BoundedBuffer() : m_nextin(0), m_nextout(0) {}
    void produce(T data);
    T consume();
};

#include "util/bounded_buffer.tpp"

#endif  // __bounded_buffer_include
