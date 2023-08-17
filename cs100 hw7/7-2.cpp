#include <cstddef>
#include <iterator>
#include <type_traits>
#include <utility>

using namespace std;
// The node structure of the linked-list.
template <typename T>
struct Slist_node {
    T value;
    Slist_node<T>* next;
    // Add constructors if you need.
    Slist_node(const Slist_node<T>& other):value(other.value),next(other.next) {

    }
    Slist_node(T o_value):value(o_value),next(nullptr) {

    }
};

template <typename T>
class Slist;


template <typename T, bool is_const>
class Slist_iterator {
public:
    using value_type = T;
    using difference_type = typename Slist<T>::difference_type;  //就是用左边的比较简短的名称来替代右边很长的名称
    using pointer = typename std::conditional<is_const, const T*, T*>::type; //即如果is_const为true，则pointer指的是const T*这个类型，反之则是T*
    using reference = typename std::conditional<is_const, const T&, T&>::type;
    using iterator_category = std::forward_iterator_tag;

private:
    using node_t = Slist_node<T>;                  //node_t与self_t代表的都是class
    using self_t = Slist_iterator<T, is_const>;
    node_t* m_cur;  //m_cur指向Slist_node<T>这个class的对象也就是指向node_t这个class的对象

public:
    Slist_iterator(node_t* pos=nullptr) : m_cur(pos) {}   
    ~Slist_iterator() {
        delete m_cur;
    }

    template <typename Other,
        typename = typename std::enable_if<
        is_const&&
        std::is_same<Other, Slist_iterator<T, false>>::value>::type>
    Slist_iterator(const Other& oi) : m_cur(oi.base()) {}

    node_t* base() const {
        return m_cur;
    }

    self_t next() const {
        return self_t(m_cur->next);//这里返回的是一个Slist_iterator对象，参数是调用该函数的Slist_iterator对象的m_cur->next 就是用Slist_iterator所指向的元素的下一个的地址作为参数构造出新的一个iterator 
    }

    reference operator*() const {   //感觉这里不太对
        return this->base()->value;
    }

    pointer operator->() const {
        return std::addressof(operator*());
    }

    self_t& operator++() {
        m_cur->next = m_cur->next->next;
        return *this;
    }

    self_t operator++(int) {
        Slist_node<T>* new_node = new Slist_node<T>(*(this->base()));
        Slist_iterator<T,false>* object = new Slist_iterator<T,false>(new_node);
        /*object->base()->next = this->base()->next;
        object->base()->value = this->base()->value;*/
        m_cur->next = m_cur->next->next;
        return *object;
    }
};


template <typename T, bool C1, bool C2>
inline bool operator==(const Slist_iterator<T, C1>& lhs,
    const Slist_iterator<T, C2>& rhs) {
    return lhs.base() == rhs.base();   
}

template <typename T, bool C1, bool C2>
inline bool operator!=(const Slist_iterator<T, C1>& lhs,
    const Slist_iterator<T, C2>& rhs) {
    return !(lhs == rhs);            
}

template <typename T>
class Slist {
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;
    using const_pointer = const T*;
    using const_reference = const T&;

    using iterator = Slist_iterator<T, false>;
    using const_iterator = Slist_iterator<T, true>;

private:
    using node_t = Slist_node<T>;
    node_t* m_head;  //指向Slist_node<T>这个类对象的指针
    size_type m_length;

public:
     void swap(Slist& other)  
    {
        using std::swap;
        //std::swap(obj1.m_head, obj2.m_head);//要把list中的元素都拷贝过来
        Slist_node<T>* temp1 = m_head;
        Slist_node<T>* temp2 = other.m_head;
        while (temp1 != nullptr)
        {
            swap(temp1, temp2);
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        delete temp1;
        delete temp2;
        swap(m_length, other.m_length);
    }
    Slist():m_head(nullptr),m_length(0) {
        
    }
    Slist(const Slist& other) {//要把list中的元素都拷贝过来
        m_length = other.m_length;
        Slist_node<T>* temp1 = other.m_head;
        Slist_node<T>* temp2 = m_head;
        while (temp1 != nullptr)
        {
            temp2 = temp1;
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        delete temp1; 
        delete temp2;
    }
    
    Slist& operator=(const Slist& other) {
        Slist(other).swap(*this);
        return *this;
    }
    ~Slist() {
        Slist_node<T>* temp1 = this->m_head;
        Slist_node<T>* temp2 = nullptr;
        while (temp1 != nullptr)
        {
            temp2 = temp1->next;
            delete temp1;
            temp1 = temp2;
        }
        delete temp1;//可写可不写？
        delete temp2;
    }
 
    void push_front(const value_type& value) {
        Slist_node<T>* new_node = new Slist_node<T>(value);
        new_node->next = m_head;
        m_head = new_node;
        m_length += 1;
    }

    void pop_front() {
        Slist_node<T>* temp1 = this->m_head;
        m_head = temp1->next;
        delete temp1;
        m_length -= 1;
    }

    // Insert an element with given value after the position denoted by 'pos'.
    // Return an iterator pointing to the element that has been inserted.
    iterator insert_after(const_iterator pos, const value_type& value) {
        
        Slist_node<T>* new_node = new Slist_node<T>(value);
        new_node->next = pos.base()->next;
        Slist_iterator<T, false>* new_iterator = new Slist_iterator<T, false>(new_node);
        
        pos.base()->next = new_node;
        m_length += 1;
        //new_iterator->base()->next = new_node->next;
        //new_iterator->base()->value = new_node->value;  //可以把这两步综合起来写成new_iterator->base()=new_node;吗？
        return *new_iterator;
    }

    // Erase the element after the position denoted by 'pos'.   
    void erase_after(const_iterator pos) {
        Slist_node<T>* temp1 = pos.base()->next;
        pos.base()->next = pos.base()->next->next;
        delete temp1;
        m_length -= 1;
    }


    size_type size()const{
        return m_length;
    }

    void clear() {
        Slist_node<T>* temp1 = this->m_head;
        Slist_node<T>* temp2 = nullptr;
        while (temp1 != nullptr)
        {
            temp2 = temp1->next;
            delete temp1;
            temp1 = temp2;
        }
        delete temp1;
        this->m_head = nullptr;
        m_length = 0;
    }
    
    bool empty()const {
        if (this->size() == 0) {
            return true;
        }
        else {
            return false;
        }
    }
    // The following are the well-known 'begin' and 'end' functions.
    iterator begin() {
        return iterator(m_head);
    }

    iterator end() {
        return iterator(nullptr);
    }

    // Why do we need these two functions? Think about this.
    const_iterator begin() const {
        return const_iterator(m_head);
    }

    const_iterator end() const {
        return const_iterator(nullptr);
    }

    // Note:
    // It was not until C++11 that cbegin() and cend() were added to the standard.
    const_iterator cbegin() const {
        return begin();
    }

    const_iterator cend() const {
        return end();
    }
};

// Two Slists are thought of as equal if and only if they are of the same
// length, and every pair of corresponding elements are equal.
// It is guaranteed that we will only use this operator when
// bool operator==(const T &, const T &) is defined.
// Hint: Use std::equal and the iterators you have defined.
template <typename T>
inline bool operator==(const Slist<T>& lhs, const Slist<T>& rhs) {
    return equal(lhs.begin(), lhs.end(), rhs.begin());   
}

// Lexicographical-order comparison.
// It is guaranteed that we will only use this operator when
// bool operator<(const T &, const T &) is defined.
// Hint: Use std::lexicographical_compare and the iterators you have defined.
template <typename T>
inline bool operator<(const Slist<T>& lhs, const Slist<T>& rhs) {
    return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());   
}

// Why do we define the following functions like this? Think about it.
template <typename T>
inline bool operator!=(const Slist<T>& lhs, const Slist<T>& rhs) {
    return !(lhs == rhs);
}

template <typename T>
inline bool operator>(const Slist<T>& lhs, const Slist<T>& rhs) {
    return rhs < lhs;
}

template <typename T>
inline bool operator<=(const Slist<T>& lhs, const Slist<T>& rhs) {
    return !(lhs > rhs);
}

template <typename T>
inline bool operator>=(const Slist<T>& lhs, const Slist<T>& rhs) {
    return !(lhs < rhs);
}

