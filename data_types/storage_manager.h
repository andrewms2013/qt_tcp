#pragma once
#ifndef STORAGE_MANAGER_H
#define STORAGE_MANAGER_H

#include <json_storage.h>
#include <stdexcept>
#include "data_types_global.h"

using namespace std;

class DATA_TYPESSHARED_EXPORT StorageManager {
public:
    static JsonDeveloperStorage * createStorage(std::string & storageFileName);
};

class DATA_TYPESSHARED_EXPORT MessageException : public std::exception {
    string _error;
public:
    MessageException(std::string & error) {
        this->_error = error;
    }
    const char * what() const noexcept{
        return this->_error.c_str();
    }
};

#endif // STORAGE_MANAGER_H
