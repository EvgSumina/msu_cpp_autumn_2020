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
		if (allocator_data == nullptr) 
		{
			throw std::bad_alloc();
		}
		return allocator_data;
	}

	void deallocate(T* pointer, size_t count) noexcept
	{
		delete[] (pointer);
	}

	template <class... Args>
	void construct(T *ptr, Args &&... args)
	{
		new (ptr) T(std::forward<Args>(args)...);
	}

	void destroy(T *ptr) noexcept
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
	Alloc allocator_;
	T *ptr_;
	size_t size_;
	size_t capacity_;

public:
	Vector(): allocator_(), ptr_{allocator_.allocate(5)}, capacity_(5), size_(0)
	{
	};

	Vector(const Vector<T>& other): allocator_(), 
									ptr_(allocator_.allocate(other.size_)), 
									capacity_(other.size_)
	{
		for (size_ = 0; size_ < other.size_; ++size_) 
		{
			allocator_.construct(ptr_ + size_, other.ptr_[size_]);
		}
	}

	Vector(std::initializer_list<T> init): allocator_(), 
										ptr_(allocator_.allocate(init.size())), 
										size_{0}, capacity_{init.size()}
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

	template <class... Args>
 	T& emplace_back(Args &&... args) 
	{
		if (size_ >= capacity_) 
		{
			reserve(size_ * 2);
  		}
		auto new_ptr = new (ptr_ + size_) T(std::move(args)...);
  		++size_;
  		return *new_ptr;
	}

	void push_back(const T& value) 
	{
		if (size_ >= capacity_)
		{
			reserve(size_ * 2);
		}
		allocator_.construct(ptr_ + size_++, value);
	}


	void pop_back() 
	{
		if (size_ == 0)
			throw(std::runtime_error("Empty vector"));
		allocator_.destroy(ptr_ + --size_);
	}

	bool empty() const noexcept 
	{
		return size_ == 0;
	}

	size_t size() const noexcept 
	{
		return size_;
	}

	void clear() noexcept 
	{
		for (; size_ > 0;)
		{
			allocator_.destroy(ptr_ + --size_);
		}
	}

	Iterator<T> begin() noexcept
	{
		return Iterator<T>(ptr_);
	}

	std::reverse_iterator<Iterator<T>> rbegin() noexcept
	{
		return std::reverse_iterator<Iterator<T>>(end());
	}

	Iterator<T> end() noexcept
	{
		return Iterator<T>(ptr_ + size_);
	}

	std::reverse_iterator<Iterator<T>> rend() noexcept
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
};
	
