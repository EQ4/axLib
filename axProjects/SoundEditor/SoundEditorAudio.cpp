//
//  SoundEditorAudio.cpp
//  MidiSequencer
//
//  Created by Alexandre Arsenault on 2014-11-14.
//  Copyright (c) 2014 Alexandre Arsenault. All rights reserved.
//

#include "SoundEditorAudio.h"
#include "axAudioBuffer.h"
#include "axAudioBufferPlayer.h"

SoundEditorAudio* SoundEditorAudio::_instance = nullptr;

SoundEditorAudio* SoundEditorAudio::GetInstance()
{
    return _instance == nullptr ? _instance = new SoundEditorAudio() : _instance;
}

SoundEditorAudio::SoundEditorAudio():
    axAudio()
{
    std::string app_path("/Users/alexarse/Project/axLib/axProjects/SoundEditor/");
    std::string snd_path = app_path + ("808 Samples/snare (41).wav");
    
    _sndBuffer = new axAudioBuffer(snd_path);
    _bufferPlayer = new axAudioBufferPlayer(_sndBuffer);
}

void SoundEditorAudio::OnPlay(const int& msg)
{
    _bufferPlayer->Play();
}

void SoundEditorAudio::OnChangeFilePath(const std::string& msg)
{
    SetSoundFilePath(msg);
}

void SoundEditorAudio::SetSoundFilePath(const std::string& path)
{
    _sndBuffer->OpenSoundFile(path);
    _bufferPlayer->SetBuffer(_sndBuffer);
}

axAudioBuffer* SoundEditorAudio::GetSoundBuffer()
{
    return _sndBuffer;
}

int SoundEditorAudio::CallbackAudio(const float* input,
                                    float* output,
                                    unsigned long frameCount)
{
    _bufferPlayer->ProcessBlock(output, frameCount);

    return 0;
}
