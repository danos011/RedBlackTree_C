#ifndef REDBLACKTREE_EXEPTIONS_H
#define REDBLACKTREE_EXEPTIONS_H

#include <exception>
#include <string>

class BaseException : public std::exception {
public:
    const char *what() const noexcept override { return message_; }

protected:
    const char *message_;
};

class ErrorEmptyList : public BaseException {
public:
    ErrorEmptyList() { message_ = "List is empty!"; }
};

class WrongCommand : public BaseException {
public:
    WrongCommand() { message_ = "Wrong command!"; }
};

class ErrorEmptyTree : public BaseException {
public:
    ErrorEmptyTree() { message_ = "Tree is empty!"; }
};

class WrongIntegerNumber : public BaseException {
public:
    WrongIntegerNumber() { message_ = "Wrong integer number!"; }
};

class WrongUnsignedNumber : public BaseException {
public:
    WrongUnsignedNumber() { message_ = "Wrong unsigned number!"; }
};

class WrongRepeatingWord : public BaseException {
public:
    WrongRepeatingWord() { message_ = "Repeated word error!"; }
};

#endif //REDBLACKTREE_EXEPTIONS_H
