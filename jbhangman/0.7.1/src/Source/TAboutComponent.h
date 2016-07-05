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
#ifndef _TAboutComponent_h_
#define _TAboutComponent_h_
//---------------------------------------------------------------------
#include "../JuceLibraryCode/JuceHeader.h"
//---------------------------------------------------------------------
class TAboutComponent : public Component,
                        public ButtonListener
{
public:
    TAboutComponent();
    ~TAboutComponent();
    
    void paint(Graphics&);
    void resized();
    void buttonClicked(Button*);
    
    void LanguageChange(LocalisedStrings&);
    
private:   
    Label* pAppNameLabel;
    Label* pAuthorLabel;
    Label* pAppInfoLabel;
    HyperlinkButton* pLinkedinLinkButton;
    HyperlinkButton* pLinkButton;
    TextButton* pAcceptButton;
    Image Me_Image;
    
    StringArray s;
    
    TAboutComponent (const TAboutComponent&);
    const TAboutComponent& operator= (const TAboutComponent&);
};
//---------------------------------------------------------------------
#endif
