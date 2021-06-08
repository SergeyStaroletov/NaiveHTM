#ifndef __MESSAGETYPES_H__
#define __MESSAGETYPES_H__

namespace messagetypes {

enum EMessageTypes {
    FIXED_EVENT_BEGIN = 1,
    FIXED_EVENT_END = 2,
    PREDICTED_MIDI_EVENT_BEGIN = 3,
    PREDICTED_MIDI_EVENT_END = 4,

    ADVANCED_MUSIC_SETTINGS = 5,
    DATA_FILE_PATH = 6,
    EXIT = 7,

    DATA_BEGIN = 8,
    DATA_END = 9,
    BRAIN_GIVE_ME_THE_GRAPH = 10,
    MODULE_DATA = 11,

    FIXED_EVENT_BEGIN_KEY2,
    FIXED_EVENT_END_KEY = 13,

    UNSPECIFIED = -1
};
};

#endif
