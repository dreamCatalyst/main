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


#ifndef IMAGESEARCHQUERYSETTINGS_H
#define IMAGESEARCHQUERYSETTINGS_H

#include <QString>


class ImageSearchQuerySettings
{
public:

/**
 * ImageType
 * 
 * The different filetype that can be searched on.
 * See also GoogleImageSearcher::restrictImagetype()
 */
enum ImageType {
	AllImageTypes, JPG, PNG, GIF, BMP
};

/**
 * LicenseType
 * 
 * The different licences that can be searched on.
 * See also GoogleImageSearcher::restrictLicense()
 */
enum LicenseType {
	AllLicenses = 0,
	PublicDomain = 1,
	Attribute = 2,
	ShareALike = 4,
	NonCommercial = 8,
	NonDerived = 16
};

enum ColorizationType {
	AllColorizations, Colored, Grayed
};

enum ImageColor {
	AllColors, Black, Blue, Brown, Gray, Green, Orange, Pink, Purple, Red, Teal, White, Yellow
};

enum ImageSize {
	AllSizes = 0, Icon = 1, Small = 2 , Medium = 4, Large = 8, XLarge = 16, XXLarge = 32, Huge
};

enum SafetyType {
	Active, Moderate, Off
};

public:
    ImageSearchQuerySettings();
    virtual ~ImageSearchQuerySettings();
	
	QString getSearchUrl();
	int getStart() const;
	int getResultSize() const;

	/**
	 * Resets all settings back to their default.
	 * The searchQuery is cleared as well.
	 */
	void setDefaults();
	
	/**
	 * Sets the search query. Don't worry about escaping, we do.
	 */
	void setQuery(const QString &query);
	
	/**
	 * Set the start from which to fetch results.
	 * 
	 * default: 0
	 */
	void setStart(const int start);
	
	/**
	 * Restrict results to images of the specified type.
	 * 
	 * default: ImageType::AllImageTypes
	 */
	void setImageType(const ImageType t);
	
	/**
	 * Restrict results to images with the specified licence restriction.
	 * licenseRestriction can be any of the licenses combined bitwise:
	 *   setLicence( LicenseType::PublicDomain | LicenseType::NonCommercial );
	 * 
	 * default: LicenseType::AllLicenses
	 */
	void setLicence(const int licenseMask);
	
	/**
	 * Restrict results to a single site.
	 * If not set or set to an empty string this does nothing.
	 * 
	 * default: empty string
	 */
	void setSite(const QString &site);
	
	/**
	 * Restrict the color of the images searched.
	 * 
	 * default: ImageColor::AllColors
	 */
	void setImageColor(const ImageColor c);
	
	/**
	 * Restrict the colorization of the images returned. (Color or Gray)
	 * 
	 * default: ColorizationType::AllColorizations
	 */
	void setImageColorization(const ColorizationType t);
	
	/**
	 * Restrict the size of images returned.
	 * 
	 * The sizeSpecifier can be any of a number of combinations:
	 * - Icon
	 * - Small|Medium|Large|XLarge
	 * - XXLarge
	 * - Huge
	 * 
	 * default: ImageSize::AllSizes
	 */
	void setImageSize(const int sizeMask);
	
	/**
	 * Set the application-key which gets sent with each request to identify
	 * your application to Google.
	 * Go to http://code.google.com/apis/loader/signup.html
	 * to sign up and create your application key.
	 * 
	 * default: an empty string
	 */
	void setKey(const QString &appKey);
	
	/**
	 * Specify the number of results per request
	 * 0 > size < 9
	 * 
	 * default: 4
	 */
	void setResultSize(const int size);
	
	/**
	 * Specify a search safety level.
	 * 
	 * default: SafetyType::Active
	 */
	void setSafetyLevel(const SafetyType t);
	
	/**
	 * Specify the enduser ip address for which a request is made.
	 * 
	 * default: empty string
	 */
	void setUserIp(const QString &userIp);

protected:
	QString m_searchUrl;
	
	QString m_searchQuery, m_site, m_appKey, m_userIp;
	int m_start, m_licenseMask, m_imageSizeMask, m_resultSize;
	ImageType m_imageType;
	ImageColor m_imageColor;
	ColorizationType m_colorization;
	SafetyType m_safetyLevel;
	
private:
	void checkForSearchQuery();
	void buildSearchUrl();
	
	void addKeyValueToUrl(const QString &key, const QString &val);
	void addKeyValueToUrl(const QString &key, const int val);
	
	void addSearchQueryToUrl();
	void addRemainingSettingsToUrl();
	void addSiteToUrl();
	void addApplicationKeyToUrl();
	void addUserIpToUrl();
	void addStartToUrl();
	void addLicenseToUrl();
	void addImageSizeToUrl();
	void addResultSizeToUrl();
	void addImageTypeToUrl();
	void addImageColorToUrl();
	void addColorizationToUrl();
	void addSafetyToUrl();
	
	bool isSiteDefault() const;
	bool isApplicationKeyDefault() const;
	bool isUserIpDefault() const;
	bool isStartDefault() const;
	bool isLicenseDefault() const;
	bool isImageSizeDefault() const;
	bool isResultSizeDefault() const;
	bool isImageTypeDefault() const;
	bool isImageColorDefault() const;
	bool isColorizationDefault() const;
	bool isSafetyDefault() const;
};

#endif // IMAGESEARCHQUERYSETTINGS_H
