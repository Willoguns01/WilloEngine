#pragma once

#include <memory>

namespace WilloEngine
{
    template <typename Impl_T>
    class PimplClass
    {
    public:
        PimplClass() = default;
        ~PimplClass() {
            impl.reset();
        }     

        std::shared_ptr<Impl_T> impl = nullptr;
    };
}
