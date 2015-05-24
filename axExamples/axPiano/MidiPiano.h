//
//  MidiPiano.h
//  axDemo
//
//  Created by Alexandre Arsenault on 2015-05-19.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

#ifndef __axDemo__MidiPiano__
#define __axDemo__MidiPiano__

//#include <axMidi/axMidi.h>
#include <axMidi/axMidi.h>

class AudioPiano;

class PianoMidi : public ax::Midi::Core
{
public:
    PianoMidi(AudioPiano* audio);
    
protected:
    AudioPiano* _audio;
    
    virtual void OnMidiNoteOn(const ax::Midi::Note& msg);
    virtual void OnMidiNoteOff(const ax::Midi::Note& msg);
};

#endif /* defined(__axDemo__MidiPiano__) */
