#include <iostream>
#include <string>
#include <string_view>

static std::string get_user_name(std::string_view person_num);

static unsigned int get_user_age(std::string_view person_name);

void print_name_age(std::string_view name, unsigned int age)
{
	std::cout << name << "(age " << age << ")";
}

int main(int, char**)
{
	std::cout << "Hello, world" << std::endl;
	std::string first_person_name {get_user_name("#1")};
	unsigned int first_person_age {get_user_age(first_person_name)};
	std::string second_person_name {get_user_name("#2")};
	unsigned int second_person_age {get_user_age(second_person_name)};

	std::cout << "n1::" << first_person_name << "a1::" << first_person_age << std::endl;
	std::cout << "n2::" << second_person_name << "a2::" << second_person_age << std::endl;

	if(first_person_age > second_person_age)
	{
		print_name_age(first_person_name, first_person_age);
		std::cout << " is older than ";
		print_name_age(second_person_name, second_person_age);
		std::cout << std::endl;
	}
	else if(first_person_age < second_person_age)
	{
		print_name_age(second_person_name, second_person_age);
		std::cout << " is older than ";
		print_name_age(first_person_name, first_person_age);
		std::cout << std::endl;
	}
	else if(first_person_age == second_person_age)
	{
		print_name_age(first_person_name, first_person_age);
		std::cout << " is equal to ";
		print_name_age(second_person_name, second_person_age);
		std::cout << std::endl;
	}

	return 0;
}

std::string get_user_name(std::string_view person_num)
{
	std::string result;
	std::cout << "Enter the name of person " << person_num << ": ";
	std::getline(std::cin >> std::ws, result);
	return result;
}

unsigned int get_user_age(std::string_view person_name)
{
	unsigned int age {};
	std::cout << "Enter the age of " << person_name << ": ";
	std::cin >> age;
	return age;
}
