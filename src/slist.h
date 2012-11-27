#pragma once

#include <stdlib.h>
//#include <atomic>
#include <tbb/atomic.h>
#include <iterator>

namespace slib{
class ListHead{
public:
	ListHead *n, *p;
    tbb::atomic<int> ref;
    int size;
    bool sharable ;

    static ListHead shared_null;
};
  
template <typename T>
class ListEntry{
public:  
	ListEntry* next;
	ListEntry* prev;
	T t;
	ListEntry(const T& arg):t(arg){}
};
  
template <typename T>
class LinkedList{
	typedef ListEntry<T> Node;
	union { ListHead *d; Node *e; };

public:
	inline LinkedList(const LinkedList<T> &l) : d(l.d) { d->ref++; if (!d->sharable) detach(); }
	inline LinkedList() : d(&ListHead::shared_null) { d->ref++; }
	
	bool isDetached() const { return d->ref == 1; }
	
	inline void detach(){ 
		if (!isDetached()) 
			detach_helper(); 
	}
	
	/**
	 * 返回链表的长度
	 */
	int size() const { return d->size; }
	
	/**
	 * 判断链表是否为空
	 */
	bool isEmpty() const { return d->size == 0; }
	
	/**
	 * 向末尾追加一个元素
	 */
	void append(const T &t){
		detach();
		
		Node *i = new Node(t);
		i->next = e;
		i->prev = e->prev;
		i->prev->next = i;
		e->prev = i;
		d->size++;
	}
	
	/**
	 * 计算某个元素的出现次数
	 */
	size_t count(const T &t) const{
		Node *i = e;
		size_t c = 0;
		while ((i = i->next) != e)
			if (i->t == t)
				c++;
		return c;
	}

	/** 
	 * 清空链表
	 */
	void clear(){
		 *this = LinkedList<T>();
	}
	
	/**
	 * 重载等号运算符
	 */
	LinkedList<T> & operator=(const LinkedList<T> &l)
	{
		if (d != l.d) {
			ListHead *o = l.d;
			o->ref++;
			if (!--d->ref)
				destroy(d);
			d = o;
			if (!d->sharable)
				detach_helper();
		}
		return *this;
	}
	
	~LinkedList(){
		if (!d)
			return;
		try{
			if (!--d->ref)
				destroy(d);
		}catch(...){
			
		}	
	};
	
	class list_iterator
{
protected:
  Node* _M_current;

  typedef std::iterator_traits<T*>                traits_type_;

public:
  typedef Node*                                 iterator_type;
  typedef typename traits_type_::iterator_category iterator_category;
  typedef typename traits_type_::value_type        value_type;
  typedef typename traits_type_::difference_type   difference_type;
  typedef typename traits_type_::reference         reference;
  typedef typename traits_type_::pointer           pointer;

  list_iterator() : _M_current(NULL) { }

  explicit list_iterator(const Node* __i) : _M_current(__i) { }

  
  // Forward iterator requirements
  reference
  operator*() const
  { return _M_current->t; }

  pointer
  operator->() const
  { return &_M_current->t; }

  
  bool operator==(const list_iterator &o) const { return _M_current == o._M_current; }
  bool operator!=(const list_iterator &o) const { return _M_current != o._M_current; }
  
  /* bool operator==(const list_iterator &o) const
		{ return _M_current == o._M_current; }
  bool operator!=(const list_iterator &o) const
		{ return _M_current != o._M_current; } */
		
  list_iterator&
  operator++(){
   _M_current = _M_current->next; 
   return *this;
  }

  list_iterator
  operator++(int)
  {  Node *n = _M_current; _M_current = _M_current->next; return n; }

  // Bidirectional iterator requirements
  list_iterator&
  operator--()
  {
	_M_current = _M_current->prev; 
	return *this;
  }

  list_iterator
  operator--(int)
  { Node *n = _M_current; _M_current = _M_current->prev; return n;}


  list_iterator&
  operator+=(const difference_type& j)
  { return *this = *this + j; }

  list_iterator
  operator+(const difference_type& j) const
  { Node *n = _M_current; 
	if (j > 0) {
	   while (j--) 
		 n = n->n; 
	}
	else {
	   while (j++) n = n->p;    
	}
	return n; 
   }
	

  list_iterator&
  operator-=(const difference_type& j)
  { return *this = *this - j;}

  list_iterator
  operator-(const difference_type& j) const
  { return operator+(-j); }

  const Node*  base() const
  { return _M_current; }
};
private:
	void destroy(ListHead *x){
		Node *y = reinterpret_cast<Node*>(x);
		Node *i = y->next;
		if (x->ref == 0) {
			while(i != y) {
				Node *n = i;
				i = i->next;
				delete n;
			}
			delete x;
		}
	}
    /** copy on write的copy */
    void detach_helper(){
		union { ListHead *d; Node *e; } x;
		x.d = new ListHead;
		x.d->ref = 1;
		x.d->size = d->size;
		x.d->sharable = true;
		Node *original = e->next;
		Node *copy = x.e;
		while (original != e) {
			try {
				copy->next = new Node(original->t);
				copy->next->prev = copy;
				original = original->next;
				copy = copy->next;
			} catch(...) {
				copy->next = x.e;
				destroy(x.d);
				throw;
			}
		}
		copy->next = x.e;
		x.e->prev = copy;
		if (!--d->ref)
			destroy(d);
		d = x.d;
	}
};

}