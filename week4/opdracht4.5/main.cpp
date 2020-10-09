#include "hwlib.hpp"

extern "C" void uart_put_char( char c ){
   hwlib::cout << c;
}

extern "C" void application();

int main(){

	hwlib::wait_ms(2000);

	application();

}
