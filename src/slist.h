#pragma once

#include <stdlib.h>
#include <atomic>

namespace slib{
class ListHead{
public:
	ListHead *n, *p;
    std::atomic_int ref;
    int size;
    uint sharable : 1;

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