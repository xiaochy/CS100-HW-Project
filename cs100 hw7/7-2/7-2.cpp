#include <cstddef>
#include <iterator>
#include <type_traits>
#include <utility>
#include<iostream>
using namespace std;
// The node structure of the linked-list.
template <typename T>
struct Slist_node {
    T value;
    Slist_node<T>* next;
    // Add constructors if you need.
    Slist_node(const Slist_node<T>& other) :value(other.value), next(other.next) {  //对的

    }
    Slist_node(T o_value) :value(o_value), next(nullptr) {   //对的

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
    Slist_iterator(node_t* pos = nullptr) : m_cur(pos) {}
    ~Slist_iterator() {
        //delete m_cur;
    }

    template <typename Other,
        typename = typename std::enable_if<
        is_const&&
        std::is_same<Other, Slist_iterator<T, false>>::value>::type>
    Slist_iterator(const Other& oi) : m_cur(oi.base()) {}

    node_t* base() const {    //对的
        return m_cur;
    }

    self_t next() const {
        return self_t(m_cur->next);//这里返回的是一个Slist_iterator对象，参数是调用该函数的Slist_iterator对象的m_cur->next 就是用Slist_iterator所指向的元素的下一个的地址作为参数构造出新的一个iterator 
    }

    reference operator*() const {   //对的
        return this->base()->value;
    }

    pointer operator->() const {
        return std::addressof(operator*());
    }

    self_t& operator++() {  //对的
        m_cur = m_cur->next;
        return *this;
    }

    self_t operator++(int) {  //对的
        auto temp = *this;
        ++*this;
        return temp;
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
    void swap(Slist<T>& other){
        using std::swap;
        swap(m_length, other.m_length);
        swap(m_head, other.m_head);

    }
    Slist() :m_head(nullptr), m_length(0) {  

    }
    Slist(const Slist<T>& other):m_head(nullptr),m_length(0) {//要把list中的元素都拷贝过来  //这里有大问题...根本没有复制任何的结点
        //Slist_node<T>* current = nullptr;//current
        //Slist_node<T>* after = nullptr;//next

        //if (other.m_head == nullptr) {
        //    m_head = nullptr;
        //}
        //else{
        //    m_head = new Slist_node<T>(other.m_head->value);
        //    //m_head->value = other.m_head->value;
        //    current = m_head;
        //    after = other.m_head->next;
        //}
        //while (after!=nullptr){
        //    current->next = new Slist_node<T>(after->value);
        //    current = current->next;
        //    //current->value = after->value;
        //    after = after->next;
        //}
        //current->next = nullptr;
        //delete current;
        //delete after;
        Slist<T> temp;                  //对的
        for (const auto& x : other) {
            temp.push_front(x);
        }
        for (const auto& x : temp) {
            this->push_front(x);
        }
    }

    Slist& operator=(const Slist<T>& other) { //对的
        Slist<T>(other).swap(*this);
        return *this;
    }
    ~Slist() {
        if (!empty()) {
            Slist_node<T>* temp1 = m_head;
            while (temp1 != nullptr) {
                Slist_node<T>* temp2 = temp1;
                temp1 = temp1->next;
                delete temp2;
            }
            delete temp1;
        }
    }

    void push_front(const value_type& value) {
        Slist_node<T>* new_node = new Slist_node<T>(value);
        new_node->next = m_head;
        m_head = new_node;
        m_length += 1;
    }

    void pop_front() {
        m_length -= 1;
        Slist_node<T>* ptr = m_head->next;
        delete m_head;
        m_head = ptr;
    }

    // Insert an element with given value after the position denoted by 'pos'.
    // Return an iterator pointing to the element that has been inserted.
    iterator insert_after(const_iterator pos, const value_type& value) {
        Slist_node<T>* new_node = new Slist_node<T>(value);
        new_node->next = pos.base()->next;
        Slist_iterator<T, false> new_iterator(new_node);
        pos.base()->next = new_node;
        m_length += 1;
        return new_iterator;
    }

    // Erase the element after the position denoted by 'pos'.   
    void erase_after(const_iterator pos) {
        m_length -= 1;
        Slist_node<T>* ptr = pos.base()->next->next;
        delete pos.base()->next;
        pos.base()->next = ptr;
    }


    size_type size()const {  //对的
        return m_length;
    }

    void clear() {  //对的
        //Slist_node<T>* temp1 =this->m_head;
        //Slist_node<T>* temp2=nullptr;
        //while (temp1 != nullptr)
        //{
        //    temp2 = temp1->next;
        //    delete temp1;
        //    temp1 = temp2;
        //}
        ////delete temp1;
        ////delete temp2;
        //this->m_head = nullptr;
        //m_length = 0;
        while (!this->empty()) {
            this->pop_front();
        }
    }

    bool empty()const { //对的
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
inline bool operator==(const Slist<T>& lhs, const Slist<T>& rhs) {  //对的
    return equal(lhs.begin(), lhs.end(), rhs.begin(),rhs.end());
}

// Lexicographical-order comparison.
// It is guaranteed that we will only use this operator when
// bool operator<(const T &, const T &) is defined.
// Hint: Use std::lexicographical_compare and the iterators you have defined.
template <typename T>
inline bool operator<(const Slist<T>& lhs, const Slist<T>& rhs) {//对的
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

/**********************************************************/

// This type is not default-constructible and not copy-assignable.
// You should make sure that your Slist can store such thing.
class Special_type {
    int x;

public:
    Special_type() = delete;
    Special_type(const Special_type&) = default;
    Special_type& operator=(const Special_type&) = delete;
    Special_type(int xx) : x(xx) {}
    int get() const {
        return x;
    }
};

inline bool operator==(const Special_type& lhs, const Special_type& rhs) {
    return lhs.get() == rhs.get();
}

inline bool operator<(const Special_type& lhs, const Special_type& rhs) {
    return lhs.get() < rhs.get();
}

// The following are some compile-time checks.

static_assert(std::is_default_constructible<Slist<int>>::value,
    "Slist should be default-constructible.");

static_assert(std::is_copy_constructible<Slist<int>>::value,
    "Slist should be copy-constructible.");

static_assert(std::is_copy_assignable<Slist<int>>::value,
    "Slist should be copy-assignable.");

// Note: even if the following two assertions succeed, your Slist may still have
// some problem when storing data of the Special_type. These static-assertions
// only deduce whether the relevant functions are callable, without actually
// calling them. You need to try on your own to test whether any error arises
// when some functions are called.

static_assert(std::is_default_constructible<Slist<Special_type>>::value,
    "Slist<T> should be default-constructible even if T is not.");

static_assert(std::is_copy_assignable<Slist<Special_type>>::value,
    "Slist<T> should be copy-assignable even if T is not.");

static_assert(
    std::is_same<decltype(++std::declval<Slist_iterator<int, false>>()),
    Slist_iterator<int, false>&>::value,
    "Prefix operator++ should return reference to the object itself.");

namespace detail {

    template <typename T = Slist_iterator<int, false>,
        typename = decltype(((const T*)nullptr)->operator*())>
    std::true_type deref_const_helper(int);

    std::false_type deref_const_helper(double);

    constexpr bool deref_is_const = decltype(deref_const_helper(0))::value;

    template <typename T = Slist<int>,
        typename = decltype(((const T*)nullptr)->size())>
    std::true_type size_const_helper(int);

    std::false_type size_const_helper(double);

    constexpr bool size_is_const = decltype(size_const_helper(0))::value;

    template <typename T = Slist<int>,
        typename = decltype(((const T*)nullptr)->empty())>
    std::true_type empty_const_helper(int);

    std::false_type empty_const_helper(double);

    constexpr bool empty_is_const = decltype(empty_const_helper(0))::value;

    constexpr bool size_return_size_type =
        std::is_same<decltype(std::declval<Slist<int>>().size()),
        Slist<int>::size_type>::value;

    constexpr bool assignment_return_ref =
        std::is_same<decltype(std::declval<Slist<int>>().operator=(
            std::declval<Slist<int>>())),
        Slist<int>&>::value;

} // namespace detail

static_assert(detail::deref_is_const,
    "Why don't you define Slist_iterator::operator* as a const "
    "member function?");

static_assert(detail::size_is_const,
    "Why don't you define Slist::size as a const member function?");

static_assert(detail::empty_is_const,
    "Why don't you define Slist::empty as a const member function?");

static_assert(
    detail::size_return_size_type,
    "The return-type of Slist<T>::size() should be Slist<T>::size_type.");

static_assert(
    detail::assignment_return_ref,
    "operator= should return reference to the object on the left-hand side.");

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RESET "\x1b[0m"

#define SET_COLOR(COLOR, STRING) (ANSI_COLOR_##COLOR STRING ANSI_COLOR_RESET)

#define RED(STRING) SET_COLOR(RED, STRING)
#define GREEN(STRING) SET_COLOR(GREEN, STRING)

inline void report_if_wrong(bool condition, long line) {
    if (!condition) {
        std::cout << ANSI_COLOR_RED "Wrong on line " << line << ANSI_COLOR_RESET
            << std::endl;
        exit(0);
    }
}

#ifdef assert
#undef assert
#endif

#define assert(COND) report_if_wrong(COND, __LINE__)

int main() {
    std::cout << GREEN("You've passed the compile-time tests.") << std::endl;

    int a[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
    Slist<int> list;
    for (auto x : a)
        list.push_front(x);
    assert(list.size() == 10);
    assert(!list.empty());
    int num = 0;
    for (auto x : list)
       assert(x == num++); 
    

    for (auto i = 0; i != 5; ++i)
        list.pop_front();
    assert(list.size() == 5);
    assert(!list.empty());
    num = 5;
    for (auto x : list)
        assert(x == num++);

    --* list.begin();
    --* list.begin();
    list.insert_after(list.cbegin(), 5);
    list.insert_after(list.cbegin(), 4);
    assert(list.size() == 7);
    assert(!list.empty());
    num = 3;
    for (auto x : list)
        assert(x == num++);//在这里有问题

    for (auto i = 0; i != 4; ++i)
        list.erase_after(list.begin());
    assert(list.size() == 3);
    assert(!list.empty());
    *list.begin() = 7;
    num = 7;
    for (auto x : list)
        assert(x == num++);//在这里有问题

    list.clear();
    assert(list.size() == 0);
    assert(list.empty());
    assert(list.begin() == list.end());

    std::cout << GREEN("Congratulations! You've passed the simple test.")
        << std::endl;
    return 0;
}