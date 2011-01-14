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


#include "imagesearchquerysettings.h"


#include <QDebug>
#include <QTextStream>
#include <QUrl>
#include "qgexceptions.h"


ImageSearchQuerySettings::ImageSearchQuerySettings()
{
	setDefaults();
}

ImageSearchQuerySettings::~ImageSearchQuerySettings()
{
	/* empty dtor */
}


QString ImageSearchQuerySettings::getSearchUrl()
{
	checkForSearchQuery();
	buildSearchUrl();
	return m_searchUrl;
}

int ImageSearchQuerySettings::getStart() const
{
	return m_start;
}

int ImageSearchQuerySettings::getResultSize() const
{
	return m_resultSize;
}

void ImageSearchQuerySettings::setDefaults()
{
	m_searchQuery = "";
	m_appKey = "";
	m_colorization = AllColorizations;
	m_imageColor = AllColors;
	m_imageSizeMask = AllSizes;
	m_imageType = AllImageTypes;
	m_licenseMask = AllLicenses;
	m_resultSize = 4;
	m_safetyLevel = Active;
	m_site = "";
	m_start = 0;
	m_userIp = "";
}



// Small sanity check method
void ImageSearchQuerySettings::checkForSearchQuery()
{
	if(m_searchQuery.isEmpty())
		throw QG::InvalidSettingsError("No search query provided!");
}


void ImageSearchQuerySettings::buildSearchUrl()
{
	m_searchUrl = "https://ajax.googleapis.com/ajax/services/search/images?v=1.0";
	addSearchQueryToUrl();
	addRemainingSettingsToUrl();
}

void ImageSearchQuerySettings::addRemainingSettingsToUrl()
{
	if(!isApplicationKeyDefault())
		addApplicationKeyToUrl();
	if(!isColorizationDefault())
		addColorizationToUrl();
	if(!isImageColorDefault())
		addImageColorToUrl();
	if(!isImageSizeDefault())
		addImageSizeToUrl();
	if(!isImageTypeDefault())
		addImageTypeToUrl();
	if(!isLicenseDefault())
		addLicenseToUrl();
	if(!isResultSizeDefault())
		addResultSizeToUrl();
	if(!isSafetyDefault())
		addSafetyToUrl();
	if(!isSiteDefault())
		addSiteToUrl();
	if(!isStartDefault())
		addStartToUrl();
	if(!isUserIpDefault())
		addUserIpToUrl();
}


/* ------------------------------- addXxxxToUrl methods */

void ImageSearchQuerySettings::addKeyValueToUrl(const QString& key, const QString& val)
{
	QString urlPart;
	QTextStream(&urlPart) << "&" << key << "=" << QUrl::toPercentEncoding( val );
	m_searchUrl.append(urlPart);
}

void ImageSearchQuerySettings::addKeyValueToUrl(const QString& key, const int val)
{
	QString urlPart;
	QTextStream(&urlPart) << "&" << key << "=" << val;
	m_searchUrl.append(urlPart);
}


void ImageSearchQuerySettings::addApplicationKeyToUrl()
{
	addKeyValueToUrl("key", m_appKey);
}

void ImageSearchQuerySettings::addColorizationToUrl()
{
	QString value("color");
	if(m_colorization == Grayed)
		value = "gray";
	addKeyValueToUrl("imgc", value);
}

void ImageSearchQuerySettings::addImageColorToUrl()
{
	QString colorString;
	switch(m_imageColor) {
		case Black:  colorString = "black"; break;
		case Blue:   colorString = "blue"; break;
		case Brown:  colorString = "brown"; break;
		case Gray:   colorString = "gray"; break;
		case Green:  colorString = "green"; break;
		case Orange: colorString = "orange"; break;
		case Pink:   colorString = "pink"; break;
		case Purple: colorString = "purple"; break;
		case Red:    colorString = "red"; break;
		case Teal:   colorString = "teal"; break;
		case White:  colorString = "white"; break;
		case Yellow: colorString = "yellow"; break;
	};
	addKeyValueToUrl("imgcolor", colorString);
}

void ImageSearchQuerySettings::addImageSizeToUrl()
{
	QString sizeString("Large");
	qDebug() << "TODO: implement ImageSizeToURL()";
	addKeyValueToUrl("imgsz", sizeString);
}

void ImageSearchQuerySettings::addImageTypeToUrl()
{
	QString imageTypeString;
	switch(m_imageType) {
		case JPG: imageTypeString = "jpg"; break;
		case PNG: imageTypeString = "png"; break;
		case GIF: imageTypeString = "gif"; break;
		case BMP: imageTypeString = "bmp"; break;
	};
	addKeyValueToUrl("as_filetype", imageTypeString);
}

void ImageSearchQuerySettings::addLicenseToUrl()
{
	QString licenseString("cc_publicdomain");
	qDebug() << "TODO implement add license url";
	addKeyValueToUrl("as_rights", licenseString);
}

void ImageSearchQuerySettings::addResultSizeToUrl()
{
	addKeyValueToUrl("rsz", m_resultSize);
}

void ImageSearchQuerySettings::addSafetyToUrl()
{
	QString safetyString;
	switch(m_safetyLevel) {
		case Active:   safetyString = "active"; break;   // this is the default so it should never get added
		case Moderate: safetyString = "moderate"; break;
		case Off:      safetyString = "off"; break;
	};
	addKeyValueToUrl("safe", safetyString);
}

void ImageSearchQuerySettings::addSearchQueryToUrl()
{
	addKeyValueToUrl("q", m_searchQuery);
}

void ImageSearchQuerySettings::addSiteToUrl()
{
	addKeyValueToUrl("as_sitesearch", m_site);
}

void ImageSearchQuerySettings::addStartToUrl()
{
	addKeyValueToUrl("start", m_start);
}

void ImageSearchQuerySettings::addUserIpToUrl()
{
	addKeyValueToUrl("userip", m_userIp);
}


/* ------------------------------- the isXXXDefault methods */

bool ImageSearchQuerySettings::isApplicationKeyDefault() const
{
	return m_appKey.isEmpty();
}

bool ImageSearchQuerySettings::isColorizationDefault() const
{
	return m_colorization == AllColorizations;
}

bool ImageSearchQuerySettings::isImageColorDefault() const
{
	return m_imageColor == AllColors;
}

bool ImageSearchQuerySettings::isImageSizeDefault() const
{
	return m_imageSizeMask == AllSizes;
}

bool ImageSearchQuerySettings::isImageTypeDefault() const
{
	return m_imageType == AllImageTypes;
}

bool ImageSearchQuerySettings::isLicenseDefault() const
{
	return m_licenseMask == AllLicenses;
}

bool ImageSearchQuerySettings::isResultSizeDefault() const
{
	return m_resultSize == 4;
}

bool ImageSearchQuerySettings::isSafetyDefault() const
{
	return m_safetyLevel == Active;
}

bool ImageSearchQuerySettings::isSiteDefault() const
{
	return m_site.isEmpty();
}

bool ImageSearchQuerySettings::isStartDefault() const
{
	return m_start == 0;
}

bool ImageSearchQuerySettings::isUserIpDefault() const
{
	return m_userIp.isEmpty();
}



/* ------------------------------- Boring public api implementation */


void ImageSearchQuerySettings::setImageType ( const ImageType t )
{
	m_imageType = t;
}

void ImageSearchQuerySettings::setImageColor ( const ImageColor c )
{
	m_imageColor = c;
}

void ImageSearchQuerySettings::setImageColorization ( const ColorizationType t )
{
	m_colorization = t;
}

void ImageSearchQuerySettings::setImageSize ( const int sizeMask )
{
	m_imageSizeMask = sizeMask;
}

void ImageSearchQuerySettings::setKey ( const QString& appKey )
{
	m_appKey = appKey;
}

void ImageSearchQuerySettings::setLicence ( const int licenseMask )
{
	m_licenseMask = licenseMask;
}

void ImageSearchQuerySettings::setQuery ( const QString& query )
{
	m_searchQuery = query;
}

void ImageSearchQuerySettings::setResultSize ( const int size )
{
	m_resultSize = size;
}

void ImageSearchQuerySettings::setSafetyLevel ( const SafetyType t )
{
	m_safetyLevel = t;
}

void ImageSearchQuerySettings::setSite ( const QString& site )
{
	m_site = site;
}

void ImageSearchQuerySettings::setStart ( const int start )
{
	m_start = start;
}

void ImageSearchQuerySettings::setUserIp ( const QString& userIp )
{
	m_userIp = userIp;
}
