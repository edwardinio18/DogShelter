#include "userServ.h"
#include <algorithm>
#include "../Repository/repositoryCSV.h"
#include <iostream>
#include "../Repository/repositoryHTML.h"


UserServ::UserServ(Repository &repository1, UserRepository *userRepo1) : repo(repository1) {
	this->userRepo = userRepo1;
	this->repoType = false;
}

UserServ::UserServ(Repository &repository1) : repo(repository1) {
}

std::vector<Dog> UserServ::getAllUserService() {
	return this->userRepo->listDogsRepo();
}

void UserServ::addDogServUser(const std::string &breed, const std::string &name, const int &age,
							  const std::string &photograph) {
	Dog dog{breed, name, age, photograph, true};
	this->userRepo->addDogRepoUser(dog);
}

void UserServ::repositoryType(const std::string &fileType) {
	std::vector<Dog> userVector;
	std::string userFile;
	if (fileType == "1") {
		userFile = R"(C:\Users\edwar\Documents\OOP\a14-edwardinio18\adopted.csv)";
		if (!this->repoType) {
			this->repoType = true;
		} else {
			userVector = this->getAllUserService();
		}
		auto *repository = new RepositoryCSV{userVector, userFile};
		this->userRepo = repository;
		this->userRepo->writeFile();
	} else if (fileType == "2") {
		userFile = R"(C:\Users\edwar\Documents\OOP\a14-edwardinio18\adopted.html)";
		if (!this->repoType) {
			this->repoType = true;
		} else {
			userVector = this->getAllUserService();
		}
		auto *repository = new RepositoryHTML{userVector, userFile};
		this->userRepo = repository;
		this->userRepo->writeFile();
	}
}

std::string &UserServ::getFileUserRepo() {
	return this->userRepo->getFile();
}

void UserServ::clearFile(const std::string &file) {
	std::ofstream fout;
	fout.open(file, std::ofstream::out | std::ofstream::trunc);
	fout.close();
}

void UserServ::writeFileUser() {
	this->userRepo->writeFile();
}
