#pragma once

template<typename KeyType>
class BloomFilter{
private:
	static const size_t bitsPerByte=8;
	BloomFilter(size_t size){
	  this->data=new uint8_t[size];
	  this->dataLen=size;
	};
	
	static uint32_t BloomHash(const KeyType& key) {
	  return Hash(key.data(), key.size(), 0xbc9f1d34);
	}

	void init(const KeyType* keys, int n){
		const size_t bits=dataLen*bitsPerByte;
		//TODO:for each
		 for (size_t i = 0; i < n; ++i) {
			// Use double-hashing to generate a sequence of hash values.
			// See analysis in [Kirsch,Mitzenmacher 2006].
			uint32_t h = BloomHash(keys[i]);
			const uint32_t delta = (h >> 17) | (h << 15);  // Rotate right 17 bits
			for (size_t j = 0; j < k_; j++) {
			const uint32_t bitpos = h % bits;
			data[bitpos/8] |= (1 << (bitpos % 8));
			h += delta;
			}
		 }
	}
	
	uint8_t* data[];
	const size_t dataLen;
	size_t bits_per_key_;
	size_t k_;
	
public:
	bool KeyMayMatch(const KeyType& key, const KeyType& bloom_filter){
		
	}
	
	static BloomFilter create(const KeyType* keys, int n, int bits_per_key){
		//计算需要多少位。不能太少，至少64位，否则假阳性率太高
		size_t bits = std::max(64,n * bits_per_key);
		
		//把位数折合成字节数，此时要向上取整。例如： 9位=2字节

		size_t bytes = (bits + (bitsPerByte-1) ) / bitsPerByte;
		bits = bytes * bitsPerByte;
		
		BloomFilter ret=new BloomFilter(bytes);
		ret.bits_per_key_=bits_per_key;
		double ln2_=0.69; // 0.69 =~ ln(2)		
		//k应该在[1，30]之间
		ret.k_=std::min<size_t>(30,std::max<size_t>(1,static_cast<size_t>(bits_per_key * ln2_)));  
		ret.init(keys,n);		
	}
	~BloomFilter() throw (){
		delete[] this->data;
	}
};
