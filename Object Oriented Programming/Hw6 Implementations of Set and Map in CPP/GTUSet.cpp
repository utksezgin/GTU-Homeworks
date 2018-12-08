using std::shared_ptr;
using std::pair;
using std::make_pair;

namespace mySpace{

	template<class T>
	mySpace::GTUSet<T>::GTUSet(){
		container = std::shared_ptr<V>(new int[5]);
		cSize = 0;
		mSize = 5;
		index = 0;
	}


	template<class T>
	mySpace::GTUSet<T>::GTUSet(GTUSet& other){
		std::shared_ptr<T> temp(new V[cSize]);

		for(int i=0; i<this->size(); ++i)
			temp.get()[i] = this->container.get()[i];

		

		this->container.reset();

		this->container = std::shared_ptr<int>(new V[other.max_size()]);

		for(int i=0; i<other.size(); ++i)
			this->container.get()[i] = temp.get()[i];

		cSize = other.size();
		mSize = other.max_size();
		index = 0;
	}


	template<class T>
	void GTUSet<T>::resize(int newSize){

		while(newSize > mSize)
			mSize *= 2;				//Expanding max size multiplying by 2 if the new size is bigger than max size.

		shared_ptr<T> temp(new V[cSize]);  //Storing old data on a temp variable

		for(int i=0; i<this->size(); ++i)
			temp.get()[i] = this->container.get()[i];

		this->container.reset(); //Clearing container

		this->container = shared_ptr<int>(new V[mSize]);

		for(int i=0; i<newSize; ++i)
			this->container.get()[i] = temp.get()[i]; //Restoring data from temp.
		temp.reset();
	}


	template<class T>
	bool GTUSet<T>::empty(){
		if(cSize == 0)
			return true;
		else
			return false;
	}


	template<class T>
	int GTUSet<T>::size(){
			return cSize;
	}


	template<class T>
	int GTUSet<T>::max_size(){
			return mSize;
	}


	template<class T>
	pair<GTUSet<T>::GTUIterator<T>*, bool> GTUSet<T>::insert (T val){

		GTUIterator<T> temp;

		for(int i =0; i<cSize; ++i){
			if(val == container.get()[i]){
				//Throw exception
				temp.index = i;
				temp.itP = container.get()[i];
				return make_pair(temp, false);
			}
		}

			if(cSize <= mSize)
				resize(cSize*2);
			for(int i=0; i<size; ++i){
				if( val >= container.get()[i] ){
					for(int j = cSize; j>i; --j) //shifting elements to right in order to make a space for new element
							container.get()[j] = container.get()[j-1];
					container.get()[i] = val; //Insertion
					++cSize;
					temp.itP = container.get()[i];
					temp.itP = container.get()[i];
				}
			}

		return make_pair(temp, true);
	}


	template<class T>
	GTUSet<T>::GTUIterator<T>* GTUSet<T>::erase(GTUSet<T>::GTUIterator<T>* position){
		if(position.index < cSize){
			std::cerr << "Iterator out of range" << std::endl;
			exit(-1);
		}
		if(!( GTUIterator<T>::hasNext() )){ //If trying to erase last element
			--cSize;
		}
		else{
			for(int i=position.index; i<size-1; ++i){//Shifting elements and decrementing size to erase the element
				container->get()[i] = container->get()[i+1];
				--cSize;
			}
		}
	}


	template<class T>
	void GTUSet<T>::clear(){
		container.reset();
		cSize = 0;
	}


	template<class T>
	GTUSet<T>::GTUIterator<T>* GTUSet<T>::find (V val) {
		GTUIterator<T> temp;
		for(int i=0; i<size; ++i){
			if( val == container->get()[i] ){
				temp.index = i;
				temp.itP = container.get()[i];
				return temp;
			}

			return ( temp = this->end() ); 
		}
	}


	template<class T>
	size_t GTUSet<T>::count (T val) {
		int count = 0;
		for(int i=0; i<cSize; ++i){
			if(container.get()[i] == val)
				++count;
		}
		return count;
	}


	template<class T>
	GTUSet<T>::GTUIterator<T>* GTUSet<T>::begin(){
		GTUIterator<T> it;
		it.itP = container.get()[0];
		it.index = 0;

		return it;
	}


	template<class T>
	GTUSet<T>::GTUIterator<T>* GTUSet<T>::end(){
		GTUIterator<T> it;
		it.itP = container.get()[cSize-1];
		it.index = cSize-1;
		
		return it;
	}


	template<class T>
	GTUSet<T>::~GTUSet(){
		container.reset();
		mSize = 0;
		cSize = 0;
	}


	/*****ITERATOR IMPLEMENTATION*****/

	template<class T>
	template<class U>
	GTUSet<T>::GTUIterator<U>::GTUIterator() : GTUSet<T>(), itP(container){};



	template<class T>
	template<class U>
	bool GTUSet<T>::GTUIterator<U>::hasNext(){
		if( index == size-1 )
			return false;
		else
			return true;
	}

	template<class T>
	template<class U>
	GTUSet<T>::GTUIterator<U>& GTUSet<T>::GTUIterator<U>::operator++(){
		if( hasNext() ){//Boundary check
			std::cerr << "This is the last element, you cannot increment anymore" << std::endl;
			return(*this);
		}
		else{
			++index;
			return (++itP);
		}	
	}

	template<class T>
	template<class U>
	GTUSet<T>::GTUIterator<U> GTUSet<T>::GTUIterator<U>::operator++(int){
		if( hasNext() ){//Boundary check
			std::cerr << "This is the last element, you cannot increment anymore" << std::endl;
			return(*this);
		}
		else{
			GTUIterator temp(*this);
			operator++();
			return temp;
		}	
	}


	template<class T>
	template<class U>
	GTUSet<T>::GTUIterator<U>& GTUSet<T>::GTUIterator<U>::operator--(){
		if(index == 0){//Boundary check
			std::cerr << "This is the first element, you cannot decrement anymore" << std::endl;
			return (*this);
		}
		else{
			--index;
			return (--itP);
		}
		
	}


	template<class T>
	template<class U>
	GTUSet<T>::GTUIterator<U> GTUSet<T>::GTUIterator<R, U>::operator--(int){
		if(index == 0){ //Boundary check
			std::cerr << "This is the first element, you cannot decrement anymore" << std::endl;
			return (*this);
		}
		else{
			GTUIterator temp(*this);
			operator--();
			return temp;
		}
	}


	template<class T>
	template<class U>
	GTUSet<T>::GTUIterator<U>& GTUSet<T>::GTUIterator<U>::operator=( tmplt){
		return (itP->get() = tmplt);
	}


	template<class T>
	template<class U>
	bool GTUSet<T>::GTUIterator<U>::operator==(T tmplt){
		if( this->itP.get() == tmplt->itP.get() )
			return true;
		else
			return false;
	}

	template<class T>
	template<class U>
	GTUSet<T>::GTUIterator<U>::~GTUIterator(){
		itP = nullptr;
	}
}