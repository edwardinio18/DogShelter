#ifndef A8_9_EDWARDINIO18_REPOSITORYCSV_H
#define A8_9_EDWARDINIO18_REPOSITORYCSV_H

#include "userRepository.h"

#include <fstream>

class RepositoryCSV : public UserRepository {
public:
	RepositoryCSV(const std::vector<Dog> &adopted, const std::string &file);

	std::vector<Dog> &listDogsRepo() override;

	void addDogRepoUser(const Dog &dog) override;

	void writeFile() override;

	std::string &getFile() override;

	bool isEmpty(std::ifstream &f) override;
};


#endif //A8_9_EDWARDINIO18_REPOSITORYCSV_H
