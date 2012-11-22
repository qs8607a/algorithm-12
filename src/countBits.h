#pragma once


namespace slib {

	/**
	 * 计算数字v的二进制表示中有多少个1
	 */	
	template <typename T>
	int countBits(T v){
		int c=0;
		while(v>0){
			if(v&1) c++;
			v>>=1;		
		}
		return c;
	}
	
	
};