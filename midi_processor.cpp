#include "event.h"
#include "predictionstatus.h"
#include "propertylist.h"
#include "stdlibs.h"

//#include "midi_parser.h"
#include "midi_processor.h"

#include "jdkmidi/fileread.h"
#include "jdkmidi/filereadmultitrack.h"
#include "jdkmidi/fileshow.h"
#include "jdkmidi/multitrack.h"
#include "jdkmidi/track.h"
#include "jdkmidi/world.h"
#include <list>

using namespace jdkmidi;

void MidiProcessor::returnParamsFromEvent(brain::EventPtr _event,
                                          int &_note,
                                          int &_channel,
                                          int &_velocity,
                                          bool &_isnoteon,
                                          int &_timestamp)
{
    if (_event == NULL) {
        _note = 0;
        _channel = 0;
        _velocity = 0;
        _isnoteon = false;
        _timestamp = false;
        return;
    }

    if (_event->getType() == messagetypes::FIXED_EVENT_BEGIN)
        _isnoteon = true;
    else
        _isnoteon = false;

    _timestamp = _event->timestamp; //? my be Time

    brain::PropertyListPtr list = _event->properties;

    //note
    brain::IPropertyPtr prop = list->getProperty(brain::PropertyID::Tone);
    // brain::TonePropertyPtr tone((brain::ToneProperty*)prop.get());
    brain::TonePropertyPtr tone = boost::static_pointer_cast<brain::ToneProperty>(prop);
    _note = tone->getData();
    //velocity
    prop = list->getProperty(brain::PropertyID::Velocity);
    //    brain::VelocityPropertyPtr velo((brain::VelocityProperty*)prop.get());
    brain::VelocityPropertyPtr velo = boost::static_pointer_cast<brain::VelocityProperty>(prop);
    _velocity = velo->getData();

    if (_velocity == 0)
        _isnoteon = false;

    //chanel
    prop = list->getProperty(brain::PropertyID::Channel);
    //    brain::ChannelPropertyPtr chan((brain::ChannelProperty*)prop.get());
    brain::ChannelPropertyPtr chan = boost::static_pointer_cast<brain::ChannelProperty>(prop);

    _channel = chan->getData();
}

brain::EventPtr MidiProcessor::createEventFromParameters(
    int _note, int _channel, int _velocity, bool _isnoteon, int _timestamp)
{
    messagetypes::EMessageTypes t;
    if (_isnoteon)
        t = messagetypes::FIXED_EVENT_BEGIN;
    else
        t = messagetypes::FIXED_EVENT_END;

    if (_velocity == 0 && _isnoteon)
        t = messagetypes::FIXED_EVENT_END;

    //  brain::Event* event=new brain::Event(t) ;
    brain::EventPtr event = brain::EventPtr(new brain::Event(t));

    event->properties = brain::PropertyListPtr(new brain::PropertyList());
    event->status = brain::PredictionStatus::Real;
    event->timestamp = _timestamp;

    brain::TonePropertyPtr pr1(new brain::ToneProperty());
    pr1->setData(_note);

    brain::VelocityPropertyPtr pr2(new brain::VelocityProperty());
    pr2->setData(_velocity);

    brain::ChannelPropertyPtr pr4(new brain::ChannelProperty());
    pr4->setData(_channel);

    //drumsid -?
    brain::DrumsIdPropertyPtr pr5(new brain::DrumsIdProperty());
    pr5->setData(_note);

    //HyperSensorID -> 9
    brain::HyperSensorIdPropertyPtr pr6(new brain::HyperSensorIdProperty);
    if (_channel == 9)
        pr6->setData(brain::HyperSensor::Drums);
    else
        pr6->setData(brain::HyperSensor::Piano);

    event->properties->setProperty(pr1);
    event->properties->setProperty(pr2);
    //event->properties->setProperty(pr3);
    event->properties->setProperty(pr4);
    event->properties->setProperty(pr5);
    event->properties->setProperty(pr6);

    return event;
}

void MidiProcessor::dumpMIDIMultiTrack(MIDIMultiTrack *mlt)
{
    jdkmidi::MIDIMultiTrackIterator i( mlt );
    jdkmidi::MIDITimedBigMessage *msg;
    i.GoToTime(0);

    result.clear();

    do
    {
        int trk_num;
        if( i.GetCurEvent(&trk_num, &msg ) )
        {

            if( msg->IsNoteOn()||msg->IsNoteOff())
            {
                brain::EventPtr event
                    = MidiProcessor::createEventFromParameters(msg->GetNote(),
                                                               msg->GetChannel(),
                                                               msg->GetVelocity(),
                                                               msg->IsNoteOn(),
                                                               msg->GetTime()
                                                                   * this->getResolution());
                result.push_back(event) ;
            }


        }
    } while( i.GoToNextEvent() );
}


std::list<brain::EventPtr>*  MidiProcessor::process() {
    MIDIFileReadStreamFile *rs = new MIDIFileReadStreamFile(this->filename.c_str());
    MIDIMultiTrack * tracks = new MIDIMultiTrack();
    MIDIFileReadMultiTrack * track_loader = new MIDIFileReadMultiTrack ( tracks );
    MIDIFileRead  *reader =  new MIDIFileRead (rs, track_loader );
    reader->Parse();
    this->division=reader->GetDivision() ;
    dumpMIDIMultiTrack( tracks );
    return &(this->result) ;

}


