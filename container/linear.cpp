
namespace lasd {

/* ************************************************************************** */

// LinearContainer

// (LinearContainer) comparison operators

template <typename Data>
bool LinearContainer<Data>::operator==(const LinearContainer<Data> & linCont) const noexcept {
    if(size == linCont.size){
        for(ulong i=0; i<size; ++i){
            if(operator[](i) != linCont.operator[](i)){
                return false;
            }
        }
        return true;
    }else{
        return false;
    }
}

template <typename Data>
bool LinearContainer<Data>::operator!=(const LinearContainer<Data> & linCont) const noexcept {
    return !(*this == linCont);
}

// (LinearContainer) specific member functions 

template <typename Data>
const Data & LinearContainer<Data>::Front() const {
    return operator[](0);
}

template <typename Data>
const Data & LinearContainer<Data>::Back() const {
    return operator[](size-1);
}

// (LinearContainer) specific member functions inherited from TraversableContainer
//Traverse: uso PreOrderTraverse
template <typename Data>
void LinearContainer<Data>::Traverse(TraverseFun fun) const {
    PreOrderTraverse(fun);
} 

// (LinearContainer) specific member functions inherited from PreOrderTraversableContainer and PostOrderTraversableContainer

template <typename Data>
void LinearContainer<Data>::PreOrderTraverse(TraverseFun fun) const {
    for(ulong i=0; i<size; ++i){
        fun(operator[](i));
    }
}

template <typename Data>
void LinearContainer<Data>::PostOrderTraverse(TraverseFun fun) const {
   ulong index = size;
   while(index > 0){
        fun(operator[](--index));
   }
}

/* ************************************************************************** */

// MutableLinearContainer

// (MutableLinearContainer) specific member functions

template <typename Data>
Data & MutableLinearContainer<Data>::Front() {
    return operator[](0);
}

template <typename Data>
Data & MutableLinearContainer<Data>::Back() {
    return operator[](size-1);
}

// (MutableLinearContainer) specific member functions inherited from MappableContainer

template <typename Data>
void MutableLinearContainer<Data>::Map(MapFun fun) {
    PreOrderMap(fun);
}

// (MutableLinearContainer) specific member functions inherited from PreOrderMappableContainer and PostOrderMappableContainer

template <typename Data>
void MutableLinearContainer<Data>::PreOrderMap(MapFun fun) {
    for(ulong i=0; i<size; ++i){
        fun(operator[](i));
    }
}

template <typename Data>
void MutableLinearContainer<Data>::PostOrderMap(MapFun fun) {
    ulong index = size;
    while(index > 0){
        fun(operator[](--index));
    }
}

// (SortableLinearContainer) InsertionSort

template <typename Data>
void SortableLinearContainer<Data>::Swap(ulong i, ulong j) noexcept {
    std::swap((*this)[i], (*this)[j]);
}

// Insertion Sort
template <typename Data>
void SortableLinearContainer<Data>::Sort() noexcept {
    for(ulong i=1; i<size; ++i){
        ulong j = i;
        while(j>0 && (*this)[j] < (*this)[j-1]){
            Swap(j, j-1);
            --j;
        }
    }
}

}
