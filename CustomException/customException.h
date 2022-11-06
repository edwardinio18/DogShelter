#ifndef A8_9_EDWARDINIO18_CUSTOMEXCEPTION_H
#define A8_9_EDWARDINIO18_CUSTOMEXCEPTION_H

#include <exception>

class CustomException : public std::exception {
private:
	const char *msg;
public:
	explicit CustomException(const char *msg);

	const char *what() const noexcept override;
};


#endif //A8_9_EDWARDINIO18_CUSTOMEXCEPTION_H
