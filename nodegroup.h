#ifndef __NodeGroupProcessor_h__
#define __NodeGroupProcessor_h__


#include "brain.h"
#include "stdlibs.h"

namespace brain
{
    class NodeGroupProcessor
    {
            public: NodeGroupProcessor(MemoryModulePtr memoryModule, IMemoryPtr storage);
            public: void processNode(NodePtr node);
    };
}

#endif
