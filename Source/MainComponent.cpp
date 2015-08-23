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
}

MainContentComponent::~MainContentComponent()
{
}

void MainContentComponent::paint (Graphics& g)
{
    g.fillAll (Colours::lightblue);
//    g.setFont (Font (20.0f));
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
}
