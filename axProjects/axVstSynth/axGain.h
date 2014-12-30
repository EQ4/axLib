//-------------------------------------------------------------------------------------------------------
// VST Plug-Ins SDK
// Version 2.4		$Date: 2006/11/13 09:08:27 $
//
// Category     : VST 2.x SDK Samples
// Filename     : again.h
// Created by   : Steinberg Media Technologies
// Description  : Stereo plugin which applies Gain [-oo, 0dB]
//
// © 2006, Steinberg Media Technologies, All Rights Reserved
//-------------------------------------------------------------------------------------------------------

#ifndef __again__
#define __again__

#include "axLib.h"

#include "axAudioWaveTable.h"
#include "axAudioFilter.h"
#include "axAudioEnvelope.h"

#include "public.sdk/source/vst2.x/audioeffectx.h"
#include "public.sdk/source/vst2.x/aeffeditor.h"

class axGainGUI : public AEffEditor
{
public:
    axGainGUI(AudioEffect* effect);
    
//    void MyOpen(void*& win);
    virtual bool open(void* ptr);
    virtual void draw(ERect* rect);
    virtual bool getRect(ERect** rect);
private:
    ERect _rect;
    static bool _pluginHasBeenOpenOnHostInit;
    static bool _isFirstTimeVstGUIOpen;
};

//-------------------------------------------------------------------------------------------------------
class AGain : public AudioEffectX
{
public:
    AGain(audioMasterCallback audioMaster);
    ~AGain();
    
    virtual void open();
    virtual void close();
    
    virtual VstInt32 getProgram();
    
    // Processing
    virtual void processReplacing(float** inputs,
                                   float** outputs,
                                   VstInt32 sampleFrames);
    
    virtual void processDoubleReplacing(double** inputs,
                                        double** outputs,
                                        VstInt32 sampleFrames);
    
    // Program
    virtual void setProgramName (char* name);
    virtual void getProgramName (char* name);
    
    // Parameters
    void SetParameterFromGUI(VstInt32 index, float value);
    
    virtual void setParameter(VstInt32 index, float value);
    virtual float getParameter(VstInt32 index);
    virtual void getParameterLabel(VstInt32 index, char* label);
    virtual void getParameterDisplay(VstInt32 index, char* text);
    virtual void getParameterName(VstInt32 index, char* text);
    
    virtual bool getEffectName(char* name);
    virtual bool getVendorString(char* text);
    virtual bool getProductString(char* text);
    virtual VstInt32 getVendorVersion();
    
    virtual VstInt32 canDo(char *text);
    
    VstInt32 processEvents(VstEvents* ev);
    
    virtual VstPlugCategory getPlugCategory();
    
    virtual VstIntPtr dispatcher(VstInt32 opCode,
                                 VstInt32 index,
                                 VstIntPtr value,
                                 void* ptr, float opt);
    
protected:
    float fGain;
    float _filterFreq;
    
    int _pluginId;
    static int pluginIdCounter;
    char programName[kVstMaxProgNameLen + 1];
    
    //------------------------
    axAudioWaveTable* _waveTable;
    axAudioFilter* _filter;
    axAudioEnvelope* _env;
    
    double c0;
};

extern AGain* GlobalAGain;

#endif