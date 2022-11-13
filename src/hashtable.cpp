// file: hashtable.h
// author: aidan collins
// github: aijac0
// email: aidancollinscs@gmail.com
// Header of the perfect hash table
// // // // // // // // // // // // //

#include <vector>


template <typename ValType>
class HashTable<ValType>
{
	public:
		
		// Constructors
		HashTable<ValType>()
		: expr(sizeof(ValType) * 8), masks(sizeof(ValType) * 8) {}

		HashTable<ValType>(size_t size)
		: table(size, 0).erase(), exprs(sizeof(ValType) * 8), masks(sizeof(ValType) * 8) {}

		ValType & operator[](size_t index);
		ValType operator[](size_t index) const;

		void insert();	

		bool contains(const ValType val) const;	

		


	private:
		// Attributes
		vector<ValType> table;
		vector< vector<ValType> > exprs;
		vector< vector<ValType> > masks;

		
		

}
