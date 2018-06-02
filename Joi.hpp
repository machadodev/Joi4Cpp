#ifndef JOI_H
#define JOI_H

// Includes
#include <vector>
#include <regex>
#include <string>
#include <tuple>
#include <ctype.h>


// Result of validations
class JoiResult
{
private:
	bool _error;
	std::string _description;

public:
	// Constructor
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

	// Destructor
	virtual ~JoiResult() {}

	// Setter
	void error(bool value)
	{
		_error = value;
	}
	void description(const std::string &desc)
	{
		_description = desc;
	}

	// Getter
	bool error() const
	{
		return _error;
	}
	std::string description() const
	{
		return _description;
	}
};

// Validate Integer Numbers
class JoiNumber
{
private:
	// C++ 11 struct initialization 	
	struct Number
	{
		bool flag = false;
		int value = 0;
	};

	// C++ 11 struct initialization 	
	struct NumberList
	{
		bool flag = false;
		std::vector<int> values;
	};

	Number _min; // Specifies the minimum value where _min.value is the minimum value allowed.
	Number _max; // Specifies the maximum value where _max is the maximum value allowed.
	NumberList _disallow; // Specifies the invalids input.
	NumberList _allow; // Specifies the valids input.
	Number _less; // Specifies that the value must be less than _less.
	Number _greater; // Specifies that the value must be greater than _greater.
	Number _negative; // Requires the number to be negative.
	Number _positive; // Requires the number to be positive.

private:
	// Private Constructor to prevent instance creation
	// JoiNumber must be created with JoiNumber::build() method.
	JoiNumber() {}

public:
	// Destructor
	virtual ~JoiNumber() {}

	// Setters
	JoiNumber minimum(const int &value)
	{
		_min.flag = true;
		_min.value = value;

		return *this;
	}
	JoiNumber maximum(const int &value)
	{
		_max.flag = true;
		_max.value = value;
		return *this;
	}
	template<typename ...Ints>
	JoiNumber disallow(Ints... ints)
	{
		_disallow.flag = true;

		int args[]{ ints... };

		for(auto &v : args)
			_disallow.values.push_back(v);

		return *this;
	}
	template<typename ...Ints>
	JoiNumber allow(Ints... ints)
	{
		_allow.flag = true;

		int args[]{ ints... };

		for(auto &v : args)
			_allow.values.push_back(v);

		return *this;
	}
	JoiNumber less(const int &value)
	{
		_less.flag = true;
		_less.value = value;
		return *this;
	}
	JoiNumber greater(const int &value)
	{
		_greater.flag = true;
		_greater.value = value;
		return *this;
	}
	JoiNumber negative()
	{
		_negative.flag = true;
		return *this;
	}
	JoiNumber positive()
	{
		_positive.flag = true;
		return *this;
	}

	// Builder Design Pattern -  Instance Creator
	static JoiNumber build()
	{
		return JoiNumber();
	}

	JoiResult validate(const int &value) const
	{
		// Validate _min
		if(_min.flag)
		{
			if(value < _min.value)
			{
				return JoiResult(true, "The number must be at least " + std::to_string(_min.value) + ". Number: [ " + std::to_string(value) + " ]");
			}
		}

		// Validate _max
		if(_max.flag)
		{
			if(value > _max.value)
			{
				return JoiResult(true, "The number must be at most " + std::to_string(_max.value) + ". Number: [ " + std::to_string(value) + " ]");
			}
		}

		// Validate _disallow
		if(_disallow.flag)
		{
			if(std::find(_disallow.values.begin(), _disallow.values.end(), value) != _disallow.values.end())
				return JoiResult(true, "The number [" + std::to_string(value) + "] is in the blacklist.");
		}

		// Validate _allow
		if(_allow.flag)
		{
			if(std::find(_allow.values.begin(), _allow.values.end(), value) == _allow.values.end())
				return JoiResult(true, "The number [" + std::to_string(value) + "] isn't in the whitelist.");
		}

		// Validate _less
		if(_less.flag)
		{
			if(value >= _less.value)
			{
				return JoiResult(true, "The number must be less than " + std::to_string(_less.value) + ". Value: [ " + std::to_string(value) + " ]");
			}
		}

		// Validate _greater
		if(_greater.flag)
		{
			if(value <= _greater.value)
			{
				return JoiResult(true, "The number must be greater than " + std::to_string(_greater.value) + ". Value: [ " + std::to_string(value) + " ]");
			}
		}

		// Validate _negative
		if(_negative.flag && value >= 0)
		{
			return JoiResult(true, "The number must be negative. Value: [ " + std::to_string(value) + " ]");
		}

		// Validate _positive
		if(_positive.flag && value < 0)
		{
			return JoiResult(true, "The number must be positive. Value: [ " + std::to_string(value) + " ]");
		}

		// The number value is valid. 
		// Return NO ERROR flag.
		return JoiResult(false, "");
	}
};

// Validate Strings
class JoiString
{
private:
	bool _required; // Requires the string to be non-empty.
	int _min; // Requires the string to be at least _min characters long. >=
	int _max; // Requires the string to be at most _max characters long. <=
	int _length; // Requires the string to be at exactly _length characters long. ==
	std::string _regex; // Requires the string to satisfies the regex expression.
	bool _alpha; // Requires the string to only contain a-z, A-Z.
	bool _num; // Requires the string to only contain 0-9.
	bool _alphanum; // Requires the string to only contain a-z, A-Z, and 0-9.
	bool _ip; // Requires the string to be a valid ip address v4.
	bool _lowercase; // Requires the string to be all lowercase. 
	bool _uppercase; // Requires the string to be all uppercase.

private:
	// Private Constructor to prevent instance creation
	// JoiString must be created with JoiString::build() method.
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
	// Destructor
	virtual ~JoiString()
	{}

	// Setters
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

	// Builder Design Pattern -  Instance Creator
	static JoiString build()
	{
		return JoiString();
	}

	JoiResult validate(const std::string &value) const
	{
		// Validate _required
		if(_required && length(value, 1) == 0)
		{
			return JoiResult(true, "The string is required");
		}

		// Validate _min
		if(_min >= 0)
		{
			int len = length(value, _min);

			if(len < _min)
			{
				if(_required)
					return JoiResult(true, "The string must be at least " + std::to_string(_min) + " characters long");
			}
		}


		// Validate _max
		if(_max > 0)
		{
			int len = length(value, _max + 1);

			if(len > _max)
			{
				return JoiResult(true, "The string value be at most " + std::to_string(_max) + " characters long");
			}
		}


		// Validate _length
		if(_length > 0)
		{
			int len = length(value, _length + 1);

			if(len != _length)
			{
				if(_required)
					return JoiResult(true, "The string value must be " + std::to_string(_length) + " characters long");
			}
		}


		// Validate _regex
		if(_regex.size())
		{
			std::regex validation(_regex);

			if(!std::regex_match(value, validation))
			{
				if(_required)
					return JoiResult(true, "Regex validation failed");
			}
		}

		// Validate _alpha
		if(_alpha)
		{
			for(auto &c : value)
			{
				if(!isalpha(c))
				{
					return JoiResult(true, "The string value can only contain a-z, A-Z.");
				}
			}
		}

		// Validate _num
		if(_num)
		{
			for(auto &c : value)
			{
				if(!isdigit(c))
				{
					return JoiResult(true, "The string value can only contain 0-9.");
				}
			}
		}

		// Validate _alphanum
		if(_alphanum)
		{
			for(auto &c : value)
			{
				if(!isalnum(c))
				{
					return JoiResult(true, "The string value can only contain a-z, A-Z, and 0-9.");
				}
			}
		}

		// Validate _ip
		if(_ip)
		{
			std::regex validation("^(?=\\d+\\.\\d+\\.\\d+\\.\\d+$)(?:(?:25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9][0-9]|[0-9])\\.?){4}$"); // IP v4 VALIDATION

			if(!std::regex_match(value, validation))
			{
				if(_required)
					return JoiResult(true, "IP validation failed");
			}
		}

		// Validate _lowercase
		if(_lowercase)
		{
			for(auto &c : value)
			{
				if(isalpha(c) && !islower(c))
				{
					return JoiResult(true, "The string value can only contain lowercase characters.");
				}
			}
		}

		// Validate _uppercase
		if(_uppercase)
		{
			for(auto &c : value)
			{
				if(isalpha(c) && !isupper(c))
				{
					return JoiResult(true, "The string value can only contain uppercase characters.");
				}
			}
		}

		// The string is valid. 
		// Return NO ERROR flag.

		return JoiResult(false, "");
	}

private:
	// Helper functions
	int length(const std::string& value, int max) const
	{
		int len = 0;

		while(value[len] > 0 && len < max)
		{
			len++;
		}

		return len;
	}
};

// Wrapper Class
class Joi
{
public:
	template <typename T>
	static JoiResult validate(T param)
	{
		return std::get<1>(param).validate(std::get<0>(param));
	}

	template <typename T, typename... Params>
	static JoiResult validate(T param, Params... params)
	{
		JoiResult result = Joi::validate(param);

		if(result.error())
			return result;

		return Joi::validate(params...);
	}

	template <typename T1, typename T2>
	static std::tuple<T1, T2> key(T1 arg1, T2 arg2)
	{
		return std::make_tuple(arg1, arg2);
	}
};

#endif // JOI_H