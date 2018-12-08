#ifndef GTUSETBASE_HPP
#define GTUSETBASE_HPP


namespace MySpace{
	
	template<class T>
	class GTUSetBase{
		public:
			typedef std::iterator<std::bidirectional_iterator_tag, T> myIterator;
			virtual bool empty() = 0;
			virtual int size() = 0;
			virtual int max_size() = 0;
			virtual std::pair<myIterator, bool> insert (T val) = 0;
			virtual myIterator erase(myIterator position) = 0;
			virtual void clear() = 0;
			virtual myIterator find (T val)  = 0;
			virtual size_t count (T val)  = 0;
			virtual myIterator begin() = 0;
			virtual myIterator end() = 0;

	};

}

//#include "GTUSetBase.cpp"

#endif