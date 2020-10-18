namespace hwlib {

#ifndef SPI_HPP
#define SPI_HPP

#include "hwlib.hpp"

/// bit-banged SPI bus implementation
///
/// This class implements a bit-banged master interface to a SPI bus.
class spi_bus_bit_banged_sclk_mosi_miso_st7789 : public spi_bus {
private:

   pin_direct_from_out_t sclk;
   pin_direct_from_out_t mosi;
   pin_direct_from_in_t  miso;
   
   // very crude;
   // delay should be a constructor parameter
   void HWLIB_INLINE wait_half_period(){
      wait_us( 1 );      
   }
   
   void write_and_read( 
      const size_t n, 
      const uint8_t data_out[], 
      uint8_t data_in[] 
   ) override {

      for( uint_fast8_t i = 0; i < n; ++i ){

         uint_fast8_t d = *data_out++; 

         for( uint_fast8_t j = 0; j < 8; ++j ){
	    if(( d & 0x80 ) != 0 ){
	    	PIOC->PIO_SODR = 0x01 << 26;
	    } 
	    else{
	    	PIOC->PIO_CODR = 0x01 << 26;
	    }
	    PIOC->PIO_CODR = 0x01 << 28;
            d = d << 1;
	    PIOC->PIO_SODR = 0x01 << 28;
         }
      }      
   }      
   
public:

   /// construct a bit-banged SPI bus from the sclk, miso and mosi pins
   ///
   /// This constructor creates a simple bit-banged SPI bus master
   /// from the sclk, miso and mosi pins. 
   ///
   /// The chip select pins for the individual chips supplied to the 
   /// write_and_read() functions.
   ///
   /// When the SPI bus is used for either only writing or only reading,
   /// the unused pin argument can be specified as pin_out_dummy or
   /// pin_in_dummy.
   spi_bus_bit_banged_sclk_mosi_miso_st7789( 
      pin_out & _sclk, 
      pin_out & _mosi, 
      pin_in  & _miso 
   ):
      //sclk( direct( _sclk ) ), 
      //mosi( direct( _mosi ) ), 
      //miso( direct( _miso ) )

      sclk( _sclk ), 
      mosi( _mosi ), 
      miso( _miso )   {

      //sclk
      PIOC->PIO_OER = 0x01 << 28;
      //mosi
      PIOC->PIO_OER = 0x01 << 26;

      PIOC->PIO_SODR = 0x01 << 28;
   }
   
}; // class spi_bus_bit_banged_sclk_mosi_miso   

#endif // SPI_HPP
};
