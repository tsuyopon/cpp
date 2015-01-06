#include "FileException.h"

FileException::FileException(const char* error){
	m_error = error;
}

const char* FileException::What() const {
	return m_error.c_str();
}
