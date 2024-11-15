#include <iostream>
#include <iterator>
#include <memory>
#include <memory_resource>
#include <stdexcept>

template <typename T, typename Allocator = std::pmr::polymorphic_allocator<T>>
class PmrQueue {
  public:
    struct Node {
        T data;
        std::shared_ptr<Node> next;

        Node(const T &data, const Allocator &alloc)
            : data(data), next(nullptr) {}
    };

    // Iterator definition
    class Iterator {
      public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T *;
        using reference = T &;

        explicit Iterator(std::shared_ptr<Node> node) : current(node) {}

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
        std::shared_ptr<Node> current;
    };

    // Adjusted allocator for Node type
    using NodeAllocator =
        typename std::allocator_traits<Allocator>::template rebind_alloc<Node>;

    explicit PmrQueue(const Allocator &alloc = {})
        : alloc_(alloc), node_alloc_(alloc.resource()), head_(nullptr),
          tail_(nullptr) {}

    PmrQueue(const PmrQueue &other)
        : alloc_(other.alloc_), node_alloc_(other.node_alloc_), head_(nullptr),
          tail_(nullptr), size_(0) {
        for (auto it = other.begin(); it != other.end(); ++it) {
            push(*it);
        }
    }

    PmrQueue &operator=(const PmrQueue &other) {
        if (this != &other) {
            clear();
            alloc_ = other.alloc_;
            node_alloc_ = other.node_alloc_;
            for (auto it = other.begin(); it != other.end(); ++it) {
                push(*it);
            }
        }
        return *this;
    }

    PmrQueue(PmrQueue &&other) noexcept
        : alloc_(std::move(other.alloc_)),
          node_alloc_(std::move(other.node_alloc_)),
          head_(std::move(other.head_)), tail_(std::move(other.tail_)),
          size_(other.size_) {
        other.head_ = other.tail_ = nullptr;
        other.size_ = 0;
    }

    PmrQueue &operator=(PmrQueue &&other) noexcept {
        if (this != &other) {
            clear();
            alloc_ = std::move(other.alloc_);
            node_alloc_ = std::move(other.node_alloc_);
            head_ = std::move(other.head_);
            tail_ = std::move(other.tail_);
            size_ = other.size_;
            other.head_ = other.tail_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    ~PmrQueue() { clear(); }

    void push(const T &value) {
        auto node = std::allocate_shared<Node>(node_alloc_, value, alloc_);
        if (!head_) {
            head_ = tail_ = node;
        } else {
            tail_->next = node;
            tail_ = node;
        }
        ++size_;
    }

    void pop() {
        if (!head_) {
            throw std::out_of_range("Queue is empty");
        }
        head_ = head_->next;
        if (!head_) {
            tail_ = nullptr;
        }
        --size_;
    }

    T &front() {
        if (!head_) {
            throw std::out_of_range("Queue is empty");
        }
        return head_->data;
    }

    bool contains(const T &value) const {
        for (const auto &item : *this) {
            if (item == value) {
                return true;
            }
        }
        return false;
    }

    bool empty() const { return head_ == nullptr; }

    size_t size() const { return size_; }

    void clear() {
        while (!empty()) {
            pop();
        }
    }

    Iterator begin() { return Iterator(head_); }
    Iterator end() { return Iterator(nullptr); }

    Iterator begin() const { return Iterator(head_); }
    Iterator end() const { return Iterator(nullptr); }

  private:
    Allocator alloc_;            // Original allocator for T type
    NodeAllocator node_alloc_;   // Allocator for Node type
    std::shared_ptr<Node> head_; // Head of the queue
    std::shared_ptr<Node> tail_; // Tail of the queue
    size_t size_ = 0;
};
