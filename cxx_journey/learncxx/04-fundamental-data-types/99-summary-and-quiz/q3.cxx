//**********
// Includes
//**********
#include <iostream>
#include <cmath>

//***********
// Constants
//***********
static const int total_seconds {5};
static const double gravity {9.8f};

//************************
// Functions declarations
//************************
double get_value();
double calculate_current_distance(double gravity, int seconds);

//***************
// Main Function
//***************
int main(int argc, char** argv)
{
	std::cout << "Hello, s.4.x.q3" << std::endl;
	double initial_height {get_value()};
	double current_height;
	for(size_t i{0}; i <= total_seconds; i++)
	{
		current_height = initial_height - calculate_current_distance(gravity, i);
		if(current_height < 0.f)
			current_height = 0.f;

		std::cout << "Height at "<< i << " sec: " << current_height << std::endl;
	}

	return 0;
}

double get_value()
{
	double height{0.f};
	std::cout << "Enter height > ";
	std::cin >> height;
	return height;
}

double calculate_current_distance(double gravity, int seconds)
{
	return (gravity * std::pow(seconds, 2))/2;
}
