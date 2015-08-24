/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

using namespace stk;


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent   : public AudioAppComponent,
                               public Slider::Listener

{
public:
    //==============================================================================
    MainContentComponent();
    ~MainContentComponent();

    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void releaseResources() override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;

    void paint (Graphics&) override;
    void resized() override;

    void sliderValueChanged (Slider* slider) override;
    

private:
    String currentSizeAsString;

    Slider osc1FrequencySlider;
    Slider osc1AmplitudeSlider;

    Slider osc2FrequencySlider;
    Slider osc2AmplitudeSlider;

    Slider osc3FrequencySlider;
    Slider osc3AmplitudeSlider;

    SineWave osc1Generator;
    SineWave osc2Generator;
    SineWave osc3Generator;

    float osc1Level = 0.5f;
    float osc1StartFrequency = 500.0f;

    float osc2Level = 0.0f;
    float osc2StartFrequency = 522.0f;

    float osc3Level = 0.0f;
    float osc3StartFrequency = 544.0f;

    const int oscSize = 150;
    const int oscLeftMargin = 50;
    const int oscTopMargin = 50;
    const int numberOsc = 3;

    void drawSliders();

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
