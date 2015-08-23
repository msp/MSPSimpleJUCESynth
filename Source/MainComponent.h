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

    Slider frequencySlider;
    Slider amplitudeSlider;

    SineWave sineWaveGenerator;

    float level = 0.125f;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
