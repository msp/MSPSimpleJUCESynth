#include "MainComponent.h"


/*==============================================================================
 * Constructor / Destructor
 *=============================================================================*/
MainContentComponent::MainContentComponent()
{
    setSize (800, 600);
    drawSliders();

    sineWaveGenerator.setFrequency(startFrequency);
    setAudioChannels (0, 2);
}

MainContentComponent::~MainContentComponent()
{
    shutdownAudio();
}

/*==============================================================================
 * AudioAppComponent overrides
 *=============================================================================*/
void MainContentComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    Stk::setSampleRate(sampleRate);
}

void MainContentComponent::releaseResources()
{
}

void MainContentComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
    {
		StkFloat data = sineWaveGenerator.tick();
        for (int channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel)
        {
            float* const buffer = bufferToFill.buffer->getWritePointer (channel, bufferToFill.startSample);
			buffer[sample] = data * level;
        }
	}
}

/*==============================================================================
 * Listener events
 *=============================================================================*/

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

/*==============================================================================
 * GUI
 *=============================================================================*/

void MainContentComponent::paint (Graphics& g)
{
    g.fillAll (Colours::transparentBlack);
    g.setFont (Font ("Helvetica", 20.0f, Font::plain));
    g.setColour (Colours::black);
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
    frequencySlider.setBounds(50, 50, 150, 150);
    amplitudeSlider.setBounds(50, 250, 150, 150);
}

/*==============================================================================
 * Util
 *=============================================================================*/
void MainContentComponent::drawSliders()
{
    frequencySlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    frequencySlider.setTextBoxStyle (Slider::TextBoxBelow, false, 100, 30);

    frequencySlider.setRange (50.0, 5000.0);
    frequencySlider.setValue(startFrequency, dontSendNotification);
    frequencySlider.setSkewFactorFromMidPoint (500.0);
    frequencySlider.addListener (this);

    addAndMakeVisible (frequencySlider);

    amplitudeSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    amplitudeSlider.setTextBoxStyle (Slider::TextBoxBelow, false, 100, 30);

    amplitudeSlider.setRange (0.0, 1.0);
    amplitudeSlider.setValue(level, dontSendNotification);
    amplitudeSlider.setSkewFactorFromMidPoint (0.5);
    amplitudeSlider.addListener (this);

    addAndMakeVisible (amplitudeSlider);
}
