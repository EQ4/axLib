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
#include <vector>
#include <axLib/axLib.h>
//#include <axAudio/axAudioWaveTable.h>



class AudioPiano : public ax::Audio::Core, public ax::Event::Object
{
public:
    AudioPiano(ax::App* app);
    
    void LoadSamples();
    
    void PlayNode(const int& note, const int& velocity);
    
    typedef std::vector<ax::Audio::Buffer*> BufferVector;
    typedef std::vector<axAudioBufferPlayer*> PlayerVector;
    
private:    
    std::vector<BufferVector> _buffers;
    std::vector<PlayerVector> _players;
    
    int CoreCallbackAudio(const float* input,
                          float* output,
                          unsigned long frameCount);
};

#endif /* defined(__axDemo__Audio__) */
