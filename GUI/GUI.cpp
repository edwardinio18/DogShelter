#include "GUI.h"

GUI::GUI(Service serv, UserServ userServ, Validator validator, QWidget *parent) : serv{serv}, userServ{userServ},
																				  validator{validator} {
	this->curIdx = 0;
	this->undoShort = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_Z), this);
	this->redoShort = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_Y), this);

	this->initGUI();
	this->connectSignals();
}

void GUI::initGUI() {
	this->setWindowTitle("Dinder!");

	this->layout = new QVBoxLayout;

	this->box = new QGroupBox(tr("Welcome to Dinder!"));
	this->box->setStyleSheet("font-size: 25px; color: grey; text-decoration: underline; font-style: italic;");

	auto *boxLayout = new QHBoxLayout;
	auto *gridLayout = new QGridLayout;

	auto *buttonsTitle = new QLabel("Select a mode");
	buttonsTitle->setStyleSheet("text-decoration: none; font-style: normal;");

	this->userButton = new QPushButton("User");
	this->adminButton = new QPushButton("Admin");

	this->userButton->setStyleSheet(
			"font-size: 30px; color: black; padding: 15px; text-decoration: none; font-style: normal; border: 2px solid black; border-radius: 10px; background-color: white;");
	this->adminButton->setStyleSheet(
			"font-size: 30px; color: black; padding: 15px; text-decoration: none; font-style: normal; border: 2px solid black; border-radius: 10px; background-color: white;");

	gridLayout->addWidget(buttonsTitle, 0, 0, 1, 2, Qt::AlignCenter);

	gridLayout->addWidget(this->userButton, 1, 0);
	gridLayout->addWidget(this->adminButton, 1, 1);

	boxLayout->addLayout(gridLayout);

	this->box->setLayout(boxLayout);

	this->layout->addWidget(this->box);

	this->setLayout(this->layout);

	QObject::connect(this->userButton, &QPushButton::clicked, this, &GUI::showUser);
	QObject::connect(this->adminButton, &QPushButton::clicked, this, &GUI::showAdmin);
}

void GUI::showAdmin() {
	this->serv.emptyUndoRedo();

	delete this->box;
	delete this->layout;

	this->dogList = new QListWidget;
	this->dogList->setStyleSheet(
			"font-size: 18px; text-decoration: none; font-style: normal; border: 2px solid black; border-radius: 3px; background-color: white;");
	this->populate();

	this->layout = new QVBoxLayout;
	this->box = new QGroupBox(tr("Admin Mode"));
	this->box->setStyleSheet("font-size: 25px; color: grey; text-decoration: underline; font-style: italic;");

	auto *boxLayout = new QHBoxLayout;

	auto *boxLayoutLeft = new QHBoxLayout;
	auto *gridLayoutLeft = new QGridLayout;

	auto *nameLabel = new QLabel("Name:");
	nameLabel->setStyleSheet("text-decoration: none; font-style: normal; font-size: 20px;");
	this->nameEdit = new QLineEdit;
	this->nameEdit->setStyleSheet(
			"text-decoration: none; font-style: normal; font-size: 20px; border: 2px solid black; background-color: white; border-radius: 5px; color: black;");

	auto *breedLabel = new QLabel("Breed:");
	breedLabel->setStyleSheet("text-decoration: none; font-style: normal; font-size: 20px;");
	this->breedEdit = new QLineEdit;
	this->breedEdit->setStyleSheet(
			"text-decoration: none; font-style: normal; font-size: 20px; border: 2px solid black; background-color: white; border-radius: 5px; color: black;");

	auto *ageLabel = new QLabel("Age:");
	ageLabel->setStyleSheet("text-decoration: none; font-style: normal; font-size: 20px;");
	this->ageEdit = new QLineEdit;
	this->ageEdit->setStyleSheet(
			"text-decoration: none; font-style: normal; font-size: 20px; border: 2px solid black; background-color: white; border-radius: 5px; color: black;");

	auto *urlLabel = new QLabel("URL:");
	urlLabel->setStyleSheet("text-decoration: none; font-style: normal; font-size: 20px;");
	this->urlEdit = new QLineEdit;
	this->urlEdit->setStyleSheet(
			"text-decoration: none; font-style: normal; font-size: 20px; border: 2px solid black; background-color: white; border-radius: 5px; color: black;");

	auto *adoptedLabel = new QLabel("Adopted:");
	adoptedLabel->setStyleSheet("text-decoration: none; font-style: normal; font-size: 20px;");
	this->isAdoptedEdit = new QLineEdit;
	this->isAdoptedEdit->setStyleSheet(
			"text-decoration: none; font-style: normal; font-size: 20px; border: 2px solid black; background-color: white; border-radius: 5px; color: black;");

	gridLayoutLeft->addWidget(nameLabel, 0, 0);
	gridLayoutLeft->addWidget(this->nameEdit, 0, 1);

	gridLayoutLeft->addWidget(breedLabel, 1, 0);
	gridLayoutLeft->addWidget(this->breedEdit, 1, 1);

	gridLayoutLeft->addWidget(ageLabel, 2, 0);
	gridLayoutLeft->addWidget(this->ageEdit, 2, 1);

	gridLayoutLeft->addWidget(urlLabel, 3, 0);
	gridLayoutLeft->addWidget(this->urlEdit, 3, 1);

	gridLayoutLeft->addWidget(adoptedLabel, 4, 0);
	gridLayoutLeft->addWidget(this->isAdoptedEdit, 4, 1);

	this->addDogButton = new QPushButton("Add");
	this->addDogButton->setStyleSheet(
			"font-size: 30px; color: black; padding: 15px; text-decoration: none; font-style: normal; border: 2px solid black; border-radius: 10px; background-color: white;");

	this->deleteDogButton = new QPushButton("Delete");
	this->deleteDogButton->setStyleSheet(
			"font-size: 30px; color: black; padding: 15px; text-decoration: none; font-style: normal; border: 2px solid black; border-radius: 10px; background-color: white;");

	this->updateDogButton = new QPushButton("Update");
	this->updateDogButton->setStyleSheet(
			"font-size: 30px; color: black; padding: 15px; text-decoration: none; font-style: normal; border: 2px solid black; border-radius: 10px; background-color: white;");

	gridLayoutLeft->addWidget(this->addDogButton, 5, 0, 1, 3);
	gridLayoutLeft->addWidget(this->deleteDogButton, 6, 0, 1, 3);
	gridLayoutLeft->addWidget(this->updateDogButton, 7, 0, 1, 3);

	this->backButton = new QPushButton("Back");
	this->backButton->setStyleSheet(
			"font-size: 30px; color: black; padding: 15px; text-decoration: none; font-style: normal; border: 2px solid black; border-radius: 10px; background-color: white;");

	gridLayoutLeft->addWidget(this->backButton, 8, 0, 1, 3);

	this->undoButton = new QPushButton("Undo");
	this->undoButton->setStyleSheet(
			"font-size: 30px; color: black; padding: 15px; text-decoration: none; font-style: normal; border: 2px solid black; border-radius: 10px; background-color: white;");

	gridLayoutLeft->addWidget(this->undoButton, 9, 0);

	this->redoButton = new QPushButton("Redo");
	this->redoButton->setStyleSheet(
			"font-size: 30px; color: black; padding: 15px; text-decoration: none; font-style: normal; border: 2px solid black; border-radius: 10px; background-color: white;");

	gridLayoutLeft->addWidget(this->redoButton, 9, 2);

	boxLayoutLeft->addLayout(gridLayoutLeft);
	boxLayout->addLayout(boxLayoutLeft);

	auto *boxLayoutRight = new QHBoxLayout;
	auto *gridLayoutRight = new QGridLayout;

	auto *dogListLabel = new QLabel("Dog list");
	dogListLabel->setStyleSheet("font-size: 25px; color: grey;");

	gridLayoutRight->addWidget(dogListLabel);

	gridLayoutRight->addWidget(this->dogList);

	boxLayoutRight->addLayout(gridLayoutRight);

	boxLayout->addLayout(boxLayoutRight);

	this->box->setLayout(boxLayout);

	this->layout->addWidget(this->box);

	this->layout->addLayout(boxLayout);

	this->setLayout(this->layout);

	QObject::connect(this->dogList, &QListWidget::itemSelectionChanged, [this]() {
		QModelIndexList selectedIdxs = this->dogList->selectionModel()->selectedIndexes();
		if (selectedIdxs.empty()) {
			return;
		}
		int idx = selectedIdxs.at(0).row();
		if (idx < 0) {
			return;
		}
		Dog dog = this->serv.listDogsServ()[idx];
		this->nameEdit->setText(QString::fromStdString(dog.getName()));
		this->breedEdit->setText(QString::fromStdString(dog.getBreed()));
		this->ageEdit->setText(QString::fromStdString(std::to_string(dog.getAge())));
		this->urlEdit->setText(QString::fromStdString(dog.getPhotograph()));
		if (!dog.getIsAdopted()) {
			this->isAdoptedEdit->setText("No");
		} else {
			this->isAdoptedEdit->setText("Yes");
		}
	});

	QObject::connect(this->addDogButton, &QPushButton::clicked, this, &GUI::addDog);
	QObject::connect(this->deleteDogButton, &QPushButton::clicked, this, &GUI::deleteDog);
	QObject::connect(this->updateDogButton, &QPushButton::clicked, this, &GUI::updateDog);
	QObject::connect(this->backButton, &QPushButton::clicked, this, &GUI::goBack);

	QObject::connect(this->undoButton, &QPushButton::clicked, this, &GUI::undo);
	QObject::connect(this->redoButton, &QPushButton::clicked, this, &GUI::redo);
}

void GUI::showUser() {
	this->adoptedTableModel = new TableView{this->userServ};

	delete this->box;
	delete this->layout;

	this->dogListUser = new QListWidget;
	QString linearGradient = QString(
			"qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(255, 255, 255, 1), stop:1 rgba(228, 233, 237, 1));");

	this->dogListUser->setStyleSheet(QString("background-color: %1").arg(linearGradient));

	this->adoptionList = new QListWidget;
	this->adoptionList->setStyleSheet(
			"font-size: 18px; text-decoration: none; font-style: normal; border: 2px solid black; border-radius: 3px; background-color: white;");

	this->layout = new QVBoxLayout;
	this->box = new QGroupBox(tr("User Mode"));
	this->box->setStyleSheet("font-size: 25px; color: grey; text-decoration: underline; font-style: italic;");

	auto *boxLayout = new QHBoxLayout;

	auto *boxLayoutLeft = new QHBoxLayout;
	auto *gridLayoutLeft = new QGridLayout;

	this->HTMLFileButton = new QRadioButton("HTML");
	this->HTMLFileButton->setStyleSheet("font-size: 20px; text-decoration: none; font-style: normal; color: black;");
	this->CSVFileButton = new QRadioButton("CSV");
	this->CSVFileButton->setStyleSheet("font-size: 20px; text-decoration: none; font-style: normal; color: black;");

	gridLayoutLeft->addWidget(this->HTMLFileButton, 0, 0);
	gridLayoutLeft->addWidget(this->CSVFileButton, 0, 1);

	this->openFileButton = new QPushButton("Open file");
	this->openFileButton->setStyleSheet(
			"font-size: 30px; color: black; padding: 15px; text-decoration: none; font-style: normal; border: 2px solid black; border-radius: 10px; background-color: white;");

	this->openTableButton = new QPushButton("Open table");
	this->openTableButton->setStyleSheet(
			"font-size: 30px; color: black; padding: 15px; text-decoration: none; font-style: normal; border: 2px solid black; border-radius: 10px; background-color: white;");

	this->dogListButton = new QPushButton("Populate list");
	this->dogListButton->setStyleSheet(
			"font-size: 30px; color: black; padding: 15px; text-decoration: none; font-style: normal; border: 2px solid black; border-radius: 10px; background-color: white;");

	gridLayoutLeft->addWidget(this->openFileButton, 1, 0);

	gridLayoutLeft->addWidget(this->openTableButton, 1, 1);

	gridLayoutLeft->addWidget(this->dogListButton, 2, 0, 1, 2);

	auto *nameLabel = new QLabel("Name:");
	nameLabel->setStyleSheet("text-decoration: none; font-style: normal; font-size: 20px;");
	this->nameEdit = new QLineEdit;
	this->nameEdit->setDisabled(true);
	nameEdit->setStyleSheet(
			"text-decoration: none; font-style: normal; font-size: 20px; border: 2px solid black; background-color: white; border-radius: 5px; color: black;");

	auto *breedLabel = new QLabel("Breed:");
	breedLabel->setStyleSheet("text-decoration: none; font-style: normal; font-size: 20px;");
	this->breedEdit = new QLineEdit;
	this->breedEdit->setDisabled(true);
	breedEdit->setStyleSheet(
			"text-decoration: none; font-style: normal; font-size: 20px; border: 2px solid black; background-color: white; border-radius: 5px; color: black;");

	auto *ageLabel = new QLabel("Age:");
	ageLabel->setStyleSheet("text-decoration: none; font-style: normal; font-size: 20px;");
	this->ageEdit = new QLineEdit;
	this->ageEdit->setDisabled(true);
	ageEdit->setStyleSheet(
			"text-decoration: none; font-style: normal; font-size: 20px; border: 2px solid black; background-color: white; border-radius: 5px; color: black;");

	auto *urlLabel = new QLabel("URL:");
	urlLabel->setStyleSheet("text-decoration: none; font-style: normal; font-size: 20px;");
	this->urlEdit = new QLineEdit;
	this->urlEdit->setDisabled(true);
	urlEdit->setStyleSheet(
			"text-decoration: none; font-style: normal; font-size: 20px; border: 2px solid black; background-color: white; border-radius: 5px; color: black;");

	auto *adoptedLabel = new QLabel("Adopted:");
	adoptedLabel->setStyleSheet("text-decoration: none; font-style: normal; font-size: 20px;");
	this->isAdoptedEdit = new QLineEdit;
	this->isAdoptedEdit->setDisabled(true);
	this->isAdoptedEdit->setStyleSheet(
			"text-decoration: none; font-style: normal; font-size: 20px; border: 2px solid black; background-color: white; border-radius: 5px; color: black;");

	gridLayoutLeft->addWidget(nameLabel, 3, 0);
	gridLayoutLeft->addWidget(this->nameEdit, 3, 1);

	gridLayoutLeft->addWidget(breedLabel, 4, 0);
	gridLayoutLeft->addWidget(this->breedEdit, 4, 1);

	gridLayoutLeft->addWidget(ageLabel, 5, 0);
	gridLayoutLeft->addWidget(this->ageEdit, 5, 1);

	gridLayoutLeft->addWidget(urlLabel, 6, 0);
	gridLayoutLeft->addWidget(this->urlEdit, 6, 1);

	gridLayoutLeft->addWidget(adoptedLabel, 7, 0);
	gridLayoutLeft->addWidget(this->isAdoptedEdit, 7, 1);

	this->adoptButton = new QPushButton("Adopt dog");
	this->adoptButton->setStyleSheet(
			"font-size: 30px; color: black; padding: 15px; text-decoration: none; font-style: normal; border: 2px solid black; border-radius: 10px; background-color: white;");

	auto *filterBreedLabel = new QLabel("Filter breed:");
	filterBreedLabel->setStyleSheet("text-decoration: none; font-style: normal; font-size: 20px;");
	this->filterBreed = new QLineEdit;
	this->filterBreed->setStyleSheet(
			"text-decoration: none; font-style: normal; font-size: 20px; border: 2px solid black; background-color: white; border-radius: 5px; color: black;");

	auto *filterAgeLabel = new QLabel("Filter size < n:");
	filterAgeLabel->setStyleSheet("text-decoration: none; font-style: normal; font-size: 20px;");
	this->filterAge = new QLineEdit;
	this->filterAge->setStyleSheet(
			"text-decoration: none; font-style: normal; font-size: 20px; border: 2px solid black; background-color: white; border-radius: 5px; color: black;");

	this->filterDogButton = new QPushButton("Filter");
	this->filterDogButton->setStyleSheet(
			"font-size: 30px; color: black; padding: 15px; text-decoration: none; font-style: normal; border: 2px solid black; border-radius: 10px; background-color: white;");

	this->nextButton = new QPushButton("Next");
	this->nextButton->setStyleSheet(
			"font-size: 30px; color: black; padding: 15px; text-decoration: none; font-style: normal; border: 2px solid black; border-radius: 10px; background-color: white;");

	this->backButton = new QPushButton("Back");
	this->backButton->setStyleSheet(
			"font-size: 30px; color: black; padding: 15px; text-decoration: none; font-style: normal; border: 2px solid black; border-radius: 10px; background-color: white;");

	gridLayoutLeft->addWidget(this->adoptButton, 8, 0, 1, 2);

	gridLayoutLeft->addWidget(filterBreedLabel, 9, 0);
	gridLayoutLeft->addWidget(this->filterBreed, 9, 1);

	gridLayoutLeft->addWidget(filterAgeLabel, 10, 0);
	gridLayoutLeft->addWidget(this->filterAge, 10, 1);

	gridLayoutLeft->addWidget(this->filterDogButton, 11, 0, 1, 2);

	gridLayoutLeft->addWidget(this->nextButton, 12, 0, 1, 2);

	gridLayoutLeft->addWidget(this->backButton, 13, 0, 1, 2);

	boxLayoutLeft->addLayout(gridLayoutLeft);

	boxLayout->addLayout(boxLayoutLeft);

	auto *boxLayoutRight = new QHBoxLayout;
	auto *gridLayoutRight = new QGridLayout;

	auto *dogListLabel = new QLabel("Dog list");
	dogListLabel->setStyleSheet("font-size: 25px; color: grey;");

	gridLayoutRight->addWidget(dogListLabel);

	gridLayoutRight->addWidget(this->dogListUser);

	auto *adoptedListLabel = new QLabel("Adoption list");
	adoptedListLabel->setStyleSheet("font-size: 25px; color: grey;");

	gridLayoutRight->addWidget(adoptedListLabel);

	gridLayoutRight->addWidget(this->adoptionList);

	boxLayoutRight->addLayout(gridLayoutRight);

	boxLayout->addLayout(boxLayoutRight);

	this->box->setLayout(boxLayout);

	this->layout->addWidget(this->box);

	this->layout->addLayout(boxLayout);

	this->setLayout(this->layout);

	QObject::connect(this->dogListUser, &QListWidget::itemClicked, [this]() {
		std::string name = this->dogListUser->selectedItems().at(0)->text().toStdString();
		std::string breed = this->serv.trim(this->serv.tokenizeServ(this->serv.tokenizeServ(name, '>')[1], ';')[0]);
		name = this->serv.trim(this->serv.tokenizeServ(this->serv.tokenizeServ(name, '>')[2], ';')[0]);
		int index = this->serv.checkDogExiNameBreedUser(breed, name);
		Dog dog = this->serv.listDogsServ()[index];
		this->nameEdit->setText(QString::fromStdString(dog.getName()));
		this->breedEdit->setText(QString::fromStdString(dog.getBreed()));
		this->ageEdit->setText(QString::fromStdString(std::to_string(dog.getAge())));
		this->urlEdit->setText(QString::fromStdString(dog.getPhotograph()));
		if (!dog.getIsAdopted()) {
			this->isAdoptedEdit->setText("No");
		} else {
			this->isAdoptedEdit->setText("Yes");
		}

		std::string link = std::string("start ").append(dog.getPhotograph());
		system(link.c_str());
	});

	QObject::connect(this->dogListButton, &QPushButton::clicked, this, &GUI::populateUser);
	QObject::connect(this->backButton, &QPushButton::clicked, this, &GUI::goBack);

	QObject::connect(this->CSVFileButton, &QRadioButton::clicked, [this]() {
		this->userServ.repositoryType("1");
		this->selectedRepo = true;
	});

	QObject::connect(this->HTMLFileButton, &QRadioButton::clicked, [this]() {
		this->userServ.repositoryType("2");
		this->selectedRepo = true;
	});

	QObject::connect(this->openFileButton, &QPushButton::clicked, [this]() {
		if (!this->selectedRepo) {
			auto *error = new QMessageBox();
			error->setIcon(QMessageBox::Warning);
			error->setText("Please select the type of file you want!");
			error->setWindowTitle("No file selected!");
			error->exec();
		} else {
			std::string link = std::string("start ").append(this->userServ.getFileUserRepo());
			system(link.c_str());
		}
	});

	QObject::connect(this->filterDogButton, &QPushButton::clicked, this, &GUI::populateFilter);

	QObject::connect(this->adoptButton, &QPushButton::clicked, this, &GUI::adoptDog);

	QObject::connect(this->nextButton, &QPushButton::clicked, this, &GUI::nextDog);

	QObject::connect(this->openTableButton, &QPushButton::clicked, [this]() {
		this->createTable();
	});
}

void GUI::goBack() {
	delete this->box;
	delete this->layout;
	this->selectedRepo = false;
	this->filtString = "Null";
	this->filtAge = INT_MAX;

	this->initGUI();
}

void GUI::populate() {
	this->dogList->clear();
	std::vector<Dog> dogs = this->serv.listDogsServ();
	for (Dog &dog: dogs) {
		this->dogList->addItem(QString::fromStdString(dog.toString()));
	}
}

void GUI::addDog() {
	std::string name = this->nameEdit->text().toStdString();
	std::string breed = this->breedEdit->text().toStdString();
	std::string age = this->ageEdit->text().toStdString();
	std::string photograph = this->urlEdit->text().toStdString();
	int ageNr;
	try {
		this->validator.validateName(name);
		this->validator.validateBreed(breed);
		this->validator.validateAge(age);
		ageNr = std::stoi(age);
		this->validator.validatePhotograph(photograph);
		this->serv.addDogServ(breed, name, ageNr, photograph);
		this->populate();
		this->nameEdit->clear();
		this->breedEdit->clear();
		this->ageEdit->clear();
		this->urlEdit->clear();
		this->isAdoptedEdit->clear();
	} catch (CustomException &e) {
		auto *error = new QMessageBox();
		error->setIcon(QMessageBox::Critical);
		error->setText(e.what());
		error->setWindowTitle("Error!");
		error->exec();
	}
}

void GUI::deleteDog() {
	try {
		std::string name = this->nameEdit->text().toStdString();
		std::string breed = this->breedEdit->text().toStdString();
		this->validator.validateName(name);
		this->validator.validateBreed(breed);
		if (!this->serv.checkDogExiNameBreed(breed, name)) {
			throw CustomException("Dog doesn't exist!");
		}
		if (this->serv.checkDogExiNameBreedUser(breed, name) == -1) {
			throw CustomException("Dog doesn't exist!");
		}
		int idx = this->serv.checkDogExiNameBreedUser(breed, name);
		std::string idxString = std::to_string(idx);
		this->validator.validateIndex(idxString, this->serv.listDogsServ().size());
		this->serv.deleteDogServ(idx);
		this->populate();
		this->nameEdit->clear();
		this->breedEdit->clear();
		this->ageEdit->clear();
		this->urlEdit->clear();
		this->isAdoptedEdit->clear();
	} catch (CustomException &e) {
		auto *error = new QMessageBox();
		error->setIcon(QMessageBox::Critical);
		error->setText(e.what());
		error->setWindowTitle("Error!");
		error->exec();
	}
}

void GUI::updateDog() {
	QModelIndexList selectedIdxs = this->dogList->selectionModel()->selectedIndexes();
	if (selectedIdxs.empty()) {
		return;
	}
	int idx = selectedIdxs.at(0).row();
	try {
		if (idx < 0) {
			auto *error = new QMessageBox();
			error->setIcon(QMessageBox::Critical);
			error->setText("No dog selected!");
			error->setWindowTitle("Selection error!");
			error->exec();
		} else {
			std::string newName = this->nameEdit->text().toStdString();
			std::string newBreed = this->breedEdit->text().toStdString();
			std::string age = this->ageEdit->text().toStdString();
			int ageNr;
			std::string newPhotograph = this->urlEdit->text().toStdString();
			this->validator.validateName(newName);
			this->validator.validateBreed(newBreed);
			this->validator.validateAge(age);
			ageNr = std::stoi(age);
			this->validator.validatePhotograph(newPhotograph);
			if (this->serv.checkDogExiNameBreed(newBreed, newName)) {
				throw CustomException("Dog already exists!");
			}
			std::string idxString = std::to_string(idx);
			this->validator.validateIndex(idxString, this->serv.listDogsServ().size());
			this->serv.updateDogServ(newBreed, newName, ageNr, newPhotograph, idx,
									 this->serv.listDogsServ()[idx].getIsAdopted());
			this->populate();
			this->nameEdit->clear();
			this->breedEdit->clear();
			this->ageEdit->clear();
			this->urlEdit->clear();
			this->isAdoptedEdit->clear();
		}
	} catch (CustomException &e) {
		auto *error = new QMessageBox();
		error->setIcon(QMessageBox::Critical);
		error->setText(e.what());
		error->setWindowTitle("Error!");
		error->exec();
	}
}

void GUI::populateFilter() {
	this->curIdx = 0;
	this->dogListUser->clear();
	try {
		this->filtString = this->filterBreed->text().toStdString();
		this->filtAgeString = this->filterAge->text().toStdString();
		if (this->filtString.empty() && this->filtAgeString.empty()) {
			this->populateUser();
		} else {
			this->validator.validateBreed(this->filtString);
			this->validator.validateAge(filtAgeString);
			this->filtAge = std::stoi(filtAgeString);

			std::vector<Dog> filt;
			this->serv.listFilteredDogsBreed(this->filtString, this->filtAge, filt);

			if (filt.empty()) {
				throw CustomException("The list of filtered dogs is empty!");
			} else {
				if (this->filtString == "Null") {
					for (Dog &dog: filt) {
						if (dog.getAge() < this->filtAge && !dog.getIsAdopted()) {
							this->dogListUser->addItem(QString::fromStdString(dog.toString()));
						}
					}
				} else {
					for (Dog &dog: filt) {
						if (dog.getAge() < this->filtAge && dog.getBreed() == this->filtString && !dog.getIsAdopted()) {
							this->dogListUser->addItem(QString::fromStdString(dog.toString()));
						}
					}
				}
			}
		}
	} catch (CustomException &e) {
		auto *error = new QMessageBox();
		error->setIcon(QMessageBox::Critical);
		error->setText(e.what());
		error->setWindowTitle("Error!");
		error->exec();
	}
}

void GUI::populateUser() {
	this->curIdx = 0;

	this->dogListUser->clear();
	std::vector<Dog> dogs = this->serv.listAdoptedDogsServ();
	for (Dog &dog: dogs) {
		this->dogListUser->addItem(QString::fromStdString(dog.toString()));
	}

	this->adoptionList->clear();
	dogs = this->userServ.getAllUserService();
	for (Dog &dog: dogs) {
		this->adoptionList->addItem(QString::fromStdString(dog.toString()));
	}
}

void GUI::adoptDog() {
	if (!this->selectedRepo) {
		auto *error = new QMessageBox();
		error->setIcon(QMessageBox::Warning);
		error->setText("You must select a file first!");
		error->setWindowTitle("File type warning!");
		error->exec();
	} else {
		try {
			std::string name = this->nameEdit->text().toStdString();
			std::string breed = this->breedEdit->text().toStdString();
			std::string age = this->ageEdit->text().toStdString();
			std::string photograph = this->urlEdit->text().toStdString();

			if (name.empty()) {
				throw CustomException("No dog selected!");
			} else {
				int ageNr = std::stoi(age);
				int index = this->serv.getIndexNonAdoptedDog(breed, name);
				this->userServ.addDogServUser(breed, name, ageNr, photograph);
				this->serv.updateDogServ(breed, name, ageNr, photograph, index, true);
				this->serv.deleteDogServ(index);
				int auxIdx = this->curIdx - 1;
				this->populateUser();
				this->populateAdopted();
				this->populateUserTable();

				this->curIdx = auxIdx;
				if (this->curIdx >= this->dogListUser->count()) {
					this->curIdx = 0;
				}

				if (this->dogListUser->count() > 0) {
					this->dogListUser->item(this->curIdx)->setSelected(true);
					this->dogListUser->setCurrentRow(this->curIdx);
					this->dogListUser->setFocus();

					name = this->dogListUser->selectedItems().at(0)->text().toStdString();
					breed = this->serv.trim(this->serv.tokenizeServ(this->serv.tokenizeServ(name, '>')[1], ';')[0]);
					name = this->serv.trim(this->serv.tokenizeServ(this->serv.tokenizeServ(name, '>')[2], ';')[0]);

					index = this->serv.getIndexNonAdoptedDog(breed, name);
					Dog dog = this->serv.listDogsServ()[index];
					this->nameEdit->setText(QString::fromStdString(dog.getName()));
					this->breedEdit->setText(QString::fromStdString(dog.getBreed()));
					this->ageEdit->setText(QString::fromStdString(std::to_string(dog.getAge())));
					this->urlEdit->setText(QString::fromStdString(dog.getPhotograph()));
					if (!dog.getIsAdopted()) {
						this->isAdoptedEdit->setText("No");
					} else {
						this->isAdoptedEdit->setText("Yes");
					}
					++this->curIdx;
				} else {
					this->nameEdit->clear();
					this->breedEdit->clear();
					this->ageEdit->clear();
					this->urlEdit->clear();
					this->isAdoptedEdit->clear();
				}
			}
		} catch (CustomException &e) {
			auto *error = new QMessageBox();
			error->setIcon(QMessageBox::Critical);
			error->setText(e.what());
			error->setWindowTitle("Error!");
			error->exec();
		}
	}
}

void GUI::populateAdopted() {
	this->adoptionList->clear();
	std::vector<Dog> adopted = this->userServ.getAllUserService();
	for (Dog &dog: adopted) {
		this->adoptionList->addItem(QString::fromStdString(dog.toString()));
	}
}

void GUI::nextDog() {
	if (this->curIdx >= this->dogListUser->count()) {
		this->curIdx = 0;
	}

	this->dogListUser->item(this->curIdx)->setSelected(true);
	this->dogListUser->setCurrentRow(this->curIdx);
	this->dogListUser->setFocus();

	std::string name = this->dogListUser->selectedItems().at(0)->text().toStdString();
	std::string breed = this->serv.trim(this->serv.tokenizeServ(this->serv.tokenizeServ(name, '>')[1], ';')[0]);
	name = this->serv.trim(this->serv.tokenizeServ(this->serv.tokenizeServ(name, '>')[2], ';')[0]);
	int index = this->serv.getIndexNonAdoptedDog(breed, name);
	Dog dog = this->serv.listDogsServ()[index];
	this->nameEdit->setText(QString::fromStdString(dog.getName()));
	this->breedEdit->setText(QString::fromStdString(dog.getBreed()));
	this->ageEdit->setText(QString::fromStdString(std::to_string(dog.getAge())));
	this->urlEdit->setText(QString::fromStdString(dog.getPhotograph()));
	if (!dog.getIsAdopted()) {
		this->isAdoptedEdit->setText("No");
	} else {
		this->isAdoptedEdit->setText("Yes");
	}

	std::string link = std::string("start ").append(dog.getPhotograph());
	system(link.c_str());

	++this->curIdx;
}

void GUI::connectSignals() {
	QObject::connect(this->undoShort, &QShortcut::activated, [this]() {
		this->undo();
		this->nameEdit->clearFocus();
	});
	QObject::connect(this->redoShort, &QShortcut::activated, [this]() {
		this->redo();
		this->nameEdit->clearFocus();
	});
}


void GUI::undo() {
	try {
		this->serv.undoAction();
		this->populate();
	} catch (CustomException &e) {
		QMessageBox::critical(this, "Error", e.what());
	}
}

void GUI::redo() {
	try {
		this->serv.redoAction();
		this->populate();
	} catch (CustomException &e) {
		QMessageBox::critical(this, "Error", e.what());
	}
}

void GUI::createTable() {
	auto *window = new QWidget;
	auto *tableView = new QTableView;

	tableView->setModel(this->adoptedTableModel);
	tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	window->setMinimumWidth(tableView->width());

	auto *Vbox = new QVBoxLayout{window};
	Vbox->addWidget(tableView);
	window->setWindowState(Qt::WindowMaximized);
	window->show();
}

void GUI::populateUserTable() {
	this->adoptedTableModel->propagate();
}
