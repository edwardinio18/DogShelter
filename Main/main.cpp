#include <QApplication>
#include "main.h"
#include "../GUI/GUI.h"

int main(int argc, char *argv[]) {
	Main mainStart;
	mainStart.start(argc, argv);
}

int Main::start(int argc, char *argv[]) {
	QApplication a(argc, argv);
	std::string file = "../dogs.txt";
	Repository repo{file};
	Validator validator;
	Service serv{repo, validator};
	UserServ userServ{repo};
	serv.initRepoServ();
	userServ.clearFile("../adopted.csv");
	userServ.clearFile("../adopted.html");
	auto *gui = new GUI{serv, userServ, validator};
	gui->setWindowState(Qt::WindowMaximized);
	gui->show();
	return QApplication::exec();
}