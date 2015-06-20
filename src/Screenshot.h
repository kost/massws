#include <QApplication>
#include <QWebPage>
#include <QWebFrame>
#include <QDebug>
#include <QUrl>
#include <QPainter>
#include <QString>
#include <QSslError>
#include <QNetworkReply>

class Screenshot : public QObject
{
	Q_OBJECT

public:
	Screenshot();
	void takeshot(const QUrl &url);

	int isFinished();

	unsigned int sizex;
	unsigned int sizey;
	int ignoreSSL;
	int isfinished;
	QString filename;
	QApplication *myapp;

signals:
	void finished();

private slots:
	void render();
	void haveFinished();
	void handleSslErrors(QNetworkReply* reply, const QList<QSslError> &errors);

private:
	QWebPage page;
};



