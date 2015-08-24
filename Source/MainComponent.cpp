#include "MainComponent.h"


/*==============================================================================
 * Constructor / Destructor
 *=============================================================================*/
MainContentComponent::MainContentComponent()
{
    setSize (oscSize * numberOsc + oscTopMargin * (numberOsc - 1),
             oscSize * 2 + oscLeftMargin * (numberOsc));

    drawSliders();

    osc1Generator.setFrequency(osc1StartFrequency);
    osc2Generator.setFrequency(osc2StartFrequency);
    osc3Generator.setFrequency(osc3StartFrequency);
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
		StkFloat osc1Data = osc1Generator.tick();
        StkFloat osc2Data = osc2Generator.tick();
        StkFloat osc3Data = osc3Generator.tick();

        for (int channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel)
        {
            float* const buffer = bufferToFill.buffer->getWritePointer (channel, bufferToFill.startSample);
			buffer[sample] = (osc1Data * osc1Level) + (osc2Data * osc2Level) + (osc3Data * osc3Level);
        }
	}
}

/*==============================================================================
 * Listener events
 *=============================================================================*/

void MainContentComponent::sliderValueChanged (Slider* slider)
{
    if (slider == &osc1FrequencySlider)
    {
        osc1Generator.setFrequency(osc1FrequencySlider.getValue());
    }
    else if (slider == &osc1AmplitudeSlider)
    {
        osc1Level = osc1AmplitudeSlider.getValue();
    }
    else if (slider == &osc2FrequencySlider)
    {
        osc2Generator.setFrequency(osc2FrequencySlider.getValue());
    }
    else if (slider == &osc2AmplitudeSlider)
    {
        osc2Level = osc2AmplitudeSlider.getValue();
    }
    else if (slider == &osc3FrequencySlider)
    {
        osc3Generator.setFrequency(osc3FrequencySlider.getValue());
    }
    else if (slider == &osc3AmplitudeSlider)
    {
        osc3Level = osc3AmplitudeSlider.getValue();
    }

}

/*==============================================================================
 * GUI
 *=============================================================================*/

void MainContentComponent::paint (Graphics& g)
{
    g.fillAll (Colours::transparentBlack);
    g.setFont (Font ("Helvetica", 10.0f, Font::plain));
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

    osc1FrequencySlider.setBounds(oscLeftMargin,
                                  oscTopMargin,
                                  oscSize,
                                  oscSize);
    osc1AmplitudeSlider.setBounds(oscLeftMargin,
                                  oscTopMargin*2+oscSize,
                                  oscSize,
                                  oscSize);

    osc2FrequencySlider.setBounds(oscLeftMargin+oscSize,
                                  oscTopMargin,
                                  oscSize,
                                  oscSize);
    osc2AmplitudeSlider.setBounds(oscLeftMargin+oscSize,
                                  oscTopMargin*2+oscSize,
                                  oscSize,
                                  oscSize);

    osc3FrequencySlider.setBounds(oscLeftMargin+oscSize*2,
                                  oscTopMargin,
                                  oscSize,
                                  oscSize);
    osc3AmplitudeSlider.setBounds(oscLeftMargin+oscSize*2,
                                  oscTopMargin*2+oscSize,
                                  oscSize,
                                  oscSize);

}

/*==============================================================================
 * Util
 *=============================================================================*/
void MainContentComponent::drawSliders()
{
    osc1FrequencySlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    osc1FrequencySlider.setTextBoxStyle (Slider::TextBoxBelow, false, 100, 30);

    osc1FrequencySlider.setRange (50.0, 5000.0);
    osc1FrequencySlider.setValue(osc1StartFrequency, dontSendNotification);
    osc1FrequencySlider.setSkewFactorFromMidPoint (500.0);
    osc1FrequencySlider.addListener (this);

    addAndMakeVisible (osc1FrequencySlider);

    osc1AmplitudeSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    osc1AmplitudeSlider.setTextBoxStyle (Slider::TextBoxBelow, false, 100, 30);

    osc1AmplitudeSlider.setRange (0.0, 1.0);
    osc1AmplitudeSlider.setValue(osc1Level, dontSendNotification);
    osc1AmplitudeSlider.setSkewFactorFromMidPoint (0.5);
    osc1AmplitudeSlider.addListener (this);

    addAndMakeVisible (osc1AmplitudeSlider);

    osc2FrequencySlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    osc2FrequencySlider.setTextBoxStyle (Slider::TextBoxBelow, false, 100, 30);

    osc2FrequencySlider.setRange (50.0, 5000.0);
    osc2FrequencySlider.setValue(osc2StartFrequency, dontSendNotification);
    osc2FrequencySlider.setSkewFactorFromMidPoint (500.0);
    osc2FrequencySlider.addListener (this);

    addAndMakeVisible (osc2FrequencySlider);

    osc2AmplitudeSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    osc2AmplitudeSlider.setTextBoxStyle (Slider::TextBoxBelow, false, 100, 30);

    osc2AmplitudeSlider.setRange (0.0, 1.0);
    osc2AmplitudeSlider.setValue(osc2Level, dontSendNotification);
    osc2AmplitudeSlider.setSkewFactorFromMidPoint (0.5);
    osc2AmplitudeSlider.addListener (this);

    addAndMakeVisible (osc2AmplitudeSlider);

    osc3FrequencySlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    osc3FrequencySlider.setTextBoxStyle (Slider::TextBoxBelow, false, 100, 30);

    osc3FrequencySlider.setRange (50.0, 5000.0);
    osc3FrequencySlider.setValue(osc3StartFrequency, dontSendNotification);
    osc3FrequencySlider.setSkewFactorFromMidPoint (500.0);
    osc3FrequencySlider.addListener (this);

    addAndMakeVisible (osc3FrequencySlider);

    osc3AmplitudeSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    osc3AmplitudeSlider.setTextBoxStyle (Slider::TextBoxBelow, false, 100, 30);

    osc3AmplitudeSlider.setRange (0.0, 1.0);
    osc3AmplitudeSlider.setValue(osc3Level, dontSendNotification);
    osc3AmplitudeSlider.setSkewFactorFromMidPoint (0.5);
    osc3AmplitudeSlider.addListener (this);

    addAndMakeVisible (osc3AmplitudeSlider);
}
