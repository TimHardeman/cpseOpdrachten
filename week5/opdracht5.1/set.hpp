#ifndef SET_HPP
#define SET_HPP

#include <iostream>
#include <vector>

class set{
private:
	std::vector<int> values = {};
		
public:
	set(){}
		
	void add( int value ){
		if(values.size() >= 10){
		return;
		}
	
		for(unsigned int i = 0; i < values.size(); i++){
			if(values[i] == value){
			return;
			}
		}
		values.push_back(value);
	}
	
	void remove( int value ){
		for(unsigned int i = 0; i < values.size(); i++){
			if(values[i] == value){
				values.erase(values.begin()+i);
				return;
			}
		}
	}
	
	bool contains( int value ){
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

