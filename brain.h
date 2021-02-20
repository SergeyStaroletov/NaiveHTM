#ifndef __BRAIN_H
#define __BRAIN_H

#include <boost/smart_ptr.hpp>

#include "basedifftype.h"
#include "predictionstatus.h"
#include "propertyid.h"

namespace brain {
struct Node;
struct Link;
class NodeGroupProcessor;
class PropertyList;
// enum PropertyID::PropertyID;
class RealNode;
class OffsetList;
class Utils;
// enum PredictionStatus::PredictionStatus;
class IProperty;
class IMemory;
class Event;
class IOffset;
struct Pattern;

class Hypothesis;

class OffsetList;
class MemoryModule;
class IStrategy;

class MyStrategy;

class TimeOffset;
class TimeProperty;

class BoostMemory;

template <class baseClass, enum PropertyID::Enum id,
          enum BaseDiffType::Enum diffType>
class BaseOffset;
template <class baseClass, enum PropertyID::Enum id,
          enum BaseDiffType::Enum diffType>
class BaseProperty;

typedef long long NodeId;
typedef long long HyperSensorId;
typedef long long Timestamp;

typedef boost::shared_ptr<Node> NodePtr;
typedef boost::shared_ptr<Link> LinkPtr;
typedef boost::shared_ptr<NodeGroupProcessor> NodeGroupProcessorPtr;
typedef boost::shared_ptr<PropertyList> PropertyListPtr;
typedef boost::shared_ptr<RealNode> RealNodePtr;
typedef boost::shared_ptr<OffsetList> OffsetListPtr;
typedef boost::shared_ptr<IProperty> IPropertyPtr;
typedef boost::shared_ptr<IMemory> IMemoryPtr;
typedef boost::shared_ptr<Event> EventPtr;
typedef boost::shared_ptr<IOffset> IOffsetPtr;
typedef boost::shared_ptr<Pattern> PatternPtr;
typedef boost::shared_ptr<OffsetList> OffsetListPtr;
typedef boost::shared_ptr<Hypothesis> HypothesisPtr;
typedef boost::shared_ptr<IStrategy> IStrategyPtr;
typedef boost::shared_ptr<MemoryModule> MemoryModulePtr;

typedef boost::shared_ptr<TimeOffset> TimeOffsetPtr;
typedef boost::shared_ptr<TimeProperty> TimePropertyPtr;

typedef BaseProperty<char, PropertyID::Tone, BaseDiffType::Add> ToneProperty;
typedef boost::shared_ptr<ToneProperty> TonePropertyPtr;

typedef BaseProperty<int, PropertyID::Velocity, BaseDiffType::Add>
    VelocityProperty;
typedef boost::shared_ptr<VelocityProperty> VelocityPropertyPtr;

typedef BaseProperty<int, PropertyID::InstrumentID, BaseDiffType::Add>
    InstrumentIdProperty;
typedef boost::shared_ptr<InstrumentIdProperty> InstrumentIdPropertyPtr;

typedef BaseProperty<int, PropertyID::DrumsID, BaseDiffType::Add>
    DrumsIdProperty;
typedef boost::shared_ptr<DrumsIdProperty> DrumsIdPropertyPtr;

typedef BaseProperty<NodeId, PropertyID::HyperSensorId, BaseDiffType::Add>
    HyperSensorIdProperty;
typedef boost::shared_ptr<HyperSensorIdProperty> HyperSensorIdPropertyPtr;

typedef BaseProperty<int, PropertyID::Channel, BaseDiffType::Add>
    ChannelProperty;
typedef boost::shared_ptr<ChannelProperty> ChannelPropertyPtr;

// REMOVE THIS SHIT LATER, BTW I'VE CHANGED char TO float IN TONEOFFSET
typedef BaseOffset<float, PropertyID::Tone, BaseDiffType::Add> ToneOffset;
typedef boost::shared_ptr<ToneOffset> ToneOffsetPtr;

/*Tone,
Velocity,
DrumsID,
InstrumentID,
InstrumentType,
*/

}  // namespace brain

#include "event.h"
#include "imemory.h"
#include "ioffset.h"
#include "iproperty.h"
#include "nodegroupprocessor.h"
#include "offsetlist.h"
#include "pattern.h"
#include "propertylist.h"
#include "utils.h"

#include "compareresult.h"
#include "hypothesis.h"

#include "istrategy.h"
#include "memorymodule.h"
#include "offsetlist.h"

#include "link.h"
#include "node.h"
#include "realnode.h"

#include "mystrategy.h"

#include "timeoffset.h"
#include "timeproperty.h"

#include "baseoffset.hpp"
#include "baseproperty.hpp"

#include "boostmemory.h"

#endif  // BRAIN_H
