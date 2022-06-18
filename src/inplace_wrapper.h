#ifndef CPPTOOLS_INPLACE_WRAPPER_H
#define CPPTOOLS_INPLACE_WRAPPER_H

#include<cstring>

/*
    This class provides a way to manage:
    - Placement constructors easier
    - Manually manage object destruction
    - Bypass missing/deleted move assignement and constructors
      (This is usually not recommanded)
*/
template<typename T>
class inplace_wrapper {
    using byte = unsigned char;
    byte buf[sizeof(T)];
    public:
        template<typename... Args>
        inline T* create(Args&&... args) {
            return reinterpret_cast<T*>(
                new ((void*)buf) T(std::forward<Args>(args)...)
            );
        }
        inline T* addr() {
            return reinterpret_cast<T*>((void*)buf);
        }
        inline T& get() {
            return *addr();
        }
        const T *operator->() const {
            return addr();
        }
        T *operator->() {
            return addr();
        }
        inline void destroy() {
            get().~T();
        }
        inline void* move(void* destination) {
            // The following does not work with deleted move assignement constructor
            // return new (destination) T(std::move(*get()));
            // We need to bypass this constructor:
            return memcpy(destination, (void*)buf, sizeof(buf));
        }
        inline void* move(inplace_wrapper<T>& destination) {
            return move((void*)destination.buf);
        }
};

/*
    Should we handle alignement?
    https://stackoverflow.com/questions/9123022/preventing-a-destructor-from-running-in-c

    char buffer[sizeof(T) + alignof(T)];
    char* aligned_buffer = buffer + alignof(T) - reinterpret_cast<intptr_t>(buffer) % alignof(T);
    T* object = new (aligned_buffer) T;
*/


#endif // CPPTOOLS_INPLACE_WRAPPER_H