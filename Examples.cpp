#include <iostream>
#include "Joi.hpp"

using namespace std;

int main()
{
	struct Model
	{
		int id = 10;
		char name[32] = { "Leonardo" };
		int age = 18;
		char email[50] = { "leonardo@gmail.com" };
	} model;

	struct Schema
	{
		JoiNumber id = JoiNumber::build().positive().less(100);
		JoiString name = JoiString::build().pattern("[A-Z][a-z]+").maximum(31).required();
		JoiNumber age = JoiNumber::build().minimum(18).maximum(65);
		JoiString email = JoiString::build().pattern("^\\S+@\\S+$").maximum(49);
		JoiString test = JoiString::build().alphanum().minimum(49).required();
	} schema;


	JoiResult validation = Joi::validate(Joi::key(model.id, schema.id),
										 Joi::key(model.name, schema.name),
										 Joi::key(model.age, schema.age));

	if(validation.error())
		cout << validation.description() << endl;
	else
		cout << "All good ~;)" << endl;

	return 0;
}