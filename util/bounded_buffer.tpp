template<typename T, int size>
void BoundedBuffer<T, size>::produce(T data) {
    if ((m_nextin + 1) % size == m_nextout) return;
    m_buffer[m_nextin] = data;
    m_nextin = (m_nextin + 1) % size;
}

template<typename T, int size> 
T BoundedBuffer<T, size>::consume() {
    if (m_nextout == m_nextin) return T();
    T result = m_buffer[m_nextout];
    m_nextout = (m_nextout + 1) % size;
    return result;
}
