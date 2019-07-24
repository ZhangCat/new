//vov

#ifndef V_BUFFER_BLOCK_HPP
#define V_BUFFER_BLOCK_HPP

#include <iostream>
#include <deque>

template <class T>
class vBufferBlock
{
    std::deque<T> buffer_;
    int buffer_size_;
public:
    vBufferBlock(int size);
    virtual ~vBufferBlock();
    void Write(const T& data);
    void Read(T& data);
    int GetDataSize();
    int GetBufferSize();
    void SetBufferEmpty();
private:
    //copy constructor
    vBufferBlock(const vBufferBlock& t) {}
    //assignment constructor
    vBufferBlock& operator=(const vBufferBlock& t) {}
};

template <class T>
vBufferBlock<T>::vBufferBlock(int size=1024) {
    buffer_size_=(size>1024||size<1)?1024:size;
}

template <class T>
vBufferBlock<T>::~vBufferBlock() {
}

template <class T>
void vBufferBlock<T>::Write(const T& data) {
    if(buffer_.size()==(unsigned int)buffer_size_) {
        buffer_.pop_front();
        std::cout<<"[vBufferBlock]buffer is full:loss one data"<<std::endl;
    }
    buffer_.push_back(data);
}

template <class T>
void vBufferBlock<T>::Read(T& data) {
    if(!buffer_.empty()) {
        data=buffer_.front();
    }
}

template <class T>
int vBufferBlock<T>::GetDataSize() {
    return buffer_.size();
}

template <class T>
int vBufferBlock<T>::GetBufferSize() {
    return buffer_size_;
}

template <class T>
void vBufferBlock<T>::SetBufferEmpty() {
    if(!buffer_.empty())
        buffer_.clear();
}
#endif
