#include <cstring> // For std::memcpy
#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

std::vector<int> v;

template <typename T, typename Allocator = std::allocator> class Array {
  private:
    // Почти всегда лучше вместо голых указателей использовать умные указатели,
    // например, std::shared_ptr. Почитай доки.
    T *_data;
    size_t _size;
    size_t _capacity;

    // Используем конфигурируемый аллокатор, по дефолту - дефолтный, который new
    // и прочая хуйня.
    Allocator allocator;

    // Реалокация памяти
    void reallocate(size_t newCapacity) {
        // Аллокация при помощи allocator_traits
        using traits = std::allocator_traits<Allocator>;
        T *newData = traits::allocate(allocator, newCapacity * sizeof(T));
        // T *newData = (T *)::operator new(newCapacity * sizeof(T));

        if (newCapacity < _size) {
            _size = newCapacity;
        }

        for (size_t i = 0; i < _size; ++i) {
            new (&newData[i]) T(std::move(_data[i]));
        }

        for (size_t i = 0; i < _size; ++i) {
            _data[i].~T();
        }

        // Освобождение памяти
        // traits::deallocate()
        ::operator delete(_data, _capacity * sizeof(T));
        _data = newData;
        _capacity = newCapacity;
    }

  public:
    // Default Constructor
    Array() : _data(nullptr), _size(0), _capacity(0) { reallocate(2); }

    // Destructor
    ~Array() {
        clear();
        ::operator delete(_data, _capacity * sizeof(T));
    }

    // Copy Constructor
    Array(const Array &other) : _data(nullptr), _size(0), _capacity(0) {
        reallocate(other.capacity());
        for (size_t i = 0; i < other._size; ++i) {
            push_back(other._data[i]);
        }
    }

    // Copy Assignment Operator
    Array &operator=(const Array &other) {
        if (this == &other) {
            return *this;
        }
        clear();
        reallocate(other.capacity());
        for (size_t i = 0; i < other._size; ++i) {
            push_back(other._data[i]);
        }
        return *this;
    }

    // Move Constructor
    Array(Array &&other) noexcept
        : _data(other._data), _size(other._size), _capacity(other._capacity) {
        other._data = nullptr;
        other._size = 0;
        other._capacity = 0;
    }

    // Move Assignment Operator
    Array &operator=(Array &&other) noexcept {
        if (this == &other) {
            return *this;
        }
        clear();
        ::operator delete(_data, _capacity * sizeof(T));

        _data = other._data;
        _size = other._size;
        _capacity = other._capacity;

        other._data = nullptr;
        other._size = 0;
        other._capacity = 0;
        return *this;
    }

    void push_back(const T &value) {
        if (_size >= _capacity) {
            reallocate(_capacity + _capacity / 2);
        }
        new (&_data[_size]) T(value);
        _size++;
    }

    void push_back(T &&value) {
        if (_size >= _capacity) {
            reallocate(_capacity + _capacity / 2);
        }
        new (&_data[_size]) T(std::move(value));
        _size++;
    }

    template <typename... Args> T &emplace_back(Args &&...constructorArgs) {
        if (_size >= _capacity) {
            reallocate(_capacity + _capacity / 2);
        }
        new (&_data[_size]) T(std::forward<Args>(constructorArgs)...);
        return _data[_size++];
    }

    void pop_back() {
        if (_size > 0) {
            _size--;
            _data[_size].~T();
        }
    }

    void clear() {
        for (size_t i = 0; i < _size; ++i) {
            _data[i].~T();
        }
        _size = 0;
    }

    size_t size() const { return _size; }

    size_t capacity() const { return _capacity; }

    const T &operator[](size_t index) const {
        if (index >= _size) {
            throw std::out_of_range("Index out of range");
        }
        return _data[index];
    }

    T &operator[](size_t index) {
        if (index >= _size) {
            throw std::out_of_range("Index out of range");
        }
        return _data[index];
    }

    void reserve(size_t n) {
        if (n > _capacity) {
            reallocate(n);
        }
    }

    T &front() {
        if (_size == 0) {
            throw std::out_of_range("Array is empty");
        }
        return _data[0];
    }

    const T &front() const {
        if (_size == 0) {
            throw std::out_of_range("Array is empty");
        }
        return _data[0];
    }

    T &back() {
        if (_size == 0) {
            throw std::out_of_range("Array is empty");
        }
        return _data[_size - 1];
    }

    const T &back() const {
        if (_size == 0) {
            throw std::out_of_range("Array is empty");
        }
        return _data[_size - 1];
    }
};
