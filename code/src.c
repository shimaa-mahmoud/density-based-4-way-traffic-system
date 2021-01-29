#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"

void normal_mode();
void road_A();
void road_B();
void road_C();
void road_D();
uint8 traffic ();
int main (void)
{
 	DDRC |= 0X77;   // TRAFFIC LEDS AS OUTPUT FOR ROADS A,B
 	PORTC &= ~ 0X77;  // LEDS ARE OFF

 	DDRB |= 0X77;   // TRAFFIC LEDS AS OUTPUT FOR ROADS C,D
 	PORTB &= ~ 0X77;  // LEDS ARE OFF

 	CLEAR_BIT(DDRB,PC3);  // IR SIGNAL AS INPUT ROAD A
 	CLEAR_BIT(DDRB,PC7);  // IR SIGNAL AS INPUT ROAD B
 	CLEAR_BIT(DDRC,PC3);  // IR SIGNAL AS INPUT ROAD D
 	CLEAR_BIT(DDRC,PC7);  // IR SIGNAL AS INPUT ROAD C

	while (1)
	{
		if (BIT_IS_SET(PINC,PC3))
			road_A();
		else if (BIT_IS_SET(PINC,PC7))
			road_B();
		else if (BIT_IS_SET(PINB,PB7))
			road_C();
		else if (BIT_IS_SET(PINB,PB3))
			road_D();
		else
			normal_mode();
	}
}

uint8 traffic ()
{
	if (BIT_IS_SET(PINC,PC3)|| BIT_IS_SET(PINC,PC7)||BIT_IS_SET(PINB,PB7) ||BIT_IS_SET(PINB,PB3))
		return 1;
	else
		return 0;
}
void normal_mode()
 {
	 road_A();
	 if (traffic())
		 return;
	 road_B();
	 if (traffic())
	 	return;
	 road_C();
	 if (traffic())
	 	return;
	 road_D();
 }

void road_A()
{
	 //ROAD A GO, THE REST STOPS
	 PORTC = 0X14;
	 PORTB = 0X11;
	 _delay_ms(500);

	 //ROAD A READY TO STOP
	 PORTC = 0X12;
	 _delay_ms(200);
}

void road_B()
{

	 //ROAD B GO, THE REST STOPS
	 PORTC = 0X41;
	 PORTB = 0X11;
	 _delay_ms(500);

	 //ROAD B READY TO STOP
	 PORTC = 0X21;
	 _delay_ms(200);
}

void road_C()
{
	 //ROAD C GO, THE REST STOPS
	 PORTC = 0X11;
	 PORTB = 0X41;
	 _delay_ms(500);

	 //ROAD C READY TO STOP
	 PORTB = 0X21;
	 _delay_ms(200);
}

void road_D()
{
	 //ROAD D GO, THE REST STOPS
	 PORTC = 0X11;
	 PORTB = 0X14;
	 _delay_ms(500);

	 //ROAD D READY TO STOP
	 PORTB = 0X12;
	 _delay_ms(200);
}
