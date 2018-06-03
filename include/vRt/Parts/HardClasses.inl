#pragma once
#include "Vulkan.inl"
#include "Enums.inl"

// C++ hard interfaces (which will storing)
namespace _vt { // store in undercover namespace
    class Instance;
    class PhysicalDevice;
    class Device;
    class RadixSort;
    class CommandBuffer;
    class Pipeline;
    class CopyProgram;
    class VertexInput;
    class Accelerator;
    class MaterialsInput;
    


    class Instance : public std::enable_shared_from_this<Instance> {
    public:
        VkInstance _instance;

        operator VkInstance() const { return _instance; }
    };


    class PhysicalDevice : public std::enable_shared_from_this<PhysicalDevice> {
    public:
        friend Instance;
        std::weak_ptr<Instance> _instance;
        VkPhysicalDevice _physicalDevice;

        operator VkPhysicalDevice() const { return _physicalDevice; }
        std::shared_ptr<Instance> _parent() const { return _instance; };
    };


    class Device : public std::enable_shared_from_this<Device> {
    public:
        friend PhysicalDevice;
        std::weak_ptr<PhysicalDevice> _physicalDevice;
        std::shared_ptr<RadixSort> _radixSort; // create native radix sort
        std::shared_ptr<CopyProgram> _copyProgram; // create native pipelines for copying
        VmaAllocator _allocator;
        VkDevice _device;

        operator VkDevice() const { return _device; }
        std::shared_ptr<PhysicalDevice> _parent() const { return _physicalDevice; };
    };


    class CommandBuffer : public std::enable_shared_from_this<CommandBuffer> {
    public:
        friend Device;
        std::weak_ptr<Device> _device;
        VkCommandBuffer _cmd;

        operator VkCommandBuffer() const { return _cmd; }
        std::shared_ptr<Device> _parent() const { return _device; };
    };


    class PipelineLayout : public std::enable_shared_from_this<PipelineLayout> {
    public:
        friend Device;
        std::weak_ptr<Device> _device;
        VkPipelineLayout _pipelineLayout; // has blocked set 0 and 1
        
        operator VkPipelineLayout() const { return _pipelineLayout; }; // no correct conversion
        std::shared_ptr<Device> _parent() const { return _device; };
    };


    class Pipeline: public std::enable_shared_from_this<Pipeline> {
    public:
        friend Device;
        std::weak_ptr<Device> _device;

        std::shared_ptr<Device> _parent() const { return _device; };
    };


    class Accelerator: public std::enable_shared_from_this<Accelerator> {
    public:
        friend Device;
        std::weak_ptr<Device> _device;

        std::shared_ptr<Device> _parent() const { return _device; };
    };

    // this is wrapped buffer class
    class DeviceBuffer: public std::enable_shared_from_this<DeviceBuffer> {
    public:
        friend Device;
        std::weak_ptr<Device> _device;
        VkBuffer _buffer;
        VkBufferView _bufferView;
        VmaAllocation _allocation;
        VmaAllocationInfo _allocationInfo;

        std::shared_ptr<Device> _parent() const { return _device; };
    };

    // this is wrapped image class
    class DeviceImage: public std::enable_shared_from_this<DeviceImage> {
    public:
        friend Device;
        std::weak_ptr<Device> _device;
        VkImage _image;
        VkImageView _imageView;
        VmaAllocation _allocation;
        VmaAllocationInfo _allocationInfo;
        VkImageSubresourceRange _subresourceRange;
        VkImageSubresourceLayers _subresourceLayers;
        VkImageLayout _layout = VK_IMAGE_LAYOUT_GENERAL;
        VkImageLayout _initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        VkFormat _format = VK_FORMAT_R32G32B32A32_SFLOAT;

        std::shared_ptr<Device> _parent() const { return _device; };
    };

    // this class does not using in ray tracing API
    // can be pinned with device
    class RadixSort: public std::enable_shared_from_this<RadixSort> {
    public:
        friend Device;
        std::weak_ptr<Device> _device;
        
        std::shared_ptr<Device> _parent() const { return _device; };
    };

    // this class does not using in ray tracing API
    // can be pinned with device
    class CopyProgram: public std::enable_shared_from_this<CopyProgram> {
    public:
        friend Device;
        std::weak_ptr<Device> _device;

        std::shared_ptr<Device> _parent() const { return _device; };
    };


};