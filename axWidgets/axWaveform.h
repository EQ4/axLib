//
//  axWaveform.h
//  MidiSequencer
//
//  Created by Alexandre Arsenault on 2014-11-14.
//  Copyright (c) 2014 Alexandre Arsenault. All rights reserved.
//

#ifndef __MidiSequencer__axWaveform__
#define __MidiSequencer__axWaveform__

#include <axLib/axLib.h>

class axAudioBuffer;

/*******************************************************************************
 * axWaveform.
 ******************************************************************************/
class axWaveform : public axWidget
{
public:
    /***************************************************************************
     * axWaveform::Info.
     **************************************************************************/
    class Info : public axInfo
    {
    public:
        Info();
        
        Info(const std::string& path);
        
        Info(const axVectorPairString& attributes);
        
        Info(const ax::Color& bg_color,
             const ax::Color& waveform_color,
             const ax::Color& contour_color,
             const ax::Color& grid_main_line_color,
             const ax::Color& grid_second_line_color,
             const ax::Color& middle_line_color,
             const ax::Color& env_color);
        
        // Info needed for debug editor. Derived from axInfo.
        virtual axStringVector GetParamNameList() const;
        virtual std::string GetAttributeValue(const std::string& name);
        virtual void SetAttribute(const axStringPair& attribute);
        
        ax::Color bg_color;
        ax::Color waveform_color;
        ax::Color contour_color;
        ax::Color grid_main_line_color;
        ax::Color grid_second_line_color;
        ax::Color middle_line_color;
        ax::Color env_color;
    };
    
    /***************************************************************************
     * axWaveform::Builder.
     **************************************************************************/
    class Builder : public axWidgetBuilder
    {
    public:
        Builder(axWindow* parent);
        
        virtual axWidget* Create(const axVectorPairString& attributes);
        
    private:
        axWaveform::Info _info;
        ax::Size _size;
    };
    
    /***************************************************************************
     * axWaveform::axWaveform.
     **************************************************************************/
    axWaveform(axWindow* parent, const ax::Rect& rect,
               const axWaveform::Info& info);
    
    void SetAudioBuffer(axAudioBuffer* buffer);
    
    void SetZoom(const double& zoom);
    
    void SetLeftPosition(const double& pos);
    
    axFloatRange GetBorders() const;
    
    std::vector<float>* _envBuffer;
    std::vector<axFloatPoint>* _envPoints;
    
    void ShowEnv(const bool& show);
    
private:
    axAudioBuffer* _audioBuffer;
    
    double _zoom, _leftPos;
    bool _showEnv;
    
    // Events.
    virtual void OnPaint();
};

#endif /* defined(__MidiSequencer__axWaveform__) */
