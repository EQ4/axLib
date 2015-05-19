//
//  Audio.h
//  axDemo
//
//  Created by Alexandre Arsenault on 2015-05-19.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

#ifndef __axDemo__Audio__
#define __axDemo__Audio__

#include <axAudio/axAudio.h>
#include <axAudio/axAudioWaveTable.h>

class AudioPiano : public ax::Audio::Core
{
public:
    AudioPiano();
    
private:
    axAudioWaveTable* _waveTable;
    
    
    int CoreCallbackAudio(const float* input,
                          float* output,
                          unsigned long frameCount);
//    virtual int CallbackAudio(ax::Audio::Frames<const float, 1>* inputs,
//                              ax::Audio::Frames<float, 1>* outputs,
//                              unsigned long frameCount);

};

#endif /* defined(__axDemo__Audio__) */
