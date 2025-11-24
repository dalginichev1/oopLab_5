#pragma once

#include <iterator>
#include <memory_resource>

template <typename T>
class ForwardList {
  private:
    struct Node {
        T data;
        Node* next;

        Node(const T& value);
        Node(T&& value) noexcept;
    };

    Node* head;
    std::pmr::polymorphic_allocator<Node> allocator;

  public:
    class Iterator {
      private:
        Node* it;

      public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        Iterator();
        Iterator(Node* node);

        reference operator*() const;
        pointer operator->() const;

        Iterator& operator++();
        Iterator operator++(int);

        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
    };

    using iterator = Iterator;
    using const_iterator = Iterator;

    ForwardList(std::pmr::memory_resource* resource);
    ~ForwardList();

    void push_front(const T& value);
    void push_front(T&& value);
    void pop_front();
    void clear();

    Iterator begin();
    Iterator end();
    Iterator begin() const;
    Iterator end() const;

    bool empty() const;
};

#include "forwardList.ipp"