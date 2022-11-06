#ifndef A8_9_EDWARDINIO18_VALIDATOR_H
#define A8_9_EDWARDINIO18_VALIDATOR_H

#include "../Repository/repository.h"

#include <iostream>

class Validator {
public:
	static void validateBreed(const std::string &breed);

	static void validateName(const std::string &name);

	static void validateAge(const std::string &age);

	static void validatePhotograph(const std::string &photograph);

	static void validateIndex(const std::string &idx, const int &size);
};


#endif //A8_9_EDWARDINIO18_VALIDATOR_H
