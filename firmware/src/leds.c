#include "leds.h"
#include "utils.h"

led led_list[NUMBER_OF_LEDS];

int leds_init (void)
{
	int i;
	
	// FIXME Inicializar os pinos aqui
	
	HOUR_TENS_BIT_1_LED.state = LED_OFF;
	HOUR_TENS_BIT_1_LED.anode[0] = ;
	HOUR_TENS_BIT_1_LED.anode[1] = ;
	HOUR_TENS_BIT_1_LED.cathode[0] = ;
	HOUR_TENS_BIT_1_LED.cathode[1] = ;
	
	HOUR_TENS_BIT_0_LED.state = LED_OFF;
	HOUR_TENS_BIT_0_LED.anode[0] = ;
	HOUR_TENS_BIT_0_LED.anode[1] = ;
	HOUR_TENS_BIT_0_LED.cathode[0] = ;
	HOUR_TENS_BIT_0_LED.cathode[1] = ;
	
	HOUR_UNIT_BIT_3_LED.state = LED_OFF;
	HOUR_UNIT_BIT_3_LED.anode[0] = ;
	HOUR_UNIT_BIT_3_LED.anode[1] = ;
	HOUR_UNIT_BIT_3_LED.cathode[0] = ;
	HOUR_UNIT_BIT_3_LED.cathode[1] = ;
	
	HOUR_UNIT_BIT_2_LED.state = LED_OFF;
	HOUR_UNIT_BIT_2_LED.anode[0] = ;
	HOUR_UNIT_BIT_2_LED.anode[1] = ;
	HOUR_UNIT_BIT_2_LED.cathode[0] = ;
	HOUR_UNIT_BIT_2_LED.cathode[1] = ;
	
	HOUR_UNIT_BIT_1_LED.state = LED_OFF;
	HOUR_UNIT_BIT_1_LED.anode[0] = ;
	HOUR_UNIT_BIT_1_LED.anode[1] = ;
	HOUR_UNIT_BIT_1_LED.cathode[0] = ;
	HOUR_UNIT_BIT_1_LED.cathode[1] = ;
	
	HOUR_UNIT_BIT_0_LED.state = LED_OFF;
	HOUR_UNIT_BIT_0_LED.anode[0] = ;
	HOUR_UNIT_BIT_0_LED.anode[1] = ;
	HOUR_UNIT_BIT_0_LED.cathode[0] = ;
	HOUR_UNIT_BIT_0_LED.cathode[1] = ;
	
	MINUTE_TENS_BIT_2_LED.state = LED_OFF;
	MINUTE_TENS_BIT_2_LED.anode[0] = ;
	MINUTE_TENS_BIT_2_LED.anode[1] = ;
	MINUTE_TENS_BIT_2_LED.cathode[0] = ;
	MINUTE_TENS_BIT_2_LED.cathode[1] = ;
	
	MINUTE_TENS_BIT_1_LED.state = LED_OFF;
	MINUTE_TENS_BIT_1_LED.anode[0] = ;
	MINUTE_TENS_BIT_1_LED.anode[1] = ;
	MINUTE_TENS_BIT_1_LED.cathode[0] = ;
	MINUTE_TENS_BIT_1_LED.cathode[1] = ;
	
	MINUTE_TENS_BIT_0_LED.state = LED_OFF;
	MINUTE_TENS_BIT_0_LED.anode[0] = ;
	MINUTE_TENS_BIT_0_LED.anode[1] = ;
	MINUTE_TENS_BIT_0_LED.cathode[0] = ;
	MINUTE_TENS_BIT_0_LED.cathode[1] = ;
	
	MINUTE_UNIT_BIT_3_LED.state = LED_OFF;
	MINUTE_UNIT_BIT_3_LED.anode[0] = ;
	MINUTE_UNIT_BIT_3_LED.anode[1] = ;
	MINUTE_UNIT_BIT_3_LED.cathode[0] = ;
	MINUTE_UNIT_BIT_3_LED.cathode[1] = ;
	
	MINUTE_UNIT_BIT_2_LED.state = LED_OFF;
	MINUTE_UNIT_BIT_2_LED.anode[0] = ;
	MINUTE_UNIT_BIT_2_LED.anode[1] = ;
	MINUTE_UNIT_BIT_2_LED.cathode[0] = ;
	MINUTE_UNIT_BIT_2_LED.cathode[1] = ;
	
	MINUTE_UNIT_BIT_1_LED.state = LED_OFF;
	MINUTE_UNIT_BIT_1_LED.anode[0] = ;
	MINUTE_UNIT_BIT_1_LED.anode[1] = ;
	MINUTE_UNIT_BIT_1_LED.cathode[0] = ;
	MINUTE_UNIT_BIT_1_LED.cathode[1] = ;
	
	MINUTE_UNIT_BIT_0_LED.state = LED_OFF;
	MINUTE_UNIT_BIT_0_LED.anode[0] = LED_LINE_4_PORT;
	MINUTE_UNIT_BIT_0_LED.anode[1] = LED_LINE_4_PIN;
	MINUTE_UNIT_BIT_0_LED.cathode[0] = LED_LINE_3_PORT;
	MINUTE_UNIT_BIT_0_LED.cathode[1] = LED_LINE_3_PIN;
	
	SECOND_TENS_BIT_2_LED.state = LED_OFF;
	SECOND_TENS_BIT_2_LED.anode[0] = LED_LINE_3_PORT;
	SECOND_TENS_BIT_2_LED.anode[1] = LED_LINE_3_PIN;
	SECOND_TENS_BIT_2_LED.cathode[0] = LED_LINE_2_PORT;
	SECOND_TENS_BIT_2_LED.cathode[1] = LED_LINE_2_PIN;
	
	SECOND_TENS_BIT_1_LED.state = LED_OFF;
	SECOND_TENS_BIT_1_LED.anode[0] = LED_LINE_2_PORT;
	SECOND_TENS_BIT_1_LED.anode[1] = LED_LINE_2_PIN;
	SECOND_TENS_BIT_1_LED.cathode[0] = LED_LINE_1_PORT;
	SECOND_TENS_BIT_1_LED.cathode[1] = LED_LINE_1_PIN;
	
	SECOND_TENS_BIT_0_LED.state = LED_OFF;
	SECOND_TENS_BIT_0_LED.anode[0] = LED_LINE_1_PORT;
	SECOND_TENS_BIT_0_LED.anode[1] = LED_LINE_1_PIN;
	SECOND_TENS_BIT_0_LED.cathode[0] = LED_LINE_0_PORT;
	SECOND_TENS_BIT_0_LED.cathode[1] = LED_LINE_0_PIN;
	
	SECOND_UNIT_BIT_3_LED.state = LED_OFF;
	SECOND_UNIT_BIT_3_LED.anode[0] = LED_LINE_3_PORT;
	SECOND_UNIT_BIT_3_LED.anode[1] = LED_LINE_3_PIN;
	SECOND_UNIT_BIT_3_LED.cathode[0] = LED_LINE_4_PORT;
	SECOND_UNIT_BIT_3_LED.cathode[1] = LED_LINE_4_PIN;
	
	SECOND_UNIT_BIT_2_LED.state = LED_OFF;
	SECOND_UNIT_BIT_2_LED.anode[0] = LED_LINE_2_PORT;
	SECOND_UNIT_BIT_2_LED.anode[1] = LED_LINE_2_PIN;
	SECOND_UNIT_BIT_2_LED.cathode[0] = LED_LINE_3_PORT;
	SECOND_UNIT_BIT_2_LED.cathode[1] = LED_LINE_3_PIN;
	
	SECOND_UNIT_BIT_1_LED.state = LED_OFF;
	SECOND_UNIT_BIT_1_LED.anode[0] = LED_LINE_1_PORT;
	SECOND_UNIT_BIT_1_LED.anode[1] = LED_LINE_1_PIN;
	SECOND_UNIT_BIT_1_LED.cathode[0] = LED_LINE_2_PORT;
	SECOND_UNIT_BIT_1_LED.cathode[1] = LED_LINE_2_PIN;
	
	SECOND_UNIT_BIT_0_LED.state = LED_OFF;
	SECOND_UNIT_BIT_0_LED.anode[0] = LED_LINE_0_PORT;
	SECOND_UNIT_BIT_0_LED.anode[1] = LED_LINE_0_PIN;
	SECOND_UNIT_BIT_0_LED.cathode[0] = LED_LINE_1_PORT;
	SECOND_UNIT_BIT_0_LED.cathode[1] = LED_LINE_1_PIN;
	
	ALARM_STATE_LED.state = LED_OFF;
	ALARM_STATE_LED.anode[0] = ;
	ALARM_STATE_LED.anode[1] = ;
	ALARM_STATE_LED.cathode[0] = ;
	ALARM_STATE_LED.cathode[1] = ;
	
	return 0;
}

int my_pio_set (int port, int pin)
{
	return 0;
}

int my_pio_clear (int port, int pin)
{
	return 0;
}

int leds_task (void)
{
	static int led_list_ptr = HOUR_TENS_BIT_1_LED;
	led current_led, previous_led;	
	
	switch (led_list_ptr)
	{
		case FIRST_TIME_LED :
		{
			current_led = led_list[FIRST_TIME_LED];
			previous_led = led_list[LAST_TIME_LED];
			
			led_list_ptr++;
			
			break;
		}
		case LAST_TIME_LED :
		{
			current_led = led_list[LAST_TIME_LED];
			previous_led = led_list[LAST_TIME_LED - 1];
			
			led_list_ptr = FIRST_TIME_LED;
			
			break;
		}
		default :
		{
			current_led = led_list[led_list_ptr];
			previous_led = led_list[led_list_ptr - 1];
			
			led_list_ptr++;
			
			break;
		}
	}
	
	my_pio_clear(previous_led.anode[0], previous_led.anode[1]);
	
	if (led_list[current_led].state == LED_ON)
	{
		my_pio_set(current_led.anode[0], current_led.anode[1]);
	}
	
	return 0;
}

int leds_set_all_off (void)
{
	return 0;
}

int leds_set_all_on (void)
{
	return 0;
}

int leds_set_time (int time)
{
	return 0;
}

