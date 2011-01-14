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


#ifndef IMAGESEARCHRESULT_H
#define IMAGESEARCHRESULT_H

#include <QList>
#include <QVariant>
#include "imagesearchquerysettings.h"
#include "imagesearchresultitem.h"


class ImageSearchResult
{
public:
	ImageSearchResult(const QVariantMap &searchResultData, ImageSearchQuerySettings* querySettings);
	virtual ~ImageSearchResult();
	
	/**
	 * Fetches the next set of results for this search and returns the ImageSearchResult pointer to it.
	 * Think of this as an iterator like method.
	 */
	ImageSearchResult* getNextSearchResult();
	
	/**
	 * Returns the number of items contained within this result.
	 */
	int count() const;
	
	/**
	 * Returns the ImageSearchResultItem pointer at idx or 0 if the index is out of bounds.
	 * @sa operator[](ImageSearchResult &searchResult, const int idx);
	 */
	ImageSearchResultItem* get(const int idx) const;
	
	/**
	 * Returns a QList of pointers to all the ImageSearchResultItems for this search.
	 */
	QList<ImageSearchResultItem*> list() const;
	
	/**
	 * Returns the estimated result count provided by Google
	 */
	long estimatedResultCount() const;
	
	/**
	 * Returns the pageindex of this result provided by Google.
	 * 0-based
	 */
	int currentPageIndex() const;
	
	/**
	 * Returns the user-url for getting more results.
	 * 
	 * If you use this display it as a link that will either opens the systembrowser
	 * or a builtin browser. Don't use this url in QGoogleImageSearcher itself.
	 */
	QString moreResultsUrl() const;

	ImageSearchResultItem* operator[](const int idx);

private:
	QVariantMap m_resultData;
	QVariantMap m_cursorData;
	ImageSearchQuerySettings* m_query;
	QList<ImageSearchResultItem*> m_itemList;
	
	void buildItemList();
};


#endif // IMAGESEARCHRESULT_H
