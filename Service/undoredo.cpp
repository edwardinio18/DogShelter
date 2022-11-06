#include "undoredo.h"

UndoRedoAdd::UndoRedoAdd(const Dog &dog, Repository &newRepo) : addedDog(dog), repo(newRepo) {}

void UndoRedoAdd::undo() {
	std::string breed = addedDog.getBreed();
	std::string name = addedDog.getName();
	int idx = this->repo.checkDogExiNameBreedUserRepo(breed, name);
	this->repo.updateDogRepo(Dog{breed, name, addedDog.getAge(), addedDog.getPhotograph(), true}, idx);
	this->repo.deleteDogRepo(idx);
}

void UndoRedoAdd::redo() {
	this->repo.addDogRepo(this->addedDog);
}

UndoRedoRemove::UndoRedoRemove(const Dog &dog, Repository &newRepo) : removedDog(dog), repo(newRepo) {}

void UndoRedoRemove::undo() {
	this->repo.addDogRepo(this->removedDog);
}

void UndoRedoRemove::redo() {
	std::string breed = removedDog.getBreed();
	std::string name = removedDog.getName();
	int idx = this->repo.checkDogExiNameBreedUserRepo(breed, name);
	this->repo.deleteDogRepo(idx);
}

UndoRedoUpdate::UndoRedoUpdate(const Dog &oldDog, const Dog &newDog, Repository &newRepo) : oldDog(oldDog),
																							newDog(newDog),
																							repo(newRepo) {}

void UndoRedoUpdate::undo() {
	std::string breed = this->newDog.getBreed();
	std::string name = this->newDog.getName();
	int idx = this->repo.checkDogExiNameBreedUserRepo(breed, name);
	this->repo.updateDogRepo(this->oldDog, idx);
}

void UndoRedoUpdate::redo() {
	std::string breed = this->oldDog.getBreed();
	std::string name = this->oldDog.getName();
	int idx = this->repo.checkDogExiNameBreedUserRepo(breed, name);
	this->repo.updateDogRepo(this->newDog, idx);
}