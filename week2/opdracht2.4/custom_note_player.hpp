#ifndef CUSTOM_NOTE_PLAYER_HPP
#define CUSTOM_NOTE_PLAYER_HPP

#include "note_player.hpp"
#include "note.hpp"
#include <iostream>
#include <fstream>
using namespace std;

class custom_note_player : note_player {
private:
   ofstream melody;
public: 
   custom_note_player(){}
   
   void open(){
        melody.open("melody.cpp");
	melody << "#include \"melody.hpp\"\n\n";
	melody << "void melody::play( note_player & p ){\n";
   }

   void play( const note & n ){
        melody << "     p.play( note{ " <<  n.frequency << ", " << n.duration << " } );\n" ;
   }

   void close(){
	melody << '}';
	melody.close();
   }

};

#endif
