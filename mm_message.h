#ifndef __SMARTAUDIOSTUDIO_MMMESSAGE_H__
#define __SMARTAUDIOSTUDIO_MMMESSAGE_H__

#include <string>
#include <utility>


#include "messages/message_types.h"
#include "dispatcher/base_message.h"

class MMMessage : public BaseMessage
{
public:
    MMMessage() : BaseMessage(messagetypes::MUSIC_MODULE_DATA) {};
    void setT(int _T){this->T_=_T;} ;
    void setMeasure(std::pair<int,int> _measure) {this->measure_=_measure;} ;
    void setShift(int _shift) {this->shift_=_shift;} ;
    int getT() {return T_;} ;
    std::pair<int,int> getMeasure() {return measure_;};
    int getShift() {return shift_ ; };


private:
int T_;
std::pair<int,int> measure_;
int shift_;

};

#endif /* __SMARTAUDIOSTUDIO_MMMESSAGE_H__ */
