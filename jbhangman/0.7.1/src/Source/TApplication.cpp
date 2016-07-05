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
#include "TApplication.h"
#include "TMainWindow.h"
//---------------------------------------------------------------------
TApplication::TApplication()
{
}
//---------------------------------------------------------------------
TApplication::~TApplication()
{
}
//---------------------------------------------------------------------
void TApplication::initialise(const String& /*sCommandLine*/)
{
    pMainWindow = new TMainWindow();
}
//---------------------------------------------------------------------
void TApplication::shutdown()
{
    if(pMainWindow != 0) delete pMainWindow;
}
//---------------------------------------------------------------------
void TApplication::systemRequestedQuit()
{
    quit();
}
//---------------------------------------------------------------------
const String TApplication::getApplicationName()
{
    return String(ProjectInfo::projectName) += 
           String(" ") +=
           String(ProjectInfo::versionString);
}
//---------------------------------------------------------------------
const String TApplication::getApplicationVersion()
{
    return ProjectInfo::versionString;
}
//---------------------------------------------------------------------
bool TApplication::moreThanOneInstanceAllowed()
{
    return false;
}
//---------------------------------------------------------------------
