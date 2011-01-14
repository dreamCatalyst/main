/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "imagesearchresultitem.h"


ImageSearchResultItem::ImageSearchResultItem(QVariantMap searchResultItemData)
{
	m_resultData = searchResultItemData;
}


int ImageSearchResultItem::width() const
{
	return m_resultData["width"].toInt();
}

int ImageSearchResultItem::height() const
{
	return m_resultData["height"].toInt();
}

QString ImageSearchResultItem::imageId() const
{
	return m_resultData["imageId"].toString();
}

int ImageSearchResultItem::tbWidth() const
{
	return m_resultData["tbWidth"].toInt();
}

int ImageSearchResultItem::tbHeight() const
{
	return m_resultData["tbHeight"].toInt();
}

QString ImageSearchResultItem::unescapedUrl() const
{
	return m_resultData["unescapedUrl"].toString();
}

QString ImageSearchResultItem::url() const
{
	return m_resultData["url"].toString();
}

QString ImageSearchResultItem::visibleUrl() const
{
	return m_resultData["visibleUrl"].toString();
}

QString ImageSearchResultItem::title() const
{
	return m_resultData["title"].toString();
}

QString ImageSearchResultItem::titleNoFormatting() const
{
	return m_resultData["titleNoFormatting"].toString();
}

QString ImageSearchResultItem::originalContextUrl() const
{
	return m_resultData["originalContextUrl"].toString();
}

QString ImageSearchResultItem::content() const
{
	return m_resultData["content"].toString();
}

QString ImageSearchResultItem::contentNoFormatting() const
{
	return m_resultData["contentNoFormatting"].toString();
}

QString ImageSearchResultItem::tbUrl() const
{
	return m_resultData["tbUrl"].toString();
}
