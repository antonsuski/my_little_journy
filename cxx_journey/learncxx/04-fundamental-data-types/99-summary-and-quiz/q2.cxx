//******************
// Headers includes
//******************
#include <iostream>

//*******************
// Data declarations
//*******************

//******************************
// Static function declarations
//******************************
static double get_value_from_user();
static char get_operation_from_user();
static bool handle_user_imput(double& lhs, double& rhs, char& operation);
static double process(const double& lhs, const double& rhs, const char& operation);

//***************
// Main programm
//***************
int main(int argc, char** argv)
{
	double lhs{0};
	double rhs{0};
	char operation{' '};

	std::cout << "Hello, s4.x.q2" << std::endl;
	if(!handle_user_imput(lhs, rhs, operation))
	{
		return 1;
	}
	std::cout << lhs << " " << operation << " " << rhs << " is " << process(lhs, rhs, operation) << std::endl;
	return 0;
}

double get_value_from_user()
{
	double value;
	std::cout << "Please enter your double value > ";
	std::cin >> value;
	return value;
}

char get_operation_from_user()
{
	char operation;
	std::cout << "Please enter op: +, -, *, / > ";
	std::cin >> operation;
	return operation;
}

bool handle_user_imput(double& lhs, double& rhs, char& operation)
{
	bool result {false};
	lhs = get_value_from_user();
	rhs = get_value_from_user();
	operation = get_operation_from_user();

	switch(operation)
	{
		case '/' :
		{
			if(rhs == 0.f)
			{
				result = false;
				break;
			}
		}
		case '*' :
		case '-' :
		case '+' :
		{
			result = true;
		} break;
		default:
			break;
	}

	return result;
}

double process(const double& lhs, const double& rhs, const char& operation)
{
	switch(operation)
	{
		case '/' : return lhs / rhs;
		case '*' : return lhs * rhs;
		case '-' : return lhs - rhs;
		case '+' : return lhs + rhs;
		default : return lhs + rhs;
	}
}

