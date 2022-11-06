#include "repositoryCSV.h"

#include <fstream>
#include <iostream>

RepositoryCSV::RepositoryCSV(const std::vector<Dog> &adopted, const std::string &file) {
	this->adopted = adopted;
	this->file = file;
}

std::vector<Dog> &RepositoryCSV::listDogsRepo() {
	return this->adopted;
}

void RepositoryCSV::addDogRepoUser(const Dog &dog) {
	this->adopted.push_back(dog);
	this->writeFile();
}

void RepositoryCSV::writeFile() {
	std::ofstream fout(this->file);
	for (const Dog &dog: this->adopted) {
		fout << dog << "\n";
	}
	fout.close();
}

std::string &RepositoryCSV::getFile() {
	return this->file;
}

bool RepositoryCSV::isEmpty(std::ifstream &f) {
	return f.peek() == std::ifstream::traits_type::eof();
}