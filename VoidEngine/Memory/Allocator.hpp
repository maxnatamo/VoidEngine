#pragma once

#include <memory>
#include <type_traits>
#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Core/EngineTypes.hpp>
#include <VoidEngine/Debug/Log.hpp>

namespace VOID_NS {
    template<typename T>
    class Ptr : public std::shared_ptr<T> {
    protected:
        using ptr = std::shared_ptr<T>;

    public:
        Ptr() : ptr() {}
        Ptr(T *t) : ptr(t) {}
        Ptr(ptr t) : ptr(t) {}
        Ptr(const ptr &t) : ptr(t) {}
        Ptr(std::nullptr_t t) : ptr( t) {}
        
        operator T *() { return this->get(); }
        operator const T *() const { return this->get(); }
    };

    class Allocator {
        static inline void *Allocate(u64 size) {
            return calloc(1, size);
        }

        static inline void *Allocate(u32 count, u64 size) {
            return calloc(count, size);
        }

        template<typename T, typename ... Args>
        static inline T *Allocate(Args&& ... args) {
            T *ptr = ::new T(std::forward<Args>(args)...);
            Logger::Assert(ptr != nullptr, TranslateString(Error::ErrorAllocation));

            return ptr;
        }

        template<typename T>
        static inline void Free(T *ptr) {
            ::delete(ptr);
        }
    };
};
