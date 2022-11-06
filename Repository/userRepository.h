#ifndef A8_9_EDWARDINIO18_USERREPOSITORY_H
#define A8_9_EDWARDINIO18_USERREPOSITORY_H

#include <vector>
#include "../Dog/dog.h"

#include <fstream>

class UserRepository {
protected:
	std::vector<Dog> adopted;
	std::string file;
public:
	explicit UserRepository(std::vector<Dog> &adopted);

	UserRepository();

	virtual std::vector<Dog> &listDogsRepo() = 0;

	virtual void addDogRepoUser(const Dog &dog) = 0;

	virtual void writeFile() = 0;

	virtual std::string &getFile() = 0;

	virtual bool isEmpty(std::ifstream &f) = 0;
};


#endif //A8_9_EDWARDINIO18_USERREPOSITORY_H
