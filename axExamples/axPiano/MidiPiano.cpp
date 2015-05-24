//
//  MidiPiano.cpp
//  axDemo
//
//  Created by Alexandre Arsenault on 2015-05-19.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

#include "MidiPiano.h"
#include <axUtils/axUtils.h>
#include "AudioPiano.h"

PianoMidi::PianoMidi(AudioPiano* audio):
_audio(audio)
{
    
}

void PianoMidi::OnMidiNoteOn(const ax::Midi::Note& msg)
{
    _audio->PlayNode(msg.GetNote(), msg.GetVelocity());
    ax::Print("Midi on", msg.GetNote(), msg.GetVelocity());
}

void PianoMidi::OnMidiNoteOff(const ax::Midi::Note& msg)
{
    ax::Print("Midi off", msg.GetNote(), msg.GetVelocity());
}