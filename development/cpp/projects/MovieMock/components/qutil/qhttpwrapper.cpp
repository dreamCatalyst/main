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


#include "qhttpwrapper.h"

#include <QApplication>
#include <QDebug>
#include <QNetworkReply>
#include <QNetworkRequest>
#include "qgexceptions.h"
#include "qthreadhelper.h"


QHttpWrapper::QHttpWrapper(QObject* parent) : QObject(parent)
{
	m_makingRequest = false;
	connect(&m_networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply*)) );
}

QString QHttpWrapper::get(const QString& url)
{
	if(m_makingRequest)
		throw QG::InvalidStateError("Still working on your first request!");
	
	m_makingRequest = true;
	m_response = "";
	
	qDebug() << "Getting data through QHttpWrapper. url='" << url << "'";
	QNetworkRequest request(url);
	m_networkManager.get(request);
	
	while(m_makingRequest) {
		QThreadHelper::sleep(100);
		qApp->processEvents();
	}
	
	qDebug() << "Returning from get()";
	return m_response;
}

bool QHttpWrapper::requestFinished(QNetworkReply* reply)
{
	qDebug("QHttpWrapper::requestFinished() reading response data");
	m_response = reply->readAll();
	m_makingRequest = false;
}

#include "qhttpwrapper.moc"
