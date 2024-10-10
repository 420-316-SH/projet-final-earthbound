#pragma once
#include <cassert>

template <class TYPE>
class liste {
protected:
	struct cellule
	{
		TYPE _element;
		cellule* _next;
		cellule* _previous;
		cellule(const TYPE& e, cellule* n, cellule* p)
		{
			_element = e;
			_next = n;
			_previous = p;
		}
	};

	cellule* _premier;
	cellule* _courant;
	liste(const liste& listObj); // Copieur désactivé

public:
	liste(); // Constructeur
	~liste(); // Destructeur
	bool empty() const; // Retourne vrai si la liste est vide et
	// faux sinon
	void clear(); // Vide la liste
	void next(); // Positionne _courant sur la cellule suivante
	// Si _courant est sur la dernière cellule, il
	// tombe à nullptr et si _courant est déjà à
	// nullptr, il le reste (aucune erreur générée)
	void previous(); // Positionne _courant sur la cellule
	// précédente. Si _courant est à nullptr,
	// il se met à pointer la dernière cellule

		// de la liste et s’il est sur la première
		// cellule de la liste, il y reste (aucune
		// erreur générée)
	void begin(); // Positionne _courant sur la première cellule
	void end(); // Positionne _courant en fin de liste (nullptr)
	bool isBegin() const; // Retourne vrai si _courant est au
	// début de la liste ou faux sinon
	bool isEnd() const; // Retourne vrai si _courant est à la
	// fin de la liste (nullptr) ou faux
	// sinon
	TYPE& value() const; // Retourne la valeur présente dans la
	// cellule pointée par _courant
	int size() const; // Retourne le nombre de cellules de la
	// liste
	void insert(const TYPE& element); // Insère une nouvelle
	// celule avec l’élément
	// reçu juste avant la
	// position de _courant.
	// Ce dernier reste au
	// même endroit qu'avant
	// l'insertion.
	void erase(); // Désalloue la cellule ciblée par _courant.
	// _courant est ensuite positionné sur la
	// cellule venant juste après celle qui vient
	// d’être désallouée. Si la dernière cellule
	// vient d’être désallouée, _courant tombe à
	// nullptr.
	const liste& operator=(const liste& l); // Affectateur
};

template<class TYPE>
inline liste<TYPE>::liste()
{
	_premier = nullptr;
	_courant = nullptr;
}

template<class TYPE>
inline liste<TYPE>::~liste()
{
	clear();
}

template<class TYPE>
inline bool liste<TYPE>::empty() const
{
	if (_premier == nullptr)
	{
		return true;
	}

	return false;
}

template<class TYPE>
inline void liste<TYPE>::clear()
{
	while (_premier != nullptr) 
	{
		erase();
	}
}

template<class TYPE>
inline void liste<TYPE>::next()
{
	if (_courant == nullptr || _courant == _premier->_previous)
	{
		_courant = nullptr;
	}
	else
	{
		_courant = _courant->_next;
	}
	
}

template<class TYPE>
inline void liste<TYPE>::previous()
{
	if (_courant == nullptr) 
	{
		_courant = _premier->_previous;
	}
	else if (_courant == _premier) 
	{
		_courant = _premier;
	}
	else 
	{
		_courant = _courant->_previous;
	}
}

template<class TYPE>
inline void liste<TYPE>::begin()
{
	_courant = _premier;
}

template<class TYPE>
inline void liste<TYPE>::end()
{
	_courant = nullptr;
}

template<class TYPE>
inline bool liste<TYPE>::isBegin() const
{
	if (_courant == _premier) 
	{
		return true;
	}
	return false;
}

template<class TYPE>
inline bool liste<TYPE>::isEnd() const
{
	if (_courant == nullptr) 
	{
		return true;
	}
	return false;
}

template<class TYPE>
inline TYPE& liste<TYPE>::value() const
{
	assert(_courant != nullptr);
	return _courant->_element;
	// TODO: insérer une instruction return ici
}

template<class TYPE>
inline int liste<TYPE>::size() const
{
	if(_premier == nullptr) 
	{
		return 0;
	}

	cellule* temp = _premier;
	int cpt = 0;

	do{
		cpt++;
		temp = temp->_next;
	} while (temp != _premier);
	return cpt;
}

template<class TYPE>
inline void liste<TYPE>::insert(const TYPE& element)
{
	if (_premier == nullptr) //cas d'insertion dans une liste vide
	{
		_premier->_next = _premier->_previous = _premier = new cellule(element, nullptr, nullptr);
	}
	else if (_courant == nullptr) //insertion à la fin de la liste
	{
		_premier->_previous = _premier->_previous->_next = new cellule(element, _premier, _premier->_previous);
	}
	else // insertion au milieu de la liste
	{
		_courant->_previous = _courant->_previous->_next = new cellule(element, _courant, _courant->_previous);
	}
}

template<class TYPE>
inline void liste<TYPE>::erase()
{
	assert(_premier != nullptr); //la liste ne doit pas être vide
	assert(_courant != nullptr); //l'itérateur doit pointer une cellule'

	cellule* deleteCell = _courant;

	if (_premier->_next == _premier) //suppression dans une liste avec une seule cellule
	{
		_premier = _courant = nullptr;
	}
	else //suppression au milieu de la liste
	{
		_courant->_next->_previous = _courant->_previous;
		_courant->_previous->_next = _courant->_next;
		if (_courant == _premier->_previous)
		{
			_courant = nullptr;
		}
		else 
		{
			_courant = _courant->_next;
		}
		
	}

	delete deleteCell;
}

template<class TYPE>
inline const liste<TYPE>& liste<TYPE>::operator=(const liste& l)
{
	if (this == &l)
	{
		return *this;
	}

	clear();

	cellule* temp = l._premier;

	
	do {
		insert(temp->_element);
		temp = temp->_next;
	} while (temp != l._premier);

	return *this;
}
