#ifndef A8_9_EDWARDINIO18_USERSERV_H
#define A8_9_EDWARDINIO18_USERSERV_H

#include "../Repository/repository.h"
#include "../Repository/userRepository.h"

class UserServ {
private:
	Repository &repo;
	UserRepository *userRepo;

	bool repoType;
public:
	UserServ(Repository &repo1, UserRepository *userRepo1);

	explicit UserServ(Repository &repo1);

	std::vector<Dog> getAllUserService();

	void
	addDogServUser(const std::string &breed, const std::string &name, const int &age, const std::string &photograph);

	void repositoryType(const std::string &fileType);

	std::string &getFileUserRepo();

	void clearFile(const std::string &file);

	void writeFileUser();
};


#endif //A8_9_EDWARDINIO18_USERSERV_H
