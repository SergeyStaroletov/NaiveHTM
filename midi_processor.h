#ifndef MIDIPROCESSOR_H
#define MIDIPROCESSOR_H

#include "jdkmidi/fileread.h"
#include "jdkmidi/filereadmultitrack.h"
#include "jdkmidi/fileshow.h"
#include "jdkmidi/multitrack.h"
#include "jdkmidi/track.h"
#include "jdkmidi/world.h"
#include <list>

#include "event.h"

using namespace jdkmidi;

class MidiProcessor {

private:
    std::string filename;

    int division;

    std::list<brain::EventPtr> result;

public:
    MidiProcessor(std::string path_to_midi) {this->filename=path_to_midi ;}
    std::list<brain::EventPtr>* process() ;
    int getDivision() { return division; };
    double getResolution() { return 1 / (division * 0.0025); };

    static void returnParamsFromEvent(brain::EventPtr _event,
                                      int &_note,
                                      int &_channel,
                                      int &_velocity,
                                      bool &_isnoteon,
                                      int &_timestamp);

    static brain::EventPtr createEventFromParameters(
        int _note, int _channel, int _velocity, bool _isnoteon, int _timestamp);

private:
    void  dumpMIDIMultiTrack(MIDIMultiTrack *mlt) ;

};



#endif // MIDIPROCESSOR_H
