#include "dog.h"

#include <vector>
#include <sstream>

Dog::Dog(const std::string &breed, const std::string &name, int age, const std::string &photograph, bool isAdopted)
		: breed{breed}, name{name}, age{age}, photograph{photograph}, isAdopted{isAdopted} {}

std::string Dog::toString() {
	std::string adopted;
	if (this->isAdopted) {
		adopted = "Yes";
	} else {
		adopted = "No";
	}
	return "Breed -> " + this->breed + "; Name -> " + this->name + "; Age -> " + std::to_string(this->age) +
		   "; Photograph -> " + this->photograph + "; Adopted -> " +
		   adopted + ";";
}

std::vector<std::string> Dog::tokenize(const std::string &str, char del) {
	std::vector<std::string> result;
	std::stringstream ss(str);
	std::string token;
	while (getline(ss, token, del))
		result.push_back(token);
	return result;
}

std::istream &operator>>(std::istream &in, Dog &dog) {
	std::string line;
	std::getline(in, line);
	std::vector<std::string> tokens;
	if (line.empty()) {
		return in;
	}
	tokens = Dog::tokenize(line, ',');
	dog.breed = tokens[0];
	dog.name = tokens[1];
	dog.age = std::stoi(tokens[2]);
	dog.photograph = tokens[3];
	if (tokens[4] == "0") {
		dog.isAdopted = false;
	} else {
		dog.isAdopted = true;
	}
	return in;
}

std::ostream &operator<<(std::ostream &out, const Dog &dog) {
	out << dog.breed << "," << dog.name << "," << std::to_string(dog.age) << "," << dog.photograph << ","
		<< dog.isAdopted;
	return out;
}

bool Dog::operator==(const Dog &dog) const {
	return this->name == dog.name;
}