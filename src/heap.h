#pragma once

//TODO:HAVE_GRAPHVIZ 、HAVE_ACE

#include <stddef.h>

#ifdef HAVE_ACE
#include <ace/OS.h>
#include <ace/Log_Msg.h>
#endif

#ifdef HAVE_GRAPHVIZ
#include <gvc.h>
#include <sstream>
#endif

/**
 * Compare(child,parent) 应始终为true。例如用std::less则为最大堆（最大的元素在顶部）
 *
 */
namespace slib {
template<typename T, typename Compare, typename Allocator = class MallocAllocator>
class Heap {
public:
	typedef size_t size_type;
	typedef T value_type;
	typedef value_type * iterator;
	typedef value_type const * const_iterator;
	typedef value_type & reference;
	typedef value_type const & const_reference;
	typedef value_type * pointer;
	typedef value_type const * const_pointer;

	static const size_type nop = (size_type) -1;

	Heap(size_type initCapacity = 0x10) {
		const size_type totalsize = initCapacity * sizeof(T);
		dataEnd = storageBegin = (T*) Allocator::malloc(totalsize);
		// if (storageBegin == NULL) throw
		storageEnd = storageBegin + initCapacity;
	}

	virtual ~Heap() {
		for (iterator iter = begin(); iter != end(); ++iter) {
			iter->~T();
		}
		Allocator::free(storageBegin);
	}

	void add(const T& v) {
		push_back(v);
		//因为已经放进去一个东西了，所以getSize肯定>=1
		size_type i = this->getSize() - 1;
		size_type parent;
		Compare cmp;
		while ((parent = this->getParent(i)) != nop) {
			if (!cmp(v, this->get(parent))) {
				this->get(i) = this->get(parent);
				i = parent;
			} else
				break;
		}
		this->get(i) = v;
#ifndef NDEBUG
		validate();
#endif
	}

	int take(T& t) {
		if (this->getSize() == 0)
			return -1;
		t = this->get(0);
		//adjust the heap
		T tmp = this->get(this->getSize() - 1);
		size_type i = 0;
		size_type left;
		Compare cmp;
		while ((left = this->getLeftChild(i)) != nop) {
			if (!cmp(this->get(left), tmp)) {
				this->get(i) = this->get(left);
				i = left;
				continue;
			}
			if ((left = this->getRightChild(i)) == nop)
				break;
			if (!cmp(this->get(left), tmp)) {
				this->get(i) = this->get(left);
				i = left;
			}
		}
		this->get(i)=tmp;
#ifndef NDEBUG
		validate();
#endif
	}

	iterator begin() {
		return storageBegin;
	}

	const_iterator begin() const {
		return storageBegin;
	}

	iterator end() {
		return dataEnd;
	}

	const_iterator end() const {
		return dataEnd;
	}

	size_type getCapacity() const {
		return storageEnd - storageBegin;
	}

	size_type getSize() const {
		return dataEnd - storageBegin;
	}

	/**
	 *  T 需要支持std::ostringstream流输出。
	 */
	int outputAsGraph(const char* filename) {
#ifdef HAVE_GRAPHVIZ
		size_type nodesNumber=this->getSize();
		char* fname=strdup(filename);
		GVC_t *gvc=gvContext();
		Agraph_t *g = agopen("g", AGDIGRAPH);
		Agnode_t** nodes=(Agnode_t**)Allocator::malloc(sizeof(Agnode_t*)*nodesNumber);
		for(size_type i=0;i!=nodesNumber;++i) {
			std::ostringstream oss;
			oss<<this->get(i);
			std::string value=oss.str();
			char* tmpValue=strdup(value.c_str());
			nodes[i]=agnode(g,tmpValue);
			free(tmpValue);
			size_type p=getParent(i);
			if(p!=nop) {
				agedge(g,nodes[p],nodes[i]);
			}
		}
		Allocator::free(nodes);
		gvLayout(gvc, g,"dot");
		gvRenderFilename(gvc, g,"png",fname);
		gvFreeLayout(gvc, g);
		agclose(g);
		gvFreeContext(gvc);
		free(fname);
#endif
		return 0;
	}

	/**
	 * @return true,数据正确。false,数据内容不正确
	 */
	bool validate() {
		size_type i = 0;
		size_type left, right;
		Compare cmp;
		bool ret = true;
		while ((left = this->getLeftChild(i)) != nop) {
			if (!cmp(this->get(left), this->get(i))) {
				ret = false;
				break;
			}
			right = this->getRightChild(i);
			if (right == nop)
				break;
			if (!cmp(this->get(right), this->get(i))) {
				ret = false;
				break;
			}
			i = right + 1;
		}
#ifdef HAVE_ACE
		if(!ret)
		ACE_DEBUG((LM_ERROR,ACE_TEXT("verify fail,result=%d\n"),ret));
#endif
		return ret;
	}

	/**
	 * 设置保留的容量
	 */
	int setCapacity(size_type newCapacity) {
		if (newCapacity == this->getCapacity())
			return 0;
		if (newCapacity < this->getCapacity()) {
			return -1;
		}

		iterator const olddataEnd = dataEnd;
		iterator const oldstorageBegin = storageBegin;
		dataEnd = storageBegin = (T*) Allocator::malloc(newCapacity * sizeof(T));
		if (storageBegin == NULL)
			return -1;
		for (iterator i = oldstorageBegin; i != olddataEnd; ++i, ++dataEnd) {
			new (dataEnd) T(*i);
			i->~T();
		}
		Allocator::free(oldstorageBegin);
		storageEnd = storageBegin + newCapacity;
		return 0;
	}

private:
	iterator storageBegin;
	iterator storageEnd;
	iterator dataEnd;

	size_type getParent(size_type i) const {
		if (i == 0)
			return nop;
		else
			return (i + 1) / 2 - 1; //向下取整
	}

	size_type getLeftChild(size_type i) const {
		if (2 * i + 1 < this->getSize())
			return 2 * i + 1;
		else
			return nop;
	}

	size_type getRightChild(size_type i) const {
		if (2 * i + 2 < this->getSize())
			return 2 * i + 2;
		else
			return nop;
	}

	T& get(size_type i) const {
		return *(this->storageBegin + i);
	}

	void push_back(const T& v) {
		if (dataEnd >= storageEnd) {
			setCapacity(this->getCapacity() * 2);
		}
		new (dataEnd++) T(v);
	}
};

}
