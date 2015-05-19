//
//  Audio.cpp
//  axDemo
//
//  Created by Alexandre Arsenault on 2015-05-19.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

#include "Audio.h"

AudioPiano::AudioPiano()
{
    _waveTable = new axAudioWaveTable();
    _waveTable->SetWaveformType(axAudioWaveTable::axWAVE_TYPE_SAW);
}

//int AudioPiano::CallbackAudio(ax::Audio::Frames<const float, 1>* inputs,
//                              ax::Audio::Frames<float, 1>* outputs,
//                              unsigned long frameCount)
//{
//    return 0;
//}

int AudioPiano::CoreCallbackAudio(const float* input,
                                  float* output,
                                  unsigned long frameCount)
{
    _waveTable->ProcessBlock(output, frameCount);
    return 0;
}