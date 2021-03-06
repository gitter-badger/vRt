#pragma once

#include "../../vRt_subimpl.inl"

namespace _vt {
    using namespace vt;

    // make default descriptor info for buffers
    template<VmaMemoryUsage U>
    inline VkDescriptorBufferInfo RoledBuffer<U>::_descriptorInfo() const {
        //return VkDescriptorBufferInfo(vk::DescriptorBufferInfo(_buffer, 0u, VK_WHOLE_SIZE));
        return bufferDescriptorInfo(_buffer);
    };

    // destructor of advanced buffer
    template<VmaMemoryUsage U>
    inline RoledBuffer<U>::~RoledBuffer() {
        vmaDestroyBuffer(_device.lock()->_allocator, _buffer, _allocation);
    };

};
