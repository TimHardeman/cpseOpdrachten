#ifndef CUSTOM_NOTE_PLAYER_HPP
#define CUSTOM_NOTE_PLAYER_HPP

#include "note_player.hpp"
#include "note.hpp"
#include "hwlib.hpp"
#include <iostream>
using namespace std;

class custom_note_player : note_player {
public: 
   custom_note_player(){}
   
   void play( const note & n ){
        cout << n.frequency << "Hz for " << n.duration << " us" << '\n';
   }
};

#endif
