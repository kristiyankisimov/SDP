#ifndef TREE_EXCEPTIONS_H
#define TREE_EXCEPTIONS_H

#include <exception>

class KeyNotFoundError : public std::exception {
};

class EmptyTreeError : public std::exception {
};

#endif

