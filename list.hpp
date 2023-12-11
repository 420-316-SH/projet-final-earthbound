#pragma once
#include <cassert>

template <typename T>
class List;

// Classe d'une cellule. La liste est compos�e de plusieurs de ces cellules
template <typename T>
class Cellule {
	private:
		T _element; // Contenu d'une cellule de la liste
		Cellule<T>* _next; // Pointeur vers la cellule suivante de la liste
		Cellule<T>* _prev; // Pointeur vers la cellule pr�c�dente de la liste

		// Constructeur d'une cellule (m�thode appel�e � chaque fois qu'on fait un "new Cellule")
		Cellule(const T& element, Cellule<T>* next = nullptr, Cellule<T>* prev = nullptr) {
			_element = element;
			_next = next;
			_prev = prev;
		}

		friend class List<T>; /* La classe "List" a acc�s � la repr�sentation de la cellule bien que la classe
								 "Cellule" ait �t� d�clar�e � l'ext�rieur de la classe "List". */
};

template <typename T>
class List {
	private:
		Cellule<T>* _first; // Pointe sur la premi�re cellule de la liste

		//List(const List<T>&); // Copieur (pour le d�sactiver, il faut le placer dans la section "private")

	public:
		// Classe d'un it�rateur d'une liste (un it�rateur doit �tre associ� � une liste pour pointer une de ses cellules).
		class Iterator {
			private:
				Cellule<T>* _current; // Adresse de la cellule sur laquelle est pr�sentement positionn� l'it�rateur
				const List<T>* _list; // Adresse de la liste concern�e par l'it�rateur

				friend class List<T>; // La classe "List" a acc�s � la repr�sentation de l'it�rateur

			public:
				Iterator(); // Constructeur qui initialise "_current" et "_list" � "nullptr".
				~Iterator(); // Destructeur qui remet "_current" et "_list" � "nullptr".

				//const Iterator& operator=(const Iterator&); // Pour assigner la valeur d'un it�rateur � un autre
				bool operator==(const Iterator& itComp) const; // Pour comparer deux it�rateus (ils traitent de la m�me liste � la m�me position)
				bool operator!=(const Iterator& itComp) const;
				Iterator operator++(int num); // Pour d�placer un it�rateur � la cellule suivante (it++)
				const Iterator& operator++(); // Pour atteindre la cellule suivante sans modifier la position courante de l'it�rateur (++it)
				Iterator operator--(int num); // Pour d�placer un it�rateur � la cellule pr�c�dente (it--)
				const Iterator& operator--(); // Pour atteindre la cellule pr�c�dente sans modifier la position courante de l'it�rateur (--it)
				T& operator*(); // Pour acc�der � l'�l�ment point� par l'it�rateur (it*)
				const T& operator*() const; // Pour acc�der � l'�l�ment point� par l'it�rateur (it*) sans pouvoir le modifier
		};

		List(); // Constructeur qui initialise "_first" � "nullptr".
		~List(); // Destructeur qui supprime toutes les cellules de la liste

		void clear(); // M�thode qui supprime toutes les cellules de la liste
		bool empty() const; // M�thode qui v�rifie si la liste est vide (retourne true) ou non (retourne false)

		Iterator begin() const; // M�thode qui retourne un it�rateur pointant sur la premi�re cellule
		Iterator end() const; // M�thode qui retourne un it�rateur ayant pour adresse "nullptr"

		Iterator insert(Iterator it, const T& element); // M�thode qui cr�e une nouvelle cellule juste avant la position de l'it�rateur.
		Iterator erase(Iterator it); // M�thode qui supprime la cellule occupant la position point�e par l'it�rateur.
		Iterator erase(Iterator it1, Iterator it2); /* M�thode qui supprime toutes les cellules se retrouvant inclusivement entre le
											   premier it�rateur et le second it�rateur pass�s en param�tres d'entr�e. */
		T& operator[](Iterator it); /* Cette surcharge d'op�rateur [] n'est pas pr�sente dans la librairie STL. Elle permet
									d'acc�der � l'�l�ment contenu dans la cellule qi occupe l'index sp�cifi� en param�tre
									d'entr�e. */
		const T& operator[](Iterator it) const;

		Iterator operator()(const T& element) const; /* Cette m�thode cherche dans la liste l'ocurrence de l'�l�ment pass� en param�tre
												d'entr�e. Si cet �l�ment est inexistant, un it�rateur "nullptr" est retourn�. */
		Iterator operator()(const T& element, Iterator it) const;

		const List<T>& operator=(const List<T>& liste); // Surcharge de l'op�rateur = pour copier le contenu d'une liste vers une autre.
};


/********************************************************/
/* CODEZ CI-DESSOUS LES M�THODES DE LA CLASSE ITERATOR. */
/********************************************************/

template<typename T>
inline List<T>::Iterator::Iterator()
{
	_current = nullptr;
	_list = nullptr;
}

template<typename T>
inline List<T>::Iterator::~Iterator()
{
	_current = nullptr;
	_list = nullptr;
}

template<typename T>
inline bool List<T>::Iterator::operator==(const Iterator& itComp) const
{
	assert(this->_list == itComp._list);
	assert(this->_list != nullptr);
	assert(itComp._list != nullptr);

	return (this->_current == itComp._current);
}

template<typename T>
inline bool List<T>::Iterator::operator!=(const Iterator& itComp) const
{
	return !operator==(itComp);
}

template<typename T>
inline typename List<T>::Iterator List<T>::Iterator::operator++(int num)
{
	typename List<T>::Iterator it = *this;

	operator++();

	return it;
}

template<typename T>
inline const typename List<T>::Iterator& List<T>::Iterator::operator++() //++it
{
	assert(_list != nullptr);
	assert(_list->_first != nullptr);//la liste ne peut pas etre vide
	assert(_current == nullptr);//fin de liste

	if (_current->_next == nullptr)
	{
		_current = nullptr;
	}
	else
	{
		_current = _current->_next;
	}
	
	return *this;
}

template<typename T>
inline typename List<T>::Iterator List<T>::Iterator::operator--(int num)
{
	typename List<T>::Iterator it = *this;

	operator--();

	return it;
}

template<typename T>
inline const typename List<T>::Iterator& List<T>::Iterator::operator--()//--it
{
	assert(_list != nullptr);
	assert(_list->_first != nullptr);
	assert(_current != _list->_first); 

	if (_current == nullptr) //si on est en fi de liste
	{
		_list->_first->_prev;//on revient sur la derniere cellule
	}
	else
	{
		_current = _current->_prev;
	}

	return *this;
}

template<typename T>
inline T& List<T>::Iterator::operator*()//*it
{
	assert(_list != nullptr);
	assert(_list->_first != nullptr);//la liste ne peut pas etre vide
	assert(_current == nullptr);//fin de liste

	return _current->_element;
}

template<typename T>
inline const T& List<T>::Iterator::operator*() const
{
	assert(_list != nullptr);
	assert(_list->_first != nullptr);//la liste ne peut pas etre vide
	assert(_current != nullptr);//fin de liste

	return _current->_element;
}

/****************************************************/
/* CODEZ CI-DESSOUS LES M�THODES DE LA CLASSE LIST. */
/****************************************************/

template<typename T>
inline List<T>::List()
{
	_first = nullptr;
}

template<typename T>
inline List<T>::~List()
{
	clear();
}

template<typename T>
inline void List<T>::clear()
{
	erase(begin(), end());
}

template<typename T>
inline bool List<T>::empty() const
{
	if (_first == nullptr) 
	{
		return true;
	}

	return false;
}

template<typename T>
inline typename List<T>::Iterator List<T>::begin() const
{
	List<T>::Iterator it;

	it._current = _first;
	it._list = this;

	return it;
}

template<typename T>
inline typename List<T>::Iterator List<T>::end() const
{
	List<T>::Iterator it;

	it._current = nullptr;
	it._list = this;

	return Iterator();
}

template<typename T>
inline typename List<T>::Iterator List<T>::insert(Iterator it, const T& element)
{
	assert(it._list == this); //Verifie que l'iterateur recu en entre est initialise sur la liste qui fait l'appel
	
	if (_first == nullptr) //cas d'une liste vide
		it._current = _first->_prev = _first = new Cellule<T>(element, nullptr, nullptr);
	else if (it._current == _first) 
		it._current = _first = _first->_prev = new Cellule<T>(element, _first, _first->_prev);
	else if (it._current == nullptr)
		it._current = _first->_prev = _first->_prev->_next = new Cellule<T>(element, nullptr, _first->_prev);
	else
		it._current = it._current->_prev = it._current->_prev->_next = new Cellule<T>(element, it._current, it._current->_prev);

	return it;
}

template<typename T>
inline typename List<T>::Iterator List<T>::erase(Iterator it)
{
	assert(it._list == this); //Verifie que l'iterateur recu en entre est initialise sur la liste qui fait l'appel
	assert(_first != nullptr);
	assert(it._current != nullptr);
	//assert(it._current->_prev != nullptr);

	Cellule<T>* deleteCell = it._current;

	if (_first == _first->_prev)
		it._current = _first = nullptr;
	else if (_first == it._current->_prev) 
	{
		_first->_next->_prev = _first->_prev;
		it._current = _first->_next;
		_first = _first->_next;
	}
	else if (it._current == _first->_prev)
	{
		_first->_prev->_prev->_next = nullptr;
		it._current = _first->_prev->_prev;
		_first->_prev = _first->_prev->_prev;
	}
	else
	{
		it._current->_next->_prev = it._current->_prev;
		it._current->_prev->_next = it._current->_next;
		it._current = it._current->_next;
	}

	delete[] deleteCell;

	return it;
}

template<typename T>
inline typename List<T>::Iterator List<T>::erase(Iterator it1, Iterator it2)
{
	assert(it1._list == this);
	assert(it2._list == this);
	assert(it1._current != nullptr);
	assert(it1._current != it2._current);

	while (it1 != it2 && it1 != end())
	{
		it1 = erase(it1);
	}

	return it1;
}

template<typename T>
inline T& List<T>::operator[](Iterator it)
{
	assert(it._list == this); //verifie que l'iterateur est sur notre liste
	assert(it._current != nullptr); //verifie que l'iterateur est sur une cellule

	return it._current->_elemet;
}

template<typename T>
inline const T& List<T>::operator[](Iterator it) const
{
	return operator[](it);
}

template<typename T>
inline typename List<T>::Iterator List<T>::operator()(const T& element) const
{
	return operator()(element, begin());
}

template<typename T>
inline typename List<T>::Iterator List<T>::operator()(const T& element, Iterator it) const
{
	while (it._current != nullptr && it._current->_element != element) //it._current->_element peut etre remplacer par *it
	{
		//it++; ou
		it._current = it._current->_next;
	}

	return it;
}

template<typename T>
inline const List<T>& List<T>::operator=(const List<T>& liste)
{
	if (this == &liste)
		return *this;
	clear(); // desalouer l'ancien objet

	List<T>::Iterator it = liste.begin();

	while (!liste.end())
	{
		insert(end(), it._current->_element); //it._current->_element == *it
		it++;
	}

	return *this;
}
