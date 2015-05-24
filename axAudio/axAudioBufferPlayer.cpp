//
//  axBufferPlayer.cpp
//  MidiSequencer
//
//  Created by Alexandre Arsenault on 2014-11-14.
//  Copyright (c) 2014 Alexandre Arsenault. All rights reserved.
//

#include "axAudioBufferPlayer.h"
#include "axAudioBuffer.h"
#include <cmath>

axAudioBufferPlayer::axAudioBufferPlayer():
_bufferCurrentIndex(0),
_buffer(nullptr),
_bufferData(nullptr),
_playing(false),
_playingType(AUDIO_PLAYING_TYPE_PLAY_ONCE),
_currentVolumeValue(0.0),
_rms(0.0),
_rmsNSamples(1.0),
_speed(1.0),
_speedBufferRatio(0.0)
{
    
}

axAudioBufferPlayer::axAudioBufferPlayer(ax::Audio::Buffer* buffer):
_bufferCurrentIndex(0),
_buffer(buffer),
_bufferData(_buffer->GetBuffer()),
_playing(false),
_playingType(AUDIO_PLAYING_TYPE_PLAY_ONCE),
_currentVolumeValue(0.0),
_rms(0.0),
_rmsNSamples(1.0),
_speed(1.0),
_speedBufferRatio(0.0)
{
    
}

void axAudioBufferPlayer::SetBuffer(ax::Audio::Buffer* buffer)
{
    _bufferCurrentIndex = 0;
    _buffer = buffer;
    _bufferData = _buffer->GetBuffer();
    _playing = false;
    _currentVolumeValue = 0.0;
    _rms = 0.0;
    _rmsNSamples = 1.0;
    _speed = 1.0;
    _speedBufferRatio = 0.0;
}

void axAudioBufferPlayer::Play()
{
    _bufferCurrentIndex = 0;
    _playing = true;
    _currentVolumeValue = 0.0;
    _rms = 0.0;
    _rmsNSamples = 1.0;
    _speedBufferRatio = 0.0;
}

bool axAudioBufferPlayer::IsPlaying() const
{
    return _playing;
}

void axAudioBufferPlayer::SetPlayingType(const axAudioBufferPlayingType& type)
{
    _playingType = type;
}

void axAudioBufferPlayer::SetPlaySpeed(const double& speed)
{
    _speed = speed;
}


double axAudioBufferPlayer::GetCursorPercentPosition() const
{
    double percent_pos = double(_bufferCurrentIndex) /
    double(_buffer->GetBufferInfo().frames * _buffer->GetBufferInfo().channels);
    
//    std::cout << "Percent_pos : " << percent_pos << std::endl;
    return percent_pos;
}

double axAudioBufferPlayer::GetCurrentVolume() const
{
    return _rms * sqrt(2.0);
}

void axAudioBufferPlayer::ProcessSample(float* out)
{
    
}

void axAudioBufferPlayer::ProcessBlock(float* out, unsigned long frameCount)
{
    if(_buffer != nullptr && _bufferData != nullptr && _playing)
    {
        int nChan = _buffer->GetBufferInfo().channels;
        if( nChan == 1)
        {
            ProcessMonoBlock(out, frameCount);
        }
        else if(nChan == 2)
        {
            ProcessStereoBlock(out, frameCount);
        }
        else
        {
            for(int i = 0; i < frameCount; i++)
            {
                *out++ += 0.0f;
                *out++ += 0.0f;
            }

        }
    }
    else
    {
        for(int i = 0; i < frameCount; i++)
        {
            _rms = 0.0;
            _rmsNSamples = 1.0;
            *out++ += 0.0f;
            *out++ += 0.0f;
        }
        
    }
}

void axAudioBufferPlayer::ProcessStereoBlock(double** out,
                                             const unsigned long& frameCount)
{
    if(_buffer != nullptr && _playing)
    {
        float* buf = _bufferData;
        unsigned long buffer_total_frame = _buffer->GetBufferInfo().frames * 2;
        unsigned long stereo_index = _bufferCurrentIndex;
        
        double* left = out[0];
        double* right = out[1];
        _rms = 0.0;
        
        if(stereo_index + frameCount * 2 < buffer_total_frame * 2)
        {
            for(int i = 0; i < frameCount; i++)
            {
                float v = buf[stereo_index++];
                _rms += v * v;
                *left++ += v;
                *right++ += buf[stereo_index++];
            }
        }
        else
        {
            for(int i = 0; i < frameCount; i++)
            {
                float v = _playing ? buf[stereo_index++] : 0.0f;
                _rms += v * v;
                *left++ += v;
                *right++ += _playing ? buf[stereo_index++] : 0.0f;
                
                if(stereo_index >= buffer_total_frame * 2)
                {
                    if(_playingType == AUDIO_PLAYING_TYPE_PLAY_ONCE)
                    {
                        _playing = false;
                    }
                    
                    stereo_index = 0;
                }
            }
        }
        
        _rms = sqrt(1.0 / double(frameCount) * _rms);
        _bufferCurrentIndex = stereo_index;
    }

}

void axAudioBufferPlayer::ProcessMonoSample(float* out)
{
    
}

void axAudioBufferPlayer::ProcessMonoBlock(float* out,
                                           unsigned long frameCount)
{
    float* buf = _bufferData;
    unsigned long buffer_total_frame = _buffer->GetBufferInfo().frames;
    unsigned long index = _bufferCurrentIndex;
    float value = 0.0;
    
    _rms = 0.0;
    
    if(index + frameCount < buffer_total_frame)
    {
        for(int i = 0; i < frameCount; i++)
        {
            
            value = buf[index++];
            _rms += value * value;
//            _currentVolumeValue = value;
            *out++ += value;
            *out++ += value;
        }
    }
    else
    {
        for(int i = 0; i < frameCount; i++)
        {
            value = _playing ? buf[index++] : 0.0f;
            _rms += value * value;
            *out++ += value;
            *out++ += value;
            
            if(index >= buffer_total_frame)
            {
                if(_playingType == AUDIO_PLAYING_TYPE_PLAY_ONCE)
                {
                    _playing = false;
                }
                
                index = 0;
            }
        }
    }
    
    _rms = sqrt(1.0 / double(frameCount) * _rms);
    _bufferCurrentIndex = index;
}

void axAudioBufferPlayer::ProcessStereoSample(float* out)
{
    
}

void axAudioBufferPlayer::ProcessStereoBlock(float* out,
                                             unsigned long frameCount)
{

    if(_speed != 1.0)
    {
        ProcessSpeedChangeStereoBlock(out, frameCount);
        return;
    }
    
    float* buf = _bufferData;
    unsigned long buffer_total_frame = _buffer->GetBufferInfo().frames * 2;
    unsigned long stereo_index = _bufferCurrentIndex;
    
    _rms = 0.0;
    
    if(stereo_index + frameCount * 2 < buffer_total_frame)
    {
        for(int i = 0; i < frameCount; i++)
        {
            float v = buf[stereo_index++];
            _rms += v * v;
            *out++ += v;
            *out++ += buf[stereo_index++];
        }
    }
    else
    {
        for(int i = 0; i < frameCount; i++)
        {
            float v = _playing ? buf[stereo_index++] : 0.0f;
            _rms += v * v;
            
            *out++ += v;
            *out++ += _playing ? buf[stereo_index++] : 0.0f;
            
            if(stereo_index >= buffer_total_frame)
            {
                if(_playingType == AUDIO_PLAYING_TYPE_PLAY_ONCE)
                {
                    _playing = false;
                }
                
                stereo_index = 0;
            }
        }
    }
    
    _rms = sqrt(1.0 / double(frameCount) * _rms);
    _bufferCurrentIndex = stereo_index;
}

void axAudioBufferPlayer::ProcessSpeedChangeStereoBlock(float* out,
                                                        unsigned long frameCount)
{
    float* buf = _bufferData;
    unsigned long buffer_total_frame = _buffer->GetBufferInfo().frames * 2;
    unsigned long nFrame = _buffer->GetBufferInfo().frames;
    
    double index_ratio = _speedBufferRatio;
    
    for(int i = 0; i < frameCount; i++)
    {
        if(index_ratio >= 1.0)
        {
            _playing = false;

            *out++ += 0.0f;
            *out++ += 0.0f;
        }
        else
        {
            double floatFrame = index_ratio * nFrame * 2.0;
            
            unsigned long index_left = floor(floatFrame);
            unsigned long index_right = ceil(floatFrame);
            
            if(index_left % 2 != 0 && index_left != 0)
            {
                index_left -= 1;
//                std::cout << "Wrong stereo channel" << std::endl;
            }
            
            if(index_right % 2 != 0 && index_right != 0)
            {
                index_right += 1;
                //                std::cout << "Wrong stereo channel" << std::endl;
            }
            
//            unsigned long index_right = index_left + 2;
            
            
            if(index_left % 2 != 0 && index_left != 0)
            {
                std::cout << "Wrong stereo channel (left)" << std::endl;
            }
            
            if(index_right % 2 != 0 && index_right != 0)
            {
                std::cout << "Wrong stereo channel (right)" << std::endl;
            }
            
            
            double frac = 0.0;
            
            if(index_left != index_right)
            {
//                double frac = floatFrame - index_left;
                frac = (floatFrame - index_left) / double(index_right - index_left);
//                std::cout << frac << std::endl;
            }
//
            
            //-----------------------
            if(frac > 1.0)
            {
                std::cout << "frac > 1" << std::endl;
            }
            
//            frac = frac * (index_right - index_left);
//            double frac =
            
            if(index_right + 1 >= buffer_total_frame)
            {
                _playing = false;
                *out++ += 0.0f;
                *out++ += 0.0f;
            }
            else
            {
                
//                double v = ax::Audio::LineairInterpole<double>(buf[index_left], buf[index_right], frac);
//
//                *out++ += v;
//                *out++ += v;
                
                *out++ += ax::Audio::LineairInterpole<double>(buf[index_left], buf[index_right], frac);
                *out++ += ax::Audio::LineairInterpole<double>(buf[index_left + 1], buf[index_right + 1], frac);
            }
         }
        
        double speed_incr = _speed / double(nFrame);
        index_ratio += speed_incr;
//        index_ratio += 1.0 / double(nFrame);
        
    }
    
    _speedBufferRatio = index_ratio;
    
//    if(stereo_index + frameCount * 2 < buffer_total_frame)
//    {
//        for(int i = 0; i < frameCount; i++)
//        {
//            float v = buf[stereo_index++];
//            _rms += v * v;
//            *out++ += v;
//            *out++ += buf[stereo_index++];
//        }
//    }
//    else
//    {
//        for(int i = 0; i < frameCount; i++)
//        {
//            float v = _playing ? buf[stereo_index++] : 0.0f;
//            _rms += v * v;
//            
//            *out++ += v;
//            *out++ += _playing ? buf[stereo_index++] : 0.0f;
//            
//            if(stereo_index >= buffer_total_frame)
//            {
//                if(_playingType == AUDIO_PLAYING_TYPE_PLAY_ONCE)
//                {
//                    _playing = false;
//                }
//                
//                stereo_index = 0;
//            }
//        }
//    }
    
//    _rms = sqrt(1.0 / double(frameCount) * _rms);
//    _bufferCurrentIndex = stereo_index;
}