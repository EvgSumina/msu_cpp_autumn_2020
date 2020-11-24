#pragma once
#include <iostream>
#include <memory>

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

	template <class... Args>
	void construct(T *ptr, Args &&... args)
	{
		new (ptr) T(std::forward<Args>(args)...);
	}

	void destroy(T *ptr)
	{
		ptr -> ~T();
	}
};


template <class T>
class Iterator: public std::iterator<std::random_access_iterator_tag, T>
{
	T* ptr_;
public:

	Iterator(T* ptr) : 
		ptr_(ptr)
	{ 
	};

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

	Vector(const Vector<T>& other): allocator_(), ptr_(allocator_.allocate(other.size_)), capacity_(other.size_)
	{
		for (size_ = 0; size_ < other.size_; ++size_) 
		{
			allocator_.construct(ptr_ + size_, other.ptr_[size_]);
		}
	}

	Vector(): allocator_(), ptr_(nullptr), size_(0), capacity_(0)
	{}

	Vector(std::initializer_list<T> init): allocator_(), ptr_(allocator_.allocate(init.size())), size_(0), capacity_(init.size())
	{
		for (const T& value: init) 
		{
			allocator_.construct(ptr_ + size_++, std::move(value));
		}
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

	void push_back(const T& value) 
	{
		if (size_ >= capacity_)
		{
			reserve(size_ * 2);
		}
		allocator_.construct(ptr_ + size_++, value);
	}

	void push_back(T&& value)
	{
		if (size_ >= capacity_)
		{
			reserve(size_ * 2);
		}
		ptr_[size_++] = std::move(value);
    }


	void pop_back() 
	{
		if (size_ == 0)
			throw(std::runtime_error("Empty vector"));
		allocator_.destroy(ptr_ + --size_);
	}

	bool empty() const 
	{
		return size_ == 0;
	}

	size_t size() const
	{
		return size_;
	}

	void clear()
	{
		for (; size_ > 0;)
		{
			allocator_.destroy(ptr_ + --size_);
		}
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
		if (new_size < size_)
		{
			for (size_t i = new_size; i < size_; ++i)
				allocator_.destroy(ptr_ + i);
		}
		else if (new_size > size_)
		{
			reserve(new_size);
			for (size_t i = size_; i < new_size; ++i)
				allocator_.construct(ptr_ + i);
		}
		size_ = new_size;
	}

	void reserve(size_t new_capacity)
	{
		if (new_capacity > capacity_)
		{
			T* tmp = allocator_.allocate(new_capacity);
			for (size_t i = 0; i < size_; ++i)
				allocator_.construct(tmp + i, ptr_[i]);
			for (size_t i = 0; i < size_; ++i)
				allocator_.destroy(ptr_ + i);
			allocator_.deallocate(ptr_, capacity_);
			ptr_ = tmp;
			capacity_ = new_capacity;
		}
	}

	size_t capacity() const
	{
		return capacity_;
	}

	~Vector()
	{
		for (size_t i = 0; i < size_; ++i)
		{
			allocator_.destroy(ptr_ + i);
		}
		allocator_.deallocate(ptr_, capacity_);
	}

private:
	Alloc allocator_;
	T *ptr_;
	size_t size_;
	size_t capacity_;
};
	
