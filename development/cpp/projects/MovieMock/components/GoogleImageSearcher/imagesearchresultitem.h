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


#ifndef IMAGESEARCHRESULTITEM_H
#define IMAGESEARCHRESULTITEM_H

#include <QObject>
#include <QVariant>
#include <QString>


class ImageSearchResultItem : public QObject
{

public:
	ImageSearchResultItem(QVariantMap searchResultItemData);
	
	int width() const;
	int height() const;
	QString imageId() const;
	int tbWidth() const;
	int tbHeight() const;
	QString unescapedUrl() const;
	QString url() const;
	QString visibleUrl() const;
	QString title() const;
	QString titleNoFormatting() const;
	QString originalContextUrl() const;
	QString content() const;
	QString contentNoFormatting() const;
	QString tbUrl() const;
protected:
	QVariantMap m_resultData;
};

#endif // IMAGESEARCHRESULTITEM_H
