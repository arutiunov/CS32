//#ifndef SET_INCLUDED
//#define SET_INCLUDED
//
//template <typename T>
//class Set
//{
//public:
//    Set();
//    bool empty() const;
//    int size() const;
//    
//    bool insert(const T& value); //
//    
//    bool erase(const T& value); //
//    
//    bool contains(const T& value) const; //
//    
//    bool get(int i, T& value) const; //
//   
//    void swap(Set& other); //
//    
//    // Housekeeping functions
//    ~Set(); //
//    Set(const Set& other); //
//    Set& operator=(const Set& rhs); //
//    
//private:
//    struct Node
//    {
//        T m_value;
//        Node*    m_next;
//        Node*    m_prev;
//    };
//    
//    Node* m_head;
//    int   m_size;
//    
//    void createEmpty();
//    
//    void insertAtTail(const T& value);
//    
//    void doErase(Node* p);
//    
//    Node* find(const T& value) const;
//};
//
//template <typename T>
//void unite(const Set<T>& s1, const Set<T>& s2, Set<T>& result);
//
//template <typename T>
//void subtract(const Set<T>& s1, const Set<T>& s2, Set<T>& result);
//
//
//// Set function implementations
//
//template <typename T>
//Set<T>::Set()
//{
//    createEmpty();
//}
//
//template <typename T>
//int Set<T>::size() const
//{
//    return m_size;
//}
//
//template <typename T>
//bool Set<T>::empty() const
//{
//    return size() == 0;
//}
//
//template <typename T>
//bool Set<T>::contains(const T& value) const
//{
//    return find(value) != m_head;
//}
//
//
//template <typename T>
//bool Set<T>::insert(const T& value)
//{
//    // Fail if value already present
//    
//    if (contains(value) )
//        return false;
//    
//    // Insert new Node (at tail; choice of position is arbitrary),
//    // incrementing m_size
//    
//    insertAtTail(value);
//    return true;
//}
//
//template <typename T>
//bool Set<T>::erase(const T& value)
//{
//    // Find the Node with the value, failing if there is none.
//    
//    Node* p = find(value);
//    if (p == m_head)
//        return false;
//    
//    // Erase the Node, decrementing m_size
//    doErase(p);
//    return true;
//}
//
//template <typename T>
//bool Set<T>::get(int i, T& value) const
//{
//    if (i < 0  ||  i >= m_size)
//        return false;
//    
//    Node* p;
//    if (i < m_size / 2)  // closer to head
//    {
//        p = m_head->m_next;
//        for (int k = 0; k != i; k++)
//            p = p->m_next;
//    }
//    else  // closer to tail
//    {
//        p = m_head->m_prev;
//        for (int k = m_size-1; k != i; k--)
//            p = p->m_prev;
//    }
//    
//    value = p->m_value;
//    return true;
//}
//
//template <typename T>
//void Set<T>::swap(Set& other)
//{
//    // Swap head pointers
//    
//    Node* p = other.m_head;
//    other.m_head = m_head;
//    m_head = p;
//    
//    // Swap sizes
//    
//    int s = other.m_size;
//    other.m_size = m_size;
//    m_size = s;
//}
//
//template <typename T>
//Set<T>::~Set()
//{
//    // Delete all Nodes from first non-dummy up to but not including
//    // the dummy
//    
//    while (m_head->m_next != m_head)
//        doErase(m_head->m_next);
//    
//    // delete the dummy
//    
//    delete m_head;
//}
//
//template <typename T>
//Set<T>::Set(const Set& other)
//{
//    createEmpty();
//    
//    // Copy all non-dummy other Nodes.  (This will set m_size.)
//    // Inserting each new node at the tail rather than anywhere else is
//    // an arbitrary choice.
//    
//    for (Node* p = other.m_head->m_next; p != other.m_head; p = p->m_next)
//        insertAtTail(p->m_value);
//}
//
//template <typename T>
//Set<T>& Set<T>::operator=(const Set& rhs)
//{
//    if (this != &rhs)
//    {
//        // Copy and swap idiom
//        
//        Set temp(rhs);
//        swap(temp);
//    }
//    return *this;
//}
//
//template <typename T>
//void Set<T>::createEmpty()
//{
//    m_size = 0;
//    
//    // Create dummy node
//    
//    m_head = new Node;
//    m_head->m_next = m_head;
//    m_head->m_prev = m_head;
//}
//
//template <typename T>
//void Set<T>::insertAtTail(const T& value)
//{
//    // Create a new node
//    
//    Node* newNode = new Node;
//    newNode->m_value = value;
//    
//    // Insert new item at tail of list (predecessor of the dummy at m_head)
//    //     Adjust forward links
//    
//    newNode->m_next = m_head;
//    m_head->m_prev->m_next = newNode;
//    
//    //     Adjust backward links
//    
//    newNode->m_prev = m_head->m_prev;
//    m_head->m_prev = newNode;
//    
//    m_size++;
//}
//
//template <typename T>
//void Set<T>::doErase(Node* p)
//{
//    // Unlink p from the list and destroy it
//    
//    p->m_prev->m_next = p->m_next;
//    p->m_next->m_prev = p->m_prev;
//    delete p;
//    
//    m_size--;
//}
//
//template <typename T>
//typename Set<T>::Node* Set<T>::find(const T& value) const
//{
//    // Walk through the list looking for a match
//    
//    Node* p = m_head->m_next;
//    for ( ; p != m_head  &&  p->m_value != value; p = p->m_next)
//        ;
//    return p;
//}
//
//// Declaration/implementation of non-member functions
//
//template <typename T>
//void unite(const Set<T>& s1, const Set<T>& s2, Set<T>& result)
//{
//    const Set<T>* sp = &s2;
//    if (&result == &s1)
//    {
//        if (&result == &s2)
//            return;
//    }
//    else if (&result == &s2)
//        sp = &s1;
//        else
//        {
//            result = s1;
//            if (&s1 == &s2)
//                return;
//        }
//    for (int k = 0; k < sp->size(); k++)
//    {
//        T v;
//        sp->get(k, v);
//        result.insert(v);
//    }
//}
//
//template <typename T>
//void subtract(const Set<T>& s1, const Set<T>& s2, Set<T>& result)
//{
//    
//    Set<T> s2copy(s2);
//    result = s1;
//    for (int k = 0; k < s2copy.size(); k++)
//    {
//        T v;
//        s2copy.get(k, v);
//        result.erase(v);
//    }
//}
//
//#endif // SET_INCLUDED