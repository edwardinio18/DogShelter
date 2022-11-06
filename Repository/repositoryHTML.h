#ifndef A8_9_EDWARDINIO18_REPOSITORYHTML_H
#define A8_9_EDWARDINIO18_REPOSITORYHTML_H

#include "userRepository.h"

#include <fstream>

class RepositoryHTML : public UserRepository {
public:
	RepositoryHTML(const std::vector<Dog> &adopted, const std::string &file);

	std::vector<Dog> &listDogsRepo() override;

	void addDogRepoUser(const Dog &dog) override;

	void writeFile() override;

	std::string &getFile() override;

	bool isEmpty(std::ifstream &f) override { return false; }
};


#endif //A8_9_EDWARDINIO18_REPOSITORYHTML_H
