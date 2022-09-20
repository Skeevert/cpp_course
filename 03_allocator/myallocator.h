#include <cstdint>
#include <cstdlib>
#include <cstring>

#include <stdexcept>

template <typename T, std::size_t SIZE>
struct MyAllocator {
	using value_type = T;

	template <typename U, std::size_t USIZE>
	MyAllocator(const MyAllocator<U, USIZE>&);

    template <typename U>
    struct rebind
    {
        using other = MyAllocator<U, SIZE>;
    };

    MyAllocator() {
        // Create main buffer for allocations
        m_buffer = static_cast<T*>(std::malloc(SIZE * sizeof(T)));
        if (!m_buffer) {
            throw std::bad_alloc();
        }
    }

    ~MyAllocator() {
        free(m_buffer);
    }

    T* allocate(std::size_t n) {
        std::size_t iter = 0;

        if (n + m_offset > SIZE) {
            throw std::bad_alloc();
        }

        return m_buffer + m_offset++;
    }

    void deallocate (T* p, std::size_t ) {
    }

    MyAllocator(const MyAllocator &other) = delete;
    MyAllocator(MyAllocator &&other) = delete;
    MyAllocator operator=(MyAllocator) = delete;

    template <typename U, typename... Args>
    void construct(U* p, Args&&... args) {
        ::new(p) U(std::forward<Args>(args)...);
    }

    template <typename U>
    void destroy(U* p) {
        p->~U();
    }
private:
    T* m_buffer = nullptr; 
    std::size_t m_offset = 0;
};

