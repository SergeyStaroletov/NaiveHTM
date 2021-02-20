#include "brain.h"
#include "stdlibs.h"

#include <QDateTime>
#include <QFile>
#include <QTextStream>

using namespace std;
using namespace brain;

void testEventCreation() {
  Event e(messagetypes::DATA_BEGIN);
  e.properties = PropertyListPtr(new PropertyList());
  e.status = PredictionStatus::Real;
  e.timestamp = 45151;

  // tone number (type - char, 0-255)
  TonePropertyPtr pr1(new ToneProperty());
  pr1->setData(55);

  // velocity (char, 0-255)
  VelocityPropertyPtr pr2(new VelocityProperty());
  pr2->setData(100);

  // standartizirovanniy ID instrumenta (int)
  InstrumentIdPropertyPtr pr3(new InstrumentIdProperty());
  pr3->setData(510);

  // tarelka, tamtam (int)
  DrumsIdPropertyPtr pr4(new DrumsIdProperty());
  pr4->setData(8);

  // piano, drum, organ )) (int)
  // InstrumentTypePropertyPtr pr5(new InstrumentTypeProperty());
  // pr5->setData(3);

  e.properties->setProperty(pr1);
  e.properties->setProperty(pr2);
  e.properties->setProperty(pr3);
  e.properties->setProperty(pr4);
  // e.properties->setProperty(pr5);

  // send kuda-to peremennoy e
}

class TestStrategy : public IStrategy {
  std::vector<NodeGroupProcessorPtr> getParents(NodeGroupProcessorPtr node) {
    return std::vector<NodeGroupProcessorPtr>();
  }

  int getMinimalOccurrencesNumber(NodeGroupProcessorPtr nodeGroup) { return 2; }

  float getMaxDelta(PropertyID::Enum propertyID) { return 5.0f; }
  float getMaxDelta(NodePtr node) { return 0.5; }

  float getMaxDelta() { return 100.0f; }

  long long getSmallWindowSize(NodeGroupProcessorPtr nodeGroup) { return 100; }

  long long getBigWindowSize(NodeGroupProcessorPtr nodeGroup) { return 1000; }

  int getSmallWindowElementsNumber(NodeGroupProcessorPtr nodeGroup) {
    return 5;
  }

  /*
  Time in microseconds, w ~ 1.0f / 1000000.0f
  Tone in piano key number - halftones, w ~ 0.5f
  Velocity - not important
  HyperSensorId - not comparable, getMaxDelta = 0.0f, w ~ inf
  InstrumentId - comparable, w ~ 1.0f
  */
  float getWeight(PropertyID::Enum propertyID) {
    switch (propertyID) {
      case PropertyID::Tone:
        return 1.0f;
      case PropertyID::InstrumentID:
        return 10.0f;
      case PropertyID::Time:
        return 3.0f;
    }
    return 0.0f;
  }
};

void testFloat() {
  float a = 0.0f;
  float b = 0.01f;

  for (int i = 0; i < 100000; i += 10) {
    float c = b - a;
    a += 10.0f;
    b += 10.0f;
    if (c < 0.01f) {
      cout << "FUCKUP on " << i << " " << c << " " << endl;
      break;
    }
  }
}

vector<NodePtr> createNodes(int n, int id) {
  vector<NodePtr> result;
  for (int i = 0; i < n; i++) {
    NodePtr node(new Node());
    node->id = id;
    node->amount = 1;
    result.push_back(node);
  }
  return result;
}

LinkPtr createLink(Timestamp startTime, Timestamp endTime, char tone) {
  LinkPtr link(new Link());
  link->amount = 1;
  link->offsets = OffsetListPtr(new OffsetList());
  TimeOffsetPtr timeOffset(new TimeOffset());
  timeOffset->SetData(startTime, endTime - startTime);
  link->offsets->setOffset(timeOffset);

  ToneOffsetPtr toneOffset(new ToneOffset());
  toneOffset->setData(tone);
  link->offsets->setOffset(toneOffset);

  return link;
}

Event* generateEvent(char tone, Timestamp time,
                     messagetypes::EMessageTypes type, int HyperSensorId) {
  Event* e = new Event(type);
  e->status = PredictionStatus::Real;
  e->timestamp = time;
  e->properties = PropertyListPtr(new PropertyList());
  IPropertyPtr toneProp(new ToneProperty());
  ((ToneProperty*)(toneProp.get()))->setData(tone);
  e->properties->setProperty(toneProp);

  IPropertyPtr hypProp(new HyperSensorIdProperty());
  ((HyperSensorIdProperty*)(hypProp.get()))->setData(HyperSensorId);
  e->properties->setProperty(hypProp);

  return e;
}

Event* generateSimpleEvent(Timestamp time, messagetypes::EMessageTypes type) {
  Event* e = new Event(type);
  e->status = PredictionStatus::Real;
  e->timestamp = time;
  e->properties = PropertyListPtr(new PropertyList());
  return e;
}

void testRealEventsRemembering() {
  IStrategyPtr strategy(new MyStrategy());
  IMemoryPtr memory(new BoostMemory(strategy));
  MemoryModulePtr mm(new MemoryModule(memory));
  mm->setStrategy(strategy);
  strategy->setMemory(mm, memory);

  for (int i = 0; i < 100; i++) {
    Event* e1 = generateEvent(1, 200000 + 10000000 * i,
                              messagetypes::FIXED_CAN_EVENT_BEGIN, -18);
    Event* e2 = generateEvent(2, 300000 + 10000000 * i,
                              messagetypes::FIXED_CAN_EVENT_BEGIN, -18);
    Event* e3 = generateEvent(1, 500000 + 10000000 * i,
                              messagetypes::FIXED_CAN_EVENT_END, -18);
    Event* e4 = generateEvent(1, 700000 + 10000000 * i,
                              messagetypes::FIXED_CAN_EVENT_BEGIN, -18);
    Event* e5 = generateEvent(2, 800000 + 10000000 * i,
                              messagetypes::FIXED_CAN_EVENT_END, -18);
    Event* e6 = generateEvent(1, 900000 + 10000000 * i,
                              messagetypes::FIXED_CAN_EVENT_END, -18);

    mm->processMessage(BaseMessagePtr(e1));
    mm->processMessage(BaseMessagePtr(e2));
    mm->processMessage(BaseMessagePtr(e3));
    mm->processMessage(BaseMessagePtr(e4));
    mm->processMessage(BaseMessagePtr(e5));
    mm->processMessage(BaseMessagePtr(e6));
  }

  Event* end = generateSimpleEvent(100000000000LL, messagetypes::DATA_END);
  mm->processMessage(BaseMessagePtr(end));

  memory->getVisualization("graph.txt");
}

void testCarData() {
  IStrategyPtr strategy(new MyStrategy());
  IMemoryPtr memory(new BoostMemory(strategy));
  MemoryModulePtr mm(new MemoryModule(memory));
  mm->setStrategy(strategy);
  strategy->setMemory(mm, memory);

  Event* start = generateSimpleEvent(0, messagetypes::DATA_END);
  mm->processMessage(BaseMessagePtr(start));

  QString fileName = "/Users/sergey/projects/can_data/3uskor/CAN1_201_6.csv";
  // QString fileName = "/Users/sergey/projects/can_data/spok/CAN1_201_6.csv";

  bool isFirst = true;
  long long oldVal;
  QDateTime time0;
  long long timeStamp = 0;
  QFile inputFile(fileName);

  int i = 0;
  if (inputFile.open(QIODevice::ReadOnly)) {
    QTextStream in(&inputFile);
    while (!in.atEnd()) {
      QString line = in.readLine();
      int virgule = line.indexOf(',');

      if (virgule > 0) {
        QString timeStr = line.left(virgule);
        printf("%s ", timeStr.toLocal8Bit().data());
        QDateTime dt =
            QDateTime::fromString(timeStr, "yyyy-MM-dd hh:mm:ss.zzz");

        if (isFirst) {
          time0 = dt;
        } else
          timeStamp = time0.msecsTo(dt);

        // timeStamp = 100000 + 100000 * i;
        i++;
        printf("%ld", timeStamp);

        int value = line.mid(virgule + 1).toInt();

        // value = 1 + rand() % 2;

        printf(" %d\n", value);
        //

        Event* e1 = generateEvent((char)value, 10000 + 100000 * i,
                                  messagetypes::FIXED_CAN_EVENT_BEGIN, -18);

        if (value > 190) {
          value = 190;
        }
        Event* e2 = generateEvent((char)value, 20000 + 100000 * i,
                                  messagetypes::FIXED_CAN_EVENT_END, -18);
        //
        mm->processMessage(BaseMessagePtr(e1));
        mm->processMessage(BaseMessagePtr(e2));

        oldVal = value;
        isFirst = true;
      }
    }
    inputFile.close();
  }

  /*
  for (int i = 0; i < 100; i++) {
    Event* e1 = generateEvent(1, 200000 + 10000000 * i,
                              messagetypes::FIXED_MIDI_EVENT_BEGIN, -18);
    Event* e2 = generateEvent(2, 300000 + 10000000 * i,
                              messagetypes::FIXED_MIDI_EVENT_BEGIN, -18);
    Event* e3 = generateEvent(1, 500000 + 10000000 * i,
                              messagetypes::FIXED_MIDI_EVENT_END, -18);
    Event* e4 = generateEvent(1, 700000 + 10000000 * i,
                              messagetypes::FIXED_MIDI_EVENT_BEGIN, -18);
    Event* e5 = generateEvent(2, 800000 + 10000000 * i,
                              messagetypes::FIXED_MIDI_EVENT_END, -18);
    Event* e6 = generateEvent(1, 900000 + 10000000 * i,
                              messagetypes::FIXED_MIDI_EVENT_END, -18);

    mm->processMessage(BaseMessagePtr(e1));
    mm->processMessage(BaseMessagePtr(e2));
    mm->processMessage(BaseMessagePtr(e3));
    mm->processMessage(BaseMessagePtr(e4));
    mm->processMessage(BaseMessagePtr(e5));
    mm->processMessage(BaseMessagePtr(e6));
  }

  */

  Event* end = generateSimpleEvent(timeStamp + 1, messagetypes::DATA_END);
  mm->processMessage(BaseMessagePtr(end));

  memory->getVisualization("graph.txt");
}

int main() {
  cout << "I'm smart ;)" << endl;

  cout << "HI THERE!" << endl;

  // testRealEventsRemembering();

  testCarData();

  return 0;
}
