/**
*
*  Input Validation Module
*  Author: Leonardo Machado [05/31/2018]
*
*  Description:
*   A header-only runtime input validator inspired in Joi module for javascript [ https://github.com/hapijs/joi ]
*
*	Input Validation:
*
* 		Example:
*
* 		int main()
*		{
*			int value = 10;
*
*			JoiNumber schema = JoiNumber::build().less(1000).positive();
*
*			JoiResult result = JoiNumber::validate(value, &schema);
*
*			if(result.error())
*				cout << result.description() << endl;
*			else
*				cout << "parsed successfully ;)" << endl;
*
*			return 0;
*		}
*

*/

#ifndef JOI_H
#define JOI_H

#include <string>
#include <regex>

// Builder Design Pattern
using namespace std;

class JoiResult
{
private:
	bool _error;
	std::string _description;

public:
	JoiResult()
	{
		error(false);
		description("");
	}

	JoiResult(bool err, const std::string &desc)
	{
		error(err);
		description(desc);
	}

	~JoiResult() {}

	void error(bool value)
	{
		_error = value;
	}

	void description(const std::string &desc)
	{
		_description = desc;
	}

	bool error() const
	{
		return _error;
	}

	string description() const
	{
		return _description;
	}

};

class JoiNumber
{
private:
	int _min; // Specifies the minimum value where _min is the minimum value allowed.
	int _max; // Specifies the maximum value where _max is the maximum value allowed.
	int _less; // Specifies that the value must be less than _less.
	int _greater; // Specifies that the value must be greater than _greater.
	bool _negative; // Requires the number to be negative.
	bool _positive; // Requires the number to be positive.

private:
	JoiNumber()
	{
		_min = INT_MAX; // Specifies the minimum value where _min is the minimum value allowed.
		_max = INT_MIN; // Specifies the maximum value where _max is the maximum value allowed.
		_less = INT_MIN; // Specifies that the value must be less than _less.
		_greater = INT_MAX; // Specifies that the value must be greater than _greater.
		_negative = false; // Requires the number to be negative.
		_positive = false; // Requires the number to be positive.
	}

public:

	virtual ~JoiNumber() {}

	JoiNumber minimum(int value)
	{
		_min = value;
		return *this;
	}
	JoiNumber maximum(int value)
	{
		_max = value;
		return *this;
	}
	JoiNumber less(int value)
	{
		_less = value;
		return *this;
	}
	JoiNumber greater(int value)
	{
		_greater = value;
		return *this;
	}
	JoiNumber negative()
	{
		_negative = true;
		return *this;
	}
	JoiNumber positive()
	{
		_positive = true;
		return *this;
	}

	static JoiNumber build()
	{
		return JoiNumber();
	}
	static JoiResult validate(const int value, JoiNumber *schema)
	{
		// Validate _min
		if(schema->_min != INT_MAX && value < schema->_min)
			return JoiResult(true, "The number value must be at least " + std::to_string(schema->_min) + ". Value: [ " + std::to_string(value) + " ]");

		// Validate _max
		if(schema->_max != INT_MIN && value > schema->_max)
			return JoiResult(true, "The number value must be at most " + std::to_string(schema->_max) + ". Value: [ " + std::to_string(value) + " ]");

		// Validate _less
		if(schema->_less != INT_MIN && value >= schema->_less)
			return JoiResult(true, "The number value must lesser than " + std::to_string(schema->_less) + ". Value: [ " + std::to_string(value) + " ]");

		// Validate _greater
		if(schema->_greater != INT_MAX && value <= schema->_greater)
			return JoiResult(true, "The number value must greater than " + std::to_string(schema->_greater) + ". Value: [ " + std::to_string(value) + " ]");

		// Validate _negative
		if(schema->_negative && value >= 0)
			return JoiResult(true, "The number value must be negative. Value: [ " + std::to_string(value) + " ]");

		// Validate _positive
		if(schema->_positive && value < 0)
			return JoiResult(true, "The number value must be positive. Value: [ " + std::to_string(value) + " ]");

		// The number value is valid. 
		// Return NO ERROR flag.
		return JoiResult(false, "");
	}
};

class JoiString
{
private:
	bool _required; // Requires the string value to be non-empty.
	int _min; // Requires the string value to be at least _min characters long.
	int _max; // Requires the string value to be at most _max characters long.
	int _length; // Requires the string value to be at exactly _length characters long.
	string _regex; // Requires the string value to satisfies the regex expression.
	bool _alpha; // Requires the string value to only contain a-z, A-Z.
	bool _num; // Requires the string value to only contain 0-9.
	bool _alphanum; // Requires the string value to only contain a-z, A-Z, and 0-9.
	bool _ip; // Requires the string value to be a valid ip address v4.
	bool _lowercase; // Requires the string value to be all lowercase. 
	bool _uppercase; // Requires the string value to be all uppercase.

private:
	JoiString()
	{
		_required = false;
		_min = INT_MIN;
		_max = INT_MIN;
		_length = INT_MIN;
		_regex = "";
		_alpha = false;
		_num = false;
		_alphanum = false;
		_ip = false;
		_lowercase = false;
		_uppercase = false;
	}

public:
	virtual ~JoiString()
	{}

	JoiString required()
	{
		_required = true;
		return *this;
	}
	JoiString minimum(int value)
	{
		_min = value;
		return *this;
	}
	JoiString maximum(int value)
	{
		_max = value;
		return *this;
	}
	JoiString length(int value)
	{
		_length = value;
		return *this;
	}
	JoiString pattern(const std::string &regex)
	{
		_regex = regex;
		return *this;
	}
	JoiString alpha()
	{
		_alpha = true;
		return *this;
	}
	JoiString num()
	{
		_num = true;
		return *this;
	}
	JoiString alphanum()
	{
		_alphanum = true;
		return *this;
	}
	JoiString ip()
	{
		_ip = true;
		return *this;
	}
	JoiString lowercase()
	{
		_lowercase = true;
		return *this;
	}
	JoiString uppercase()
	{
		_uppercase = true;
		return *this;
	}

	// Builder Design Pattern
	static JoiString build()
	{
		return JoiString();
	}

	static JoiResult validate(const string &value, JoiString *schema)
	{
		// Validate _required
		if(schema->_required && schema->length(value, 1) == 0)
			return JoiResult(true, "The string value is required");


		// Validate _min
		if(schema->_min >= 0)
		{
			int len = schema->length(value, schema->_min);

			if(len < schema->_min)
				return JoiResult(true, "The string value must be at least " + std::to_string(schema->_min) + " characters long");
		}


		// Validate _max
		if(schema->_max > 0)
		{
			int len = schema->length(value, schema->_max + 1);

			if(len > schema->_max)
				return JoiResult(true, "The string value must be at most " + std::to_string(schema->_max) + " characters long");
		}


		// Validate _length
		if(schema->_length > 0)
		{
			int len = schema->length(value, schema->_length + 1);

			if(len != schema->_length)
				return JoiResult(true, "The string value must be " + std::to_string(schema->_length) + " characters long");
		}


		// Validate _regex
		if(schema->_regex.size())
		{
			std::regex validation(schema->_regex);

			if(!std::regex_match(value, validation))
				return JoiResult(true, "Regex validation failed");
		}

		// Validate _alpha
		if(schema->_alpha)
		{
			for(auto &c : value)
			{
				if(!isalpha(c))
					return JoiResult(true, "The string value can only contain a-z, A-Z.");
			}
		}

		// Validate _num
		if(schema->_num)
		{
			for(auto &c : value)
			{
				if(!isdigit(c))
					return JoiResult(true, "The string value can only contain 0-9.");
			}
		}

		// Validate _alphanum
		if(schema->_alphanum)
		{
			for(auto &c : value)
			{
				if(!isalnum(c))
					return JoiResult(true, "The string value can only contain a-z, A-Z, and 0-9.");
			}
		}

		// Validate _ip
		if(schema->_ip)
		{
			std::regex validation("^(?=\\d+\\.\\d+\\.\\d+\\.\\d+$)(?:(?:25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9][0-9]|[0-9])\\.?){4}$"); // IP v4 VALIDATION

			if(!std::regex_match(value, validation))
				return JoiResult(true, "IP validation failed");
		}

		// Validate _lowercase
		if(schema->_lowercase)
		{
			for(auto &c : value)
			{
				if(isalpha(c) && !islower(c))
					return JoiResult(true, "The string value can only contain lowercase characters.");
			}
		}

		// Validate _uppercase
		if(schema->_uppercase)
		{
			for(auto &c : value)
			{
				if(isalpha(c) && !isupper(c))
					return JoiResult(true, "The string value can only contain uppercase characters.");
			}
		}

		// The string is valid. 
		// Return NO ERROR flag.

		return JoiResult(false, "");
	}

private:
	int length(const string& value, int max) const
	{
		int len = 0;

		while(value[len] > 0 && len < max)
			len++;

		return len;
	}

};


#endif // JOI_H