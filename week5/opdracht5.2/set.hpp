#ifndef SET_HPP
#define SET_HPP

#include <iostream>
#include <vector>

template< typename T, int N>
class set{
private:
	std::vector<T> values = {};
		
public:
	set(){}
		
	void add( T value ){
		if(values.size() >= N){
		return;
		}
	
		for(unsigned int i = 0; i < values.size(); i++){
			if(values[i] == value){
			return;
			}
		}
		values.push_back(value);
	}
	
	void remove( T value ){
		for(unsigned int i = 0; i < values.size(); i++){
			if(values[i] == value){
				values.erase(values.begin()+i);
				return;
			}
		}
	}
	
	bool contains( T value ){
		for(unsigned int i = 0; i < values.size(); i++){
			if(values[i] == value){
				return true;
			}
		}
		return false;
	}
	
	friend std::ostream& operator<<( std::ostream & o, const set & collection ){
		for(unsigned int i = 0; i < collection.values.size(); i++){
			o << collection.values[i] << ' ';
		}
		o << '\n';
		return o;
	}
};
		
#endif // SET_HPP
