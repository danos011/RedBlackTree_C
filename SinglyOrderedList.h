#ifndef REDBLACKTREE_SINGLYORDEREDLIST_H
#define REDBLACKTREE_SINGLYORDEREDLIST_H

template <class T>
class SinglyOrderedList
{
private:

    template <class T>
    struct Node
    {
        T item_;
        Node<T>* next_;

        explicit Node(T item, Node<T>* next = nullptr) : item_(item), next_(next) { }
    };

    size_t count_ = 0;
    Node<T>* head_;

    void swap(SinglyOrderedList& other) noexcept;

    void insertNode(Node<T>* node);

    bool deleteNode(std::size_t num);

    Node<T>* searchNode(T item);

public:


    SinglyOrderedList();

    SinglyOrderedList(const SinglyOrderedList<T>& src);

    SinglyOrderedList& operator=(const SinglyOrderedList<T>& right);

    SinglyOrderedList(SinglyOrderedList<T>&& other) noexcept;

    SinglyOrderedList& operator=(SinglyOrderedList<T>&& right) noexcept;

    void print();

    void insertItem(T item) ;

    void deleteItem(std::size_t num);

    bool searchItem(T item) ;

    ~SinglyOrderedList();
};
template <class T>
SinglyOrderedList<T>::SinglyOrderedList() {
    head_ = nullptr;
}

template <class T>
SinglyOrderedList<T>::SinglyOrderedList (const SinglyOrderedList & src)
{}

template <class T>
void SinglyOrderedList<T>::swap(SinglyOrderedList& other) noexcept
{
    std::swap(head_, other.head_);
}

template <class T>
SinglyOrderedList<T>& SinglyOrderedList<T>::operator=(const SinglyOrderedList<T>& right)
{
    if (this != &right) {
        SinglyOrderedList temp(right);
        swap(temp);
    }
    return *this;
}

template <class T>
SinglyOrderedList<T>::SinglyOrderedList(SinglyOrderedList<T>&& other) noexcept :
        head_(other.head_)
{
    other.head_ = nullptr;
}

template <class T>
SinglyOrderedList<T>& SinglyOrderedList<T>::operator=(SinglyOrderedList<T>&& right) noexcept
{
    if (this != &right) {
        swap(right);
    }
    return *this;
}

template <class T>
void SinglyOrderedList<T>::print(){
    Node<T>* current = head_;

    if(current == nullptr){
        std::cout << "Place for translation is empty!" << std::endl;
    }
    else {
        size_t i = 1;
        while (current != nullptr) {
            std::cout << i++ << " " << current->item_ << std::endl;
            current = current->next_;
        }
    }
}

template <class T>
void SinglyOrderedList<T>::insertNode(Node<T>* node)
{
    if (head_ == nullptr)
    {
        head_ = node;
    }
    else if(node->item_ < head_->item_)
    {
        node->next_ = head_;
        head_ = node;
    }
    else
    {
        bool flag = false;
        Node<T> *current = head_;

        while(current->next_ != nullptr)
        {
            if((current->next_)->item_ > node->item_ || current->item_ > node->item_) {
                flag = true;
                break;
            }
            current = current->next_;
        }

        if (flag)
        {
            node->next_ = current->next_;
        }
        current->next_ = node;
    }
    count_++;
}

template <class T>
bool SinglyOrderedList<T>::deleteNode(std::size_t num)
{
    if (head_ == nullptr) {
        throw ErrorEmptyList();
    }

    if( num > count_ || num < 1){
        throw WrongCommand();
    }

    Node<T>* node = head_;
    for(size_t i = 1; i < num; i++){
            node = node->next_;
    }

    if (head_ == nullptr) {
        throw ErrorEmptyList();
    }

    if(node->item_ == head_->item_)
    {
        head_ = node->next_;
    }
    else{
        Node<T> *current = head_;

        while((current->next_)->item_ != node->item_){
            current = current->next_;
        }
        current->next_ = node->next_;
    }
    delete node;
    count_--;
    return true;
}

template <class T>
void SinglyOrderedList<T>::deleteItem(std::size_t num)
{
    if(!deleteNode(num)){
        std::cout << "There is not translate in list!" << std::endl;
    }

}

template <class T>
typename SinglyOrderedList<T>::template Node<T>* SinglyOrderedList<T>::searchNode(T item)
{
    Node<T>* current = head_;
    while (current != nullptr && current->item_ != item) {
        current = current->next_;
    }
    return current;
}

template <class T>
void SinglyOrderedList<T>::insertItem(T item)
{
    insertNode(new Node<T>(item));
}

template <class T>
bool SinglyOrderedList<T>::searchItem(T item)
{
    return (searchNode(item) != nullptr);
}

template <class T>
SinglyOrderedList<T>::~SinglyOrderedList()
{
    Node<T>* current = nullptr;
    Node<T>* next = head_;
    while (next != nullptr) {
        current = next;
        next = next->next_;
        delete current;
    }
}

#endif //REDBLACKTREE_SINGLYORDEREDLIST_H
