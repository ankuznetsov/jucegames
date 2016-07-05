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
#ifndef _TCentralComponent_h_
#define _TCentralComponent_h_
//---------------------------------------------------------------------
#include "../JuceLibraryCode/JuceHeader.h"
#include "TMainWindow.h"
#include "TToolbarFactory.h"
//---------------------------------------------------------------------
class TCentralComponent : public Component,
                          public ButtonListener,
                          public MenuBarModel,
                          public ApplicationCommandTarget,
                          public TextEditor::Listener
{
public:
    TCentralComponent(TMainWindow* pParent);
    ~TCentralComponent();

    void paint (Graphics&);
    void resized();
    
    void buttonClicked(Button*);
    void textEditorReturnKeyPressed(TextEditor&);

private:
    TMainWindow* pParent;
    
    LookAndFeel_V1 Look1;
    LookAndFeel_V2 Look2;
    LookAndFeel_V3 Look3;
    int iLook;
    
    String sPath;
    StringArray s;
    String sLocale;
    
    Toolbar* pToolbar;
    TToolbarFactory ToolbarFactory;
    
    TextEditor* pUsedLettersEdit;
    Label* pMissesCaptionLabel;
    OwnedArray<Label> MissLabel;
    Label* pWordCaptionLabel;
    OwnedArray<Label> LetterLabel;
    Label* pLetterInputLabel;
    TextEditor* pLetterInputEdit;
    TextButton* pSubmitLetterButton;
    Image HangmanImage;
    
    String sWord;
    int iLetters;
    StringArray sUsedLetters;
    int iMisses;
    int iHits;
    
    StringArray getMenuBarNames();
    void menuItemSelected(int, int);
    PopupMenu getMenuForIndex(int, const String&);
    ApplicationCommandTarget* getNextCommandTarget();
    void getAllCommands(Array<int>&);
    void getCommandInfo(CommandID, ApplicationCommandInfo&);
    bool perform(const InvocationInfo&);
    
    void LoadSettings();
    LocalisedStrings NewTranslator(String);
    void LanguageChange(LocalisedStrings&);
    bool bLanguageSelected(String);
    
    bool bLookAndFeelSelected(int);
    
    inline void CreateToolbar();
    
    bool bSaveSettings();
    
    void CreateMissLabels();
    void ResizeMissLabels();
    
    void CreateWordLabels(int);
    void ResizeWordLabels(int);
    void SetNewWord();
    
    void SubmitLetter();
    void DrawHangman(int);
    Array<int> GetLetterPositions(String, String);
    
    void ClearMissLabels();
    void NewGame();
    
    void ShowAboutDialogue();
    void ShowAboutJuceDialogue();
    
    TCentralComponent(const TCentralComponent&);
    const TCentralComponent& operator= (const TCentralComponent&);
};

//---------------------------------------------------------------------
#endif
