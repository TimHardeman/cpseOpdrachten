#include <iostream>
#include <fstream>

#include "compressor.hpp" 
#include "decompressor.hpp" 
#include <string>

int main( void ){	
   lz_compressor< 4096 > compressor;

   std::ifstream f1;
   f1.open( "wilhelmus.txt" );
   if( ! f1.is_open()){
      std::cerr << "input file not opened";
      return -1;      
   }
   
   std::ofstream f2;
   f2.open( "compressed.asm" );
   if( ! f2.is_open()){
      std::cerr << "output file not opened";
      return -1;      
   }
   
   compressor.compress(
      [ &f2 ]( char c ){ f2.put( c ); },
      [ &f1 ]()-> int { auto c = f1.get(); return f1.eof() ? '\0' : c; },
      [ &f2 ]( char c ){ if(c != '\n'){ f2.put( c );} else{f2 << "\\n";} }
  );
   
   f1.close();
   f2.close();
   
   f1.open( "compressed.asm" );
   if( ! f1.is_open()){
      std::cerr << "compressed file not opened";
      return -1;      
   }   
   
   lz_decompressor decompressor;
   decompressor.decompress( 
      [ &f1 ]()-> int { auto c = f1.get(); return f1.eof() ? '\0' : c; },
      [ &f2 ]( char c ){ if(c == '\n'){std::cout << '\n';}else{ std::cout << c;} }
   );
}
