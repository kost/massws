#include "Screenshot.h"

Screenshot::Screenshot()
{
	sizex = 1024;
	sizey = 768;
	isfinished=0;
	myapp = NULL;
	ignoreSSL=0;
}

void Screenshot::takeshot(const QUrl &url) {
	page.mainFrame()->load(url);
	connect(&page, SIGNAL(loadFinished(bool)), this, SLOT(render()));
	connect(this, SIGNAL(finished()), this, SLOT(haveFinished()));
	// for handling SSL errors
	connect(page.networkAccessManager(),SIGNAL(sslErrors(QNetworkReply*, const QList<QSslError> & )),
		this, SLOT(handleSslErrors(QNetworkReply*, const QList<QSslError> & )));
}

void Screenshot::handleSslErrors(QNetworkReply* reply, const QList<QSslError> &errors) {
	qDebug() << "handleSslErrors: ";
	foreach (QSslError e, errors) {
		qDebug() << "ssl error: " << e;
	}
	if (ignoreSSL) {
		qWarning() << "SSL/TLS verification error: Ignoring";
		reply->ignoreSslErrors();
	} else {
		qCritical() << "SSL/TLS verification error: Quitting";
	}
}

void Screenshot::haveFinished() {
	qDebug() << "Finished!!!\n";		
	isfinished=1;
	if (myapp!=NULL) myapp->exit(0);
}

int Screenshot::isFinished() {
	qDebug() << "Are we finished? " << isfinished << "\n";		
	return (isfinished);
}

void Screenshot::render()
{
	page.setViewportSize(QSize(sizex,sizey));
	QImage image(page.viewportSize(), QImage::Format_ARGB32);
	QPainter painter(&image);

	page.mainFrame()->render(&painter);
	painter.end();

	QImage shot = image.scaled(sizex, sizey);

	qDebug() << "Calling to save: " << sizex << "x" << sizey;

	shot.save(filename);

	qDebug() << "Calling to save: finished\n";

	emit finished();
}

