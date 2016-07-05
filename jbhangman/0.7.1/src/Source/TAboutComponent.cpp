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
#include "TAboutComponent.h"
//---------------------------------------------------------------------
TAboutComponent::TAboutComponent()
{  
    pAppNameLabel = new Label("AppNameLabel", 
                    String(ProjectInfo::projectName) +=
                    String(" ") +=
                    String(ProjectInfo::versionString));
                    
    pAppNameLabel->setFont(Font(18.0000f, Font::bold));
    pAppNameLabel->setJustificationType(Justification::centredLeft);
    pAppNameLabel->setEditable(false, false, false);
    addAndMakeVisible(pAppNameLabel);
    
    pAuthorLabel = new Label("AuthorLabel", String::empty);
    pAuthorLabel->setFont(Font(15.0000f, Font::bold));
    pAuthorLabel->setJustificationType(Justification::centredLeft);
    pAuthorLabel->setEditable(false, false, false);
    addAndMakeVisible(pAuthorLabel);
    
    pLinkedinLinkButton = new HyperlinkButton(s[2],
                                              URL("http://linkedin.com/in/andreynkuznetsov"));
    pLinkedinLinkButton->setTooltip("http://linkedin.com/in/andreynkuznetsov");
    addAndMakeVisible(pLinkedinLinkButton);
    
    pAppInfoLabel = new Label("AppInfoLabel", String::empty);
    pAppInfoLabel->setFont(Font(15.0000f, Font::plain));
    pAppInfoLabel->setJustificationType(Justification::topLeft);
    pAppInfoLabel->setEditable(false, false, false);
    addAndMakeVisible(pAppInfoLabel);
    
    pLinkButton = new HyperlinkButton(L"JUCE games website",
                                      URL("http://ankuznetsov.wix.com/jucegames"));
    pLinkButton->setTooltip("http://ankuznetsov.wix.com/jucegames");
    addAndMakeVisible(pLinkButton);
    
    pAcceptButton = new TextButton("AcceptButton");
    pAcceptButton->addListener(this);
    addAndMakeVisible(pAcceptButton);
    
    Me_Image = ImageCache::getFromMemory(BinaryData::me_png, 
                                         BinaryData::me_pngSize);
    
    setSize(400, 500);
}
//---------------------------------------------------------------------
TAboutComponent::~TAboutComponent ()
{
    deleteAllChildren();
}
//---------------------------------------------------------------------
void TAboutComponent::paint(Graphics& Canvas)
{
    Canvas.fillAll(Colours::lightgrey);

    Canvas.drawImageWithin(Me_Image,
                           10, 10, 160, 153,
                           RectanglePlacement::centred,
                           false);
}
//---------------------------------------------------------------------
void TAboutComponent::resized()
{
    pAppNameLabel->setBounds(175, 10, 215, 50);
    pAuthorLabel->setBounds(175, 70, 215, 60);
    pLinkedinLinkButton->setBounds(175, 140, 215, 25);
    pAppInfoLabel->setBounds(10, 172, 380, 210);
    pLinkButton->setBounds(10, 400, 380, 25);
    pAcceptButton->setBounds(125, 460, 150, 25);
}
//---------------------------------------------------------------------
void TAboutComponent::buttonClicked(Button* pButton)
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
void TAboutComponent::LanguageChange(LocalisedStrings& sTr)
{
    s.set(0, sTr.translate(L"Author: Andrey Kuznetsov"));
    s.set(1, sTr.translate(L"city of Almaty, Kazakhstan"));
    s.set(2, sTr.translate(L"My LinkedIn profile"));
    s.set(3, sTr.translate(L"Computer implementation of the popular guessing game"));
    s.set(4, sTr.translate(L"Hangman"));
    s.set(5, sTr.translate(L"How to play"));
    s.set(6, sTr.translate(L"In a classical paper and pencil game one player thinks of a word, and the other tries to guess it by suggesting letters, within a certain number of guesses."));
    s.set(7, sTr.translate(L"In the JBHangman application, the programme acts as the first player thinking a random word from the certain category which may be selected by a player from the drop-down list or menu."));
    s.set(8, sTr.translate(L"Number of guesses in the programme is 10."));
    s.set(9, sTr.translate(L"Accept"));
    
    String sAuthorInfo = s[0];
    sAuthorInfo += String("\n");
    String sTmpStr = s[1];
    sAuthorInfo += sTmpStr += String("\n") +=
    String(L"linmedsoft@gmail.com");
                         
    pAuthorLabel->setText(sAuthorInfo, dontSendNotification);
    pLinkedinLinkButton->setButtonText(s[2]);
    
    String sText = s[3]; 
    sText += String(" \"");
    sTmpStr = s[4];
    sText += sTmpStr += String("\".\n\n");
    sTmpStr = s[5];
    sText += sTmpStr += String("\n\n");
    sTmpStr = s[6];
    sText += sTmpStr += String("\n");
    sTmpStr = s[7];
    sText += sTmpStr;
    sTmpStr = s[8];
    sText += String(" ") += sTmpStr;
    
    pAppInfoLabel->setText(sText, dontSendNotification);
    
    pAcceptButton->setButtonText(s[9]);
}
//---------------------------------------------------------------------
