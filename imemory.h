#ifndef __IMemory_h__
#define __IMemory_h__

#include "brain.h"
#include "stdlibs.h"

namespace brain
{
    class IMemory
    {
    public:
        virtual std::string serialize() = 0;
        virtual void deserialize(std::string fromString) = 0;
        virtual void getVisualization(const char* filename) = 0;

        virtual std::list<std::pair<LinkPtr, NodePtr> > getParentLinks(NodePtr node) = 0;
        virtual std::list<std::pair<LinkPtr, NodePtr> > getChildrenLinks(NodePtr node) = 0;

        virtual NodePtr remember(std::vector<NodePtr>* nodes, std::vector<LinkPtr>* links, int amount, NodeGroupProcessorPtr sender) = 0;
    };
}
#endif
