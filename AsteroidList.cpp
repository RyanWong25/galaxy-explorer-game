#include <galaxy-explorer/AsteroidList.hpp>

//default constructor
AsteroidListItem::AsteroidListItem() {
	this->next = nullptr;
	this->data = nullptr;
}

//constructor with Asteroid passed in
AsteroidListItem::AsteroidListItem(Asteroid a) {
	this->next = nullptr;
	this->data = new Asteroid(a);
}

AsteroidListItem::~AsteroidListItem() {
    //destructor
}

AsteroidList::AsteroidList()
{
    //empty list
}

AsteroidList::AsteroidList(const AsteroidList& src)
{
	// The functions in this class are listed in a suggested order of implementation,
	// except for this one and the destructor (because you should put all your constructors together).
    //create an independent copy of 'src' for AsteroidList
    const AsteroidListItem* ptr = src.begin();
    AsteroidListItem* last = NULL;
    AsteroidListItem* nptr = NULL;
    head.setNext(NULL);
    while (ptr != NULL) {
        nptr = new AsteroidListItem(ptr->getData());
        if (last == NULL)
            head.setNext(nptr);
        else
            last -> setNext(nptr);
        ptr = ptr-> getNext();
        last = nptr;
    }
}

AsteroidList::~AsteroidList() {
	// The functions in this class are listed in a suggested order of implementation,
	// except for this one and the copy constructor (because you should put all your constructors together).
    //Free all memory associated with AsteroidList
    this -> clear();
}

void AsteroidList::pushFront(Asteroid e) {
    //create a new AsteroidListItem and put it at the front of the AsteroidList
    AsteroidListItem* nptr = new AsteroidListItem(e);
    nptr -> setNext(begin());
    head.setNext(nptr);
}

Asteroid& AsteroidList::front() {
    return (head.getNext() -> getData());
}

const Asteroid& AsteroidList::front() const {
    return (head.getNext() -> getData());
}

bool AsteroidList::isEmpty() const {
    //return true if the list is empty
    if (head.getNext() == NULL)
	return true;
    else
        return false;
}

int AsteroidList::size() const {
    int count = 0;
    const AsteroidListItem* tptr = head.getNext();
    while (tptr != NULL) {
        count++;
        tptr = tptr -> getNext();
    }
    return count;
}

AsteroidListItem* AsteroidList::beforeBegin() {
	//return the address of head
        return &head;
}

const AsteroidListItem* AsteroidList::beforeBegin() const {
	//return the address of head
        return &head;
}

AsteroidListItem* AsteroidList::begin() {
	return head.getNext();
}

const AsteroidListItem* AsteroidList::begin() const {
	return head.getNext();
}

AsteroidListItem* AsteroidList::beforeEnd() {
	//if list is empty, return beforeBegin
    if (isEmpty()) {
        return beforeBegin();
    }
    AsteroidListItem* tptr = head.getNext();
    while(tptr -> getNext() != NULL) {
        tptr = tptr -> getNext();
    }
    return tptr;
}

const AsteroidListItem* AsteroidList::beforeEnd() const {
	//if list is empty, return beforeBegin
    if (isEmpty()) {
        return beforeBegin();
    }
    const AsteroidListItem* tptr = head.getNext();
    while(tptr -> getNext() != NULL) {
        tptr = tptr -> getNext();
    }
    return tptr;
}

AsteroidListItem* AsteroidList::end() {
        //returns null,  because it is the last thing in the list
	return nullptr;
}

const AsteroidListItem* AsteroidList::end() const {
        //returns null,  because it is the last thing in the list
	return nullptr;
}

AsteroidListItem* AsteroidList::insertAfter(AsteroidListItem* prev, Asteroid e) {
    //insert a new Asteroid after prev in the list
    AsteroidListItem* nptr = new AsteroidListItem(e);
    AsteroidListItem* temp = prev->getNext();
    prev->setNext(nptr);
    nptr->setNext(temp);
    return nptr;
}

AsteroidListItem* AsteroidList::insertAfter(AsteroidListItem* prev, const AsteroidList& others) {
    //insert a new AsteroidList after prev in the list
    const AsteroidListItem* ptr = others.begin();
    while (ptr != NULL) {
        prev = this -> insertAfter(prev, ptr->getData());
        ptr = ptr -> getNext();
    }
    return prev;
}

AsteroidListItem* AsteroidList::eraseAfter(AsteroidListItem* prev) {
    //delete the asteroid following prev in the list
    if (prev->getNext() != NULL) {
        AsteroidListItem* ptr = prev->getNext();
        AsteroidListItem* temp = ptr->getNext();
        delete ptr;
        prev->setNext(temp);
    }
}

void AsteroidList::clear() {
    //Makes the list empty, frees all nodes
    AsteroidListItem* ptr;
    while (head.getNext() != NULL) {
        ptr = head.getNext();
        head.setNext(ptr -> getNext());
        delete ptr;
    }
}

AsteroidList& AsteroidList::operator=(const AsteroidList& src) {
    //makes 'this' list an independent copy of 'src'
    if (this == &src)
        return (*this);
    this -> clear();
    this -> insertAfter(&head, src);
    return(*this);
}
