// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#pragma once

#include "DmlReservedResourceWrapper.h"

namespace Dml
{
    class BucketizedBufferAllocator;

    class AllocationInfo : public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::ClassicCom>, IUnknown>
    {
    public:
        AllocationInfo(
            BucketizedBufferAllocator* owner,
            size_t id,
            uint64_t pooledResourceId,
            DmlResourceWrapper* resourceWrapper,
            size_t requestedSize)
            : m_owner(owner)
            , m_allocationId(id)
            , m_pooledResourceId(pooledResourceId)
            , m_resourceWrapper(resourceWrapper)
            , m_requestedSize(requestedSize)
        {}

        ~AllocationInfo();

        BucketizedBufferAllocator* GetOwner() const
        {
            return m_owner;
        }

        ID3D12Resource* GetUavResource() const
        {
            return m_resourceWrapper->GetUavResource();
        }

        ID3D12Resource* GetCopySrcResource() const
        {
            return m_resourceWrapper->GetCopySrcResource();
        }

        ID3D12Resource* GetCopyDstResource() const
        {
            return m_resourceWrapper->GetCopyDstResource();
        }

        ComPtr<DmlResourceWrapper> DetachResourceWrapper() const
        {
            return std::move(m_resourceWrapper);
        }

        size_t GetRequestedSize() const
        {
            return m_requestedSize;
        }

        size_t GetId() const
        {
            return m_allocationId;
        }

        uint64_t GetPooledResourceId() const
        {
            return m_pooledResourceId;
        }

    private:
        BucketizedBufferAllocator* m_owner;
        size_t m_allocationId; // For debugging purposes
        uint64_t m_pooledResourceId = 0;
        Microsoft::WRL::ComPtr<DmlResourceWrapper> m_resourceWrapper;

        // The size requested during Alloc(), which may be smaller than the physical resource size
        size_t m_requestedSize;
    };
} // namespace Dml