#include "Vector.hpp"
#include <vector>
#include <cassert>

int main()
{
	Vector<int> my_vector;
	Vector<int> vector;

	for (int i = 0; i < 3; i++)
	{
		my_vector.push_back(1);
		vector.push_back(1);
	}
	my_vector.push_back(3);
	vector.push_back(3);
	
	assert (my_vector.size() == vector.size());
	for (size_t i = 0; i < vector.size(); i++) 
	{
		assert(vector[i] == my_vector[i]);
	}

	my_vector.pop_back();
	my_vector.push_back(1);
	vector.pop_back();
	vector.push_back(1);

	assert (my_vector.size() == vector.size());

	for (size_t i = 0; i < vector.size(); i++) 
	{
		assert(vector[i] == my_vector[i]);
	}

	for (auto i = my_vector.begin(); i != my_vector.end(); ++i) 
	{
		assert(*i == 1);
	}

	for (auto i = my_vector.rbegin(); i != my_vector.rend(); ++i) 
	{
		assert(*i == 1);
	}

	Vector <int> first_vec = my_vector;
	assert(first_vec.size() == my_vector.size());
	assert(first_vec.capacity() == my_vector.capacity());
	for (int i = 0; i < 3; i++)
	{
		assert(first_vec[i] == my_vector[i]);
	}
	
	Vector <int> second_vec;
	second_vec = my_vector;
	assert(second_vec.size() == my_vector.size());
	assert(second_vec.capacity() == my_vector.capacity());
	for (int i = 0; i < 3; i++)
	{
		assert(my_vector[i] == second_vec[i]);
	}
	
	my_vector.clear(); 
	vector.clear();
	assert(my_vector.size() == vector.size());

	std::cout << "Success!!!" << std::endl;
	return 0;
}
