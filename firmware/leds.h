#ifndef LEDS_H_
#define LEDS_H_

enum led_enum
{
	/* Dezena da hora */
	HOUR_TENS_BIT_1_LED,
	HOUR_TENS_BIT_0_LED,
	/* Unidade da hora */
	HOUR_UNIT_BIT_3_LED,
	HOUR_UNIT_BIT_2_LED,
	HOUR_UNIT_BIT_1_LED,
	HOUR_UNIT_BIT_0_LED,
	/* Dezena do minuto */
	MINUTE_TENS_BIT_2_LED,
	MINUTE_TENS_BIT_1_LED,
	MINUTE_TENS_BIT_0_LED,
	/* Unidade da minuto */
	MINUTE_UNIT_BIT_3_LED,
	MINUTE_UNIT_BIT_2_LED,
	MINUTE_UNIT_BIT_1_LED,
	MINUTE_UNIT_BIT_0_LED,
	/* Dezena do segundo */
	SECOND_TENS_BIT_2_LED,
	SECOND_TENS_BIT_1_LED,
	SECOND_TENS_BIT_0_LED,
	/* Unidade do segundo */
	SECOND_UNIT_BIT_3_LED,
	SECOND_UNIT_BIT_2_LED,
	SECOND_UNIT_BIT_1_LED,
	SECOND_UNIT_BIT_0_LED,
	/* Alarm ligado/desligado */
	ALARM_STATE_LED
};

#define NUMBER_OF_LEDS		17

typedef enum
{
	LED_ON,
	LED_OFF
} led_state;

/* FIXME Depois trocar os valores para os valores reais dos pinos */
#define	LED_LINE_0_PORT		0
#define	LED_LINE_1_PORT		1
#define	LED_LINE_2_PORT		2
#define	LED_LINE_3_PORT		3
#define	LED_LINE_4_PORT		4
#define	LED_LINE_0_PIN		0
#define	LED_LINE_1_PIN		1
#define	LED_LINE_2_PIN		2
#define	LED_LINE_3_PIN		3
#define	LED_LINE_4_PIN		4

typedef struct
{
	led_state state;
	int anode[2];
	int cathode[2];
} led;

int leds_init (void);
int leds_task (void);
int leds_set_all_off (void);
int leds_set_all_on (void);
int leds_set_time (int time);

#endif
