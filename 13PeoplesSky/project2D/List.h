#pragma once

template<typename T>
class ListIterator;

template <typename T>
struct Node
{
	Node* m_prev = nullptr;
	Node* m_next = nullptr;

	T m_contents;
};

template<typename T>
class List 
{
public:

	template<typename T>
	friend class ListIterator;

	List() 
	{
		m_root = new Node<T>;
		m_end = m_root;
	}

	~List() 
	{
		Clear();
		delete m_root;
	}

	// Adds the value to the end of the list.
	void Add(T value) 
	{
		Node<T>* newEnd = nullptr;

		m_end->m_contents = value;

		Node<T>* prevEnd = m_end;
		Node<T>*& nextNode = m_end->m_next;
		if(nextNode) 
		{
			// The next node already exists
			m_end = nextNode;
		}
		else
		{
			// The next node needs to be created.
			nextNode = new Node<T>;
			m_end = nextNode;
		}

		m_end->m_prev = prevEnd;
		m_end->m_contents = value;

		++m_nCount;
	}

	void RemoveAt(int nIndex) 
	{
		//if(nIndex == m_nCount - 1) 
		//{
		//	RemoveEnd();
		//	return;
		//}
		//else if(nIndex > 0) 
		//{
		//	Node<T>* currentNode = m_root;
		//
		//	for (int i = 0; i < nIndex; ++i)
		//	{
		//		currentNode = currentNode->m_next;
		//	}
		//
		//	// Current node is now the node that needs to be removed.
		//	Node<T>* prev = currentNode->m_prev;
		//	Node<T>* next = currentNode->m_next;
		//
		//	prev->m_next = next;
		//	next->m_prev = prev;
		//
		//	delete currentNode;
		//
		//	--m_nCount;
		//}
		//else
		//{
		//	// Node to remove is the root node.
		//	RemoveStart();
		//	return;
		//}

		if (nIndex == 0 && m_nCount > 1) // Current node is the root node.
		{
			Node<T>*& rootPtrRef = m_root; // Get reference to the pointer of the root.
			Node<T>* oldRoot = rootPtrRef; // Store a copy of the old root pointer.

			rootPtrRef = rootPtrRef->m_next;
			rootPtrRef->m_prev = nullptr;

			delete oldRoot; // Delete old root node using old root node pointer.

			--m_nCount; // Decrement count in list.
		}
		else if (nIndex == m_nCount - 1)  // Current node is the end node.
		{
			Node<T>*& endPtrRef = m_end; // Get reference to the pointer of the end.
			Node<T>* oldEnd = endPtrRef; // Store a copy of the old end pointer.

			endPtrRef = endPtrRef->m_prev;
			endPtrRef->m_next = nullptr;

			delete oldEnd; // Delete the old end node using the old end node pointer.

			--m_nCount; // Decrement count in list.
		}
		else // Current node is not the root or end node.
		{
			Node<T>* currentNode = m_root;

			for (int i = 0; i < nIndex; ++i)
			{
				currentNode = currentNode->m_next;
			}
			
			// Current node is now the node that needs to be removed.
			Node<T>* prev = currentNode->m_prev;
			Node<T>* next = currentNode->m_next;
			
			prev->m_next = next;
			next->m_prev = prev;
			
			delete currentNode;
			
			--m_nCount;
		}
	}

	T& At(int nIndex) 
	{
		Node<T>* currentNode = m_root;

		for (int i = 0; i < nIndex; ++i)
		{
			currentNode = currentNode->m_next;
		}

		// Current node is now the node to return.

		return currentNode->m_contents;
	}

	T& operator [] (int nIndex) 
	{
		return At(nIndex);
	}

	int Count() 
	{
		return m_nCount;
	}

	ListIterator<T> CreateIterator() 
	{
		// Return iterator class instance that has pointers to this list's root node, end node, and count value.
		return ListIterator<T>(&m_root, &m_end, &m_nCount);
	}

	void Clear() 
	{
		// Note: The root node is not deleted.

		// Start at the end node.
		Node<T>* currentNode = m_end;

		// While the current node is not the root node...
		while(currentNode != m_root) 
		{
			Node<T>* nodeToDelete = currentNode; // Get copy of the current node-to-delete pointer.

			currentNode = currentNode->m_prev; // Shift current node to the next node.

			delete nodeToDelete; // Delete current node using copied pointer.
		}

		// Make end point to root.
		m_end = m_root;
		m_root->m_next = nullptr; // Ensure the root's next pointer is nullptr so the Add() function can create new nodes.
		m_nCount = 0; // Set the count to zero.
	}

private:

	Node<T>* m_root = nullptr;
	Node<T>* m_end = nullptr;
	int m_nCount = 0;
};

template<typename T>
class ListIterator
{
public:

	ListIterator(Node<T>** root, Node<T>** end, int* nCount)
	{
		m_root = root;
		m_end = end;
		m_currentNode = *m_root;
		m_nCount = nCount;
	}

	~ListIterator()
	{

	}

	// Returns true if the iterator index is 0.
	bool AtStart() 
	{
		return (m_nCurrentIndex == 0);
	}

	// Returns true if the iterator reaches the end of the list.
	bool AtEnd() 
	{
		return (m_nCurrentIndex >= *m_nCount);
	}

	// Returns the iterator to the start of the list.
	void Restart() 
	{
		m_currentNode = *m_root;
		m_nCurrentIndex = 0;
	}

	// Increments the iterator forward by one.
	void operator ++()
	{
		m_currentNode = m_currentNode->m_next;
		++m_nCurrentIndex;
	}

	// Returns the current iterator value.
	T& Value() 
	{
		return m_currentNode->m_contents;
	}

	// Returns the current iterator index.
	int Index() 
	{
		return m_nCurrentIndex;
	}

	// Removes the current iterator value from the list.
	void RemoveCurrent() 
	{
		if(m_nCurrentIndex == 0 && *m_nCount > 1) // Current node is the root node.
		{
			Node<T>*& rootPtrRef = *m_root; // Get reference to the pointer of the root.
			Node<T>* oldRoot = rootPtrRef; // Store a copy of the old root pointer.

			rootPtrRef = rootPtrRef->m_next;
			rootPtrRef->m_prev = nullptr;

			m_currentNode = rootPtrRef; // Set current node to new root node.

			delete oldRoot; // Delete old root node using old root node pointer.
		}
		else if(m_nCurrentIndex == *m_nCount - 1)  // Current node is the end node.
		{
			Node<T>*& endPtrRef = *m_end; // Get reference to the pointer of the end.
			Node<T>* oldEnd = endPtrRef; // Store a copy of the old end pointer.

			endPtrRef = endPtrRef->m_prev;
			endPtrRef->m_next = nullptr;

			m_currentNode = endPtrRef; // Set the current node to the new end node.

			m_nCurrentIndex = *m_nCount; // Set the index to the count to stop iteration.

			delete oldEnd; // Delete the old end node using the old end node pointer.
		}
		else // Current node is not the root or end node.
		{
			Node<T>* nodeToRemove = m_currentNode;

			m_currentNode = m_currentNode->m_next;

			nodeToRemove->m_prev->m_next = nodeToRemove->m_next;
			nodeToRemove->m_next->m_prev = nodeToRemove->m_prev;

			delete nodeToRemove;
		}

		--*m_nCount; // Decrement count in list.
	}

private:

	Node<T>** m_root = nullptr;
	Node<T>** m_end = nullptr;
	Node<T>* m_currentNode = nullptr;
	int* m_nCount = nullptr;
	int m_nCurrentIndex = 0;
};
