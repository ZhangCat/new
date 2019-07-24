//vov

#ifndef VARRAY_HPP
#define VARRAY_HPP

template<typename T>
static T** vArray2DInit(const int row,const int col) {
    if(row<1||col<1) {
        return nullptr;
    }

    T** root=new T*[row];
    for(int i=0;i<row;i++) {
        root[i]=new T[col];
    }
    return root;
}

template<typename T>
static void vArray2DFree(T**& root,const int row,const int col) {
    if(!root) {
        return;
    }

    for(int i=0;i<row;i++) {
        if(root[i]) {
            delete[] root[i];
        }
    }

    delete[] root;
    root=nullptr;
    return;
}

#endif
