/***********************************************************************
* This is a JUCE based computer realization of the Hangman game.       *
* 17-28 June 2016                                                      *
* Copyright (C) 2016 by Andrey N. Kuznetsov, Almaty, Kazakhstan.       *
* E-mail: linmedsoft@gmail.com                                         *
*                                                                      *
* This programme is free software; you can redistribute it and/or      *
* modify it under the terms of the GNU General Public License          *
* as published by the Free Software Foundation; either version 2       *
* of the named License, or any later version.                          *
*                                                                      *
* This program is distributed in the hope that it will be useful,      *
* but WITHOUT ANY WARRANTY; without even the implied warranty of       *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the         *
* GNU General Public License for more details.                         *
*                                                                      *
* You should have received a copy of the GNU General Public License    *
* along with this program; if not, write to the Free Software          *
* Foundation, Inc., 59 Temple Place, Suite 330, Boston,                *
* MA 02111-1307, USA                                                   *
************************************************************************/
#include "TAboutJuceComponent.h"
//---------------------------------------------------------------------
TAboutJuceComponent::TAboutJuceComponent()
{
    pAboutJuceTitleLabel = new Label("AboutJuceTitleLabel",
                                     sAboutJuceCaption);
    pAboutJuceTitleLabel->setFont(Font(18.0000f, Font::bold));
    pAboutJuceTitleLabel->setJustificationType(Justification::centredLeft);
    pAboutJuceTitleLabel->setEditable(false, false, false);
    addAndMakeVisible(pAboutJuceTitleLabel);
    
    pJuceInfoLabel = new Label ("JuceInfoLabel", String::empty);
    pJuceInfoLabel->setFont(Font(15.0000f, Font::plain));
    pJuceInfoLabel->setJustificationType(Justification::centredLeft);
    pJuceInfoLabel->setEditable(false, false, false);
    addAndMakeVisible(pJuceInfoLabel);
    
    pAcceptButton = new TextButton("AcceptButton");
    pAcceptButton->setButtonText(sAcceptButtonText);
    pAcceptButton->addListener(this);
    addAndMakeVisible(pAcceptButton);
    
    Juce_Image = ImageCache::getFromMemory(BinaryData::juce_png, 
                                           BinaryData::juce_pngSize);
    
    setSize(500, 400);
}
//---------------------------------------------------------------------
TAboutJuceComponent::~TAboutJuceComponent ()
{
    deleteAllChildren();
}
//---------------------------------------------------------------------
void TAboutJuceComponent::paint(Graphics& Canvas)
{
    Canvas.fillAll(Colours::lightgrey);

    Canvas.drawImage(Juce_Image,
                     10, 10, 100, 100,
                     0, 0, Juce_Image.getWidth(), Juce_Image.getHeight());
}
//---------------------------------------------------------------------
void TAboutJuceComponent::resized()
{
    pAboutJuceTitleLabel->setBounds(120, 10, 370, 25);
    pJuceInfoLabel->setBounds(120, 45, 370, 300);
    pAcceptButton->setBounds(175, 360, 150, 25);
}
//---------------------------------------------------------------------
void TAboutJuceComponent::buttonClicked(Button* pButton)
{
    if(pButton == pAcceptButton)
    {
        DialogWindow* pDialogWindow = this->findParentComponentOfClass<DialogWindow>();
        if (pDialogWindow != nullptr)
        {
            pDialogWindow->exitModalState(14101969);
        }
    }
}
//---------------------------------------------------------------------
void TAboutJuceComponent::LanguageChange(LocalisedStrings& sTr)
{
    sAboutJuceCaption = sTr.translate(L"About JUCE");
    pAboutJuceTitleLabel->setText(sAboutJuceCaption, dontSendNotification);
    
    String sVersion = SystemStats::getJUCEVersion().substring(6);
    sText = sTr.translate(L"This programme uses JUCE version") += String(" ") += sVersion 
            += String(L".\n\n");
    sText += sTr.translate(L"JUCE is a C++ toolkit for cross-platform application development.") 
                           += String(L"\n");
    sText += sTr.translate(L"JUCE provides single-soure portability across Linux, MS Windows, Mac OS X and Android.")
                           += String(L"\n\n");
    sText += sTr.translate(L"JUCE is a ROLI product. See https://www.roli.com/juce for more information.")
                           += String(L"\n\n");                  
    sText += sTr.translate(L"JUCE is available under different licenses. This application uses the Open Source version of JUCE under GPL 2.")
                           += String(L"\n\n");                    
    sText += sTr.translate(L"You need the commercial license of JUCE for proprietary (closed source) applications.");
    pJuceInfoLabel->setText(sText, dontSendNotification);
    
    sAcceptButtonText = sTr.translate(L"Accept");
    pAcceptButton->setButtonText(sAcceptButtonText);
}
//---------------------------------------------------------------------
