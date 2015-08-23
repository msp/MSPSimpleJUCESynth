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

    frequencySlider.setValue(200.0, dontSendNotification);
    frequencySlider.setRange (50.0, 5000.0);
    frequencySlider.setSkewFactorFromMidPoint (500.0);
    frequencySlider.addListener (this);

    addAndMakeVisible (frequencySlider);

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
    const float level = 0.125f;

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
}

void MainContentComponent::paint (Graphics& g)
{
    g.fillAll (Colours::lightblue);
    g.setFont (Font (20.0f));
    g.setFont (Font ("Times New Roman", 20.0f, Font::italic));
    g.setColour (Colours::darkblue);
    g.drawText (currentSizeAsString, getLocalBounds(), Justification::centred, true);

    g.setColour (Colours::green);
    g.drawLine (10, 300, 590, 300, 5);

    Rectangle<int> house (300, 120, 200, 170);
    g.fillCheckerBoard(house, 30, 10, Colours::sandybrown, Colours::saddlebrown);

    g.setColour (Colours::yellow);
    g.drawEllipse (getWidth() - 70, 10, 60, 60, 3);

    g.setColour (Colours::red);
    Path roof;
    roof.addTriangle (300, 110, 500, 110, 400, 70);
    g.fillPath (roof);
}

void MainContentComponent::resized()
{
    currentSizeAsString = String (getWidth()) + " x " + String (getHeight());
    frequencySlider.setBounds (10, 10, getWidth() - 20, 20);

}
