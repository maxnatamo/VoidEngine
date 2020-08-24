#ifndef VOID_CORE_ALLOCATOR_H__
#define VOID_CORE_ALLOCATOR_H__

#include <memory>
#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Core/Errors.hpp>
#include <VoidEngine/Debug/Log.hpp>

namespace VOID_NS {
    class Allocator {
        friend Logger;

    public:
        /**
         *  Allocator::Allocate(size_t)
         *
         *  Allocate memory using class/type size.
         */
        static inline void *Allocate(u64 size) {
            m_AllocatedSize += size;
            return calloc(1, size);
        }

        /**
         *  Allocator::Allocate(Args&&...)
         *
         *  Allocate memory using class specification,
         *  with optional arguments.
         */
        template<class T, typename... Args >
        static inline T *Allocate(Args&&... args) {
            m_AllocatedSize += sizeof(T);
            T *ptr = ::new T(std::forward<Args>(args)...);
            VOID_ASSERT(ptr != nullptr, VOID_ERR_ALLOC);

            return ptr;
        }

        /**
         *  Allocator::Free(T *)
         *
         *  Free memory, using a raw pointer.
         */
        template<class T>
        static inline void Free(T *ptr) {
            m_AllocatedSize -= sizeof(ptr);
            ::free(ptr);
        }

    protected:
        static u64 m_AllocatedSize;

    private:
    };
};

#if defined(VOID_CUSTOM_ALLOC)
void *operator new (u64);
void operator delete(void *) noexcept;
#endif /* VOID_CUSTOM_ALLOC */

#endif /* VOID_CORE_ALLOCATOR_H__ */
