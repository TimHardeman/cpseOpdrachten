#include "lookup.hpp"
#include "hwlib.hpp"

int main( void ){	  

   // wait for the PC console to start
   hwlib::wait_ms( 500 );   

   namespace target = hwlib::target;
   
   auto scl = target::pin_oc( target::pins::scl );
   auto sda = target::pin_oc( target::pins::sda );
   
   auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );
   
   auto display = hwlib::glcd_oled( i2c_bus, 0x3c );
  
  
   constexpr auto cosinusses = lookup<360, int, 30>( scaled_cos_from_degrees );
   constexpr auto sinusses = lookup<360, int, 30>( scaled_sine_from_degrees );

   constexpr auto cosinusses2 = lookup<360, int, 25>( scaled_cos_from_degrees );
   constexpr auto sinusses2 = lookup<360, int, 25>( scaled_sine_from_degrees );

   constexpr auto cosinusses3 = lookup<360, int, 20>( scaled_cos_from_degrees );
   constexpr auto sinusses3 = lookup<360, int, 20>( scaled_sine_from_degrees );


   int seconds, minutes, hours, hours60 = 0;
   int cosinusSeconds, sinusSeconds, cosinusMinutes, sinusMinutes, cosinusHours, sinusHours;

   for(;;){
	hwlib::wait_ms(10);
	seconds = hwlib::now_us() / 1000000;
	minutes = seconds/60;
	hours = minutes/60;
	hours60 = hours/60;

	cosinusSeconds = cosinusses.get(((seconds - (minutes * 60)) * 6));
	sinusSeconds = sinusses.get(((seconds - (minutes * 60)) * 6));

	cosinusMinutes = cosinusses2.get((minutes - (hours * 60)) * 6);
	sinusMinutes = sinusses2.get((minutes - (hours * 60)) * 6);

	cosinusHours = cosinusses3.get((hours - (hours60 * 60)) * 6);
	sinusHours = sinusses3.get((hours - (hours60 * 60)) * 6);

	hwlib::line secondHand( hwlib::xy(64, 30), hwlib::xy(cosinusSeconds + 34, sinusSeconds));
	hwlib::line minuteHand( hwlib::xy(64, 30), hwlib::xy(cosinusMinutes + 5 + 34, sinusMinutes + 5));
	hwlib::line hourHand( hwlib::xy(64, 30), hwlib::xy(cosinusHours + 10 + 34, sinusHours + 10));

	display.clear();
	
	for(int i = 0; i < 12; i++){
		int cosinus = cosinusses.get(i * 30);
		int sinus = sinusses.get(i * 30);
		display.write( hwlib::xy( cosinus + 34, sinus ) );
	}

	secondHand.draw( display );
	minuteHand.draw( display );
	hourHand.draw( display );

	display.flush();
   }
}
