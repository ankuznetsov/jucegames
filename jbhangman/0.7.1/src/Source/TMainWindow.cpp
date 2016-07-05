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
#include "TMainWindow.h"
#include "TCentralComponent.h"
//---------------------------------------------------------------------
TMainWindow::TMainWindow() : DocumentWindow(
        JUCEApplication::getInstance()->getApplicationName(),
        Colours::darkblue,
        DocumentWindow::allButtons)
{
    setResizable(true, false);
    setVisible(true);
    
    pCentralComponent = new TCentralComponent(this);
    setContentOwned(pCentralComponent, true);
    CommandManager.registerAllCommandsForTarget(pCentralComponent);
    CommandManager.registerAllCommandsForTarget(JUCEApplication::getInstance());
    setMenuBar(pCentralComponent);
    
    centreWithSize(getWidth(), getHeight());
}
//---------------------------------------------------------------------
TMainWindow::~TMainWindow()
{
    setMenuBar(NULL);
}
//---------------------------------------------------------------------
void TMainWindow::closeButtonPressed()
{
    JUCEApplication::getInstance()->systemRequestedQuit();
}
//---------------------------------------------------------------------
