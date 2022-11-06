#include "userRepository.h"

UserRepository::UserRepository() = default;

UserRepository::UserRepository(std::vector<Dog> &adopted) { this->adopted = adopted; }