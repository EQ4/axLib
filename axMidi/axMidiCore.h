#ifndef __AX_MIDI__
#define __AX_MIDI__

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
//#include "axUtils.h"

#include "RtMidi.h"

namespace ax
{
    namespace Midi
    {
        class Note
        {
        public:
            Note(const int& note, const int& velocity):
            _note(note), _velocity(velocity)
            {
            }
            
            int GetNote() const
            {
                return _note;
            }
            
            int GetVelocity() const
            {
                return _velocity;
            }
            
        private:
            int _note, _velocity;
        };
        
        class Core
        {
        public:
            Core();
            ~Core();
            
            
        protected:
            virtual void OnMidiNoteOn(const Note& msg);
            virtual void OnMidiNoteOff(const Note& msg);
            
        private:
            RtMidiIn* _midiInHandle;
            
            static void MidiCallBack(double deltatime,
                                     std::vector<unsigned char>* message,
                                     void* userData);
        };
    }
}


#endif // __AX_MIDI__