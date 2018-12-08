#ifndef GTUSET_HPP
#define GTUSET_HPP
using std::shared_ptr;
using std::pair;
#include "GTUSetBase.hpp"

namespace mySpace{

	template<class U>
	class GTUSetBase;

	template<class T>
	class GTUSet : public GTUSetBase<T>{ //No Big three needed since we use shared_ptr
			template<class V>
			class GTUIterator{
				public:
					GTUIterator();

					bool hasNext(); //Checks if iterator is at the last element.
					GTUIterator& operator++();
					GTUIterator operator++(int);
					GTUIterator& operator--();
					GTUIterator operator--(int);
					GTUIterator& operator=(V tmplt);
					bool operator==(V tmplt);

					virtual ~GTUIterator();

				private:
					shared_ptr<V> *itP;

			};

			GTUSet();
			GTUSet(GTUSet& other);
	 		
			bool empty() override;
			int size() override;
			int max_size() override;
			pair<GTUIterator<T>, bool> insert (T val) override;
			GTUIterator<T> erase(GTUIterator<T> position) override;
			void clear() override;
			GTUIterator<T> find (T val) override;
			std::size_t count (T val) override;
			GTUIterator<T> begin() override;
			GTUIterator<T> end() override;

			virtual ~GTUSet();

		protected:
			void resize(int newSize);


			shared_ptr<T> container;
			int index;
			int cSize;
			int mSize;
		};
}

//#include "GTUSet.cpp"

#endif