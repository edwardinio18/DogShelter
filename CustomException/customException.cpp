#include "customException.h"

CustomException::CustomException(const char *msg) {
	this->msg = msg;
}

const char *CustomException::what() const noexcept {
	return this->msg;
}