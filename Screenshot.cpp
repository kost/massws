#include "Screenshot.h"

Screenshot::Screenshot()
{
	sizex = 1024;
	sizey = 768;
	isfinished=0;
	myapp = NULL;
}

void Screenshot::takeshot(const QUrl &url) {
	page.mainFrame()->load(url);
	connect(&page, SIGNAL(loadFinished(bool)), this, SLOT(render()));
	connect(this, SIGNAL(finished()), this, SLOT(haveFinished()));
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

