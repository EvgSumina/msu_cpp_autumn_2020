#pragma once
#include <iostream>
#include <memory>
#include <initializer_list>

template <class T>
class Allocator
{
public:

	T* allocate(size_t count)
	{
		T* allocator_data = static_cast <T*> (operator new[] (count* sizeof(T)));
		return allocator_data;
	}

	void deallocate(T* pointer, size_t count)
	{
		delete[] (pointer);
	}
};


template <class T>
class Iterator: public std::iterator<std::random_access_iterator_tag, T>
{
	T* ptr_;
public:

	Iterator(T* ptr): ptr_(ptr) {};

	bool operator==(const Iterator<T>& other) 
	{
		return ptr_ == other.ptr_;
	}

	bool operator!=(const Iterator<T>& other) 
	{
		return !(*this == other);
	}

	bool operator<(const Iterator<T>& other) 
	{
		return ptr_ < other.ptr_;
	}

	bool operator<=(const Iterator<T>& other) 
	{
		return ptr_ <= other.ptr_;
	}

	bool operator>(const Iterator<T>& other) 
	{
		return !(*this <= other);
	}

	bool operator>=(const Iterator<T>& other) 
	{
		return !(*this < other);
	}

	Iterator<T>& operator++() 
	{
		++ptr_;
		return *this;
	}

	Iterator<T>& operator--()
	{
		--ptr_;
		return *this;
	}

	Iterator<T> operator+(size_t n) const 
	{
		return Iterator(ptr_ + n);
	}

	Iterator<T> operator-(size_t  n) const 
	{
		return Iterator(ptr_ - n);
	}

	Iterator<T>& operator+=(size_t n)
	{
		ptr_ += n;
		return *this;
	}

	Iterator<T>& operator-=(size_t n) 
	{
		ptr_ -= n;
		return *this;
	}

	T& operator*() 
	{
		return *ptr_;
	}

	T& operator[](size_t i) const
	{
		return ptr_[i];
	}
};


template <class T, class Alloc = Allocator<T> >
class Vector
{
public:

	Vector(): allocator_(), ptr_(allocator_.allocate(1)), size_(0), capacity_(1)
	{}

	Vector(const Vector<T>& other): allocator_(), size_(other.size_), capacity_(other.capacity_)
	{
		ptr_ = allocator_.allocate(other.capacity_);
		std::copy(other.ptr_, other.ptr_ + capacity_, ptr_);
	}

	Vector(Vector&& other): size_(other.size()), capacity_(other.capacity()) 
	{
		ptr_ = other.ptr_;
		other.ptr_ = nullptr;
		other.capacity_ = 0;
		other.size_ = 0;
	}

	Vector& operator=(const Vector& other) 
	{
		if (this == &other)
			return *this;
		if (ptr_)
		{
			allocator_.deallocate(ptr_, capacity_);
		}
		size_ = other.size();
		capacity_ = other.capacity();
		ptr_ = allocator_.allocate(capacity_);
		std::copy(other.ptr_, other.ptr_ + capacity_, ptr_);
		return *this;
	}

	Vector& operator=(Vector&& other) 
	{
		if (this == &other)
			return *this;
		ptr_ = other.ptr_;
		size_ = std::move(other.size_);
		capacity_ = std::move(other.capacity_);
		other.ptr_ = nullptr;
		other.size_ = 0;
		other.capacity_ = 0;
		return *this;
	}

	T& operator[](size_t i)
	{
		if (i < size_)
		{
			return ptr_[i];
		}
		else
		{
			throw std::out_of_range("Error");
		}
	}

	const T& operator[](size_t i) const
	{
		if (i < size_)
		{
			return ptr_[i];
		}
		else
		{
			throw std::out_of_range("Error");
		}
	}

	template <class... ArgsT>
	void emplace_back(ArgsT&& ... args)
	{
		this->push_back(T(std::forward<ArgsT>(args)...));
	}

	void push_back(T&& value)
	{
		if (size_ == capacity_)
		{
			this -> reserve(size_ * 2);
		}
		ptr_[size_++] = value;
	}

	void pop_back() 
	{
		if (size_ == 0)
		{
			throw(std::runtime_error("Empty vector"));
		}
		size_--;
	}

	bool empty() const 
	{
		return size_ == 0;
	}

	size_t size() const
	{
		return size_;
	}

	size_t capacity() const
	{
		return capacity_;
	}

	void clear()
	{
		size_ = 0;
	}

	Iterator<T> begin()
	{
		return Iterator<T>(ptr_);
	}

	std::reverse_iterator<Iterator<T>> rbegin()
	{
		return std::reverse_iterator<Iterator<T>>(end());
	}

	Iterator<T> end()
	{
		return Iterator<T>(ptr_ + size_);
	}

	std::reverse_iterator<Iterator<T>> rend()
	{
		return std::reverse_iterator<Iterator<T>>(begin());
	}

	void resize(size_t new_size)
	{
		if (new_size > size_)
		{
			this  -> reserve(new_size);
		}
		size_ = new_size;
	}

	void reserve(size_t new_capacity)
	{
		if (new_capacity > capacity_)
		{
			T* tmp = allocator_.allocate(new_capacity);
			if (ptr_)
			{
				for (size_t i = 0; i < size_; ++i)
					tmp[i] = ptr_[i];
				allocator_.deallocate(ptr_, capacity_);
			}
			ptr_ = tmp;
			capacity_ = new_capacity;
		}
	}

	~Vector()
	{
		if (ptr_)
			allocator_.deallocate(ptr_, capacity_);
	}

private:
	Alloc allocator_;
	T *ptr_;
	size_t size_;
	size_t capacity_;
};
	
