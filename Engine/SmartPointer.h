#pragma once
#include <assert.h>
#include "DebugStatement.h"
#include <stdint.h>


//Constructor takes Smart count and then Weak count
struct PointerCount
{

	uint64_t		OwnerReferences;
	uint64_t		ObserverReferences;

	PointerCount(uint64_t i_InitialOwners, uint64_t i_InitialObservers) :
		OwnerReferences(i_InitialOwners),
		ObserverReferences(i_InitialObservers)
	{}
};

template<class T>
class WeakPointer;

template<class T>
class SmartPointer
{
public:
	template<class U>
	friend class WeakPointer;

	template<class U>
	friend class SmartPointer;

	//default constructor
	SmartPointer() :
		PointerCountHolder(nullptr),
		pObject(nullptr)
	{}

	//constructor with passes templated object
	explicit SmartPointer(T * pObject) :
		PointerCountHolder(pObject ? new PointerCount(1, 0) : nullptr),
		pObject(pObject)
	{	}


	//copy constructor with Smart pointer of same type
	template<class U>
	SmartPointer(const SmartPointer & other) :
		pObject(other.pObject),
		PointerCountHolder(other.PointerCountHolder)
	{
		if (PointerCountHolder)
		{
			assert(pObject != nullptr);
			PointerCountHolder->SmartCount++;
		}
		else
			assert(pObject == nullptr);
	}

	//Copy Constructor using templated inherited type
	template<class U>
	SmartPointer(const SmartPointer<U> & other) :
		PointerCountHolder(other.PointerCountHolder),
		pObject(other.pObject)
	{
		if (PointerCountHolder)
		{
			assert(pObject != nullptr);
			PointerCountHolder->OwnerReferences++;
		}
		else
		{
			assert(pObject == nullptr);
		}
	}

	// Move Copy Constructor -- Joe had this, but I don't understand its use-case
	//I think it's like a copy constructor but moves the data to a new object
	//I don't really know why you'd do this.
	SmartPointer(SmartPointer && other) :
		PointerCountHolder(other.PointerCountHolder),
		pObject(other.pObject)
	{
		other.PointerCountHolder = nullptr;
		other.pObject = nullptr;
	}

	// Move Copy Constructor -- same as above but with templated type
	template<class U>
	SmartPointer(SmartPointer<U> && other) :
		PointerCountHolder(other.PointerCountHolder),
		pObject(other.pObject)
	{
		other.PointerCountHolder = nullptr;
		other.pObject = nullptr;
	}

	//Copy constructor using Weak pointer to make an Smart pointer
	SmartPointer(const WeakPointer<T> & other) :
		pObject(other.pObject && other.PointerCountHolder->OwnerReferences > 0 ? other.pObject : nullptr)
		PointerCountHolder(other.PointerCountHolder  && other.PointerCountHolder->SmartCount > 0 ? other.PointerCountHolder : nullptr)

	{
		IncrementOwnership();
	}

	//copy constructor using Weak pointer to make an Smart pointer using templated type 
	template<class U>
	SmartPointer(const WeakPointer<U> & other) :
		pObject(other.pObject && other.PointerCountHolder->OwnerReferences > 0 ? other.pObject : nullptr)
		PointerCountHolder(other.PointerCountHolder  && other.PointerCountHolder->SmartCount > 0 ? other.PointerCountHolder : nullptr)
	{
		IncrementOwnership();
	}

	//Operator =
	SmartPointer & operator=( SmartPointer & other)
	{
		if (pObject != other.pObject)
		{
			RemoveOwnerReference();
			PointerCountHolder = other.PointerCountHolder;
			pObject = other.pObject;
			PointerCountHolder->OwnerReferences++;
		}
		return *this;
	}

	template<class U>
	SmartPointer & operator=(const SmartPointer<U> & other)
	{
		if (pObject != other.pObject)
		{
			RemoveOwnerReference();
			PointerCountHolder = other.PointerCountHolder;
			pObject = other.pObject;
			PointerCountHolder->OwnerReferences++;
		}
		return *this;
	}

	//Move assignment operator =
	SmartPointer & operator=(SmartPointer && other)
	{
		if (pObject != other.pObject)
		{
			RemoveOwnerReference();

			PointerCountHolder = other.PointerCountHolder;
			pObject = other.pObject;

			other.PointerCountHolder = nullptr;
			other.pObject = nullptr;
		}

		return *this;
	}

	template<class U>
	SmartPointer & operator=(SmartPointer<U> && other)
	{
		if (pObject != other.pObject)
		{
			RemoveOwnerReference();

			PointerCountHolder = other.PointerCountHolder;
			pObject = other.pObject;

			other.PointerCountHolder = nullptr;
			other.pObject = nullptr;
		}

		return *this;
	}

	// Assignment Operator - converting an Weak pointer to an Smart pointer
	SmartPointer & operator=(const WeakPointer<T> & other)
	{
		if (pObject != other.pObject)
		{
			RemoveObserverReference();

			PointerCountHolder = (other.PointerCountHolder && (other.PointerCountHolder->OwnerReferences > 0)) ? other.PointerCountHolder : nullptr;
			pObject = (other.PointerCountHolder && (other.PointerCountHolder->OwnerReferences > 0)) ? other.pObject : nullptr;

			IncrementOwnership();
		}

		return *this;
	}

	template<class U>
	SmartPointer & operator=(const WeakPointer<U> & other)
	{
		if (pObject != other.pObject)
		{
			RemoveObserverReference();

			PointerCountHolder = (other.PointerCountHolder && (other.PointerCountHolder->OwnerReferences > 0)) ? other.PointerCountHolder : nullptr;
			pObject = (other.PointerCountHolder && (other.PointerCountHolder->OwnerReferences > 0)) ? other.pObject : nullptr;

			IncrementOwnership();
		}

		return *this;
	}

	//move copy constructor from Obs to Own
	SmartPointer & operator=(WeakPointer<T> && other)
	{
		if (pObject != other.pObject)
		{
			RemoveOwnerReference();

			PointerCountHolder = other.PointerCountHolder;
			pObject = other.pObject;

			other.PointerCountHolder = nullptr;
			other.pObject = nullptr;
		}

		return *this;
	}

	template<class U>
	SmartPointer & operator=(WeakPointer<U> && other)
	{
		if (pObject != other.pObject)
		{
			RemoveOwnerReference();

			PointerCountHolder = other.PointerCountHolder;
			pObject = other.pObject;

			other.PointerCountHolder = nullptr;
			other.pObject = nullptr;
		}

		return *this;
	}

	//assignment to nullptr
	SmartPointer & operator=(std::nullptr_t _null)
	{
		RemoveOwnerReference();
		PointerCountHolder = nullptr;
		pObject = nullptr;
		return *this;
	}

	//assignment to a pointer type
	SmartPointer & operator=(T * other)
	{
		if (pObject != other)
		{
			RemoveOwnerReference();
			PointerCountHolder = other ? new PointerCount(1, 0) : nullptr;
			pObject = other;
		}
		return *this;
	}


	~SmartPointer()
	{
		RemoveOwnerReference();
	}


	template<class U>
	inline bool operator==(const SmartPointer<U> & rhs)
	{
		return (pObject == rhs.pObject);
	}

	template<class U>
	inline bool operator==(const WeakPointer<U> & rhs)
	{
		return (pObject == rhs.pObject);
	}

	template<class U>
	inline bool operator!=(const SmartPointer<U> & rhs)
	{
		return (pObject != rhs.pObject);
	}

	template<class U>
	inline bool operator!=(const WeakPointer<U> & rhs)
	{
		return (pObject != rhs.pObject);
	}

	template<class U>
	inline bool operator==(U * rhs) const
	{
		return pObject == rhs;
	}

	inline bool operator==(std::nullptr_t nullp) const
	{
		return pObject != nullptr;
	}

	inline operator bool() const
	{
		return pObject != nullptr;
	}


	// member access operator
	T * operator->()
	{
		return pObject;
	}

	// indirection operator, I don't think i need this because I don't forsee accessing it like this.
	T & operator*()
	{
		assert(m_ptr != nullptr);

		return *pObject;
	}

private:

	T * pObject;
	PointerCount * PointerCountHolder;

	void RemoveOwnerReference()
	{
		if (PointerCountHolder)
		{
			assert(PointerCountHolder->OwnerReferences > 0);
			if (--(PointerCountHolder->OwnerReferences) == 0)
			{
				assert(pObject);

				delete pObject;
				pObject = nullptr;

				if (PointerCountHolder->ObserverReferences == 0)
				{
					delete PointerCountHolder;
					PointerCountHolder = nullptr;
				}
			}
		}
		else
		{
			assert(pObject == nullptr);
		}
	}

	void IncrementOwnership()
	{
		if (PointerCountHolder)
		{
			assert(PointerCountHolder->OwnerReferences > 0);
			assert(pObject != nullptr);

			PointerCountHolder->OwnerReferences++;
		}
		else
		{
			assert(pObject == nullptr);
		}
	}


};

template<class T>
class WeakPointer
{
	template<class U>
	friend class SmartPointer;
	template<class U>
	friend class WeakPointer;

public:

	WeakPointer() :
		PointerCountHolder(nullptr),
		pObject(nullptr)
	{	}


	//constructor with Smart pointer
	template<class U>
	WeakPointer(const SmartPointer<U> & other) :
		pObject(other.pObject ? other.pObject : nullptr),
		PointerCountHolder(other.PointerCountHolder && other.PointerCountHolder->SmartCount > 0 ? other.PointerCountHolder : nullptr)
	{
		if (PointerCountHolder)
		{
			assert(pObject != nullptr);
			assert(PointerCountHolder->ObserverReferences || PointerCountHolder->OwnerReferences);
			PointerCountHolder->WeakCount++;
		}
		else
			assert(pObject == nullptr);
	}

	//constructor with Weak pointer
	WeakPointer(const WeakPointer & other) :
		pObject(other.pObject ? other.pObject : nullptr),
		PointerCountHolder(other.PointerCountHolder && other.PointerCountHolder->SmartCount > 0 ? other.PointerCountHolder : nullptr)
	{
		if (PointerCountHolder)
		{
			assert(pObject != nullptr);
			assert(PointerCountHolder->ObserverReferences || PointerCountHolder->OwnerReferences);
			PointerCountHolder->WeakCount++;
		}
		else
			assert(pObject == nullptr);
	}

	//constructor with Weak pointer templated
	template<class U>
	WeakPointer(const WeakPointer<U> & other) :
		pObject(other.pObject ? other.pObject : nullptr),
		PointerCountHolder(other.PointerCountHolder && other.PointerCountHolder->SmartCount > 0 ? other.PointerCountHolder : nullptr)
	{
		if (PointerCountHolder)
		{
			assert(pObject != nullptr);
			assert(PointerCountHolder->ObserverReferences || PointerCountHolder->OwnerReferences);
			PointerCountHolder->WeakCount++;
		}
		else
			assert(pObject == nullptr);
	}



	~WeakPointer()
	{
		DEBUG_PRINT("Smart Pointer Destructor Called.");
		RemoveObserverReference();
	}

	//copy constructor
	WeakPointer & operator=(const WeakPointer & other)
	{
		if (pObject != other.pObject)
		{
			RemoveObserverReferece();

			PointerCountHolder = other.PointerCountHolder;
			pObject = other.pObject;

			IncremetObserverReference();
		}

		return *this;
	}

	//copy constructor templated
	template<class U>
	WeakPointer & operator=(const WeakPointer<U> & other)
	{
		if (pObject != other.pObject)
		{
			RemoveObserverReferece();

			PointerCountHolder = other.PointerCountHolder;
			pObject = other.pObject;

			IncremetObserverReference();
		}

		return *this;
	}

	template<class U>
	inline WeakPointer & operator=(const SmartPointer<U> & other)
	{
		if (pObject != other.pObject)
		{
			RemoveObserverReferece();

			PointerCountHolder = other.PointerCountHolder;
			pObject = other.pObject;

			IncremetObserverReference();
		}

		return *this;
	}

	WeakPointer<T> & operator=(std::nullptr_t i_null)
	{
		RemoveObserverReferece();

		PointerCountHolder = nullptr;
		pObject = nullptr;

		return *this;
	}


	template<class U>
	inline bool operator==(const SmartPointer<U> & rhs)
	{
		return (pObject == rhs.pObject);
	}

	template<class U>
	inline bool operator==(const WeakPointer<U> & rhs)
	{
		return (pObject == rhs.pObject);
	}

	template<class U>
	inline bool operator!=(const SmartPointer<U> & rhs)
	{
		return (pObject != rhs.pObject);
	}

	template<class U>
	inline bool operator!=(const WeakPointer<U> & rhs)
	{
		return (pObject != rhs.pObject);
	}

private:
	T * pObject;
	PointerCount * PointerCountHolder;

	void RemoveObserverReferece()
	{
		if (PointerCountHolder)
		{
			assert(PointerCountHolder->ObserverReferences > 0);
			if (--(PointerCountHolder->ObserverReferences) == 0)
			{
				if ((PointerCountHolder->OwnerReferences == 0))
				{
					delete PointerCountHolder;
					PointerCountHolder = nullptr;

					pObject = nullptr;
				}
			}
		}
		else
		{
			// originated a SmartPointer to nullptr. Still is
			assert(pObject == nullptr);
		}
	}

	void IncrementObservership()
	{
		if (PointerCountHolder)
		{
			assert((PointerCountHolder->OwnerReferences > 0) || (PointerCountHolder->ObserverReferences > 0));

			PointerCountHolder->ObserverReferences++;
		}
		else
		{
			// originated a SmartPointer to nullptr. Still is
			assert(pObject == nullptr);
		}
	}

};