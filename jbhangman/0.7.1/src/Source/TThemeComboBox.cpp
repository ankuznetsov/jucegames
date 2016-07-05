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
#include "TThemeComboBox.h"
//---------------------------------------------------------------------
TThemeComboBox::TThemeComboBox(const int iToolbarItemId) :
                ToolbarItemComponent(iToolbarItemId, "Theme Toolbar Item", false),
                ThemeComboBox("Theme Toolbar Combo Box")
{
    addAndMakeVisible(ThemeComboBox);
    
    for(int i = 1; i < 9; i++)
    {
        ThemeComboBox.addItem(String(i), i);
    }

    Images.add(ImageCache::getFromMemory(BinaryData::blue_png,
                                         BinaryData::blue_pngSize));
    Images.add(ImageCache::getFromMemory(BinaryData::eagle_jpg,
                                         BinaryData::eagle_jpgSize));
    Images.add(ImageCache::getFromMemory(BinaryData::mountain_village_jpg,
                                         BinaryData::mountain_village_jpgSize));
    Images.add(ImageCache::getFromMemory(BinaryData::mountains_jpg,
                                         BinaryData::mountains_jpgSize));
    Images.add(ImageCache::getFromMemory(BinaryData::night_jpg,
                                         BinaryData::night_jpgSize));
    Images.add(ImageCache::getFromMemory(BinaryData::sunset_jpg,
                                         BinaryData::sunset_jpgSize));
    Images.add(ImageCache::getFromMemory(BinaryData::island_jpeg,
                                         BinaryData::island_jpegSize));
    Images.add(ImageCache::getFromMemory(BinaryData::waterfall_jpg,
                                         BinaryData::waterfall_jpgSize));
    
    iImageNumber = 6;
    ThemeComboBox.setSelectedId(iImageNumber);
    Background_Image = ImageCache::getFromMemory(BinaryData::island_jpeg,
                                                 BinaryData::island_jpegSize);
    ThemeComboBox.setEditableText(false);
    ThemeComboBox.addListener(this);
}
//---------------------------------------------------------------------
TThemeComboBox::~TThemeComboBox()
{
}
//---------------------------------------------------------------------
bool TThemeComboBox::getToolbarItemSizes(int, bool, int& iPreferredSize,
                                         int& iMinSize, int& iMaxSize)
{
    iPreferredSize = 100;
    iMinSize = 80;
    iMaxSize = 200;
    return true;
}
//---------------------------------------------------------------------
void TThemeComboBox::paintButtonArea(Graphics&, int, int, bool, bool)
{
}
//---------------------------------------------------------------------
void TThemeComboBox::contentAreaChanged(const Rectangle<int>& iNewArea)
{
    ThemeComboBox.setSize(iNewArea.getWidth() - 2,
                            jmin(iNewArea.getHeight() - 2, 22));

    ThemeComboBox.setCentrePosition(iNewArea.getCentreX(), iNewArea.getCentreY());
}
//---------------------------------------------------------------------
void TThemeComboBox::SetTheme(int iImageNumber)
{
    this->iImageNumber = iImageNumber;
    Background_Image = Images[iImageNumber];
    ThemeComboBox.setSelectedItemIndex(iImageNumber);
    getParentComponent()->getParentComponent()->repaint();
}
//---------------------------------------------------------------------
void TThemeComboBox::comboBoxChanged(ComboBox* pComboBox)
{
    switch(pComboBox->getSelectedId())
    {
        case 1:
        {
            SetTheme(0);
            break;
        }
        case 2:
        {
            SetTheme(1);
            break;
        }
        case 3:
        {
            SetTheme(2);
            break;
        }
        case 4:
        {
            SetTheme(3);
            break;
        }
        case 5:
        {
            SetTheme(4);
            break;
        }
        case 6:
        {
            SetTheme(5);
            break;
        }
        case 7:
        {
            SetTheme(6);
            break;
        }
        case 8:
        {
            SetTheme(7);
            break;
        }
        default:
        {
            SetTheme(5);
        }

    }
}
//---------------------------------------------------------------------
int TThemeComboBox::iGetImageNumber()
{
    return ThemeComboBox.getSelectedId();
}
//---------------------------------------------------------------------
void TThemeComboBox::LanguageChange(LocalisedStrings& sTr)
{
    ThemeComboBox.clear();
    ThemeComboBox.addItem(sTr.translate(L"Clear Blue"), 1);
    ThemeComboBox.addItem(sTr.translate(L"Eagle"), 2);
    ThemeComboBox.addItem(sTr.translate(L"Mountain Village"), 3);
    ThemeComboBox.addItem(sTr.translate(L"Mountains"), 4);
    ThemeComboBox.addItem(sTr.translate(L"Night"), 5);
    ThemeComboBox.addItem(sTr.translate(L"Sunset"), 6);
    ThemeComboBox.addItem(sTr.translate(L"Tropical Island"), 7);
    ThemeComboBox.addItem(sTr.translate(L"Waterfall"), 8);
    
    SetTheme(iImageNumber);
}
//---------------------------------------------------------------------
