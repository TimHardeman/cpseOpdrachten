#ifndef OPERATORS_HPP
#define OPERATORS_HPP

std::ifstream & operator>>( std::ifstream & input, sf::Color & rhs ){
   std::string s;
   input >> s;
   const struct { const char * name; sf::Color color; } colors[]{
       { "yellow", sf::Color::Yellow },
       { "red",    sf::Color::Red },
       { "blue", sf::Color::Blue },
	   { "green", sf::Color::Green }
   };
   for( auto const & color : colors ){
       if( color.name == s ){ 
          rhs = color.color;
          return input;
       }
   }
   if( s == "" ){
      throw end_of_file();
   }
   throw unknown_color( s );
}


std::ifstream & operator>>( std::ifstream & input, sf::Vector2f & rhs ){
   char c;
   if( ! ( input >> c )){ throw end_of_file(); }
   if( c != '(' ){ throw invalid_position( c ); }

   if( ! ( input >> rhs.x )){ throw invalid_position( c ); }

   if( ! ( input >> c )){ throw invalid_position( c ); }
   
   if( ! ( input >> rhs.y )){ throw invalid_position( c ); }

   if( ! ( input >> c )){ throw invalid_position( c ); }
   if( c != ')' ){ throw invalid_position( c ); }

   return input;
}

#endif