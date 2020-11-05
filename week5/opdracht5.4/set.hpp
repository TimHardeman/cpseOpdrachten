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
	
	T max(){
		T max = values[0];
		for(unsigned int i = 1; i < values.size(); i++){
			if(values[i] > max){
				max = values[i];
			}
		}
		return max;
	}
};

template< int N>
class set< std::array<char, 3>, N >{
private:
	std::vector<std::array<char, 3>> values = {};
		
public:
	set(){}
		
	void add( std::array<char, 3> value ){
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
	
	
	void remove( std::array<char, 3> value ){
		for(unsigned int i = 0; i < values.size(); i++){
			if(values[i] == value){
				values.erase(values.begin()+i);
				return;
			}
		}
	}
	
	bool contains( std::array<char, 3> value ){
		for(unsigned int i = 0; i < values.size(); i++){
			if(values[i] == value){
				return true;
			}
		}
		return false;
	}
	
	friend std::ostream& operator<<( std::ostream & o, const set & collection ){
		for(unsigned int i = 0; i < collection.values.size(); i++){
			for(unsigned int j = 0; j < collection.values[i].size(); j++){
				if(j == 0){
					o << '{';
				}
				o << collection.values[i][j];
				if(j == 2){
					o << "} ";
				}
				else{
					o << ", ";
				}
			}
		}
		o << '\n';
		return o;
	}

	std::array<char, 3> max(){
		std::array<char, 3> max = values[0];
		for(unsigned int i = 1; i < values.size(); i++){
			if(values[i] > max){
				max = values[i];
			}
		}
		return max;
	}
};

bool operator<(std::array<char, 3> & lhs, std::array<char, 3> rhs){
	for(unsigned int i = 0; i < 3; i++){
				if(lhs[i] < rhs[i]){
					return true;
				}
				else if(lhs[i] > rhs[i]){
					return false;
				}
	}
	return false;
}
		
#endif // SET_HPP
