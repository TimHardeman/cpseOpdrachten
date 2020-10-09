#ifndef _COMPPRESSOR_HPP
#define _COMPRESSOR_HPP
#include <array>
#include "match.hpp"
#include <string>

// A LZ compressor 
// A buffer is used that holds the total message,
// which must be smaller than N
template< int N > 
class lz_compressor {
private:   
   std::array< char, N > buffer;
   int used;
   
   // read the input using read() until it returns '\0'
   template< typename F >
   void read_buffer( F read ){
      used = 0;
      for(;;){
         auto c = read();
         //std::cout << used << "[" << (char) c <<  "]\n";
         if( used == N ){
            std::cerr << "buffer overflow";
            break;
         }
         if( c == '@' ){
            std::cerr << "text contains @";
            break;
         }
         if( c == '\0' ){
            break;
         }
         buffer[ used++ ] = c;
      }         
   }
   
   // return the length of the longest identical prefix of s and p
   int count_identical_prefix_length( int s, int p ){
      return ( buffer[ s ] != buffer[ p ] )
         ? 0 
         : 1 + count_identical_prefix_length( s + 1, p + 1 );
   }   
   
   // find the best match in the buffer (40 positions back, upto index) 
   // for the string starting at index
   match find( int index ){
      auto best = match( 0 );
      for( int i = std::max( 0, index - 40 ); i < index - 1; ++i ){
         auto length = std::min( 
            40, 
            count_identical_prefix_length( i, index ));
         best = std::max( best, match( index - i - 1, length ) );
      }
      return best;
   }
   
   template< typename F >
   void write_compressed_buffer( F write ){
      for( int i = 0; i < used; ){
         auto match = find( i );
         if( match.length > 2 ){
            //std::cout << "\ni=" << i << " m=" << match << " ";            
            write( '@' );
            write( '0' + match.offset );
            write( '0' + match.length );
            i += match.length;
         } else {
            //std::cout << "\n" << i << " c=[" << buffer[ i ] << "]";
            write( buffer[ i++ ] );
         }
      }
	write('"');
   }

   template< typename T >
   void write_syntax( T test ){
	std::string syntax = ".cpu cortex-m0\n.text\n.align 2\n.global application\n\napplication:\n	push {lr}\n	ldr r0, =msg\n	bl decompressor\n	pop {pc}\n\n.data\n.align 4\nmsg:\n	.asciz \"";
	
	for(unsigned int i = 0; i < syntax.size(); i++){
		test( syntax[i] );
	}

   }
   
public: 

   template< typename T,  typename S, typename D >
   void compress( T test, S read, D write ){
      write_syntax( test );
      read_buffer( read );
      write_compressed_buffer( write ); 
   }
   
};

#endif
