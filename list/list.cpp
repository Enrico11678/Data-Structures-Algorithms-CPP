
namespace lasd {

/* ************************************************************************** */

// Node Specific constructor

template <typename Data>
List<Data>::Node::Node(Data && value) noexcept {
    std::swap(element, value);
}

// Node Move constructor
template <typename Data>
List<Data>::Node::Node(Node && node) noexcept {
    std::swap(element, node.element);
    std::swap(next, node.next);
}

// Node destructor
template <typename Data>
List<Data>::Node::~Node() {}

// Node Comparison operators

template <typename Data>
bool List<Data>::Node::operator==(const Node & node) const noexcept {
    return (element == node.element) && ((next == nullptr && node.next == nullptr) || ((next != nullptr && node.next != nullptr) && (*next == *node.next)));
}

template <typename Data>
bool List<Data>::Node::operator!=(const Node & node) const noexcept {
    return !(*this == node);
}

// Node specific member function

template <typename Data>
typename List<Data>::Node * List<Data>::Node::Clone(Node * newTail) {
    if (next == nullptr) {
    return newTail;
  } else {
    Node * newNode = new Node(element);
    newNode->next = next->Clone(newTail);
    return newNode;
  }
}

/* ************************************************************************** */

// List

// Specific constructor

template <typename Data>
List<Data>::List(const TraversableContainer<Data> & travCont) {
    travCont.Traverse(
        [this](const Data & value){
            InsertAtBack(value);
        }
    );
}

template <typename Data>
List<Data>::List(MappableContainer<Data> && mapCont) {
    mapCont.Map(
        [this](Data & value){
            InsertAtBack(std::move(value));
        }
    );
}

// Copy constructor

template <typename Data>
List<Data>::List(const List<Data> & list) {
    head = nullptr;
    tail = nullptr;
    size = 0;
    if(list.tail != nullptr){
        tail = new Node(*list.tail);
        head = list.head->Clone(tail);
        size = list.size;
    }
}

// Move constructor

template <typename Data>
List<Data>::List(List<Data> && list) noexcept {
    std::swap(head, list.head);
    std::swap(tail, list.tail);
    std::swap(size, list.size);
}

// Destructor

template <typename Data>
List<Data>::~List() {
    Clear();
}

// Copy assignment

template <typename Data>
List<Data> & List<Data>::operator=(const List<Data> & list) {
    if(this != &list){
        List<Data> tempList(list);
        std::swap(head, tempList.head);
        std::swap(tail, tempList.tail);
        std::swap(size, tempList.size);
    }
    
    return *this;
}

// Move assignment

template <typename Data>
List<Data> & List<Data>::operator=(List<Data> && list) noexcept {
    std::swap(head, list.head);
    std::swap(tail, list.tail);
    std::swap(size, list.size);
    
    return *this;
}

// Comparison operators

template <typename Data>
bool List<Data>::operator==(const List & list) const noexcept {
     if(size != list.size){
        return false;
     }

     Node * currentNode = head;
     Node * otherNode = list.head;
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
bool List<Data>::operator!=(const List & list) const noexcept {
    return !(*this == list);
}

// Specific member functions

template <typename Data>
void List<Data>::InsertAtFront(const Data & value) {
    Node * newNode = new Node(value);
    newNode->next = head;
    head = newNode;
    if(size == 0){
        tail = head;
    }
    ++size;
}

template <typename Data>
void List<Data>::InsertAtFront(Data && value) {
    Node * newNode = new Node(std::move(value));
    newNode->next = head;
    head = newNode;
    if(size == 0){
        tail = head;
    }
    ++size;
}

template <typename Data>
void List<Data>::RemoveFromFront() {
    if(size == 0){
        throw std::length_error("List is empty.");
    }else{
        Node * tempNode = head;
        head = head->next;
        tempNode->next = nullptr;
        delete tempNode;
        --size;
        if(size == 0){
            tail = nullptr;
        }
    }
}

template <typename Data>
Data List<Data>::FrontNRemove() {
    if(size == 0){
        throw std::length_error("List is empty.");
    }else{
        Data value = Front();
        RemoveFromFront();
        return value;
    }
}

template <typename Data>
void List<Data>::InsertAtBack(const Data & value) {
    Node * newNode = new Node(value);
    if(tail == nullptr){
        head = tail = newNode;
    }else{
        tail->next = newNode;
    }
    tail = newNode;
    ++size;
}

template <typename Data>
void List<Data>::InsertAtBack(Data && value) {
    Node * newNode = new Node(std::move(value));
    if(tail == nullptr){
        head = tail = newNode;
    }else{
        tail->next = newNode;
    }
    tail = newNode;
    ++size;
}

template <typename Data>
void List<Data>::RemoveFromBack() {
    if(size == 0){
        throw std::length_error("List is empty.");
    }else if(size == 1){
        delete head;
        head = tail = nullptr;
    }else{
        Node * currentNode = head;
        while(currentNode->next != tail){
            currentNode = currentNode->next;
        }
        delete tail;
        tail = currentNode;
        tail->next = nullptr;
    }
    --size;
}

template <typename Data>
Data List<Data>::BackNRemove() {
    if(size == 0){
        throw std::length_error("List is empty.");
    }else{
        Data value = Back();
        RemoveFromBack();
        return value;
    }
}

// Specific member functions (inherited from MutableLinearContainer)

template <typename Data>
Data & List<Data>::operator[](const ulong index) {
    if(index >= size){
        throw std::out_of_range("Access at index " + std::to_string(index) + " exceeds list size " + std::to_string(size) + ".");
    }else{
        Node * currentNode = head;
        for(ulong i=0; i<index; i++){
            currentNode = currentNode->next;
        }
        return currentNode->element;
    }
}

template <typename Data>
Data & List<Data>::Front() {
    if(size == 0){
        throw std::length_error("List is empty.");
    }else{
        return head->element;
    }
}

template <typename Data>
Data & List<Data>::Back() {
    if(size == 0){
        throw std::length_error("List is empty.");
    }else{
        return tail->element;
    }
} 

// Specific member functions (inherited from LinearContainer)

template <typename Data>
const Data & List<Data>::operator[](const ulong index) const {
    if(index >= size){
        throw std::out_of_range("Access at index " + std::to_string(index) + " exceeds list size " + std::to_string(size) + ".");
    }else{
        Node * currentNode = head;
        for(ulong i=0; i<index; i++){
            currentNode = currentNode->next;
        }
        return currentNode->element;
    }
}

template <typename Data>
const Data & List<Data>::Front() const {
    if(size == 0){
        throw std::length_error("List is empty.");
    }else{
        return head->element;
    }
}

template <typename Data>
const Data & List<Data>::Back() const {
    if(size == 0){
        throw std::length_error("List is empty.");
    }else{
        return tail->element;
    }
}

// Specific member function (inherited from MappableContainer)

template <typename Data>
void List<Data>::Map(MapFun fun) {
    PreOrderMap(fun);
}

// Specific member function (inherited from PreOrderMappableContainer)

template <typename Data>
void List<Data>::PreOrderMap(MapFun fun) {
    Node * currentNode = head;
    
    while(currentNode != nullptr){
        fun(currentNode->element);
        currentNode = currentNode->next;
    }
}

// Specific member function (inherited from PostOrderMappableContainer)

template <typename Data>
void List<Data>::PostOrderMap(MapFun fun) {
    if(head != nullptr){
        PostOrderMapAuxiliar(head, fun);
    }
}

// Specific member function (inherited from TraversableContainer)

template <typename Data>
void List<Data>::Traverse(TraverseFun fun) const {
    PreOrderTraverse(fun);
}

// Specific member function (inherited from PreOrderTraversableContainer)

template <typename Data>
void List<Data>::PreOrderTraverse(TraverseFun fun) const {
    Node * currentNode = head;
    
    while(currentNode != nullptr){
        fun(currentNode->element);
        currentNode = currentNode->next;
    }
}

// Specific member function (inherited from PostOrderTraversableContainer)

template <typename Data>
void List<Data>::PostOrderTraverse(TraverseFun fun) const {
    if(head != nullptr){
        PostOrderTraverseAuxiliar(head, fun);
    }
}

// Specific member function (inherited from ClearableContainer)

template <typename Data>
void List<Data>::Clear() {
    Node * currentNode = head;
    while (currentNode != nullptr) {
        Node * nextNode = currentNode->next;
        delete currentNode;
        currentNode = nextNode;
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
}

// Auxiliary functions

template <typename Data>
void List<Data>::PostOrderMapAuxiliar(Node * newNode, MapFun fun) {
    if(newNode->next != nullptr){
        PostOrderMapAuxiliar(newNode->next, fun);
    }
    fun(newNode->element);
}

template <typename Data>
void List<Data>::PostOrderTraverseAuxiliar(Node * newNode, TraverseFun fun) const {
    if(newNode->next != nullptr){
        PostOrderTraverseAuxiliar(newNode->next, fun);
    }
    fun(newNode->element);
}

}
