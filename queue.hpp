#pragma once
#include <assert.h>

template <class TYPE>
class queue {
private:
	struct cellule { // Structure d'une cellule. La file est composée de plusieurs de ces cellules
		TYPE _element; // Donnée enregistrée dans une des cellules de la file
		cellule* _next; // Pointeur vers la prochaine cellule de la file

		// Constructeur d'une cellule (méthode appelée à chaque fois qu'on fait un "new Cellule")
		cellule(const TYPE& element, cellule* next) {
			_element = element;
			_next = next;
		}
	};

	cellule* _queue; // Pointe sur la dernière cellule dont le "next" pointe sur la première

public:
	queue(); // Constructeur qui initialise "_queue" à "nullptr"
	~queue(); // Destructeur qui supprime toutes les cellules de la file

	void clear(); // Méthode qui supprime toutes les cellules de la file
	bool empty() const; // Méthode qui vérifie si la file est vide (retourne true) ou non (retourne false)
	int size() const; // Méthode qui retourne le nombre de cellules que contient la file

	const TYPE& front() const; // Méthode qui retourne l'élément contenu dans la première cellule de la file
	TYPE pop(); // Méthode qui supprime la première cellule de la file et retourne son élément par valeur
	void push(const TYPE&); // Méthode qui ajoute une nouvelle cellule à la fin de la file

	const queue<TYPE>& operator=(const queue<TYPE>&); // Surcharge de l'opérateur = pour copier le contenu
	// d'une file vers une autre.
};

// CODEZ LES MÉTHODES DE VOTRE FILE ICI.

template<class TYPE>
inline queue<TYPE>::queue()
{
	_queue = nullptr;
}

template<class TYPE>
inline queue<TYPE>::~queue()
{
	clear();
}

template<class TYPE>
inline void queue<TYPE>::clear()
{
	while (_queue != nullptr)
		pop();
}

template<class TYPE>
inline bool queue<TYPE>::empty() const
{
	if (_queue == nullptr)
		return true;

	return false;
}

template<class TYPE>
inline int queue<TYPE>::size() const
{
	if (_queue == nullptr)
		return 0;

	int nb = 1;
	cellule* temp = _queue->_next;

	while (temp != _queue)
	{
		nb++;
		temp = temp->_next;
	}

	return nb;
}

template<class TYPE>
inline const TYPE& queue<TYPE>::front() const
{
	assert(_queue != nullptr);

	return _queue->_next->_element;
}

template<class TYPE>
inline TYPE queue<TYPE>::pop()
{
	assert(_queue != nullptr);

	TYPE element;

	if (_queue == _queue->_next) //Si une seule cellule
	{
		element = _queue->_element;
		delete _queue;
		_queue = nullptr;
	}
	else
	{
		cellule* temp = _queue->_next->_next;
		element = _queue->_next->_element;
		delete _queue->_next;
		_queue->_next = temp;
	}

	return element;
}

template<class TYPE>
inline void queue<TYPE>::push(const TYPE& element)
{
	if (_queue == nullptr)
		_queue->_next = _queue = new cellule(element, nullptr);
	else
		_queue = _queue->_next = new cellule(element, _queue->_next);
}

template<class TYPE>
inline const queue<TYPE>& queue<TYPE>::operator=(const queue<TYPE>& pile)
{
	if (this == &pile)
		return *this;

	clear();

	if (pile._queue != nullptr) {
		cellule* temp = pile._queue->_next;

		do
		{
			push(temp->_element);
			temp = temp->_next;
		} while (temp != pile._queue->_next);
	}

	return *this;
	// TODO: insérer une instruction return ici
}