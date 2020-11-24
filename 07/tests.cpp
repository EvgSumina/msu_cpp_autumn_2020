#include "Vector.hpp"
#include <vector>
#include <cassert>

int main()
{
	Vector<int> my_vector = {1, 1, 3};
	std::vector<int> vec = {1, 1, 3};
	
	assert (my_vector.size() == vec.size());

	for (size_t i = 0; i < vec.size(); i++) 
	{
		assert(vec[i] == my_vector[i]);
	}


	my_vector.pop_back();
	my_vector.push_back(1);
	vec.pop_back();
	vec.push_back(1);

	assert (my_vector.size() == vec.size());

	for (size_t i = 0; i < vec.size(); i++) 
	{
		assert(vec[i] == my_vector[i]);
	}

	for (auto i = my_vector.begin(); i != my_vector.end(); ++i) 
	{
		assert(*i == 1);
	}

	for (auto i = my_vector.rbegin(); i != my_vector.rend(); ++i) 
	{
		assert(*i == 1);
	}
	
	my_vector.clear(); 
	vec.clear();
	assert(my_vector.size() == vec.size());

	std::cout << "Success!!!" << std::endl;
	return 0;
}
