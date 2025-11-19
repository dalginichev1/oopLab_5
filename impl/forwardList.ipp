#include <iostream>

template <typename T>
ForwardList<T>::Node::Node(const T& value): data(value), next(nullptr) {}

template <typename T>
ForwardList<T>::Node::Node(T&& value) noexcept: data(std::move(value)), next(nullptr) {}

template <typename T>
ForwardList<T>::Iterator::Iterator(): it(nullptr) {}

template <typename T>
ForwardList<T>::Iterator::Iterator(Node* node): it(node) {}

template <typename T>
auto ForwardList<T>::Iterator::operator*() const -> reference
{
    return it->data;
}

template <typename T>
auto ForwardList<T>::Iterator::operator->() const -> pointer
{
    return &it->data;
}

template <typename T>
auto ForwardList<T>::Iterator::operator++() -> Iterator&
{
    it = it->next;
    return *this;
}

template <typename T>
auto ForwardList<T>::Iterator::operator++(int) -> Iterator
{
    Iterator tmp = *this;
    ++(*this);
    return tmp;
}

template <typename T>
bool ForwardList<T>::Iterator::operator==(const Iterator& other) const
{
    return it == other.it;
}

template <typename T>
bool ForwardList<T>::Iterator::operator!=(const Iterator& other) const
{
    return it != other.it;
}

template<typename T>
ForwardList<T>::ForwardList(std::pmr::memory_resource* resource): allocator(resource), head(nullptr) {}

template<typename T>
void ForwardList<T>::push_front(const T& value)
{
    Node * new_node = allocator.allocate(1);
    allocator.construct(new_node, value);
    new_node->next = head;
    head = new_node;
}

template<typename T>
void ForwardList<T>::push_front(T&& value)
{
    Node* new_node = allocator.allocate(1);
    allocator.construct(new_node, std::move(value));
    new_node->next = head;
    head = new_node;
}

template<typename T>
void ForwardList<T>::pop_front()
{
    if (head)
    {
        Node* tmp = head;
        head = head->next;
        std::allocator_traits<decltype(allocator)>::destroy(allocator, tmp);
        allocator.deallocate(tmp, 1);
    }
}

template<typename T>
void ForwardList<T>::clear()
{
    while (head)
    {
        pop_front();
    }
}

template<typename T>
auto ForwardList<T>::begin() -> Iterator
{
    return Iterator(head);
}

template<typename T>
auto ForwardList<T>::end() -> Iterator
{
    return Iterator(nullptr);
}

template<typename T>
auto ForwardList<T>::begin() const -> Iterator
{
    return Iterator(head);
}

template<typename T>
auto ForwardList<T>::end() const -> Iterator
{
    return Iterator(nullptr);
}

template<typename T>
bool ForwardList<T>::empty() const
{
    return head == nullptr;
}

template<typename T>
ForwardList<T>::~ForwardList()
{
    clear();
}

