#include "service.h"
#include "../CustomException/customException.h"
#include "../Validator/validator.h"

#include <vector>
#include <algorithm>
#include <sstream>

Service::Service(Repository &repo, Validator &validator) : repo{repo}, validator{validator} {
	/*
		Constructor for the service class
	*/
}

void
Service::addDogServ(const std::string &breed, const std::string &name, const int &age, const std::string &photograph) {
	/*
		Creates a dog class instance and adds it to the repository

	 	breed - Breed of dog
	 	name - Name of dog
	 	age - Age of dog
	 	photograph - Picture of dog
	*/

	Dog dog{breed, name, age, photograph, false};
	try {
		this->repo.addDogRepo(dog);
		std::shared_ptr<UndoRedoAction> action = std::make_shared<UndoRedoAdd>(dog, this->repo);
		this->undo.push_back(action);
		this->redo.clear();
	} catch (CustomException &e) {
		throw e;
	}
}

void Service::deleteDogServ(int idx) {
	/*
		Deletes a dog from the repository

	 	idx - Index of dog to be deleted
	*/

	try {
		Dog dog = this->repo.listDogsRepo()[idx];
		this->repo.deleteDogRepo(idx);
		std::shared_ptr<UndoRedoAction> action = std::make_shared<UndoRedoRemove>(dog, this->repo);
		this->undo.push_back(action);
		this->redo.clear();
	} catch (CustomException &e) {
		throw e;
	}
}

void
Service::updateDogServ(const std::string &breed, const std::string &name, const int &age, const std::string &photograph,
					   int idx, bool adopted) {
	/*
		Updates a dog in the repository

	 	breed - Breed of dog
	 	name - Name of dog
	 	age - Age of dog
	 	photograph - Picture of dog
	 	idx - Index of dog to be updated
	*/

	Dog dog{breed, name, age, photograph, adopted};
	try {
		Dog oldDog = this->repo.listDogsRepo()[idx];
		this->repo.updateDogRepo(dog, idx);
		std::shared_ptr<UndoRedoAction> action = std::make_shared<UndoRedoUpdate>(oldDog, dog, this->repo);
		this->undo.push_back(action);
		this->redo.clear();
	} catch (CustomException &e) {
		throw e;
	}
}

int Service::checkDogExi(int idx) {
	/*
		Checks if a dog exists in the repository or not

	 	idx - Index to check against
	*/

	int j = 0;
	for (auto i: this->repo.listDogsRepo()) {
		if (j == idx) return 1;
		++j;
	}
	return 0;
}

std::vector<Dog> Service::listDogsServ() {
	/*
		Returns the list of all dogs
	*/

	return this->repo.listDogsRepo();
}

int Service::checkDogExiNameBreed(const std::string &breed, const std::string &name) {
	/*
		Checks if a dog already exists with the same breed and name

	 	breed - Breed of dog
	 	name - Name of dog
	*/

	for (const auto &i: this->repo.listDogsRepo()) {
		if (breed == i.getBreed() && name == i.getName())
			return 1;
	}
	return 0;
}

int Service::checkDogExiNameBreedUser(const std::string &breed, const std::string &name) {
	/*
		Checks if a dog already exists with the same breed and name

	 	breed - Breed of dog
	 	name - Name of dog
	*/

	int j = 0;
	for (const auto &i: this->repo.listDogsRepo()) {
		if (breed == i.getBreed() && name == i.getName())
			return j;
		++j;
	}
	return -1;
}

int Service::getSizeNonAdopted() {
	int cnt = 0;
	for (const auto &i: this->repo.listDogsRepo()) {
		if (!i.getIsAdopted()) {
			++cnt;
		}
	}
	return cnt;
}

void Service::listFilteredDogsBreed(const std::string &breed, const int &age, std::vector<Dog> &filt) {
	std::vector<Dog> d{}, v = this->repo.listDogsRepo();
	if (breed == "Null") {
		for (const auto &i: this->repo.listDogsRepo()) {
			if (!i.getIsAdopted()) {
				if (i.getAge() < age) {
					d.push_back(i);
				}
			}
		}
	} else {
		std::copy_if(v.begin(), v.end(),
					 std::back_inserter(d),
					 [&breed, &age](auto &dog) {
						 return ((!dog.getIsAdopted()) && (dog.getBreed() == breed) && (dog.getAge() < age));
					 });
	}
	filt = d;
}

void Service::initRepoServ() {
	this->repo.initRepo();
}

std::vector<std::string> Service::tokenizeServ(const std::string &str, char del) {
	std::vector<std::string> result;
	std::stringstream ss(str);
	std::string token;
	while (getline(ss, token, del))
		result.push_back(token);
	return result;
}

std::string Service::trim(const std::string &s) {
	auto start = s.begin();
	while (start != s.end() && std::isspace(*start)) {
		start++;
	}

	auto end = s.end();
	do {
		end--;
	} while (std::distance(start, end) > 0 && std::isspace(*end));

	return std::string(start, end + 1);
}

std::vector<Dog> Service::listAdoptedDogsServ() {
	std::vector<Dog> v;
	for (const auto &i: this->repo.listDogsRepo()) {
		if (!i.getIsAdopted()) {
			v.push_back(i);
		}
	}
	return v;
}

int Service::getIndexNonAdoptedDog(const std::string &breed, const std::string &name) {
	int j = 0;
	for (const auto &i: this->repo.listDogsRepo()) {
		if (breed == i.getBreed() && name == i.getName() && !i.getIsAdopted())
			return j;
		++j;
	}
	return -1;
}

void Service::undoAction() {
	if (this->undo.empty()) {
		throw CustomException("Can't undo anymore!");
	}
	this->undo.back()->undo();
	this->redo.push_back(this->undo.back());
	this->undo.pop_back();
}

void Service::redoAction() {
	if (this->redo.empty()) {
		throw CustomException("Can't redo anymore!");
	}
	this->redo.back()->redo();
	this->undo.push_back(this->redo.back());
	this->redo.pop_back();
}

void Service::emptyUndoRedo() {
	this->undo.clear();
	this->redo.clear();
}