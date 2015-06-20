#include <QApplication>
#include <QWebPage>
#include <QtWebKit>
#include <QDebug>
#include <QUrl>

#include <QCommandLineParser>

#include <iostream>

#include <stdlib.h>

#include "Screenshot.h"

void escapeFN (QString &str) {
	str.replace(QString(":"),QString("_"));
	str.replace(QString("/"),QString("_"));
	str.replace(QString("&"),QString("_"));
	str.replace(QString("?"),QString("_"));
	str.replace(QString("*"),QString("_"));
	str.replace(QString("%"),QString("_"));
}

int main (int argc, char *argv[]) {
	QApplication::setApplicationName("massws");
	QApplication::setApplicationVersion("1.0");

	QCommandLineParser parser;
	parser.setApplicationDescription("MassWebShotter v1.0. Copyright (C) Kost. Distributed under GPL.");
	parser.addHelpOption();
	parser.addVersionOption();

	QCommandLineOption optionHelp(QStringList() << "h" << "help",
	    QCoreApplication::translate("main", "Show help."));
	parser.addOption(optionHelp);

	QCommandLineOption optionIgnoreSSL(QStringList() << "s" << "ignoressl",
	    QCoreApplication::translate("main", "Ignore SSL verification errors"));
	parser.addOption(optionIgnoreSSL);

	QCommandLineOption optionOutputFN(QStringList() << "o" << "output",
		QCoreApplication::translate("main", "Save output to <filename>."),
   		QCoreApplication::translate("main", "filename"));
	parser.addOption(optionOutputFN);

	QCommandLineOption optionWidth(QStringList() << "x" << "width",
		QCoreApplication::translate("main", "Make screenshot with <width>."),
		QCoreApplication::translate("main", "width"));
	parser.addOption(optionWidth);

	QCommandLineOption optionHeight(QStringList() << "y" << "height",
		QCoreApplication::translate("main", "Make screenshot with <height>."),
		QCoreApplication::translate("main", "heigth"));
	parser.addOption(optionHeight);

	parser.addPositionalArgument("url", "URL to take screenshot");

	qDebug() << "Starting...\n";

	QApplication app(argc,argv);

	parser.process(app);

	if (parser.isSet(optionHelp)) {
		parser.showHelp();
		exit(0);
	}

	const QStringList positionalArguments = parser.positionalArguments();
	if (positionalArguments.isEmpty()) {
		qWarning() << "You have to specify at least one URL";
		exit(1);
	}

	qDebug() << "Taking ss..\n";

	Screenshot ss;

	if (parser.isSet(optionIgnoreSSL)) {
		ss.ignoreSSL=1;
	}
	if (parser.isSet(optionWidth)) {
		ss.sizex=parser.value(optionWidth).toInt();
	}
	if (parser.isSet(optionHeight)) {
		ss.sizey=parser.value(optionHeight).toInt();
	}

	QString urltoss=positionalArguments.first();

	if (parser.isSet(optionOutputFN)) {
		ss.filename=parser.value(optionOutputFN);
	} else {
		QString genfilename=urltoss;
		escapeFN(genfilename);
		ss.filename=genfilename + ".png";
	}

	qWarning() << "Taking screenshot of: " << urltoss << " to " << ss.filename;

	ss.takeshot(QUrl(urltoss));

	ss.myapp = &app;

	qDebug() << "Pre-exec...\n";

	app.exec();

	qDebug() << "End...\n";
}

