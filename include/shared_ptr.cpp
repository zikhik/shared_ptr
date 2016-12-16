#include <iostream>

template <typename T>
class shared_ptr{
public:
	shared_ptr(); /*noexcept*/
	shared_ptr(T* ptr); /*strong*/
	shared_ptr(shared_ptr const&); /*noexcept*/
	shared_ptr(shared_ptr&&); /*noexcept*/
	~shared_ptr(); /*noexcept*/
	auto operator = (shared_ptr const&)->shared_ptr&; /*noexcept*/
	auto operator = (shared_ptr&&)->shared_ptr&; /*noexcept*/
	auto swap(shared_ptr&) -> void; /*noexcept*/
	auto reset() -> void; /*noexcept*/
	auto get() const->T*; /*noexcept*/
	auto operator ->() const->T*; /*strong*/
	auto operator *() const->T&; /*strong*/
	auto countref() const->size_t; /*noexcept*/
private:
	T *ptr_;
	size_t *counter_;
};

template <typename T, class ...Args>
auto make_shared( Args && ...args ) -> shared_ptr<T>
{
    return shared_ptr<T>( new T( std::forward<Args>(args)... ) );
}


template <typename T>
shared_ptr<T>::shared_ptr() : ptr_(nullptr), counter_(nullptr) {}

template <typename T>
shared_ptr<T>::shared_ptr(T* ptr) : ptr_(ptr), counter_(new size_t(1)) {}

template <typename T>
shared_ptr<T>::shared_ptr(shared_ptr const& other) : ptr_(other.ptr_), counter_(other.counter_) 
{
	if(counter_ != nullptr) ++(*counter_);
}

template <typename T>
shared_ptr<T>::shared_ptr(shared_ptr&& other) : ptr_(other.ptr_), counter_(other.counter_)
{
	other.ptr_ = nullptr;
	other.counter_ = nullptr; 
}

template <typename T>
shared_ptr<T>::~shared_ptr()
{
	if (ptr_ != nullptr && counter_ != nullptr && --(*counter_) == 0)
	{
		delete ptr_;
		delete counter_;
	}
}

template <typename T>
auto shared_ptr<T>::operator = (shared_ptr const& other) -> shared_ptr&
{
	if (this != &other) (shared_ptr<T>(other)).swap(*this);
	return *this;
}

template <typename T>
auto shared_ptr<T>::operator = (shared_ptr&& other) -> shared_ptr&
{
	if (this != &other) {
		(shared_ptr(std::move(other))).swap(*this);
	}
	return *this;
}

template <typename T>
auto shared_ptr<T>::swap(shared_ptr& other) -> void
{
	std::swap(ptr_, other.ptr_);
	std::swap(counter_, other.counter_);
}

template <typename T>
auto shared_ptr<T>::reset() -> void
{
	this->swap(shared_ptr());
}

template <typename T>
auto shared_ptr<T>::get() const -> T*
{
	return ptr_;
}

template <typename T>
auto shared_ptr<T>::operator ->() const -> T*
{
	if (ptr_ != nullptr) return ptr_;
	else throw ("nullptr...");
}

template <typename T>
auto shared_ptr<T>::operator *() const -> T&
{
	if (ptr_ != nullptr) return *ptr_;
	else throw ("nullptr..");
}

template <typename T>
auto shared_ptr<T>::countref() const -> size_t
{
	if (counter_ != nullptr) return *counter_;
	else return 0;
}
