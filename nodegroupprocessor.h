#ifndef __NodeGroupProcessor_h__
#define __NodeGroupProcessor_h__


#include "brain.h"
#include "stdlibs.h"

namespace brain
{
    class NodeGroupProcessor
    {
    private:
        MemoryModulePtr memoryModule_;
        IMemoryPtr storage_;
        int level_;
        std::list<RealNodePtr> smallWindow;
        std::list<HypothesisPtr> bigWindow;
        IStrategyPtr strategy;
        NodeGroupProcessorPtr me;

        void cleanupSmallWindow(bool forced);
        void cleanupBigWindow(bool forced);
        void generateHypotheses();
        HypothesisPtr createHypothesis(std::vector<RealNodePtr>* realNodes);
        void sendToTop(HypothesisPtr hypothesis);
        NodePtr sendToMemory(HypothesisPtr hypothesis);
    public:
		NodeGroupProcessor(MemoryModulePtr memoryModule, IMemoryPtr storage, IStrategyPtr strategy, int level);
		void cleanupWindows();
        void processNode(RealNodePtr node);
        void setLevel(int level);
        int getLevel();

    };
}

#endif
