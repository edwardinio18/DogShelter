#include "repositoryHTML.h"

#include <fstream>

RepositoryHTML::RepositoryHTML(const std::vector<Dog> &adopted, const std::string &file) {
	this->adopted = adopted;
	this->file = file;
}

std::vector<Dog> &RepositoryHTML::listDogsRepo() {
	return this->adopted;
}

void RepositoryHTML::addDogRepoUser(const Dog &dog) {
	this->adopted.push_back(dog);
	this->writeFile();
}

std::string &RepositoryHTML::getFile() {
	return this->file;
}

void RepositoryHTML::writeFile() {
	std::ofstream fout(this->file);
	fout << "<!DOCTYPE html>\n<html><head><title>Adoption List</title></head><body>\n";
	fout << "<table border=\"1\">\n";
	fout << "<tr><td>Breed</td><td>Name</td><td>Age</td><td>Link</td></tr>\n";
	for (const Dog &dog: this->adopted) {
		fout << "<tr><td>" << dog.getBreed() << "</td>"
			 << "<td>" << dog.getName() << "</td>"
			 << "<td>" << std::to_string(dog.getAge()) << "</td>"
			 << "<td><a href=\"" << dog.getPhotograph() << "\">" << dog.getPhotograph() << "</a></td>" << '\n';
	}
	fout << "</table></body></html>";
	fout.close();
}