#include <iostream>
#include <iterator>
#include <memory>
#include <stdexcept>

template <class T> using ptr = std::shared_ptr<T>;

template <typename T, typename Allocator = std::pmr::polymorphic_allocator<T>>
class PmrQueue {
  public:
    struct Node {
        T data;
        Node *next = nullptr;

        Node(const T &data) : data(data) {}
    };

    // Iterator definition
    class Iterator {
      public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T *;
        using reference = T &;

        Iterator(Node *node) : current(node) {}

        reference operator*() const { return current->data; }
        pointer operator->() { return &(current->data); }

        Iterator &operator++() {
            current = current->next;
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        friend bool operator==(const Iterator &a, const Iterator &b) {
            return a.current == b.current;
        }
        friend bool operator!=(const Iterator &a, const Iterator &b) {
            return a.current != b.current;
        }

      private:
        Node *current;
    };

    // Adjusted allocator for Node type
    using NodeAllocator =
        typename std::allocator_traits<Allocator>::template rebind_alloc<Node>;

    PmrQueue(const Allocator &alloc = {})
        : alloc_(alloc), node_alloc_(alloc), head_(nullptr), tail_(nullptr) {}

    ~PmrQueue() { clear(); }

    void push(const T &value) {

        // auto node = std::allocate_shared<Node>(alloc_, value);
        Node *node = node_alloc_.allocate(1);
        node_alloc_.construct(node, value);

        if (!head_) {
            head_ = tail_ = node;
        } else {
            tail_->next = node;
            tail_ = node;
        }
    }

    void pop() {
        if (!head_) {
            throw std::out_of_range("Queue is empty");
        }
        Node *temp = head_;
        head_ = head_->next;

        // node_alloc_.destroy(temp);       // Destroy Node
        std::allocator_traits<NodeAllocator>::destroy(node_alloc_, temp);
        node_alloc_.deallocate(temp, 1); // Deallocate Node memory

        if (!head_) {
            tail_ = nullptr;
        }
    }

    T &front() {
        if (!head_) {
            throw std::out_of_range("Queue is empty");
        }
        return head_->data;
    }

    bool empty() const { return head_ == nullptr; }

    Iterator begin() { return Iterator(head_); }
    Iterator end() { return Iterator(nullptr); }

  private:
    Allocator alloc_;          // Original allocator for T type
    NodeAllocator node_alloc_; // Allocator for Node type
    Node *head_;
    Node *tail_;

    void clear() {
        while (head_) {
            pop();
        }
    }
};
