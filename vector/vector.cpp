
namespace lasd {

/* ************************************************************************** */

// Vector

// Specific Constructors

template <typename Data>
Vector<Data>::Vector(const ulong newSize) {
    size = newSize;
    Elements = new Data[size] {};
}

template <typename Data>
Vector<Data>::Vector(const TraversableContainer<Data> & travCont): Vector(travCont.Size()) {
    ulong index = 0;
    travCont.Traverse(
        [this, &index](const Data & value) {
            Elements[index++] = value;
        }
    );
}

template <typename Data>
Vector<Data>::Vector(MappableContainer<Data> && mapCont): Vector(mapCont.Size()) {
    ulong index = 0;
    mapCont.Map(
        [this, &index](Data & value) {
            Elements[index++] = std::move(value);
        }
    );
}

// Copy Constructor

template <typename Data>
Vector<Data>::Vector(const Vector<Data> & vec) {
    size = vec.size;
    Elements = new Data[size];
    for(ulong i = 0; i < size; ++i){
        Elements[i] = vec.Elements[i];
    }
}

// Move Constructor

template <typename Data>
Vector<Data>::Vector(Vector<Data> && vec) noexcept {
    std::swap(size, vec.size);
    std::swap(Elements, vec.Elements);
}

// Destructor

template <typename Data>
Vector<Data>::~Vector() {
    Clear();
}

// Copy assignment

template <typename Data>
Vector<Data> & Vector<Data>::operator=(const Vector<Data> & vec) {
    Vector<Data> tempVec(vec);
    std::swap(tempVec, *this);
    return *this;
}

// Move assignment

template <typename Data>
Vector<Data> & Vector<Data>::operator=(Vector<Data> && vec) noexcept {
    std::swap(size, vec.size);
    std::swap(Elements, vec.Elements);
    return *this;
}

// Comparison operators

template <typename Data>
bool Vector<Data>::operator==(const Vector<Data> & vec) const noexcept {
    if(size == vec.size){
        for(ulong i=0; i<size; ++i){
            if(Elements[i] != vec.Elements[i]){
                return false;
            }
        }
        return true;
    }else{
        return false;
    }
}

template <typename Data>
bool Vector<Data>::operator!=(const Vector<Data> & vec) const noexcept {
    return !(*this == vec);
}

// Specific member functions (inherited from MutableLinearContainer)

template <typename Data>
Data & Vector<Data>::operator[](const ulong index) {
    if(index < size){
        return Elements[index];
    }else{
        throw std::out_of_range("Access at index " + std::to_string(index) + " exceeds vector size " + std::to_string(size) + ".");
    }
}

template <typename Data>
Data & Vector<Data>::Front() {
    if(size != 0){
        return Elements[0];
    }else{
        throw std::length_error("Access to an empty vector.");
    }
}

template <typename Data>
Data & Vector<Data>::Back() {
    if(size != 0){
        return Elements[size-1];
    }else{
        throw std::length_error("Access to an empty vector.");
    }
}

// Specific member functions (inherited from LinearContainer)

template <typename Data>
const Data & Vector<Data>::operator[](const ulong index) const {
    if(index < size){
        return Elements[index];
    }else{
        throw std::out_of_range("Access at index " + std::to_string(index) + " exceeds vector size " + std::to_string(size) + ".");
    }
}

template <typename Data>
const Data & Vector<Data>::Front() const {
    if(size != 0){
        return Elements[0];
    }else{
        throw std::length_error("Access to an empty vector.");
    }
}

template <typename Data>
const Data & Vector<Data>::Back() const {
    if(size != 0){
        return Elements[size-1];
    }else{
        throw std::length_error("Access to an empty vector.");
    }
}

// Specific member function (inherited from ResizableContainer)

template <typename Data>
void Vector<Data>::Resize(const ulong newSize) {
    if(newSize == 0){
        Clear();

    }else if(size != newSize){
        Data * tempElements = new Data[newSize] {};
        ulong minSize = (size < newSize) ? size : newSize;

        for(ulong i=0; i<minSize; ++i){
            std::swap(Elements[i], tempElements[i]);
        }

        std::swap(Elements, tempElements);                          
        size = newSize;
        delete[] tempElements;
    }
}

// Specific member function (inherited from ClearableContainer)

template <typename Data>
void Vector<Data>::Clear() {
    delete[] Elements;
    Elements = nullptr;
    size = 0;
}

/* ************************************************************************** */

// SortableVector

// Specific Constructors

template <typename Data>
SortableVector<Data>::SortableVector(const ulong newSize): Vector<Data>(newSize) {}

template <typename Data>
SortableVector<Data>::SortableVector(const TraversableContainer<Data> & travCont): Vector<Data>(travCont) {}

template <typename Data>
SortableVector<Data>::SortableVector(MappableContainer<Data> && mapCont): Vector<Data>(std::move(mapCont)) {}

// Copy Constructor

template <typename Data>
SortableVector<Data>::SortableVector(const SortableVector<Data> & sortVec): Vector<Data>(sortVec) {}

// Move Constructor

template <typename Data>
SortableVector<Data>::SortableVector(SortableVector<Data> && sortVec) noexcept: Vector<Data>(std::move(sortVec)) {}

// Copy assignment

template <typename Data>
SortableVector<Data> & SortableVector<Data>::operator=(const SortableVector<Data> & sortVec) {
    Vector<Data>::operator=(sortVec);
    return *this;
}

// Move assignment

template <typename Data>
SortableVector<Data> & SortableVector<Data>::operator=(SortableVector<Data> && sortVec) noexcept {
    Vector<Data>::operator=(std::move(sortVec));
    return *this;
}

}
