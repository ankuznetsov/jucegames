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
#include "TWLComboBox.h"
//---------------------------------------------------------------------
TWLComboBox::TWLComboBox(const int iToolbarItemId) :
             ToolbarItemComponent(iToolbarItemId, "WL Toolbar Item", false),
             WLComboBox("WL Toolbar Combo Box")
{
    addAndMakeVisible(WLComboBox);

    WLComboBox.setEditableText(false);
    WLComboBox.addListener(this);
    
    for(int i = 1; i < 8; i++)
    {
        WLComboBox.addItem(String(i), i);
    }
    
    iWLNum = 1;
    sWordsList = sLists[(iWLNum - 1)];
}
//---------------------------------------------------------------------
TWLComboBox::~TWLComboBox()
{
}
//---------------------------------------------------------------------
bool TWLComboBox::getToolbarItemSizes(int, bool, int& iPreferredSize,
                                         int& iMinSize, int& iMaxSize)
{
    iPreferredSize = 100;
    iMinSize = 80;
    iMaxSize = 200;
    return true;
}
//---------------------------------------------------------------------
void TWLComboBox::paintButtonArea(Graphics&, int, int, bool, bool)
{
}
//---------------------------------------------------------------------
void TWLComboBox::contentAreaChanged(const Rectangle<int>& iNewArea)
{
    WLComboBox.setSize(iNewArea.getWidth() - 2,
                       jmin(iNewArea.getHeight() - 2, 22));

    WLComboBox.setCentrePosition(iNewArea.getCentreX(), iNewArea.getCentreY());
}
//---------------------------------------------------------------------
void TWLComboBox::comboBoxChanged(ComboBox* pComboBox)
{
    switch(pComboBox->getSelectedId())
    {
        case 1:
        {
            SetWordsList(0);
            break;
        }
        case 2:
        {
            SetWordsList(1);
            break;
        }
        case 3:
        {
            SetWordsList(2);
            break;
        }
        case 4:
        {
            SetWordsList(3);
            break;
        }
        case 5:
        {
            SetWordsList(4);
            break;
        }
        case 6:
        {
            SetWordsList(5);
            break;
        }
        case 7:
        {
            SetWordsList(6);
            break;
        }
        default:
        {
            sWordsList = sLists[0];
        }
    }
}
//---------------------------------------------------------------------
void TWLComboBox::SetWordsList(int iListNumber)
{
    sWordsList = sLists[iListNumber];
    iWLNum = iListNumber + 1;
    WLComboBox.setSelectedId(iWLNum);
}
//---------------------------------------------------------------------
int TWLComboBox::iGetListNumber()
{
    return WLComboBox.getSelectedId();
}
//---------------------------------------------------------------------
void TWLComboBox::LanguageChange(LocalisedStrings& sTr)
{
    WLComboBox.clear();
    WLComboBox.addItem(sTr.translate(L"Animals"), 1);
    WLComboBox.addItem(sTr.translate(L"Clothing"), 2);
    WLComboBox.addItem(sTr.translate(L"Fruits"), 3);
    WLComboBox.addItem(sTr.translate(L"Objects"), 4);
    WLComboBox.addItem(sTr.translate(L"Professions"), 5);
    WLComboBox.addItem(sTr.translate(L"Transportation"), 6);
    WLComboBox.addItem(sTr.translate(L"Vegetables"), 7);
    sWordsList = sLists[(iWLNum - 1)];
    WLComboBox.setSelectedId(iWLNum);
}
//---------------------------------------------------------------------
void TWLComboBox::LoadWL(String sLocale)
{
    sLists.clear();
    
    if(sLocale == "en")
    {
        String sCurrData = String(CharPointer_UTF8(BinaryData::animalsEN_txt));
        sLists.add(StringArray::fromLines(StringRef(sCurrData)));
        sCurrData = String(CharPointer_UTF8(BinaryData::clothingEN_txt));
        sLists.add(StringArray::fromLines(StringRef(sCurrData)));
        sCurrData = String(CharPointer_UTF8(BinaryData::fruitsEN_txt));
        sLists.add(StringArray::fromLines(StringRef(sCurrData)));
        sCurrData = String(CharPointer_UTF8(BinaryData::objectsEN_txt));
        sLists.add(StringArray::fromLines(StringRef(sCurrData)));
        sCurrData = String(CharPointer_UTF8(BinaryData::professionsEN_txt));
        sLists.add(StringArray::fromLines(StringRef(sCurrData)));
        sCurrData = String(CharPointer_UTF8(BinaryData::transportationEN_txt));
        sLists.add(StringArray::fromLines(StringRef(sCurrData)));
        sCurrData = String(CharPointer_UTF8(BinaryData::vegetablesEN_txt));
        sLists.add(StringArray::fromLines(StringRef(sCurrData)));
    }
    else if(sLocale == "ru")
    {
        String sCurrData = String(CharPointer_UTF8(BinaryData::animalsRU_txt));
        sLists.add(StringArray::fromLines(StringRef(sCurrData)));
        sCurrData = String(CharPointer_UTF8(BinaryData::clothingRU_txt));
        sLists.add(StringArray::fromLines(StringRef(sCurrData)));
        sCurrData = String(CharPointer_UTF8(BinaryData::fruitsRU_txt));
        sLists.add(StringArray::fromLines(StringRef(sCurrData)));
        sCurrData = String(CharPointer_UTF8(BinaryData::objectsRU_txt));
        sLists.add(StringArray::fromLines(StringRef(sCurrData)));
        sCurrData = String(CharPointer_UTF8(BinaryData::professionsRU_txt));
        sLists.add(StringArray::fromLines(StringRef(sCurrData)));
        sCurrData = String(CharPointer_UTF8(BinaryData::transportationRU_txt));
        sLists.add(StringArray::fromLines(StringRef(sCurrData)));
        sCurrData = String(CharPointer_UTF8(BinaryData::vegetablesRU_txt));
        sLists.add(StringArray::fromLines(StringRef(sCurrData)));
    }
    
    sWordsList = sLists[(iWLNum - 1)];
}
//---------------------------------------------------------------------
