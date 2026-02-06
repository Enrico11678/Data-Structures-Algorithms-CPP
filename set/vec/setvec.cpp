
namespace lasd {

/* ************************************************************************** */

// Specific constructors

template <typename Data>
SetVec<Data>::SetVec(const TraversableContainer<Data> & travCont): Container() {
    capacity = (travCont.Size() > 0) ? travCont.Size() * 2 : 2;
    Elements = new Data[capacity];
    head = 0;
    travCont.Traverse(
        [this](const Data & value){
             this->Insert(value); 
        }
    );
}

template <typename Data>
SetVec<Data>::SetVec(MappableContainer<Data> && mapCont): Container() {
    capacity = (mapCont.Size() > 0) ? mapCont.Size() * 2 : 2;
    Elements = new Data[capacity];
    head = 0;
    mapCont.Map(
        [this](Data & value){ 
            this->Insert(std::move(value)); 
        }
    );
}

// Copy constructor

template <typename Data>
SetVec<Data>::SetVec(const SetVec<Data> & setVec) {
    capacity = setVec.capacity;
    size = setVec.size;
    head = 0;
    Elements = (capacity > 0) ? new Data[capacity] : nullptr;
    for(ulong i=0; i<size; ++i){
        Elements[i] = setVec.Elements[setVec.CircularIndex(i)];
    }
}

// Move constructor

template <typename Data>
SetVec<Data>::SetVec(SetVec<Data> && setVec) noexcept {
    std::swap(capacity, setVec.capacity);
    std::swap(size, setVec.size);
    std::swap(Elements, setVec.Elements);
    std::swap(head, setVec.head);
}

// Destructor

template <typename Data>
SetVec<Data>::~SetVec() {
    Clear();
}

// Copy assignment

template <typename Data>
SetVec<Data> & SetVec<Data>::operator=(const SetVec<Data> & setVec) {
    if(this != &setVec){
        SetVec<Data> tmp(setVec);
        std::swap(*this, tmp);
    }
    return *this;
}

// Move assignment

template <typename Data>
SetVec<Data> & SetVec<Data>::operator=(SetVec<Data> && setVec) noexcept {
    if(this != &setVec){
        std::swap(Elements, setVec.Elements);
        std::swap(capacity, setVec.capacity);
        std::swap(size, setVec.size);
        std::swap(head, setVec.head);
    }
    return *this;
}

// Comparison operators

template <typename Data>
bool SetVec<Data>::operator==(const SetVec<Data> & setVec) const noexcept {
    if(size != setVec.size) return false;
    for(ulong i=0; i<size; ++i)
        if((*this)[i] != setVec[i]) return false;
    return true;
}

template <typename Data>
bool SetVec<Data>::operator!=(const SetVec<Data> & setVec) const noexcept {
    return !(*this == setVec);
}

// Specific member functions (inherited from OrderedDictionaryContainer)

// Max and Min functions

template <typename Data>
const Data & SetVec<Data>::Min() const {
    if(size == 0){
        throw std::length_error("SetVec is empty");
    } 
    return Elements[CircularIndex(0)];
}

template <typename Data>
Data SetVec<Data>::MinNRemove() {
    if(size == 0){
        throw std::length_error("SetVec is empty");
    } 
    Data min = std::move(Elements[CircularIndex(0)]);
    ShiftLeft(0);
    return min;
}

template <typename Data>
void SetVec<Data>::RemoveMin() {
   if(size == 0){
        throw std::length_error("SetVec is empty");
   } 
    ShiftLeft(0);
}

template <typename Data>
const Data & SetVec<Data>::Max() const {
   if(size == 0){
        throw std::length_error("SetVec is empty");
   } 
    return Elements[CircularIndex(size - 1)];
}


template <typename Data>
Data SetVec<Data>::MaxNRemove() {
    if(size == 0){
        throw std::length_error("SetVec is empty");
    } 
    Data max = std::move(Elements[CircularIndex(size - 1)]);
    ShiftLeft(size - 1);
    return max;
}

template <typename Data>
void SetVec<Data>::RemoveMax() {
    if(size == 0){
        throw std::length_error("SetVec is empty");
    } 
    ShiftLeft(size - 1);
}

// Predecessor and Successor functions

template <typename Data>
const Data & SetVec<Data>::Predecessor(const Data & value) const {
    if(Empty()) {
        throw std::length_error("SetVec is empty");
    }
    int index = BinarySearch(value);
    ulong insertIndex;
    if(index == -1){
        insertIndex = BinarySearchInsert(value);
        if(insertIndex == 0){
            throw std::length_error("No predecessor found");
        }
        --insertIndex;
    }else{
        if(index == 0){
            throw std::length_error("No predecessor found");
        }
        insertIndex = static_cast<ulong>(index - 1);
    }
    return Elements[CircularIndex(insertIndex)];
}

template <typename Data>
Data SetVec<Data>::PredecessorNRemove(const Data & value) {
    int index = BinarySearch(value);
    if(index == -1){
        ulong insertIndex = BinarySearchInsert(value);
        if(insertIndex == 0){
            throw std::length_error("No predecessor found");
        }
        Data predecessor = std::move(Elements[CircularIndex(insertIndex - 1)]);
        ShiftLeft(insertIndex - 1);
        return predecessor;
    }else{
        if(index == 0){
            throw std::length_error("No predecessor found");
        }
        Data predecessor = std::move(Elements[CircularIndex(index - 1)]);
        ShiftLeft(static_cast<ulong>(index - 1));
        return predecessor;
    }
}

template <typename Data>
void SetVec<Data>::RemovePredecessor(const Data & value) {
    int index = BinarySearch(value);
    if(index == -1){
        ulong insertIndex = BinarySearchInsert(value);
        if(insertIndex == 0){
            throw std::length_error("No predecessor found");
        }
        ShiftLeft(insertIndex - 1);
    }else{
        if(index == 0){
            throw std::length_error("No predecessor found");
        }
        ShiftLeft(static_cast<ulong>(index - 1));
    }
}

template <typename Data>
const Data & SetVec<Data>::Successor(const Data & value) const {
   if(Empty()) {
        throw std::length_error("SetVec is empty");
    }
    int index = BinarySearch(value);
    ulong insertIndex;
    if(index == -1){
        insertIndex = BinarySearchInsert(value);
        if(insertIndex >= size){
            throw std::length_error("No successor found");
        }
    }else{
        insertIndex = static_cast<ulong>(index + 1);
        if(insertIndex >= size){
            throw std::length_error("No successor found");
        }
    }
    return Elements[CircularIndex(insertIndex)];
}

template <typename Data>
Data SetVec<Data>::SuccessorNRemove(const Data & value) {
    int index = BinarySearch(value);
    ulong insertIndex;
    if(index == -1){
        insertIndex = BinarySearchInsert(value);
        if(insertIndex >= size){
            throw std::length_error("No successor found");
        }
    }else{
        insertIndex = static_cast<ulong>(index + 1);
        if(insertIndex >= size){
            throw std::length_error("No successor found");
        }
    }
    Data successor = std::move(Elements[CircularIndex(insertIndex)]);
    ShiftLeft(insertIndex);
    return successor;
}

template <typename Data>
void SetVec<Data>::RemoveSuccessor(const Data & value) {
    int index = BinarySearch(value);
    ulong insertIndex;
    if(index == -1){
        insertIndex = BinarySearchInsert(value);
        if(insertIndex >= size){
            throw std::length_error("No successor found");
        }
    }else{
        insertIndex = static_cast<ulong>(index + 1);
        if(insertIndex >= size){
            throw std::length_error("No successor found");
        }
    }
    ShiftLeft(insertIndex);
}

// Specific member functions (inherited from DictionaryContainer)

template <typename Data>
bool SetVec<Data>::Insert(const Data & value) {
    if(Exists(value)){
        return false;
    } 
    if(size >= capacity){
        Resize((capacity > 0) ? capacity * 2 : 2);
    } 
    ulong index = BinarySearchInsert(value);
    ShiftRight(index);
    Elements[CircularIndex(index)] = value;
    return true;
}

template <typename Data>
bool SetVec<Data>::Insert(Data && value) {
    if(Exists(value)){
        return false;
    } 
    if(size >= capacity){
        Resize((capacity > 0) ? capacity * 2 : 2);
    } 
    ulong index = BinarySearchInsert(value);
    ShiftRight(index);
    Elements[CircularIndex(index)] = std::move(value);
    return true;
}

template <typename Data>
bool SetVec<Data>::Remove(const Data & value) {
    int index = BinarySearch(value);
    if(index == -1){
        return false;
    }
       
    ShiftLeft(static_cast<ulong>(index));
    return true;
}

// Specific member functions (inherited from LinearContainer)

template <typename Data>
const Data & SetVec<Data>::operator[](const ulong index) const {
    if(index >= size){
        throw std::out_of_range("Index out of bounds in SetVec");
    } 
    return Elements[CircularIndex(index)];
}

// Specific member function (inherited from TestableContainer)

template <typename Data>
bool SetVec<Data>::Exists(const Data & value) const noexcept {
    return BinarySearch(value) != -1;
}

// Specific member function (inherited from ClearableContainer)

template <typename Data>
void SetVec<Data>::Clear() {
    delete[] Elements;
    Elements = nullptr;
    capacity = 0;
    head = 0;
    size = 0;
}

// Specific member function (inherited from ResizableContainer)

template <typename Data>
void SetVec<Data>::Resize(ulong newCapacity) {
    if(newCapacity == 0){
        Clear();
        return;
    }
    if(newCapacity == capacity){
        return;
    } 
    Data * newElements = new Data[newCapacity];
    ulong elementsToCopy = (size < newCapacity) ? size : newCapacity;
    for(ulong i=0; i<elementsToCopy; ++i){
        newElements[i] = std::move(Elements[CircularIndex(i)]);
    }
    delete[] Elements;
    Elements = newElements;
    capacity = newCapacity;
    head = 0;
    if(size > newCapacity){
        size = newCapacity;
    }
}

/* ************************************************************************** */

// Auxiliar functions

template <typename Data>
int SetVec<Data>::BinarySearch(const Data & value) const {
    if(size == 0){
        return -1;
    } 
    ulong low = 0; 
    ulong high = size - 1;
    while(low <= high){
        ulong mid = (low + high) / 2;
        const Data & current = Elements[CircularIndex(mid)];
        if(current == value){
            return static_cast<int>(mid);
        }else if(current < value){
            low = mid + 1;
        }else{
            if(mid == 0){
                return -1;
            }
            high = mid - 1;
        }
    }
    return -1;
}

template <typename Data>
ulong SetVec<Data>::BinarySearchInsert(const Data & value) const {
   ulong low = 0;
   ulong high = size;
    while(low < high){
        ulong mid = (low + high) / 2;
        const Data & current = Elements[CircularIndex(mid)];
        if(current < value){
            low = mid + 1;
        }else{
            high = mid;
        } 
    }
    return low;
}

template <typename Data>
ulong SetVec<Data>::CircularIndex(ulong index) const {
    return (capacity == 0) ? 0 : (head + index) % capacity;
}

template <typename Data>
void SetVec<Data>::ShiftLeft(ulong index) {
    if(size == 0 || index >= size){
        throw std::out_of_range("Index out of bounds in ShiftLeft");
    } 
    for(ulong i = index; i < size - 1; ++i){
        Elements[CircularIndex(i)] = std::move(Elements[CircularIndex(i + 1)]);
    }
    --size;
}

template <typename Data>
void SetVec<Data>::ShiftRight(ulong index) {
    if(size >= capacity){
        throw std::length_error("Cannot shift right, structure is full");
    } 
    if(index > size){
        throw std::out_of_range("Index out of bounds in ShiftRight");
    } 
    for(long i = static_cast<long>(size) - 1; i >= static_cast<long>(index); --i){
        Elements[CircularIndex(i + 1)] = std::move(Elements[CircularIndex(i)]);
    }
    ++size;
}

}
