#include <iostream>
#include <string>
#include "Joi.hpp"

using namespace std;

int main()
{
	string input;

	cout << "Digite seu nome: ";
	cin >> input;

	JoiString schema = JoiString::build().alphanum().maximum(32).required();
	JoiResult result = JoiString::validate(input, &schema);

	if(result.error())
		cout << result.description() << endl;
	else
		cout << "Nome valido ;)" << endl;

    return 0;
}