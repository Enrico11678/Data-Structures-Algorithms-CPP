
namespace lasd {

/* ************************************************************************** */

// Specific constructors
template <typename Data>
SetLst<Data>::SetLst(const TraversableContainer<Data> & travCont): List<Data>() {
    travCont.Traverse(
        [this](const Data & value){
            this->Insert(value); 
        }
    );
}

template <typename Data>
SetLst<Data>::SetLst(MappableContainer<Data> && mapCont): List<Data>() {
    mapCont.Map(
        [this](Data & value){ 
            this->Insert(std::move(value)); 
        }
    );
}

// Copy constructor
template <typename Data>
SetLst<Data>::SetLst(const SetLst<Data> & setLst) : List<Data>(setLst) {}

// Move constructor
template <typename Data>
SetLst<Data>::SetLst(SetLst<Data> && setLst) noexcept : List<Data>(std::move(setLst)) {}

// Copy assignment
template <typename Data>
SetLst<Data> & SetLst<Data>::operator=(const SetLst<Data> & setLst) {
    if(this != &setLst){
        SetLst<Data> temp(setLst);
        std::swap(*this, temp);
    }
    return *this;
}

// Move assignment
template <typename Data>
SetLst<Data> & SetLst<Data>::operator=(SetLst<Data> && setLst) noexcept {
    std::swap(head, setLst.head);
    std::swap(tail, setLst.tail);
    std::swap(size, setLst.size);
    return *this;
}

// Comparison operators
template <typename Data>
bool SetLst<Data>::operator==(const SetLst<Data> & setLst) const noexcept {
    if(size != setLst.size){
        return false;
    }
    Node * currentNode = head;
    Node * otherNode = setLst.head;
    while(currentNode != nullptr && otherNode != nullptr){
        if(currentNode->element != otherNode->element){
            return false;
        }
        currentNode = currentNode->next;
        otherNode = otherNode->next;
    }
    return (currentNode == nullptr && otherNode == nullptr);
}

template <typename Data>
bool SetLst<Data>::operator!=(const SetLst<Data> & setLst) const noexcept {
    return !(*this == setLst);
}

// Specific member functions (inherited from OrderedDictionaryContainer)

template <typename Data>
const Data &  SetLst<Data>::Min() const {
    if(size == 0){
        throw std::length_error("SetLst is empty.");
    }else{
        return head->element;
    }
}

template <typename Data>
Data SetLst<Data>::MinNRemove() {
    if(size == 0){
        throw std::length_error("SetLst is empty.");
    }else{
        Data minValue = head->element;
        List<Data>::RemoveFromFront();
        return minValue;
    }
}

template <typename Data>
void SetLst<Data>::RemoveMin() {
    if(size == 0){
        throw std::length_error("SetLst is empty.");
    }else{
        List<Data>::RemoveFromFront();
    }
}

template <typename Data>
const Data & SetLst<Data>::Max() const {
    if(size == 0){
        throw std::length_error("SetLst is empty.");
    }else{
        return tail->element;
    }
}

template <typename Data>
Data SetLst<Data>::MaxNRemove() {
    if(size == 0){
        throw std::length_error("SetLst is empty.");
    }else{
        Data maxValue = tail->element;
        List<Data>::RemoveFromBack();
        return maxValue;
    }
}

template <typename Data>
void SetLst<Data>::RemoveMax() {
    if(size == 0){
        throw std::length_error("SetLst is empty.");
    }else{
        List<Data>::RemoveFromBack();
    }
}

template <typename Data>
const Data & SetLst<Data>::Predecessor(const Data & value) const {
    if(size == 0){
        throw std::length_error("SetLst is empty.");
    }

    Node ** positionNode = BinarySearch(value);

    if(positionNode == &head){
        throw std::length_error("No predecessor found");
    }

    Node * predecessorNode = head;
    while(&(predecessorNode->next) != positionNode){
        predecessorNode = predecessorNode->next;
    }
    
    return predecessorNode->element;
}

template <typename Data>
Data SetLst<Data>::PredecessorNRemove(const Data & value) {
    Data predecessor = Predecessor(value);
    Remove(predecessor);
    return predecessor;
}

template <typename Data>
void SetLst<Data>::RemovePredecessor(const Data & value) {
    Remove(Predecessor(value));
}

template <typename Data>
const Data & SetLst<Data>::Successor(const Data & value) const {
    if(size == 0){
        throw std::length_error("SetLst is empty.");
    }

    Node ** positionNode = BinarySearch(value);

    if(*positionNode != nullptr && (*positionNode)->element == value){
        if((*positionNode)->next == nullptr){
            throw std::length_error("No successor found");
        }
        return (*positionNode)->next->element;
    }else{
        if(*positionNode == nullptr){
            throw std::length_error("No successor found");
        }
        return (*positionNode)->element;
    }
}

template <typename Data>
Data SetLst<Data>::SuccessorNRemove(const Data & value) {
    Data successor = Successor(value);
    Remove(successor);
    return successor;
}

template <typename Data>
void SetLst<Data>::RemoveSuccessor(const Data & value) {
    Remove(Successor(value));
}

// Specific member functions (inherited from DictionaryContainer)

template <typename Data>
bool SetLst<Data>::Insert(const Data & value) {
    Node ** positionNode = BinarySearch(value);
    
    if(*positionNode != nullptr && (*positionNode)->element == value){
        return false;
    } 

    Node * newNode = new Node(value);
    newNode->next = *positionNode;
    *positionNode = newNode;

    if(newNode->next == nullptr){
        tail = newNode;
    }
    
    ++size;
    return true;
}

template <typename Data>
bool SetLst<Data>::Insert(Data && value) {
    Node ** positionNode = BinarySearch(value);
    
    if(*positionNode != nullptr && (*positionNode)->element == value){
        return false;
    } 

    Node * newNode = new Node(std::move(value));
    newNode->next = *positionNode;
    *positionNode = newNode;

    if(newNode->next == nullptr){
        tail = newNode;
    }
    
    ++size;
    return true;
}

template <typename Data>
bool SetLst<Data>::Remove(const Data & value) {
    if (head == nullptr) { 
        return false;
    }
    Node ** foundNode = BinarySearch(value);
    if (*foundNode == nullptr || (*foundNode)->element != value) {
        return false;
    }

    Node * nodeToRemove = *foundNode;
    *foundNode = nodeToRemove->next;

    if (nodeToRemove == tail) {
        if (head == nullptr) {
            tail = nullptr;
        } else {
            Node * temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            tail = temp;
        }
    }

    delete nodeToRemove;
    --size;
    return true;
}

// Specific member function (inherited from LinearContainer)
template <typename Data>
const Data & SetLst<Data>::operator[](const ulong index) const {
    if(index >= size){
        throw std::out_of_range("Index out of bounds in SetLst");
    } 

    Node * currentNode = head;
    for(ulong i=0; i<index; ++i){
        currentNode = currentNode->next;
    }
    return currentNode->element;
}

// Specific member function (inherited from TestableContainer)

template <typename Data>
bool SetLst<Data>::Exists(const Data & value) const noexcept {
    Node ** foundNode = BinarySearch(value);
    return (*foundNode != nullptr) && ((*foundNode)->element == value);
}

// Specific member function (inherited from ClearableContainer)

template <typename Data>
void SetLst<Data>::Clear() {
    while(size > 0){
        RemoveMin();
    }
}

/* ************************************************************************** */

// Auxiliary functions binary search

template <typename Data>
typename SetLst<Data>::Node ** SetLst<Data>::BinarySearch(const Data & value) const noexcept {
    Node ** currentElement = const_cast<Node **>(&head);
    while(*currentElement != nullptr && (*currentElement)->element < value){
        currentElement = &((*currentElement)->next);
    }
    return currentElement;
}

}