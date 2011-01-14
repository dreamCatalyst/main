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


#include "imagesearchresult.h"

#include <QDebug>


ImageSearchResult::ImageSearchResult(const QVariantMap &searchResultData, ImageSearchQuerySettings* querySettings)
{
	m_resultData = searchResultData;
	m_query = querySettings;
	buildItemList();
	m_cursorData = m_resultData["cursor"].toMap();
}

ImageSearchResult::~ImageSearchResult()
{
	foreach(ImageSearchResultItem* i, m_itemList)
		delete i;
}


int ImageSearchResult::count() const
{
	return m_itemList.count();
}

ImageSearchResultItem* ImageSearchResult::get(const int idx) const
{
	return m_itemList.at(idx);
}

QList<ImageSearchResultItem*> ImageSearchResult::list() const
{
	return m_itemList; // returns a copy of the list (?)
}

int ImageSearchResult::currentPageIndex() const
{
	return m_resultData["currentPageIndex"].toInt();
}

long ImageSearchResult::estimatedResultCount() const
{
	return m_cursorData["estimatedResultCount"].toString().toLong();
}

QString ImageSearchResult::moreResultsUrl() const
{
	return m_cursorData["moreResultsUrl"].toString();
}

void ImageSearchResult::buildItemList()
{
	QVariantList resultList = m_resultData["results"].toList();
	foreach(QVariant result, resultList) {
		m_itemList << new ImageSearchResultItem(result.toMap());
	}
}

ImageSearchResult* ImageSearchResult::getNextSearchResult()
{
	qDebug() << "ImageSearchResult::getNextSearchResult() not yet implemented";
	return 0;
}


ImageSearchResultItem* ImageSearchResult::operator[](const int idx)
{
	return get(idx);
}
