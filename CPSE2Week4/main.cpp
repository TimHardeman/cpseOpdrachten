#include <algorithm>
#include <vector>
#include <fstream>
#include <iostream>
#include <map>

int main(){
	// opdracht 1
	std::ifstream file;
	file.open("KingJamesBible.txt");
	
	std::vector<char> characters;
	
	char c;
	while(file.get(c)){
		characters.push_back(c);
	}
	
	// opdracht 2
	std::cout << "The file has: " << characters.size() << " characters." << '\n';
	
	// opdracht 3
	int lines = std::count(characters.begin(), characters.end(), '\n');
	std::cout << "The file has: " << lines << " lines." << '\n';
	
	// opdracht 4, zie de functie isAlphabetical boven de main
	int alphabetical = std::count_if(characters.begin(), characters.end(), isalpha);
	std::cout << "The file has: " << alphabetical << " alphabetical characters." << '\n';
	
	// opdracht 5
	std::for_each(characters.begin(), characters.end(), [](char & c){c = tolower(c);});
	
	// opdracht 6
	std::map< char, int > charOccurences;
	std::for_each(characters.begin(), characters.end(), [&charOccurences](char c){if(isalpha(c)){charOccurences[c]++;}});
	
	// opdracht 7
	std::vector< std::pair <char, int>> sortedCharOccurences;
	for( auto & character : charOccurences){
		sortedCharOccurences.push_back(character);
	}
	
	sort(
		sortedCharOccurences.begin(), sortedCharOccurences.end(),
	
			[](std::pair<char, int> & left, std::pair<char, int> & right)
				{return left.second > right.second;});
	
	std::cout << '\n' << "Occurences of letters in file:" << '\n';
	for(unsigned int i = 0; i < sortedCharOccurences.size(); i ++){
		std::cout << "	\"" << sortedCharOccurences[i].first << "\" occurs " << sortedCharOccurences[i].second << " times" << '\n';
	}
	std::cout << '\n';
	
	// opdracht 8
	std::vector<std::string> words;
	std::string currentWord = "";
	
	std::for_each(
		characters.begin(), characters.end(), 
		
			[&words, &currentWord](char c){ 
				if(isalpha(c)){
					currentWord+=c;
					} 
				else if(currentWord != ""){
					words.push_back(currentWord); 
					currentWord = "";
				}});
	
	std::map< std::string, int > wordOccurences;
	std::for_each(words.begin(), words.end(), [&wordOccurences](std::string word){wordOccurences[word]++;});
	
	std::vector< std::pair <std::string, int>> sortedWordOccurences;
	for( auto & word : wordOccurences){
		sortedWordOccurences.push_back(word);
	}
	
	sort(
		sortedWordOccurences.begin(), sortedWordOccurences.end(),
	
			[](std::pair<std::string, int> & left, std::pair<std::string, int> & right)
				{return left.second > right.second;});
	
	unsigned int iterator;
	if(sortedWordOccurences.size() > 10){ iterator = 10; } else{iterator = sortedWordOccurences.size();}
	
	std::cout << '\n' << iterator << " most common words: " << '\n';
	for(unsigned int i = 0; i < iterator; i ++){
		std::cout << "	\"" << sortedWordOccurences[i].first << "\" occurs " << sortedWordOccurences[i].second << " times" << '\n';
	}
	std::cout << '\n';
}

