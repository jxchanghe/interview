#include "qh_string.h"

#include <string.h>
#include <stdio.h>

namespace qh
{
    string::string()
        : data_(NULL), len_(0)
    {
    }
	
    string::string( const char* s )
    {
		if (NULL == s)
		{ 
			data_ = NULL;  
			len_ = 0;
			return;
		}

		len_ = strlen(s);
		data_ = new char[len_ + 1];
		strcpy(data_, s);
    }
	
    string::string( const char* s, size_t len )
    {
		size_t sLen = 0;

		if (NULL == s)
		{ 
			data_ = NULL;  
			len_ = 0;
			return;
		}

		sLen = strlen(s);
		len_ =  sLen > len ? len : sLen;
		data_ = new char[len_ + 1];
		strncpy(data_, s, len_ + 1);
    }
	
    string::string( const string& rhs )
    {
		len_ = rhs.size();
		if (0 == len_)
		{
			data_ = NULL;
			return;
		}
		
		data_ = new char[len_ + 1];
		strcpy(data_, rhs.c_str());
    }
	
    string& string::operator=( const string& rhs )
    {
		if (this == &rhs)
		{
			return *this;
		}

		delete[] data_;
		len_ = rhs.size();
	    data_ = new char[len_ + 1];
        strcpy(data_, rhs.c_str());

		return *this;
    }
	
    string::~string()
    {
		delete[] data_;
    }
	
    size_t string::size() const
    {
        return len_;
    }
	
    const char* string::data() const
    {
        return (c_str());
    }
	
    const char* string::c_str() const
    {
        return ((data_ == NULL) ? "" : data_);
    }
	
    char& string::operator[]( size_t index )
    {
	    static char c = 0;
        if (len_ < index || data_ == NULL)
		{
			return c;
		}

		return data_[index];
    }
}