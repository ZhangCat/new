//vov

#include <iostream>
#include <string>

#include "vBufferBlock.hpp"
#include "vBufferByte.hpp"
#include "vArray2D.hpp"

void test_vBufferBlock() {
    std::cout<<__FUNCTION__<<std::endl;

    vBufferBlock<int> buf(20);
    std::cout<<"buffer size:"<<buf.GetBufferSize()<<std::endl;

    for(int i=1;i<6;i++) {
        buf.Write(i+100);
        std::cout<<"write after:"<<buf.GetDataSize()<<std::endl;
    }

    int data=0;
    buf.Read(data);
    std::cout<<"read data:"<<data<<std::endl;
    std::cout<<"read after:"<<buf.GetDataSize()<<std::endl;

    buf.SetBufferEmpty();
    std::cout<<"SetBufferEmpty after:"<<buf.GetDataSize()<<std::endl;
}

void test_vBufferByte() {
    std::cout<<__FUNCTION__<<std::endl;
    vBufferByte buf(10);
    std::cout<<"buffer size:"<<buf.GetBufferSize()<<std::endl;

    std::string str("12helloworld");
    buf.Write(str.data(),str.size());
    std::cout<<"write after:"<<buf.GetDataSize()<<std::endl;

    char data[100];
    buf.Read(data,5);
    std::cout<<"read data:"<<data<<std::endl;
    std::cout<<"read after:"<<buf.GetDataSize()<<std::endl;

    buf.SetBufferEmpty();
    std::cout<<"SetBufferEmpty after:"<<buf.GetDataSize()<<std::endl;
}

void test_vArray2D() {
    int row=2;
    int col=3;
    int** data=vArray2DInit<int>(row,col);
    if(!data) {
        std::cout<<"vArray2DInit:false"<<std::endl;
        return;
    }

    for(int i=0;i<row;i++) {
        for(int j=0;j<col;j++) {
            data[i][j]=i+j;
        }
    }

    for(int i=0;i<row;i++) {
        for(int j=0;j<col;j++) {
            std::cout<<data[i][j]<<" ";
        }
        std::cout<<std::endl;
    }

    vArray2DFree<int>(data,row,col);
}

int main(int argc,char* argv[]) {
    //test_vBufferBlock();
    //test_vBufferByte();
    test_vArray2D();
}
