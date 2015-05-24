#include "AudioPiano.h"
#include <string>
#include <axUtils/axUtils.h>
//#include <axLib/axApp.h>


ax::StringVector GetAllVelocityFromNote(const std::string& folder,
                                        const std::string& note)
{
    ax::StringVector notes;
    
    for(int i = 0; i < 16; i++)
    {
        std::string path = folder + note + "v" + std::to_string(i + 1) + ".wav";
        notes.push_back(path);
    }
    
    return notes;
}

std::vector<ax::Audio::Buffer*> GetBufferFromNote(const std::string& folder,
                                                  const std::string& note)
{
    ax::StringVector notes = GetAllVelocityFromNote(folder, note);
    
    std::vector<ax::Audio::Buffer*> buffers;
    
    for(auto& n : notes)
    {
        ax::Audio::Buffer* buffer = new ax::Audio::Buffer(n);
        buffers.push_back(buffer);
    }
    
    return buffers;
}

std::vector<axAudioBufferPlayer*>
        GetPlayersFromBuffers(std::vector<ax::Audio::Buffer*>& buffers,
                              const double& speed)
{
    std::vector<axAudioBufferPlayer*> players;
    
    for(auto& n : buffers)
    {
        axAudioBufferPlayer* player = new axAudioBufferPlayer(n);
        player->SetPlaySpeed(speed);
        players.push_back(player);
    }
    
    return players;
}



AudioPiano::AudioPiano(ax::App* app):
ax::Event::Object(app->GetEventManager())
{

}

void AudioPiano::LoadSamples()
{
    std::string folder("SalamanderGrandPianoV3/");
    
    ax::StringVector notes;
    
    for(int i = 1; i < 8; i++)
    {
        std::string str(std::to_string(i));
        notes.push_back("C" + str);
        notes.push_back("D#" + str);
        notes.push_back("F#" + str);
        notes.push_back("A" + str);
    }
    
    _buffers.push_back(GetBufferFromNote(folder, "A0"));
    _players.push_back(GetPlayersFromBuffers(_buffers[0], 1.0));
    _players.push_back(GetPlayersFromBuffers(_buffers[0], 1.0594630943592952));
    
    int i = 1;
    for(auto& n : notes)
    {
        _buffers.push_back(GetBufferFromNote(folder, n));
        _players.push_back(GetPlayersFromBuffers(_buffers[i], 0.9438743126816935));
        _players.push_back(GetPlayersFromBuffers(_buffers[i], 1.0));
        _players.push_back(GetPlayersFromBuffers(_buffers[i], 1.0594630943592952));
        
//        ax::Print("Load :", (i / 28.0) * 100.0, "%");
        PushEvent(0, new ax::Event::SimpleMsg<double>((i / 28.0)));
        
        i++;
    }
    
    _buffers.push_back(GetBufferFromNote(folder, "C8"));
    _players.push_back(GetPlayersFromBuffers(_buffers[i], 0.9438743126816935));
    _players.push_back(GetPlayersFromBuffers(_buffers[i], 1.0));

}

void AudioPiano::PlayNode(const int& note, const int& velocity)
{
    ax::Print("note", note);
    
    if(note >= 21 && note <= 108)
    {
        int player_index = note - 21;
        
        double nVelocity = _players[player_index].size();
        
        int velocity_index = (velocity / 127.0) * (nVelocity - 1);
        
        _players[player_index][velocity_index]->Play();
    }
}

int AudioPiano::CoreCallbackAudio(const float* input,
                                  float* output,
                                  unsigned long frameCount)
{
    for(auto& vec : _players)
    {
        for(axAudioBufferPlayer* player : vec)
        {
            player->ProcessBlock(output, frameCount);
        }
    }

    return 0;
}