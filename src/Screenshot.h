#include <QApplication>
#include <QWebPage>
#include <QWebFrame>
#include <QDebug>
#include <QUrl>
#include <QPainter>
#include <QString>

class Screenshot : public QObject
{
	Q_OBJECT

public:
	Screenshot();
	void takeshot(const QUrl &url);

	int isFinished();

	unsigned int sizex;
	unsigned int sizey;
	int isfinished;
	QString filename;
	QApplication *myapp;

signals:
	void finished();

private slots:
	void render();
	void haveFinished();

private:
	QWebPage page;
};



