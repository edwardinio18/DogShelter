#ifndef A5_6_EDWARDINIO18_REPOSITORY_H
#define A5_6_EDWARDINIO18_REPOSITORY_H

#include "../Dog/dog.h"

#include <vector>

class Repository {
private:
	std::vector<Dog> dyn_arr{};
	std::string file;
public:
	explicit Repository(std::string &file);

	void addDogRepo(const Dog &el);

	void deleteDogRepo(int idx);

	void updateDogRepo(const Dog &el, int idx);

	std::vector<Dog> listDogsRepo();

	void readFile();

	void writeFile();

	void initRepo();

	int checkDogExiNameBreedRepo(const std::string &breed, const std::string &name);

	bool isEmpty(std::ifstream &file);

	int checkDogExiNameBreedRepoAdd(const std::string &breed, const std::string &name);

	int checkDogExiNameBreedRepoDelUpd(int idx);

	int checkDogExiNameBreedUserRepo(const std::string &breed, const std::string &name);
};

#endif //A5_6_EDWARDINIO18_REPOSITORY_H