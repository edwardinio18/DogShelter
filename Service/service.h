#ifndef A5_6_EDWARDINIO18_SERVICE_H
#define A5_6_EDWARDINIO18_SERVICE_H

#include "../Repository/repository.h"
#include "../Repository/userRepository.h"
#include "../Validator/validator.h"
#include "undoredo.h"

#include <vector>
#include <regex>
#include <memory>

class Service {
private:
	Repository &repo;
	Validator &validator;

	std::vector<std::shared_ptr<UndoRedoAction>> undo;
	std::vector<std::shared_ptr<UndoRedoAction>> redo;
public:
	Service(Repository &repo, Validator &validator);

	void addDogServ(const std::string &breed, const std::string &name, const int &age, const std::string &photograph);

	void deleteDogServ(int idx);

	void updateDogServ(const std::string &breed, const std::string &name, const int &age, const std::string &photograph,
					   int idx, bool adopted);

	std::vector<Dog> listDogsServ();

	int checkDogExi(int idx);

	int checkDogExiNameBreed(const std::string &breed, const std::string &name);

	int getSizeNonAdopted();

	void listFilteredDogsBreed(const std::string &breed, const int &age, std::vector<Dog> &filt);

	int checkDogExiNameBreedUser(const std::string &breed, const std::string &name);

	void initRepoServ();

	static std::vector<std::string> tokenizeServ(const std::string &str, char del);

	static std::string trim(const std::string &s);

	std::vector<Dog> listAdoptedDogsServ();

	int getIndexNonAdoptedDog(const std::string &breed, const std::string &name);

	void undoAction();

	void redoAction();

	void emptyUndoRedo();
};

#endif //A5_6_EDWARDINIO18_SERVICE_H