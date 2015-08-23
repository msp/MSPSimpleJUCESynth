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

    addAndMakeVisible (frequencySlider);
    frequencySlider.setRange (50.0, 5000.0);
    frequencySlider.setSkewFactorFromMidPoint (500.0); // [4]
    frequencySlider.addListener (this);

    setAudioChannels (0, 1); // no inputs, one output

}

MainContentComponent::~MainContentComponent()
{
    shutdownAudio();
}

void MainContentComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    currentSampleRate = sampleRate;
    updateAngleDelta();
}

void MainContentComponent::releaseResources()
{
}

void MainContentComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    const float level = 0.125f;
    float* const buffer = bufferToFill.buffer->getWritePointer (0, bufferToFill.startSample);

    for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
    {
        const float currentSample = (float) std::sin (currentAngle);
        currentAngle += angleDelta;
        buffer[sample] = currentSample * level;
    }
}

void MainContentComponent::sliderValueChanged (Slider* slider)
{
    if (slider == &frequencySlider)
    {
        if (currentSampleRate > 0.0)
            updateAngleDelta();
    }
}

void MainContentComponent::updateAngleDelta()
{
    const double cyclesPerSample = frequencySlider.getValue() / currentSampleRate; // [2]
    angleDelta = cyclesPerSample * 2.0 * double_Pi;                                // [3]
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
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    currentSizeAsString = String (getWidth()) + " x " + String (getHeight());
    frequencySlider.setBounds (10, 10, getWidth() - 20, 20);

}
