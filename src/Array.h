/*
 * Array.h
 *
 *  Created on: Mar 5, 2010
 *      Author: root
 */

#ifndef ARRAY_H_
#define ARRAY_H_

template<typename T>
class Array {
private:
	T* pStart;
	T* pFinish;
	T* pEndOfStorage;

public:
	Array():pStart(NULL),pFinish(NULL),pEndOfStorage(NULL) {

	}

	virtual ~Array() {

	}

};

#endif /* ARRAY_H_ */
