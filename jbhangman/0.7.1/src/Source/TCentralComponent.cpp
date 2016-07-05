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
#include "../JuceLibraryCode/JuceHeader.h"
#include "TCentralComponent.h"
#include "TActions.h"
#include "TThemeComboBox.h"
#include "TWLComboBox.h"
#include "TAboutComponent.h"
#include "TAboutJuceComponent.h"
#include <locale>
#include <ctime>
#include <iostream>
using namespace std;
//---------------------------------------------------------------------
TCentralComponent::TCentralComponent(TMainWindow* pParent) : 
                                     Component("Central Component")
{
    this->pParent = pParent;
    
    LookAndFeel::setDefaultLookAndFeel(& Look2);
    iLook = 2;
    
    for(int i = 0; i < 45; i++)
    {
        s.add(String::empty);
    }
    
    CreateToolbar();
    
    pUsedLettersEdit = new TextEditor("Letters Used Edit");
    pUsedLettersEdit->setMultiLine(true);
    pUsedLettersEdit->setReturnKeyStartsNewLine(false);
    pUsedLettersEdit->setReadOnly(true);
    pUsedLettersEdit->setScrollbarsShown(true);
    pUsedLettersEdit->setCaretVisible(false);
    pUsedLettersEdit->setPopupMenuEnabled(false);
    pUsedLettersEdit->setColour(TextEditor::outlineColourId, Colours::blueviolet);
    addAndMakeVisible(pUsedLettersEdit);

    pMissesCaptionLabel = new Label("MissesCaptionLabel", s[1]);
    pMissesCaptionLabel->setFont(Font(20.0000f, Font::bold));
    pMissesCaptionLabel->setJustificationType(Justification::centredLeft);
    pMissesCaptionLabel->setEditable(false, false, false);
    pMissesCaptionLabel->setColour(Label::textColourId, Colours::red);
    addAndMakeVisible(pMissesCaptionLabel);
    
    CreateMissLabels();
    
    pWordCaptionLabel = new Label("WordCaptionLabel", s[2]);
    pWordCaptionLabel->setFont(Font(20.0000f, Font::bold));
    pWordCaptionLabel->setJustificationType(Justification::centredLeft);
    pWordCaptionLabel->setEditable(false, false, false);
    pWordCaptionLabel->setColour(Label::textColourId, Colours::blue);
    pWordCaptionLabel->setColour(TextEditor::backgroundColourId, Colours::white);
    addAndMakeVisible(pWordCaptionLabel);
    
    pLetterInputLabel = new Label("LetterInputLabel", s[3]);
    pLetterInputLabel->setFont(Font(15.0000f, Font::bold));
    pLetterInputLabel->setJustificationType(Justification::centredLeft);
    pLetterInputLabel->setEditable(false, false, false);
    pLetterInputLabel->setColour(Label::textColourId, Colours::black);
    pLetterInputLabel->setColour(TextEditor::backgroundColourId, Colours::white);
    addAndMakeVisible(pLetterInputLabel);

    pLetterInputEdit = new TextEditor("LetterInputEdit");
    pLetterInputEdit->setMultiLine(false);
    pLetterInputEdit->setReturnKeyStartsNewLine(false);
    pLetterInputEdit->setReadOnly(false);
    pLetterInputEdit->setScrollbarsShown(false);
    pLetterInputEdit->setCaretVisible(true);
    pLetterInputEdit->setPopupMenuEnabled(false);
    pLetterInputEdit->setText(String::empty);
    pLetterInputEdit->setColour(TextEditor::outlineColourId, Colours::blueviolet);
    pLetterInputEdit->addListener(this);
    addAndMakeVisible(pLetterInputEdit);

    pSubmitLetterButton = new TextButton("SubmitLetterButton");
    pSubmitLetterButton->addListener(this);
    addAndMakeVisible(pSubmitLetterButton);
    
    LoadSettings();
    LocalisedStrings sTr = NewTranslator(sLocale);
    LanguageChange(sTr);
    ToolbarFactory.pWLComboBox->LoadWL(sLocale);
    cout << "The words list was loaded..." << endl;
    
    SetNewWord();
    
    HangmanImage = ImageCache::getFromMemory(BinaryData::_00_png, 
                                             BinaryData::_00_pngSize);
    
    setSize(800, 600);
}
//---------------------------------------------------------------------
TCentralComponent::~TCentralComponent()
{
    MissLabel.clear();
    LetterLabel.clear();
    deleteAllChildren();
}
//---------------------------------------------------------------------
void TCentralComponent::paint(Graphics& Canvas)
{
    Canvas.fillAll(Colours::lightgrey);
    
    Canvas.drawImage(ToolbarFactory.pThemeComboBox->Background_Image,
                     0, 0, proportionOfWidth(1.0000f),
                     proportionOfHeight(1.0000f),
                     0, 0, ToolbarFactory.pThemeComboBox->Background_Image.getWidth(),
                     ToolbarFactory.pThemeComboBox->Background_Image.getHeight());
                     
    Canvas.drawImage(HangmanImage,
                     10, 40, 250, 282,
                     0, 0, HangmanImage.getWidth(), HangmanImage.getHeight());
    
    pLetterInputEdit->setWantsKeyboardFocus(true);
    pLetterInputEdit->grabKeyboardFocus();
}
//---------------------------------------------------------------------
void TCentralComponent::resized()
{
    pToolbar->setBounds(0, 0, getWidth(), 32);
    pUsedLettersEdit->setBounds(10, 332, 250, getHeight() - 342);
    pMissesCaptionLabel->setBounds(280, 60, 100, 25);
    ResizeMissLabels();
    pWordCaptionLabel->setBounds(280, 200, getWidth() - 290, 25);
    pLetterInputLabel->setBounds(280, 425, 100, 25);
    pLetterInputEdit->setBounds(280, 460, 100, 25);
    pSubmitLetterButton->setBounds(390, 460, 150, 25);
    ResizeWordLabels(iLetters);
}
//---------------------------------------------------------------------
void TCentralComponent::buttonClicked(Button* pButton)
{
    if(pButton == ToolbarFactory.pGameQuitButton)
    {
        JUCEApplication::quit();
    }
    if(pButton == ToolbarFactory.pSettingsSaveButton)
    {
        bSaveSettings();
    }
    else if(pButton == pSubmitLetterButton)
    {
        SubmitLetter();
    }
    else if(pButton == ToolbarFactory.pGameNewButton)
    {
        NewGame();
    }
    else if(pButton == ToolbarFactory.pHelpAboutButton)
    {
        ShowAboutDialogue();
    }
    else if(pButton == ToolbarFactory.pHelpAboutJuceButton)
    {
        ShowAboutJuceDialogue();
    }
}
//---------------------------------------------------------------------
StringArray TCentralComponent::getMenuBarNames()
{
    StringArray sMenuNames;
    sMenuNames.add(s[0]);
    sMenuNames.add(s[1]);
    sMenuNames.add(L"Look-and-feel");
    sMenuNames.add(s[2]);
    sMenuNames.add(s[3]);
    sMenuNames.add(L"?");
    return sMenuNames;
}
//---------------------------------------------------------------------
void TCentralComponent::menuItemSelected(int iMenuItemID, int /*iTopLevelMenuIndex*/)
{
    switch(iMenuItemID)
    {
        case GameQuit:
        {
            JUCEApplication::quit();
            break;
        }
        case GameNew:
        {
            NewGame();
            break;
        }
        case HelpAbout:
        {
            ShowAboutDialogue();
            break;
        }
        case HelpAboutJuce:
        {
            ShowAboutJuceDialogue();
            break;
        }
    }
}
//---------------------------------------------------------------------
PopupMenu TCentralComponent::getMenuForIndex(int iIndex, 
                                             const String& /*sMenuName*/)
{
    ApplicationCommandManager* pCommandManager = &(pParent->CommandManager);
    
    PopupMenu Menu;
    
    switch(iIndex)
    {
        case 0:
        {
            Menu.addItem(GameNew, s[4], true, false,
                ImageCache::getFromMemory(BinaryData::new_png, 
                                          BinaryData::new_pngSize));
            Menu.addSeparator();
            Menu.addItem(GameQuit, s[5], true, false, 
                ImageCache::getFromMemory(BinaryData::exit_png, 
                                          BinaryData::exit_pngSize));
            break;
        }
        case 1:
        {
            Menu.addCommandItem(pCommandManager, CategoryAnimals);
            Menu.addCommandItem(pCommandManager, CategoryClothing);
            Menu.addCommandItem(pCommandManager, CategoryFruits);
            Menu.addCommandItem(pCommandManager, CategoryObjects);
            Menu.addCommandItem(pCommandManager, CategoryProfessions);
            Menu.addCommandItem(pCommandManager, CategoryTransportation);
            Menu.addCommandItem(pCommandManager, CategoryVegetables);
            break;
        }
        case 2:
        {
            Menu.addCommandItem(pCommandManager, LookLook1);
            Menu.addCommandItem(pCommandManager, LookLook2);
            Menu.addCommandItem(pCommandManager, LookLook3);
            break;
        }
        case 3:
        {
            Menu.addCommandItem(pCommandManager, ThemeBlue);
            Menu.addCommandItem(pCommandManager, ThemeEagle);
            Menu.addCommandItem(pCommandManager, ThemeVillage);
            Menu.addCommandItem(pCommandManager, ThemeMountains);
            Menu.addCommandItem(pCommandManager, ThemeNight);
            Menu.addCommandItem(pCommandManager, ThemeSunset);
            Menu.addCommandItem(pCommandManager, ThemeIsland);
            Menu.addCommandItem(pCommandManager, ThemeWaterfall);
            break;
        }
        case 4:
        {
            Menu.addCommandItem(pCommandManager, LanguageEnglish, 
                                NewTranslator("en").getLanguageName());
            Menu.addCommandItem(pCommandManager, LanguageRussian, 
                                NewTranslator("ru").getLanguageName());
            break;
        }
        case 5:
        {
            Menu.addItem(HelpAbout, s[6], true, false,
                ImageCache::getFromMemory(BinaryData::info_png, 
                                          BinaryData::info_pngSize));
            Menu.addSeparator();
            Menu.addItem(HelpAboutJuce, s[7], true, false,
                ImageCache::getFromMemory(BinaryData::jucesm_png, 
                                          BinaryData::jucesm_pngSize));
            break;
        }
    }

    return Menu;
}
//---------------------------------------------------------------------
ApplicationCommandTarget* TCentralComponent::getNextCommandTarget()
{
    return findFirstTargetParentComponent();
}
//---------------------------------------------------------------------
void TCentralComponent::getAllCommands(Array<int>& iCommands)
{
    const CommandID IDs[] =
    {
        CategoryAnimals,
        CategoryClothing,
        CategoryFruits,
        CategoryObjects,
        CategoryProfessions,
        CategoryTransportation,
        CategoryVegetables,
        LookLook1,
        LookLook2,
        LookLook3,
        ThemeBlue,
        ThemeEagle,
        ThemeVillage,
        ThemeMountains,
        ThemeNight,
        ThemeSunset,
        ThemeIsland,
        ThemeWaterfall,
        LanguageEnglish,
        LanguageRussian
    };
    
    iCommands.addArray(IDs, numElementsInArray(IDs));
}
//---------------------------------------------------------------------
void TCentralComponent::getCommandInfo(CommandID ID, ApplicationCommandInfo& Result)
{
    switch(ID)
    {
        case CategoryAnimals:
        {
            Result.setInfo(s[37], L"The animals words list", "Category", 0);
            Result.setTicked(ToolbarFactory.pWLComboBox->iGetListNumber() == 1);
            break;
        }
        case CategoryClothing:
        {
            Result.setInfo(s[38], L"The clothing words list", "Category", 0);
            Result.setTicked(ToolbarFactory.pWLComboBox->iGetListNumber() == 2);
            break;
        }
        case CategoryFruits:
        {
            Result.setInfo(s[39], L"The fruits words list", "Category", 0);
            Result.setTicked(ToolbarFactory.pWLComboBox->iGetListNumber() == 3);
            break;
        }
        case CategoryObjects:
        {
            Result.setInfo(s[40], L"The objects words list", "Category", 0);
            Result.setTicked(ToolbarFactory.pWLComboBox->iGetListNumber() == 4);
            break;
        }
        case CategoryProfessions:
        {
            Result.setInfo(s[41], L"The professions words list", "Category", 0);
            Result.setTicked(ToolbarFactory.pWLComboBox->iGetListNumber() == 5);
            break;
        }
        case CategoryTransportation:
        {
            Result.setInfo(s[42], L"The transportation words list", "Category", 0);
            Result.setTicked(ToolbarFactory.pWLComboBox->iGetListNumber() == 6);
            break;
        }
        case CategoryVegetables:
        {
            Result.setInfo(s[43], L"The vegetables words list", "Category", 0);
            Result.setTicked(ToolbarFactory.pWLComboBox->iGetListNumber() == 7);
            break;
        }
        case LookLook1:
        {
            Result.setInfo(L"LookAndFeel V1", L"Switch to LookAndFeel V1", 
                           L"Look-and-feel", 0);
            Result.setTicked(bLookAndFeelSelected(1));
            break;
        }
        case LookLook2:
        {
            Result.setInfo(L"LookAndFeel V2", L"Switch to LookAndFeel V1", 
                           L"Look-and-feel", 0);
            Result.setTicked(bLookAndFeelSelected(2));
            break;
        }
        case LookLook3:
        {
            Result.setInfo(L"LookAndFeel V3", L"Switch to LookAndFeel V1", 
                           L"Look-and-feel", 0);
            Result.setTicked(bLookAndFeelSelected(3));
            break;
        }
        case ThemeBlue:
        {
            Result.setInfo(s[14], L"Set a blue theme", "Theme", 0);
            Result.setTicked(ToolbarFactory.pThemeComboBox->iGetImageNumber() == 1);
            break;
        }
        case ThemeEagle:
        {
            Result.setInfo(s[15], L"Set an eagle theme", "Theme", 0);
            Result.setTicked(ToolbarFactory.pThemeComboBox->iGetImageNumber() == 2);
            break;
        }
        case ThemeVillage:
        {
            Result.setInfo(s[16], L"Set a village theme", "Theme", 0);
            Result.setTicked(ToolbarFactory.pThemeComboBox->iGetImageNumber() == 3);
            break;
        }
        case ThemeMountains:
        {
            Result.setInfo(s[17], L"Set a mountains theme", "Theme", 0);
            Result.setTicked(ToolbarFactory.pThemeComboBox->iGetImageNumber() == 4);
            break;
        }
        case ThemeNight:
        {
            Result.setInfo(s[18], L"Set a night theme", "Theme", 0);
            Result.setTicked(ToolbarFactory.pThemeComboBox->iGetImageNumber() == 5);
            break;
        }
        case ThemeSunset:
        {
            Result.setInfo(s[19], L"Set a sunset theme", "Theme", 0);
            Result.setTicked(ToolbarFactory.pThemeComboBox->iGetImageNumber() == 6);
            break;
        }
        case ThemeIsland:
        {
            Result.setInfo(s[20], L"Set an island theme", "Theme", 0);
            Result.setTicked(ToolbarFactory.pThemeComboBox->iGetImageNumber() == 7);
            break;
        }
        case ThemeWaterfall:
        {
            Result.setInfo(s[21], L"Set a waterfall theme", "Theme", 0);
            Result.setTicked(ToolbarFactory.pThemeComboBox->iGetImageNumber() == 8);
            break;
        }
        case LanguageEnglish:
        {
            Result.setInfo(NewTranslator("en").getLanguageName(), 
                          L"Switch to English", L"Language", 0);
            Result.setTicked(bLanguageSelected("en"));
            break;
        }
        case LanguageRussian:
        {
            Result.setInfo(NewTranslator("ru").getLanguageName(), 
                           L"Switch to Russian", "Language", 0);
            Result.setTicked(bLanguageSelected("ru"));
            break;
        }
    }
}
//---------------------------------------------------------------------
bool TCentralComponent::perform(const InvocationInfo& Info)
{
    switch(Info.commandID)
    {
        case CategoryAnimals:
        {
            ToolbarFactory.pWLComboBox->SetWordsList(0);
            break;
        }
        case CategoryClothing:
        {
            ToolbarFactory.pWLComboBox->SetWordsList(1);
            break;
        }
        case CategoryFruits:
        {
            ToolbarFactory.pWLComboBox->SetWordsList(2);
            break;
        }
        case CategoryObjects:
        {
            ToolbarFactory.pWLComboBox->SetWordsList(3);
            break;
        }
        case CategoryProfessions:
        {
            ToolbarFactory.pWLComboBox->SetWordsList(4);
            break;
        }
        case CategoryTransportation:
        {
            ToolbarFactory.pWLComboBox->SetWordsList(5);
            break;
        }
        case CategoryVegetables:
        {
            ToolbarFactory.pWLComboBox->SetWordsList(6);
            break;
        }
        case LookLook1:
        {
            LookAndFeel::setDefaultLookAndFeel(& Look1);
            iLook = 1;
            break;
        }
        case LookLook2:
        {
            LookAndFeel::setDefaultLookAndFeel(& Look2);
            iLook = 2;
            break;
        }
        case LookLook3:
        {
            LookAndFeel::setDefaultLookAndFeel(& Look3);
            iLook = 3;
            break;
        }
        case ThemeBlue:
        {
            ToolbarFactory.pThemeComboBox->SetTheme(0);
            break;
        }
        case ThemeEagle:
        {
            ToolbarFactory.pThemeComboBox->SetTheme(1);
            break;
        }
        case ThemeVillage:
        {
            ToolbarFactory.pThemeComboBox->SetTheme(2);
            break;
        }
        case ThemeMountains:
        {
            ToolbarFactory.pThemeComboBox->SetTheme(3);
            break;
        }
        case ThemeNight:
        {
            ToolbarFactory.pThemeComboBox->SetTheme(4);
            break;
        }
        case ThemeSunset:
        {
            ToolbarFactory.pThemeComboBox->SetTheme(5);
            break;
        }
        case ThemeIsland:
        {
            ToolbarFactory.pThemeComboBox->SetTheme(6);
            break;
        }
        case ThemeWaterfall:
        {
            ToolbarFactory.pThemeComboBox->SetTheme(7);
            break;
        }
        case LanguageEnglish:
        {
            sLocale = "en";
            LocalisedStrings sTr = NewTranslator(sLocale);
            LanguageChange(sTr);
            ToolbarFactory.pWLComboBox->LoadWL(sLocale);
            NewGame();
            break;
        }
        case LanguageRussian:
        {
            sLocale = "ru";
            LocalisedStrings sTr = NewTranslator(sLocale);
            LanguageChange(sTr);
            ToolbarFactory.pWLComboBox->LoadWL(sLocale);
            NewGame();
            break;
        }
    }
    
    return true;
}
//---------------------------------------------------------------------
void TCentralComponent::LoadSettings()
{
    sLocale = String(setlocale(LC_CTYPE, ""));
    sLocale = sLocale.substring(0, 2);
    sLocale = sLocale.toLowerCase();
    
    sPath = File::getSpecialLocation(File::userHomeDirectory).getFullPathName();
    #if JUCE_WINDOWS
        String sFolderName(L"\\.JBHangman\\settings.xml");
    #endif
    
    #if JUCE_LINUX || JUCE-MAX
        String sFolderName(L"/.JBHangman/settings.xml");
    #endif
    
    sPath = sPath += sFolderName;
    
    File SettingsFile(sPath);
    
    if(!SettingsFile.exists())
    {
        return;
    }
    
    XmlDocument SettingsDoc(SettingsFile);
    XmlElement* pRootElement = SettingsDoc.getDocumentElement();
    
    if(pRootElement == NULL)
    {
        cout << SettingsDoc.getLastParseError().toStdString() << endl;
        return;
    }
    
    if(!pRootElement->hasTagName(String(L"settings")))
    {
        cout << "Unsupported file format!" <<endl;
        return;
    }
    
    XmlElement* pLangElement = pRootElement->getChildByName("lang");
    XmlElement* pCategoryElement = pRootElement->getChildByName("category");
    XmlElement* pThemeElement = pRootElement->getChildByName("theme");
    XmlElement* pLookElement = pRootElement->getChildByName("look");
    
    String sCategory, sTheme, sLook;
    
    if(pLangElement != 0)
    {
        sLocale = pLangElement->getAllSubText();
    }
    else
    {
        cout << "Fail to load locale..." << endl;
    }
    
    if(pCategoryElement != 0)
    {
        sCategory = pCategoryElement->getAllSubText();
    }
    else
    {
        cout << "Fail to load category..." << endl;
    }
    
    if(pLangElement != 0)
    {
        sTheme = pThemeElement->getAllSubText();
    }
    else
    {
        cout << "Fail to load theme..." << endl;
    }
    
    if(pLookElement != 0)
    {
        sLook = pLookElement->getAllSubText();
        iLook = sLook.getIntValue();
        switch(iLook)
        {
            case 1:
            {
                LookAndFeel::setDefaultLookAndFeel(& Look1);
                break;
            }
            case 2:
            {
                LookAndFeel::setDefaultLookAndFeel(& Look2);
                break;
            }
            case 3:
            {
                LookAndFeel::setDefaultLookAndFeel(& Look3);
                break;
            }
            default:
            {
                LookAndFeel::setDefaultLookAndFeel(& Look2);
            }
        }
    }
    else
    {
        cout << "Fail to load look-and-feel..." << endl;
    }
    
    cout << "Settings were loaded from the XML file..." << endl;
    
    delete(pRootElement);
    pRootElement = NULL;
    
    if(sLocale.isEmpty())
    {
        sLocale = "en";
    }
    
    cout << (String("Locale: ") += sLocale).toStdString() << endl;
    
    ToolbarFactory.pThemeComboBox->SetTheme(sTheme.getIntValue() - 1);
}
//---------------------------------------------------------------------
LocalisedStrings TCentralComponent::NewTranslator(String sLocale)
{
    String sTranslationData;
    if(sLocale == L"en")
    {
        sTranslationData = String(CharPointer_UTF8(BinaryData::en_lng));
    }
    else if(sLocale == L"ru")
    {
        sTranslationData = String(CharPointer_UTF8(BinaryData::ru_lng));
    }
    else
    {
        sLocale = L"en";
        sTranslationData = String(CharPointer_UTF8(BinaryData::en_lng));
    }
    
    LocalisedStrings sTr(sTranslationData, false);
    return sTr;
}
//---------------------------------------------------------------------
void TCentralComponent::LanguageChange(LocalisedStrings& sTr)
{
    s.set(0, sTr.translate(L"Game"));
    s.set(1, sTr.translate(L"Category"));
    s.set(2, sTr.translate(L"Theme"));
    s.set(3, sTr.translate(L"Language"));
    s.set(4, sTr.translate(L"New"));
    s.set(5, sTr.translate(L"Quit"));
    s.set(6, sTr.translate(L"About the programme"));
    s.set(7, sTr.translate(L"About JUCE"));
    s.set(8, sTr.translate(L"Saving"));
    s.set(9, sTr.translate(L"Settings were saved successfully."));
    s.set(10, sTr.translate(L"Yes"));
    s.set(11, sTr.translate(L"Error saving"));
    s.set(12, sTr.translate(L"Failed to save settings!"));
    s.set(13, sTr.translate(L"Accept"));
    s.set(14, sTr.translate(L"Clear Blue"));
    s.set(15, sTr.translate(L"Eagle"));
    s.set(16, sTr.translate(L"Mountain Village"));
    s.set(17, sTr.translate(L"Mountains"));
    s.set(18, sTr.translate(L"Night"));
    s.set(19, sTr.translate(L"Sunset"));
    s.set(20, sTr.translate(L"Tropical Island"));
    s.set(21, sTr.translate(L"Waterfall"));
    s.set(22, sTr.translate(L"Used Letters:"));
    s.set(23, sTr.translate(L"MISSES:"));
    s.set(24, sTr.translate(L"WORD:"));
    s.set(25, sTr.translate(L"Input a letter:"));
    s.set(26, sTr.translate(L"abcdefghijklmnopqrstuvwxyz"));
    s.set(27, sTr.translate(L"Enter"));
    s.set(28, sTr.translate(L"Guess a letter in the word"));
    s.set(29, sTr.translate(L"The input field is empty!"));
    s.set(30, sTr.translate(L"Enter a letter to check its presence in the secret word!"));
    s.set(31, sTr.translate(L"Attention!"));
    s.set(32, sTr.translate(L"You have already used this letter."));
    s.set(33, sTr.translate(L"It was hidden the word"));
    s.set(34, sTr.translate(L"Sorry, you just lost the game!"));
    s.set(35, sTr.translate(L"Congratulations!"));
    s.set(36, sTr.translate(L"You just won the game!"));
    s.set(37, sTr.translate(L"Animals"));
    s.set(38, sTr.translate(L"Clothing"));
    s.set(39, sTr.translate(L"Fruits"));
    s.set(40, sTr.translate(L"Objects"));
    s.set(41, sTr.translate(L"Professions"));
    s.set(42, sTr.translate(L"Transportation"));
    s.set(43, sTr.translate(L"Vegetables"));
    s.set(44, sTr.translate(L"About the programme"));
    
    cout << (String("Locale changed: ") += sLocale).toStdString() << endl;
    cout << "Interface strings were translated..." << endl;
    
    getMenuBarNames();
    menuItemsChanged();
    
    ToolbarFactory.LanguageChange(sTr);
    
    pUsedLettersEdit->clear();
    pUsedLettersEdit->setFont(Font(18.0000f, Font::bold));
    String sULText = s[22];
    sULText += String("\n");
    pUsedLettersEdit->insertTextAtCaret(sULText);
    pUsedLettersEdit->setFont(Font(15.0000f, Font::plain));
    
    pMissesCaptionLabel->setText(s[23], dontSendNotification);
    pWordCaptionLabel->setText(s[24], dontSendNotification);
    pLetterInputLabel->setText(s[25], dontSendNotification);
    pLetterInputEdit->setInputRestrictions(1, s[26]);
    pSubmitLetterButton->setButtonText(s[27]);
    pSubmitLetterButton->setTooltip(s[28]);
}
//---------------------------------------------------------------------
bool TCentralComponent::bLookAndFeelSelected(int iSelection)
{
    if(iSelection == iLook)
    {
        return true;
    }
    
    return false;
}
//---------------------------------------------------------------------
bool TCentralComponent::bLanguageSelected(String sSelectedLocale)
{
    return sLocale == sSelectedLocale;
}
//---------------------------------------------------------------------
inline void TCentralComponent::CreateToolbar()
{
    pToolbar = new Toolbar();
    addAndMakeVisible(pToolbar);
    pToolbar->setVertical(false);
    pToolbar->addDefaultItems(ToolbarFactory);
    pToolbar->addMouseListener(this, true);

    ToolbarFactory.pGameQuitButton->addListener(this);
    ToolbarFactory.pGameNewButton->addListener(this);
    ToolbarFactory.pSettingsSaveButton->addListener(this);
    ToolbarFactory.pHelpAboutButton->addListener(this);
    ToolbarFactory.pHelpAboutJuceButton->addListener(this);
    cout << "Toolbar was done!" << endl;
}
//---------------------------------------------------------------------
bool TCentralComponent::bSaveSettings()
{
    File SettingsFile(sPath);
    
    if(!SettingsFile.exists())
    {
        SettingsFile.create();
    }
    
    bool bResult;
    
    XmlElement* pRootElement = new XmlElement("settings");
    
    XmlElement* pLangElement = new XmlElement("lang");
    pLangElement->addTextElement(sLocale);
    pRootElement->addChildElement(pLangElement);
    
    XmlElement* pCategoryElement = new XmlElement("category");
    pCategoryElement->addTextElement(String(ToolbarFactory.pWLComboBox->iGetListNumber()));
    pRootElement->addChildElement(pCategoryElement);
    
    XmlElement* pThemeElement = new XmlElement("theme");
    pThemeElement->addTextElement(String(ToolbarFactory.pThemeComboBox->iGetImageNumber()));
    pRootElement->addChildElement(pThemeElement);
    
    XmlElement* pLookElement = new XmlElement("look");
    pLookElement->addTextElement(String(iLook));
    pRootElement->addChildElement(pLookElement);
    
    if(pRootElement->writeToFile(SettingsFile, String::empty))
    {
        AlertWindow::showMessageBox(AlertWindow::InfoIcon, s[8],
                                    s[9], s[10]);
        bResult = true;
    }
    else
    {
        AlertWindow::showMessageBox(AlertWindow::WarningIcon, s[11],
                                    s[12], s[13]);
                                    
        bResult = false;
    }
  
    delete(pRootElement);
    pRootElement = NULL;
    return bResult;
}
//---------------------------------------------------------------------
void TCentralComponent::CreateMissLabels()
{
    for(int i = 0; i < 10; i++)
    {
        MissLabel.add(new Label(String::empty, ""));
        MissLabel[i]->setFont(Font(15.0000f, Font::bold));
        MissLabel[i]->setJustificationType(Justification::centred);
        MissLabel[i]->setEditable(false, false, false);
        MissLabel[i]->setColour(Label::backgroundColourId, Colours::white);
        MissLabel[i]->setColour(Label::outlineColourId, Colours::blueviolet);
        addAndMakeVisible(MissLabel[i]);
    }
}
//---------------------------------------------------------------------
void TCentralComponent::ResizeMissLabels()
{
    int iX = 390;

    for(int i = 0; i < 10; i++)
    {
        MissLabel[i]->setBounds(iX, 60, 25, 25);

        iX += 35;
    }
}
//---------------------------------------------------------------------
void TCentralComponent::CreateWordLabels(int iLetters)
{
    for(int i = 0; i < iLetters; i++)
    {
        LetterLabel.add(new Label(String::empty, ""));
        LetterLabel[i]->setFont(Font(15.0000f, Font::bold));
        LetterLabel[i]->setJustificationType(Justification::centred);
        LetterLabel[i]->setEditable(false, false, false);
        LetterLabel[i]->setColour(Label::backgroundColourId, Colours::white);
        LetterLabel[i]->setColour(Label::outlineColourId, Colours::blueviolet);
        LetterLabel[i]->setColour(TextEditor::textColourId, Colours::black);
        addAndMakeVisible(LetterLabel[i]);
    }
}
//---------------------------------------------------------------------
void TCentralComponent::ResizeWordLabels(int iLabels)
{
    int iX = 280;

    for(int i = 0; i < iLabels; i++)
    {
        LetterLabel[i]->setBounds(iX, 235, 25, 25);

        iX += 35;
    }
}
//---------------------------------------------------------------------
void TCentralComponent::SetNewWord()
{
    srand((unsigned)time(NULL));
    int i = rand() % (ToolbarFactory.pWLComboBox->sWordsList.size() - 2);
    sWord = ToolbarFactory.pWLComboBox->sWordsList[i];
    iMisses = 0;
    iHits = 0;
    iLetters = sWord.length();
    
    if(sUsedLetters.size() != 0) sUsedLetters.clear();
    
    if(LetterLabel.size() != 0) 
    {
        for(int i = 0; i < LetterLabel.size(); i++)
        {
            removeChildComponent(LetterLabel[i]);
        }
        LetterLabel.clear();
    }
    
    CreateWordLabels(iLetters);
    
    HangmanImage = ImageCache::getFromMemory(BinaryData::_00_png, 
                                             BinaryData::_00_pngSize);
}
//---------------------------------------------------------------------
void TCentralComponent::SubmitLetter()
{
    if(pLetterInputEdit->getText().isEmpty())
    {
        AlertWindow::showMessageBox(AlertWindow::WarningIcon, s[29],
                                    s[30], s[13]);
        return;
    }
    
    String sLetter = pLetterInputEdit->getText().toLowerCase();

    if(sUsedLetters.size() != 0)
    {
        if(sUsedLetters.contains(StringRef(sLetter), true))
        {
            AlertWindow::showMessageBox(AlertWindow::WarningIcon, s[31],
                                    s[32], s[13]);
            pLetterInputEdit->clear();
            return;
        }
    }
    
    bool bYes = sWord.containsIgnoreCase(StringRef(sLetter));

    if(!bYes)
    {
        MissLabel[iMisses]->setText(sLetter, dontSendNotification);
        pLetterInputEdit->clear();
        iMisses++;

        DrawHangman(iMisses);

        if(iMisses > 9)
        {
            String sMessage = s[33];
            sMessage += String(" \"") += sWord += String("\"");
            AlertWindow::showMessageBox(AlertWindow::WarningIcon, s[34],
                                        sMessage,
                                        s[13]);
            pLetterInputEdit->setEnabled(false);
            pSubmitLetterButton->setEnabled(false);
        }
    }
    else
    {
        Array<int> iPositions = GetLetterPositions(sWord, sLetter);
        
        for(int i = 0; i < iPositions.size(); i++)
        {
            LetterLabel[iPositions[i]]->setText(sLetter, dontSendNotification);
            iHits++;
        }
        
        pLetterInputEdit->clear();
        
        if(iHits == sWord.length())
        {
            AlertWindow::showMessageBox(AlertWindow::InfoIcon, s[35],
                                    s[36], s[10]);
            pLetterInputEdit->setEnabled(false);
            pSubmitLetterButton->setEnabled(false);
        }
    }
    
    sUsedLetters.add(sLetter);
    pUsedLettersEdit->insertTextAtCaret(sLetter += String("\n"));
}
//---------------------------------------------------------------------
void TCentralComponent::DrawHangman(int iMisses)
{
    switch(iMisses)
    {
        case 1:
        {
            HangmanImage = ImageCache::getFromMemory(BinaryData::_01_png, BinaryData::_01_pngSize);
            repaint();
            break;
        }
        case 2:
        {
            HangmanImage = ImageCache::getFromMemory(BinaryData::_02_png, BinaryData::_02_pngSize);
            repaint();
            break;
        }
        case 3:
        {
            HangmanImage = ImageCache::getFromMemory(BinaryData::_03_png, BinaryData::_03_pngSize);
            repaint();
            break;
        }
        case 4:
        {
            HangmanImage = ImageCache::getFromMemory(BinaryData::_04_png, BinaryData::_04_pngSize);
            repaint();
            break;
        }
        case 5:
        {
            HangmanImage = ImageCache::getFromMemory(BinaryData::_05_png, BinaryData::_05_pngSize);
            repaint();
            break;
        }
        case 6:
        {
            HangmanImage = ImageCache::getFromMemory(BinaryData::_06_png, BinaryData::_06_pngSize);
            repaint();
            break;
        }
        case 7:
        {
            HangmanImage = ImageCache::getFromMemory(BinaryData::_07_png, BinaryData::_07_pngSize);
            repaint();
            break;
        }
        case 8:
        {
            HangmanImage = ImageCache::getFromMemory(BinaryData::_08_png, BinaryData::_08_pngSize);
            repaint();
            break;
        }
        case 9:
        {
            HangmanImage = ImageCache::getFromMemory(BinaryData::_09_png, BinaryData::_09_pngSize);
            repaint();
            break;
        }
        case 10:
        {
            HangmanImage = ImageCache::getFromMemory(BinaryData::_10_png, BinaryData::_10_pngSize);
            repaint();
            break;
        }
        default:
        {
            break;
        }
    }
}
//---------------------------------------------------------------------
Array<int> TCentralComponent::GetLetterPositions(String sWord, String sLetter)
{
    Array<int> iLetterPositions;
    
    for(int i = 0; i < sWord.length(); i++)
    {
        if(sWord.substring(i, i + 1) == sLetter)
        {
            iLetterPositions.add(i);
        }
    }
    
    return iLetterPositions;
}
//---------------------------------------------------------------------
void TCentralComponent::textEditorReturnKeyPressed(TextEditor&)
{
    SubmitLetter();
}
//---------------------------------------------------------------------
void TCentralComponent::ClearMissLabels()
{
    for(int i = 0; i < 10; i++)
    {
        MissLabel[i]->setText(String::empty, dontSendNotification);
    }
}
//---------------------------------------------------------------------
void TCentralComponent::NewGame()
{
    SetNewWord();
    ClearMissLabels();
    pUsedLettersEdit->setFont(Font(18.0000f, Font::bold));
    String sULText = s[22];
    sULText += String("\n");
    pUsedLettersEdit->setText(sULText);
    pUsedLettersEdit->setFont(Font(15.0000f, Font::plain));
    pLetterInputEdit->setEnabled(true);
    pSubmitLetterButton->setEnabled(true);
    resized();
    repaint();
}
//---------------------------------------------------------------------
void TCentralComponent::ShowAboutDialogue()
{
    DialogWindow::LaunchOptions DlgOptions;
    TAboutComponent* pAboutComponent = new TAboutComponent();
    LocalisedStrings sTr = NewTranslator(sLocale);
    pAboutComponent->LanguageChange(sTr);
    DlgOptions.content.setOwned(pAboutComponent);
    DlgOptions.content->setSize(400, 500);
    DlgOptions.dialogTitle = s[44];
    DlgOptions.dialogBackgroundColour = Colours::darkblue;
    DlgOptions.escapeKeyTriggersCloseButton = true;
    DlgOptions.useNativeTitleBar = false;
    DlgOptions.resizable = false;
    DialogWindow* pAboutDialogue = DlgOptions.launchAsync();
}
//---------------------------------------------------------------------
void TCentralComponent::ShowAboutJuceDialogue()
{
    DialogWindow::LaunchOptions DlgOptions;
    TAboutJuceComponent* pAboutJuceComponent = new TAboutJuceComponent();
    LocalisedStrings sTr = NewTranslator(sLocale);
    pAboutJuceComponent->LanguageChange(sTr);
    DlgOptions.content.setOwned(pAboutJuceComponent);
    DlgOptions.content->setSize(500, 400);
    DlgOptions.dialogTitle = s[7];
    DlgOptions.dialogBackgroundColour = Colours::darkblue;
    DlgOptions.escapeKeyTriggersCloseButton = true;
    DlgOptions.useNativeTitleBar = false;
    DlgOptions.resizable = false;
    DialogWindow* pAboutDialogue = DlgOptions.launchAsync();
}
//---------------------------------------------------------------------
