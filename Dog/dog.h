#ifndef A5_6_EDWARDINIO18_DOG_H
#define A5_6_EDWARDINIO18_DOG_H

#include <string>
#include <vector>

class Dog {
private:
	std::string breed;
	std::string name;
	int age;
	std::string photograph;
	bool isAdopted;
public:
	Dog() : breed{""}, name{""}, age{0}, photograph{""}, isAdopted{false} {}

	Dog(const std::string &breed, const std::string &name, int age, const std::string &photograph, bool isAdopted);

	std::string getBreed() const { return this->breed; }

	std::string getName() const { return this->name; }

	int getAge() const { return this->age; }

	std::string getPhotograph() const { return this->photograph; }

	bool getIsAdopted() const { return this->isAdopted; }

	std::string toString();

	static std::vector<std::string> tokenize(const std::string &str, char del);

	friend std::istream &operator>>(std::istream &in, Dog &dog);

	friend std::ostream &operator<<(std::ostream &out, const Dog &dog);

	bool operator==(const Dog &dog) const;
};

#endif //A5_6_EDWARDINIO18_DOG_H