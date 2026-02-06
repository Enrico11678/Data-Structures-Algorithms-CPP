
namespace lasd {

/* ************************************************************************** */

// Specific constructors

template <typename Data>
PQHeap<Data>::PQHeap(const TraversableContainer<Data> & travCont): HeapVec<Data>(travCont) {
    capacity = (size > 0) ? size * 2 : 2;
    Resize(capacity);
}

template <typename Data>
PQHeap<Data>::PQHeap(MappableContainer<Data> && mapCont): HeapVec<Data>(std::move(mapCont)) {
    capacity = (size > 0) ? size * 2 : 2;
    Resize(capacity);
}

// Copy constructor

template <typename Data>
PQHeap<Data>::PQHeap(const PQHeap<Data> & pqHeap) {
    capacity = pqHeap.capacity;
    size = pqHeap.size;
    Elements = (capacity > 0) ? new Data[capacity] : nullptr;
    for(ulong i = 0; i < size; ++i){
        Elements[i] = pqHeap.Elements[i];
    }
}

// Move constructor

template <typename Data>
PQHeap<Data>::PQHeap(PQHeap<Data> && pqHeap) noexcept {
    std::swap(capacity, pqHeap.capacity);
    std::swap(size, pqHeap.size);
    std::swap(Elements, pqHeap.Elements);
}

// Destructor

template <typename Data>
PQHeap<Data>::~PQHeap() {
    Clear();
}

// Copy assignment

template <typename Data>
PQHeap<Data> & PQHeap<Data>::operator=(const PQHeap<Data> & pqHeap){
    if(this != &pqHeap){
        PQHeap<Data> tmp(pqHeap);
        std::swap(*this, tmp);
    }
    return *this;
}

// Move assignment

template <typename Data>
PQHeap<Data> & PQHeap<Data>::operator=(PQHeap<Data> && pqHeap) noexcept {
    if(this != &pqHeap){
        std::swap(capacity, pqHeap.capacity);
        std::swap(size, pqHeap.size);
        std::swap(Elements, pqHeap.Elements);
    }
    return *this;
}

// Specific member functions (inherited from PQ)

template <typename Data>
const Data & PQHeap<Data>::Tip() const {
    if(size == 0){
        throw std::length_error("Access to the tip of an empty priority queue.");
    }
    return Elements[0];
}

template <typename Data>
void PQHeap<Data>::RemoveTip() {
    if(size == 0){
        throw std::length_error("Removal of the tip from an empty priority queue.");
    }
    if(size == 1){
        --size;
    }else{
        std::swap(Elements[0], Elements[size - 1]);
        --size;
        HeapifyDown(0);
    }
}

template <typename Data>
Data PQHeap<Data>::TipNRemove() {
    if(size == 0){
        throw std::length_error("Access and removal of the tip from an empty priority queue.");
    }
    Data tip = Tip();
    RemoveTip();
    return tip;
}

template <typename Data>
void PQHeap<Data>::Insert(const Data & value) {
    if(size >= capacity){
        ulong newCapacity = (capacity > 0) ? capacity * 2 : 2;
        Resize(newCapacity);
    }
    Elements[size] = value;
    ++size;
    HeapifyUp(size - 1);
}

template <typename Data>
void PQHeap<Data>::Insert(Data && value) {
    if(size >= capacity){
        ulong newCapacity = (capacity > 0) ? capacity * 2 : 2;
        Resize(newCapacity);
    }
    Elements[size] = std::move(value);
    ++size;
    HeapifyUp(size - 1);
}

template <typename Data>
void PQHeap<Data>::Change(ulong index, const Data & value) {
    if(size == 0){
        throw std::length_error("Change operation on an empty priority queue.");
    }
    if(index >= size){
        throw std::out_of_range("Index out of range in change operation.");
    }

    if(Elements[index] < value){
        Elements[index] = value;
        HeapifyUp(index);
    }else{
        Elements[index] = value;
        HeapifyDown(index);
    }
}

template <typename Data>
void PQHeap<Data>::Change(ulong index, Data && value) {
    if(size == 0){
        throw std::length_error("Change operation on an empty priority queue.");
    }
    if(index >= size){
        throw std::out_of_range("Index out of range in change operation.");
    }

    if(Elements[index] < value){
        Elements[index] = std::move(value);
        HeapifyUp(index);
    }else{
        Elements[index] = std::move(value);
        HeapifyDown(index);
    }
}

// Override comparison operators

template <typename Data>
bool PQHeap<Data>::operator==(const PQHeap<Data> & pqHeap) const noexcept {
    return HeapVec<Data>::operator==(pqHeap);
}

template <typename Data>
bool PQHeap<Data>::operator!=(const PQHeap<Data> & pqHeap) const noexcept {
    return HeapVec<Data>::operator!=(pqHeap);
}

// Override Resize method

template <typename Data>
void PQHeap<Data>::Resize(ulong newCapacity) {
    if(newCapacity == 0){
        Clear();
        return;
    }
    if(newCapacity == capacity){
        return;
    }

    Data * tempElements = new Data[newCapacity];
    ulong elementsToCopy = (size < newCapacity) ? size : newCapacity;
    for(ulong i = 0; i < elementsToCopy; ++i){
        tempElements[i] = std::move(Elements[i]);
    }
    delete[] Elements;
    Elements = tempElements;
    capacity = newCapacity;

    if(size > newCapacity){
        size = newCapacity;
    }
}

// Override Clear method

template <typename Data>
void PQHeap<Data>::Clear() {
    delete[] Elements;
    Elements = nullptr;
    size = 0;
    capacity = 0;
}

/* ************************************************************************** */

// Auxiliary functions

template <typename Data>
void PQHeap<Data>::HeapifyDown(ulong index) {
    HeapVec<Data>::HeapifyRecursive(index);
}

template <typename Data>
void PQHeap<Data>::HeapifyUp(ulong index) {
    while(index > 0){
        ulong parentIndex = (index -1) / 2;
        if(Elements[index] > Elements[parentIndex]){
            std::swap(Elements[index], Elements[parentIndex]);
            index = parentIndex;
        }else{
            break;
        }
    }
}

}