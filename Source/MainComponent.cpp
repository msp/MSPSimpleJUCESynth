/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"


//==============================================================================
MainContentComponent::MainContentComponent()
{
    setSize (800, 600);

    sineWaveGenerator.setFrequency(200.0f);

    frequencySlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    frequencySlider.setTextBoxStyle (Slider::TextBoxBelow, false, 100, 30);
    frequencySlider.setBounds(50, 50, 150, 150);

    frequencySlider.setValue(200.0, dontSendNotification);
    frequencySlider.setRange (50.0, 5000.0);
    frequencySlider.setSkewFactorFromMidPoint (500.0);
    frequencySlider.addListener (this);

    addAndMakeVisible (frequencySlider);

    amplitudeSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    amplitudeSlider.setTextBoxStyle (Slider::TextBoxBelow, false, 100, 30);
    amplitudeSlider.setBounds(50, 250, 150, 150);

    amplitudeSlider.setValue(0.125, dontSendNotification);
    amplitudeSlider.setRange (0.0, 0.5);
    amplitudeSlider.setSkewFactorFromMidPoint (0.2);
    amplitudeSlider.addListener (this);

    addAndMakeVisible (amplitudeSlider);

    setAudioChannels (0, 1); // no inputs, one output

}

MainContentComponent::~MainContentComponent()
{
    shutdownAudio();
}

void MainContentComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    Stk::setSampleRate(sampleRate);
}

void MainContentComponent::releaseResources()
{
}

void MainContentComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    for (int channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel)
    {
        float* const buffer = bufferToFill.buffer->getWritePointer (channel, bufferToFill.startSample);

        for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
        {
            StkFloat data = sineWaveGenerator.tick();
            buffer[sample] = data * level;
        }
    }
}

void MainContentComponent::sliderValueChanged (Slider* slider)
{
    if (slider == &frequencySlider)
    {
        sineWaveGenerator.setFrequency(frequencySlider.getValue());
    }
    else if (slider == &amplitudeSlider)
    {
        level = amplitudeSlider.getValue();
    }
}

void MainContentComponent::paint (Graphics& g)
{
    g.fillAll (Colours::transparentBlack);
    g.setFont (Font ("Times New Roman", 20.0f, Font::plain));
    g.setColour (Colours::darkblue);
    g.drawText (currentSizeAsString, getLocalBounds(), Justification::centredBottom, true);

//    g.setColour (Colours::green);
//    g.drawLine (10, 300, 590, 300, 5);

//    Rectangle<int> house (300, 120, 200, 170);
//    g.fillCheckerBoard(house, 30, 10, Colours::sandybrown, Colours::saddlebrown);

//    g.setColour (Colours::yellow);
//    g.drawEllipse (getWidth() - 70, 10, 60, 60, 3);

//    g.setColour (Colours::red);
//    Path roof;
//    roof.addTriangle (300, 110, 500, 110, 400, 70);
//    g.fillPath (roof);
}

void MainContentComponent::resized()
{
    currentSizeAsString = String (getWidth()) + " x " + String (getHeight());
//    frequencySlider.setBounds (10, 10, getWidth() - 20, 20);

}
