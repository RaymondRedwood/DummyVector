#include "global.h"


template <typename T> class DummyVector
{
private:
	T		*vector;
	__uint	vcount;
public:
	DummyVector();
	DummyVector(__uint initialcount);
	DummyVector(DummyVector &source);

	T& operator [](__uint index);
	DummyVector<T>& operator +(const DummyVector& rightpart);
	DummyVector<T>& subvector(__uint leftborder, __uint rightborder);
	bool find(T elem, __uint *retindex);
	__uint count();

	void add(T elem);
	void addhead(T elem);
	void insertat(T elem, __uint pos);

	void resize(__uint ncount);
	void removeat(__uint pos);
	void clear();

	~DummyVector();
};

template<typename T>
DummyVector<T>::DummyVector()
{
	this->vector = nullptr;
}

template<typename T>
DummyVector<T>::DummyVector(__uint initialcount)
{
	this->vector = nullptr;
	if (initialcount != 0) this->vector = new T[initialcount];
	this->vcount = initialcount;
}

template<typename T>
DummyVector<T>::DummyVector(DummyVector & source)
{
	this->vector = new T[source->count()];
	memcpy(this->vector, source->vector, sizeof(T) * source->count());
	this->vcount = source->count();
}

template<typename T>
T & DummyVector<T>::operator[](__uint index)
{
	return this->vector[index];
}

template<typename T>
DummyVector<T> & DummyVector<T>::operator+(const DummyVector & rightpart)
{
	DummyVector<T> *result = new DummyVector<T>(this->count + rightpart->count());
	memcpy(result->vector, this->vector, sizeof(T) * this->count());
	memcpy((result->vector) + (this->count - 1), rightpart->vector, sizeof(T) * rightpart->count());
	return result;
}

template<typename T>
DummyVector<T> & DummyVector<T>::subvector(__uint leftborder, __uint rightborder)
{
	DummyVector<T> *result = new DummyVector<T>((__uint)(abs(rightborder - leftborder)) + 1);
	memcpy(result->vector, this->vector + leftborder, (__uint)(abs(rightborder - leftborder)) + 1);
	return result;
}

template<typename T>
bool DummyVector<T>::find(T elem, __uint * retindex)
{
	for (__uint i = 0; i < this->vcount; ++i)
		if (this->vector[i] == elem)
		{
			(*retindex) = i;
			return true;
		}
	return false;
}

template<typename T>
__uint DummyVector<T>::count()
{
	return this->vcount;
}

template<typename T>
void DummyVector<T>::add(T elem)
{
	T *tmp = new T[this->vcount + 1];
	if (this->vector != nullptr)
		memcpy(tmp, this->vector, sizeof(T) * this->vcount);
	tmp[this->vcount] = elem;
	this->vcount++;
	if (this->vector != nullptr)
		delete[] this->vector;
	this->vector = tmp;
}

template<typename T>
void DummyVector<T>::addhead(T elem)
{
	T *tmp = new T[this->vcount + 1];
	if (this->vector != nullptr)
		memcpy(tmp + 1, this->vector, sizeof(T) * this->vcount);
	tmp[0] = elem;
	this->vcount++;
	if (this->vector != nullptr)
		delete[] this->vector;
	this->vector = tmp;
}

template<typename T>
void DummyVector<T>::insertat(T elem, __uint pos)
{
	switch (pos)
	{
	case 0: this->addhead(elem); break;
	case (this->vcount - 1): this->add(elem); break;
	default:
	{
		DummyVector<T> *tmp = this;
		DummyVector<T> *tmp2 = new DummyVector<T>(1);
		tmp2[0] = elem;
		this = (this->subvector(0, pos) + tmp2) + this->subvector(pos + 1, this->count() - 1);
		delete tmp2;
		delete tmp;
	} break;
	}
}

template<typename T>
void DummyVector<T>::resize(__uint ncount)
{
	if (ncount == 0)
	{
		delete[] this->vector;
		this->vcount = 0;
	}
	else
	{
		T *tmp = new T[ncount];
		if (ncount < this->vcount)
			memcpy(tmp, this->vector, sizeof(T) * ncount);
		else
		{
			memcpy(tmp, this->vector, sizeof(T) * this->vcount);
			if (ncount != this->vcount)
				memset(tmp + this->vcount + 1, 0, ncount - (this->vcount + 1));
		}
	}
}

template<typename T>
void DummyVector<T>::removeat(__uint pos)
{
	DummyVector<T> *tmp = this;
	this = (this->subvector(0, pos - 1) + this->subvector(pos + 1, this->count() - 1));
	delete tmp;
}

template<typename T>
void DummyVector<T>::clear()
{
	if (this->vector != nullptr)
		delete[] this->vector;
	this->vcount = 0;
}

template<typename T>
DummyVector<T>::~DummyVector()
{
	this->clear();
}