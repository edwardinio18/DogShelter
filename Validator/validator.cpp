#include "validator.h"
#include "../CustomException/customException.h"

void Validator::validateBreed(const std::string &breed) {
	if (breed.empty()) {
		throw CustomException("\nBreed can not be empty!\n");
	} else {
		for (auto i: breed) {
			if (i >= '0' && i <= '9') {
				throw CustomException("\nBreed can only contain letters!\n");
			}
		}
	}
}

void Validator::validateName(const std::string &name) {
	if (name.empty()) {
		throw CustomException("\nName can not be empty!\n");
	} else {
		for (auto i: name) {
			if (i >= '0' && i <= '9') {
				throw CustomException("\nName can only contain letters!\n");
			}
		}
	}
}

void Validator::validateAge(const std::string &age) {
	if (age.empty()) {
		throw CustomException("\nAge can not be empty!\n");
	} else {
		for (auto i: age) {
			if (i < '0' || i > '9') {
				throw CustomException("\nAge must be a number!\n");
			}
		}
	}
}

void Validator::validatePhotograph(const std::string &photograph) {
	if (photograph.empty()) {
		throw CustomException("\nPhotograph can not be empty!\n");
	} else {
		if (photograph[0] != 'h' || photograph[1] != 't' || photograph[2] != 't' || photograph[3] != 'p' ||
			photograph[4] != 's' || photograph[5] != ':' || photograph[6] != '/' || photograph[7] != '/') {
			throw CustomException("\nPhotograph must be of format https://...!\n");
		}
	}
}

void Validator::validateIndex(const std::string &idx, const int &size) {
	if (idx.empty()) {
		throw CustomException("\nIndex can not be empty!\n");
	} else {
		for (auto i: idx) {
			if (i < '0' || i > '9') {
				throw CustomException("\nIndex must be a number!\n");
			}
		}
		int n = std::stoi(idx);
		if (n < 0 || n > size) {
			throw CustomException("\nIndex out of range, please try again!\n");
		}
	}
}