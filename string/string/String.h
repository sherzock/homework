#ifndef STRING_H
#define STRING_H

#include <cstring>

class String
{
public:

	String() :
		str(nullptr),
		num_chars(0)
	{ }

	String(const char *pstr) :
		num_chars(strlen(pstr)),
		str(new char[num_chars + 1])
	{
		strcpy_s(str, num_chars + 1, pstr);
	}

	String(const String &pstr) :
		num_chars(pstr.num_chars),
		str(new char[num_chars + 1])
	{
		strcpy_s(str, num_chars + 1, pstr.str);
	}

	~String()
	{
		delete[] str;
	}

	bool empty() const
	{
		return num_chars == 0;
	}

	unsigned int size() const
	{
		return num_chars;
	}

	void clear()
	{
		delete[] str;
		str = nullptr;
		num_chars = 0;
	}

	const char *c_str() const
	{
		return str;
	}

	void operator=(const String &pstr)
	{
		delete[] str;
		num_chars = pstr.num_chars;
		str = new char[num_chars + 1];
		strcpy_s(str, num_chars + 1, pstr.str);
	}

	void operator+=(const String &pstr)
	{
		unsigned int new_num_chars = num_chars + pstr.num_chars;
		char *new_str = new char[new_num_chars + 1];
		strcpy_s(new_str, new_num_chars + 1, str);
		strcat_s(new_str, new_num_chars + 1, pstr.str);
		delete[] str;
		num_chars = new_num_chars;
		str = new_str;
	}

	String operator+(const String &s) const
	{
		String concatenation(str);
		concatenation += s;
		return concatenation;
	}

	bool operator==(const String &pstr)
	{
		return strcmp(str, pstr.str) == 0;
	}

	bool operator!=(const String &pstr)
	{
		return strcmp(str, pstr.str) != 0;
	}

private:

	unsigned int num_chars = 0;
	char *str = nullptr;
};

#endif // STRING_H