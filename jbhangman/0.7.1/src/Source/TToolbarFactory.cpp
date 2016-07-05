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
#include "TToolbarFactory.h"
#include "TWLComboBox.h"
#include "TThemeComboBox.h"
//---------------------------------------------------------------------
TToolbarFactory::TToolbarFactory()
{
    for(int i = 0; i < 4; i++)
    {
        s.add(String::empty);
    }
}
//---------------------------------------------------------------------
TToolbarFactory::~TToolbarFactory()
{
}
//---------------------------------------------------------------------
void TToolbarFactory::getAllToolbarItemIds(Array<int>& iIDs)
{
    iIDs.add(GameNew);
    iIDs.add(GameQuit);
    iIDs.add(WLToolbar);
    iIDs.add(ThemeToolbar);
    iIDs.add(HelpAbout);
    iIDs.add(HelpAboutJuce);
    iIDs.add(SettingsSave);
    iIDs.add(spacerId);
    iIDs.add(separatorBarId);
}
//---------------------------------------------------------------------
void TToolbarFactory::getDefaultItemSet(Array<int>& iIDs)
{
    iIDs.add(GameQuit);
    iIDs.add(separatorBarId);
    iIDs.add(GameNew);
    iIDs.add(WLToolbar);
    iIDs.add(separatorBarId);
    iIDs.add(spacerId);
    iIDs.add(ThemeToolbar);
    iIDs.add(SettingsSave);
    iIDs.add(separatorBarId);
    iIDs.add(spacerId);
    iIDs.add(HelpAbout);
    iIDs.add(HelpAboutJuce);
}
//---------------------------------------------------------------------
ToolbarItemComponent* TToolbarFactory::createItem(int iItemID)
{
    switch(iItemID)
    {
        case GameNew:
        {
            pGameNewButton = new ToolbarButton(iItemID, L"New", 
                                                Drawable::createFromImageData(BinaryData::new_png, BinaryData::new_pngSize),
                                                0);
            pGameNewButton->addShortcut(KeyPress('n', ModifierKeys::ctrlModifier, 0));
            return pGameNewButton;
        }
        case GameQuit:
        {
            pGameQuitButton = new ToolbarButton(iItemID, L"Quit", 
                                                Drawable::createFromImageData(BinaryData::exit_png, BinaryData::exit_pngSize),
                                                0);
            pGameQuitButton->addShortcut(KeyPress('q', ModifierKeys::ctrlModifier, 0));
            return pGameQuitButton;
        }
        case WLToolbar:
        {
            pWLComboBox = new TWLComboBox(iItemID);

            return pWLComboBox;
        }
        case ThemeToolbar:
        {
            pThemeComboBox = new TThemeComboBox(iItemID);

            return pThemeComboBox;
        }
        case HelpAbout:
        {
            pHelpAboutButton = new ToolbarButton(iItemID, L"About", 
                                                     Drawable::createFromImageData(BinaryData::info_png, BinaryData::info_pngSize),
                                                     0);
            pHelpAboutButton->addShortcut(KeyPress('a', ModifierKeys::ctrlModifier, 0));
            return pHelpAboutButton;
        }
        case HelpAboutJuce:
        {
            pHelpAboutJuceButton = new ToolbarButton(iItemID, L"About Juce", 
                                                     Drawable::createFromImageData(BinaryData::jucesm_png, BinaryData::jucesm_pngSize),
                                                     0);
            pHelpAboutJuceButton->addShortcut(KeyPress('j', ModifierKeys::ctrlModifier, 0));
            return pHelpAboutJuceButton;
        }
        case SettingsSave:
        {
            pSettingsSaveButton = new ToolbarButton(iItemID, L"Save settings", 
                                                Drawable::createFromImageData(BinaryData::save_png, BinaryData::save_pngSize),
                                                0);
            pSettingsSaveButton->addShortcut(KeyPress('s', ModifierKeys::ctrlModifier, 0));
            return pSettingsSaveButton;
        }
        default:
        {
            break;
        }
    }

    return 0;
}
//---------------------------------------------------------------------
void TToolbarFactory::LanguageChange(LocalisedStrings& sTr)
{
    s.set(0, sTr.translate(L"Guess a new word from the selected category (Ctrl+N)"));
    s.set(1, sTr.translate(L"Finish the programme (Ctrl+Q)"));
    s.set(2, sTr.translate(L"Show brief information about the programme and its author (Ctrl+A)"));
    s.set(3, sTr.translate(L"Show information about the JUCE library (Ctrl+J)"));
    s.set(4, sTr.translate(L"Save current settings (language, category, theme)  (Ctrl+S)"));
    
    pGameNewButton->setTooltip(s[0]);
    pGameQuitButton->setTooltip(s[1]);
    pHelpAboutButton->setTooltip(s[2]);
    pHelpAboutJuceButton->setTooltip(s[3]);
    pSettingsSaveButton->setTooltip(s[4]);
    
    pWLComboBox->LanguageChange(sTr);
    pThemeComboBox->LanguageChange(sTr);
}
//---------------------------------------------------------------------
