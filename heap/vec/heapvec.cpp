
namespace lasd {

/* ************************************************************************** */

// Specific constructors

template <typename Data>
HeapVec<Data>::HeapVec(const TraversableContainer<Data> &travCont): SortableVector<Data>(travCont) {
    Heapify();
}

template <typename Data>
HeapVec<Data>::HeapVec(MappableContainer<Data> &&mapCont): SortableVector<Data>(std::move(mapCont)) {
    Heapify();
}

// Copy constructor

template <typename Data>
HeapVec<Data>::HeapVec(const HeapVec<Data> & heapVec): SortableVector<Data>(heapVec) {}

// Move constructor

template <typename Data>
HeapVec<Data>::HeapVec(HeapVec<Data> && heapVec) noexcept: SortableVector<Data>(std::move(heapVec)) {}

// Copy assignment

template <typename Data>
HeapVec<Data> & HeapVec<Data>::operator=(const HeapVec<Data> & heapVec) {
    SortableVector<Data>::operator=(heapVec);
    return *this;
}

// Move assignment

template <typename Data>
HeapVec<Data> & HeapVec<Data>::operator=(HeapVec<Data> && heapVec) noexcept {
    SortableVector<Data>::operator=(std::move(heapVec));
    return *this;
}

// Comparison operators

template <typename Data>
bool HeapVec<Data>::operator==(const HeapVec<Data> & heapVec) const noexcept {
    return SortableVector<Data>::operator==(heapVec);
}

template <typename Data>
bool HeapVec<Data>::operator!=(const HeapVec<Data> & heapVec) const noexcept {
    return !(*this == heapVec);
}

// Specific member functions (inherited from Heap)

template <typename Data>
bool HeapVec<Data>::IsHeap() const noexcept {
    if(size == 0){
        return true;
    }

    for(ulong i = 0; i < size / 2; ++i) {
        ulong leftIndex = 2 * i + 1;
        ulong rightIndex = 2 * i + 2;
        if(leftIndex < size && Elements[i] < Elements[leftIndex]){
            return false;
        }
        if(rightIndex < size && Elements[i] < Elements[rightIndex]){
            return false;
        }
    }

    return true;
}

template <typename Data>
void HeapVec<Data>::Heapify() {
    for(long i = (long)size / 2 - 1; i >= 0; --i){
        HeapifyRecursive(i);
    }
}

// Specific member function heap sort (inherited from SortableLinearContainer)

template <typename Data>
void HeapVec<Data>::Sort() noexcept {
    ulong originalSize = size;
    Heapify();

    for(long i = (long)originalSize - 1; i > 0; --i){
        std::swap(Elements[0], Elements[i]);
        --size;
        HeapifyRecursive(0);
    }

    size = originalSize;
}

template <typename Data>
const Data & HeapVec<Data>::operator[](const ulong index) const {
    return Vector<Data>::operator[](index);
}

template <typename Data>
const Data & HeapVec<Data>::Front() const {
    return Vector<Data>::Front();
}

template <typename Data>
const Data & HeapVec<Data>::Back() const {
    return Vector<Data>::Back();
}

/* ************************************************************************** */

// Auxiliary functions

template <typename Data>
void HeapVec<Data>::HeapifyRecursive(ulong index) {
    if(index >= size) {
        throw std::out_of_range("Index out of range in heapify.");
    }

    ulong leftIndex = 2 * index + 1;
    ulong rightIndex = 2 * index + 2;
    ulong greatestIndex = index;

    if(leftIndex < size && Elements[leftIndex] > Elements[greatestIndex]){
        greatestIndex = leftIndex;
    }
    if(rightIndex < size && Elements[rightIndex] > Elements[greatestIndex]){
        greatestIndex = rightIndex;
    }

    if(greatestIndex != index) {
        std::swap(Elements[index], Elements[greatestIndex]);
        HeapifyRecursive(greatestIndex);
    }
}

}
