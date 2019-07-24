//vov

#ifndef V_BUFFER_BYTE_HPP
#define V_BUFFER_BYRE_HPP

#include <iostream>
#include <vector>
#include <cstring>

class vBufferByte 
{
    std::vector<char> buffer_;
    int data_size_;
public:
    vBufferByte(int size);
    virtual ~vBufferByte();
    void Write(const char* data,int size);
    int Read(char* data,int size);
    int GetDataSize();
    int GetBufferSize();
    void SetBufferEmpty();
private:
    //copy constructor
    vBufferByte(const vBufferByte& t) {}
    //assignment constructor
    vBufferByte& operator=(const vBufferByte& t) {}
    
    int iGetFromBeg(char* data,int size);
    void iDelFromBeg(int size);
    void iAddFromEnd(const char* data,int size);
};

//public
vBufferByte::vBufferByte(int size=16000) {
    size=(size<=0)?16000:size;
    buffer_=std::vector<char>(size,0);
    data_size_=0;
}

vBufferByte::~vBufferByte() {

}

int vBufferByte::GetDataSize() {
    return data_size_;
}

int vBufferByte::GetBufferSize() {
    return buffer_.size();
}

int vBufferByte::Read(char* data,int size) {
    if(!data || size<=0) {
        return 0;
    }

    int read_size=iGetFromBeg(data,size);
    if(read_size>0) {
        iDelFromBeg(read_size);
    }

    return read_size;
}

void vBufferByte::Write(const char* data,int size) {
    if(!data || size<=0) {
        return;
    }

    if(size <=(buffer_.size()-data_size_)) {
        iAddFromEnd(data,size);
        return;
    }

    if(size>=buffer_.size()) {
        std::cout<<"[vBufferByte]write:loss data-1:"<<data_size_+(size-buffer_.size())<<std::endl;
        iDelFromBeg(data_size_);
        iAddFromEnd(data+(size-buffer_.size()),buffer_.size());
        return;
    }

    if((size>(buffer_.size()-data_size_)) && (size <buffer_.size())) {
        std::cout<<"[vBufferByte]write:loss data-2:"<<size-(buffer_.size()-data_size_)<<std::endl;
        iDelFromBeg(size-(buffer_.size()-data_size_));
        iAddFromEnd(data,size);
        return;
    }
}

void vBufferByte::SetBufferEmpty() {
    data_size_=0;
}

//private
int vBufferByte::iGetFromBeg(char* data,int size) {
    if(size<=0) {
        return 0;
    }

    int size_can_read=(size<data_size_)?size:data_size_;
    memcpy(data,buffer_.data(),size_can_read);
    return size_can_read;
}

void vBufferByte::iDelFromBeg(int size) {
    if(size<=0) {
        return;
    }

    int size_delete=(size<data_size_)?size:data_size_;
    data_size_-=size_delete;
    memcpy(buffer_.data(),buffer_.data()+size_delete,data_size_);
    return;
}

void vBufferByte::iAddFromEnd(const char* data,int size) {
    if(size<=0||size>(buffer_.size()-data_size_)) {
        return;
    }

    memcpy(buffer_.data()+data_size_,data,size);
    data_size_+=size;
}

#endif