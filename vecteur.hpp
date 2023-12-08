#pragma once
#include <iostream>
#include <cassert>
#include <new>

using namespace std;
 
template <class TYPE>
class vecteur {
	private:
		TYPE* _tab;
		int _dim;

	public:
		vecteur();
		vecteur(int dim);
		~vecteur();

		vecteur(const vecteur& v1);
		void push_back(TYPE num);
		int size()const;
		void resize(int newdim);
		void print(std::ostream& output)const;
		int& at(int index);
		int& at(int index)const;
		void clear();
		void reverse();
		void reverseRecursive(int = 0);

		template <class T>
		friend void swap(vecteur<T>& v1, vecteur<T>& v2);

		const vecteur& operator=(const vecteur& vectDroite);
		vecteur operator+(const vecteur& vect)const;
		const vecteur& operator+=(const vecteur& vect);
		const bool operator==(const vecteur& vect)const;
		TYPE operator[](int index)const;
		
		// Ajoutez des méthodes ici au fur et à mesure que
		// vous avancez votre laboratoire sur le vecteur.
};

template <class TYPE>
std::ostream& operator <<(std::ostream& output, const vecteur<TYPE>& vect);

template <class TYPE>
vecteur<TYPE>::vecteur()
{
	_tab = nullptr;
	_dim = 0;
}

template <class TYPE>
vecteur<TYPE>::vecteur(int dim)
{
	assert(dim >= 0);

	if (dim == 0)
	{
		_dim = dim;
		_tab = nullptr;
	}

	else
	{
		try
		{
			_tab = new int[dim];
			_dim = dim;
		}
		catch (bad_alloc)
		{
			exit(EXIT_FAILURE);
		}
	}

}

template <class TYPE>
vecteur<TYPE>::~vecteur() //pourrait être la méthode clear et le destructeur appelerais la méthode clear
{
	clear();
}

template <class TYPE>
vecteur<TYPE>::vecteur(const vecteur& v1)
{
	if (v1._dim == 0)
	{
		_tab = nullptr;
		_dim = 0;
	}
	else
	{
		_dim = v1._dim;
		_tab = new TYPE[v1._dim];

		for (int i = 0; i < _dim; i++)
		{
			*(_tab + i) = *(v1._tab + i);
		}
	}
}

template <class TYPE>
void vecteur<TYPE>::push_back(TYPE num)
{
	_dim = _dim + 1;
	TYPE* newTab = new TYPE[_dim];

	for (int i = 0; i < _dim - 1; i++)
	{
		*(newTab + i) = *(_tab + i);
	}

	*(newTab + _dim - 1) = num;

	delete[] _tab;

	_tab = newTab;
}

template <class TYPE>
int vecteur<TYPE>::size() const
{
	return _dim;
}

template <class TYPE>
void vecteur<TYPE>::resize(int newdim)
{
	assert(newdim >= 0);//cas 2

	if (newdim == _dim) //cas 1
	{
		return;
	}

	if (newdim == 0) //cas 5
	{
		clear();
	}

	else //cas 4,6,7
	{
		TYPE* newtab = new int[newdim];
		for (int i = 0; (i < _dim && i < newdim); i++)
		{
			*(newtab + i) = *(_tab + i);
		}

		delete[] _tab;
		_tab = newtab;
		_dim = newdim;
	}
}

template <class TYPE>
void vecteur<TYPE>::print(std::ostream& output) const
{
	for (int i = 0; i < _dim; i++)
	{
		output << *(_tab + i) << " ";
	}
}

template <class TYPE>
int& vecteur<TYPE>::at(int index)
{
	assert(index >= 0 && index < _dim);
	return *(_tab + index);
}

template <class TYPE>
int& vecteur<TYPE>::at(int index)const
{
	assert(index >= 0 && index < _dim);
	return *(_tab + index);
}

template <class TYPE>
void vecteur<TYPE>::clear()
{
	delete[] _tab;
	_tab = nullptr;
	_dim = 0;
}

template <class TYPE>
const vecteur<TYPE>& vecteur<TYPE>:: operator=(const vecteur& vect)
{
	if (this == &vect)
	{
		return *this;
	}

	clear();

	_tab = new TYPE[vect._dim];
	_dim = vect._dim;

	for (int i = 0; i < _dim; i++)
	{
		*(_tab + i) = *(vect._tab + i);
	}
	return *this;
}

template <class TYPE>
void vecteur<TYPE>::reverse()
{
	int tempVal;

	for (int i = 0; i < _dim / 2; i++)
	{

		tempVal = *(_tab + _dim - 1 - i);
		*(_tab + _dim - 1 - i) = *(_tab + i);
		*(_tab + i) = tempVal;
	}
}

template <class TYPE>
void vecteur<TYPE>::reverseRecursive(int i)
{
	assert(i >= 0);
	int tempVal;

	if (i < _dim / 2)
	{
		tempVal = *(_tab + _dim - 1 - i);
		*(_tab + _dim - 1 - i) = *(_tab + i);
		*(_tab + i) = tempVal;
		reverseRecursive(i + 1);
	}
}

template <class TYPE>
void swap(vecteur<TYPE>& v1, vecteur<TYPE>& v2)
{
	TYPE* tempTab = v1._tab;
	int tempDim = v1._dim;
	v1._tab = v2._tab;
	v1._dim = v2._dim;
	v2._tab = tempTab;
	v2._dim = tempDim;
}

template <class TYPE>
vecteur<TYPE> vecteur<TYPE>:: operator+(const vecteur& vect)const
{
	vecteur newVect(_dim + vect._dim);

	for (int i = 0; i < newVect._dim; i++)
	{
		if (i < _dim)
		{
			*(newVect._tab + i) = *(_tab + i);
		}
		else
		{
			*(newVect._tab + i) = *(vect._tab + i - _dim);
		}
	}

	return newVect;
}

template <class TYPE>
const vecteur<TYPE>& vecteur<TYPE>:: operator+=(const vecteur& vect)
{
	*this = operator+(vect);

	return *this;
}

template <class TYPE>
const bool vecteur<TYPE>:: operator==(const vecteur& vect)const
{
	if (_dim != vect._dim)
	{
		return false;
	}

	for (int i = 0; i < vect._dim; i++)
	{
		if (*(vect._tab + i) != *(_tab + i))
		{
			return false;
		}
	}

	return true;
}

template <class TYPE>
TYPE vecteur<TYPE>::operator[](int index) const
{
	return this->at(index);
}

template <class TYPE>
std::ostream& operator<<(std::ostream& output, const vecteur<TYPE>& vect)
{
	vect.print(output);
	return output;
}