#ifndef A11_12_EDWARDINIO18_GUI_H
#define A11_12_EDWARDINIO18_GUI_H

#include <QtWidgets>

#include <QListWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <qwidget.h>
#include "../Service/service.h"
#include "../Service/userServ.h"
#include <QDialog>
#include <QMainWindow>
#include <QWidget>
#include <QHBoxLayout>
#include <string>
#include <iostream>
#include "../CustomException/customException.h"
#include <QShortcut>
#include "../TableView/TableView.h"
#include <QHeaderView>
#include <QTableView>


class GUI : public QWidget {
Q_OBJECT

public:
	GUI(Service serv, UserServ userServ, Validator validator, QWidget *parent = nullptr);

private:
	Service serv;
	UserServ userServ;
	Validator validator;

	QListWidget *dogList;
	QListWidget *dogListUser;
	QListWidget *adoptionList;

	QLineEdit *nameEdit;
	QLineEdit *breedEdit;
	QLineEdit *ageEdit;
	QLineEdit *urlEdit;
	QLineEdit *isAdoptedEdit;
	QLineEdit *filterBreed;
	QLineEdit *filterAge;

	QPushButton *addDogButton;
	QPushButton *deleteDogButton;
	QPushButton *updateDogButton;
	QPushButton *filterDogButton;
	QPushButton *dogListButton;
	QPushButton *adoptButton;
	QPushButton *nextButton;
	QPushButton *userButton;
	QPushButton *adminButton;
	QPushButton *backButton;
	QPushButton *openFileButton;
	QPushButton *undoButton;
	QPushButton *redoButton;
	QPushButton *openTableButton;

	QShortcut *undoShort;
	QShortcut *redoShort;

	QRadioButton *HTMLFileButton;
	QRadioButton *CSVFileButton;

	QVBoxLayout *layout;

	QGroupBox *box;

	TableView *adoptedTableModel;

	bool selectedRepo;
	std::string filtString;
	int filtAge;
	std::string filtAgeString;
	int curIdx;

	void initGUI();

	void populate();

	void showAdmin();

	void showUser();

	void goBack();

	void addDog();

	void deleteDog();

	void updateDog();

	void populateFilter();

	void populateUser();

	void adoptDog();

	void populateAdopted();

	void nextDog();

	void undo();

	void redo();

	void connectSignals();

	void createTable();

	void populateUserTable();
};

#endif //A11_12_EDWARDINIO18_GUI_H