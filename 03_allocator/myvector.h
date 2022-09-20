#include <memory.h>

template <typename T, typename Allocator = std::allocator<T>>
struct MyVector {
    public:
        MyVector() : m_size(0), m_allocator() {
        }

        ~MyVector() = default;

        void push_back(const T& element) {
            T* ptr =  basic_alloc_traits::allocate(m_allocator, 1);
            basic_alloc_traits::construct(m_allocator, ptr, element);

            if (m_size == 0)
            m_data = ptr;

            ++m_size;
        }

        void pop_back() {
            basic_alloc_traits::destroy(m_allocator, m_data + m_size);
            basic_alloc_traits::deallocate(m_allocator, m_data + m_size, 1);

            --m_size;
        }

        size_t size() const {
            return m_size;
        }

        T& operator[](size_t pos) { 
            return *(m_data + pos); 
        }

        const T& operator[](size_t pos) const {
            return *(m_data + pos); 
        }

        T* begin() { 
            return m_data;
        }

        T* end() {
            return m_data + m_size;
        }

        const T* cbegin() const {
            return m_data;
        }

        const T* cend() const {
            return m_data + m_size;
        }

    private:
        std::size_t m_size;
        T* m_data = nullptr;

        using basic_alloc = typename std::allocator_traits<Allocator>::template rebind_alloc<T>;
        using basic_alloc_traits = typename std::allocator_traits<Allocator>::template rebind_traits<T>;

        basic_alloc m_allocator;
};    
