#include <array>
#include "hwlib.hpp"

constexpr double pow( double g, int n ){
   double result = 1;
   while( n > 0 ){
       result *= g;
       --n;
   }
   return result;
}

constexpr double fac( int n ){
   double result = 1;
   while( n > 0 ){
       result *= n;
       --n;
   }
   return result;
}

constexpr double sin( double a ){
   return 
      a 
      - pow( a, 3 ) / fac( 3 ) 
      + pow( a, 5 ) / fac( 5 ) 
      - pow( a, 7 ) / fac( 7 )
      + pow( a, 9 ) / fac( 9 ) 
      - pow( a, 11 ) / fac( 11 ) 
      + pow( a, 13 ) / fac( 13 )
      - pow( a, 15 ) / fac( 15 ) 
      + pow( a, 17 ) / fac( 17 )
      - pow( a, 19 ) / fac( 19 )
      + pow( a, 21 ) / fac( 21 )
      - pow( a, 23 ) / fac( 23 )
      + pow( a, 25 ) / fac( 25 );
}

constexpr double cos( double a ){
   return sin( (3.14 / 2) - a );
}

constexpr double radians_from_degrees( int degrees ){
   int turnedDegrees = 0;
   if(degrees > 89){
	   turnedDegrees = degrees - 90;
   }	
   else{
	   turnedDegrees = 360 - 90 + degrees;
   }
	
   return 2 * 3.14 * ( turnedDegrees / 360.0 );
}

constexpr int scaled_sine_from_degrees( int degrees, int radius ){
   return radius * ( 1.0 + sin( radians_from_degrees( degrees )));
}

constexpr int scaled_cos_from_degrees( int degrees, int radius ){
   return radius * (1.0 + cos( radians_from_degrees( degrees )));
}

template< int N, typename T, int R >
class lookup {
private:    
   std::array< T, N > values = {};

public: 

   template< typename F >
   constexpr lookup( F function ){
      for( int i = 0; i < N; ++i ){
          values[ i ] = function( i, R );
      }
   }

   constexpr T get( int n ) const {
      return values[ n ];    
   }
};



