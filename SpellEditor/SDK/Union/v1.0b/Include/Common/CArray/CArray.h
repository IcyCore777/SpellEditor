// Supported with union (c) 2018 Union team

#include "CArrayBase.h"

#ifndef __UNION_ARRAY_H__
#define __UNION_ARRAY_H__

namespace Common {
	template <class T>
	class CArray : public CArrayBase
	{
	public:
		CArray ();
		CArray (const T* dst);
		void InsertEnd (const T& obj);
		void Insert (const T& obj);
		void InsertAt (const uint32& idx, const T& obj);
		void InsertFront (const T& obj);

		void Merge (CArray& arr);
		void MergeAt (CArray& arr, const uint32& idx);

		void Remove (const T& obj);
		void RemoveAt (const uint32& idx);
		void FastRemove (const T& obj);
		void FastRemoveAt (const uint32& idx);

		void Delete (const T& obj);
		void DeleteAt (const uint32& idx);
		void FastDelete (const T& obj);
		void FastDeleteAt (const uint32& idx);
		void DeleteAtBounds (const uint32& idx, const uint32& length);
		void DeleteData ();
        void ReleaseData ();

		uint32 Search (const T& obj) const;
		T* CopyAtBounds (const uint32& idx, const uint32& length) const;
		T& operator [] (uint32 idx);
		const T& operator [] (uint32 idx) const;
        T& GetLast();
        const T& GetLast() const;
		T* GetSafe (const uint32& idx);
		bool32 IsIn (const T& obj) const;

		virtual ~CArray ();
	};

    #define pointer_cast(v) reinterpret_cast<const void32>(reinterpret_cast<uint32>(&v))

	template <class T>
	CArray<T>::CArray () 
		: CArrayBase (sizeof(T)) {
			Clear ();
	}

	template <class T>
	CArray<T>::CArray (const T* dst) 
		: CArrayBase (sizeof(T), (void32)dst) {
	
	}

	template <class T>
    void CArray<T>::InsertEnd( const T& obj ) {
      CArrayBase::
        InsertEnd( pointer_cast( tmp ) );
    }

    template <class T>
    void CArray<T>::Insert( const T& obj ) {
      CArrayBase::
        Insert( pointer_cast( obj ) );
	}

	template <class T>
    void CArray<T>::InsertAt( const uint32& idx, const T& obj ) {
      CArrayBase::
        InsertAt( idx, pointer_cast( obj ) );
	}

	template <class T>
	void CArray<T>::Merge (CArray& arr) {
		CArrayBase::
			Merge (&arr);
	}

	template <class T>
	void CArray<T>::MergeAt (CArray& arr, const uint32& idx) {
		CArrayBase::
			MergeAt (&arr, idx);
	}

	template <class T>
	void CArray<T>::Remove (const T& obj) {
		CArrayBase::
			Remove (pointer_cast(obj));
	}

	template <class T>
	void CArray<T>::RemoveAt (const uint32& idx) {
		CArrayBase::
			RemoveAt (idx);
	}

	template <class T>
	void CArray<T>::FastRemove (const T& obj) {
		CArrayBase::
			FastRemove (pointer_cast(obj));
	}

	template <class T>
	void CArray<T>::FastRemoveAt (const uint32& idx) {
		CArrayBase::
			FastRemoveAt (idx);
	}

	template <class T>
	void CArray<T>::DeleteData () {
		for (uint32 i = 0; i < GetNum(); i++)
			delete T(operator [] (i));
		Clear ();
	}

    template <class T>
	void CArray<T>::ReleaseData () {
		for (uint32 i = 0; i < GetNum(); i++)
          if( operator [] (i) )
			T(operator [] (i))->Release();
	}

	template <class T>
	void CArray<T>::Delete (const T& obj) {
		uint32 idx = Search (obj);
		if (idx != NotFound) {
			delete T(operator [] (idx));
			RemoveAt (idx);
		}
	}

	template <class T>
	void CArray<T>::DeleteAt (const uint32& idx) {
		if (idx >= unSize)
			return;
		delete T(operator [] (idx));
		RemoveAt (idx);
	}

	template <class T>
	void CArray<T>::FastDelete (const T& obj) {
		uint32 idx = Search (obj);
		if (idx != NotFound) {
			delete T(operator [] (idx));
			FastRemoveAt (idx);
		}
	}

	template <class T>
	void CArray<T>::FastDeleteAt (const uint32& idx) {
		if (idx >= unSize)
			return;
		delete T(operator [] (idx));
		FastRemoveAt (idx);
	}

	template <class T>
	void CArray<T>::DeleteAtBounds (const uint32& idx, const uint32& length) {
		for (uint32 i = 0; i < length; i++) {
			T* data = GetSafe(idx + i);
			if (data)
				delete *data;
		}
		RemoveAtBounds (idx, length);
	}

	template <class T>
	void CArray<T>::InsertFront (const T& obj) {
		CArrayBase::
			InsertAt (0, pointer_cast(obj));
	}

	template <class T>
	uint32 CArray<T>::Search (const T& obj) const {
		return CArrayBase::
			Search (pointer_cast(obj));
	}

	template <class T>
	T* CArray<T>::CopyAtBounds (const uint32& idx, const uint32& length) const {
		return (T*)CArrayBase::
			CopyAtBounds (idx, length);
	}

	template <class T>
	T& CArray<T>::operator [] (uint32 idx) {
		return *(T*)CArrayBase::
			operator [] (idx);
	}

	template <class T>
	const T& CArray<T>::operator [] (uint32 idx) const {
		return *(T*)CArrayBase::
			operator [] (idx);
	}

	template <class T>
	T* CArray<T>::GetSafe (const uint32& idx) {
		if (idx >= GetNum())
			return Null;
		return & operator [] (idx);
	}

    template <class T>
	T& CArray<T>::GetLast () {
		return operator [] (GetNum() - 1);
	}

    template <class T>
	const T& CArray<T>::GetLast () const {
		return operator [] (GetNum() - 1);
	}

	template <class T>
	bool32 CArray<T>::IsIn (const T& obj) const {
		return CArrayBase::
			Search (pointer_cast(obj)) != -1;
	}

	template <class T>
	CArray<T>::~CArray () {
      Clear();
	}



    template <class T>
    class CCollection : public CArray<T> {
    public:
      void InsertEnd( const T& obj );
      void Insert( const T& obj );
      void InsertAt( const uint32& idx, const T& obj );
      ~CCollection();
    };

    template <class T>
    void CCollection<T>::InsertEnd( const T& obj ) {
      CArrayBase::InsertEnd( Null );
      T* tvec = (T*)vector;
      tvec[unSize - 1] = obj;
    }

    template <class T>
    void CCollection<T>::Insert( const T& obj ) {
      CArrayBase::InsertEnd( Null );
      T* tvec = (T*)vector;
      tvec[unSize - 1] = obj;
	}

	template <class T>
    void CCollection<T>::InsertAt( const uint32& idx, const T& obj ) {
      T* tmp = new T( obj );
      CArrayBase::
        InsertAt( idx, tmp );
      free( tmp );
	}
    
	template <class T>
	CCollection<T>::~CCollection () {
      for( uint i = 0; i < GetNum(); i++ ) {
        operator[]( i ).~T();
      }
      Clear();
	}

} // namespace Common

#endif // __UNION_ARRAY_H__