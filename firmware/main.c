#include <stdint.h>
#include "buttons.h"
#include "leds.h"
#include "utils.h"

/* Os tempos abaixo sao calculados numa base de tempo de 10ms 
 * Por exemplo: timer = 1s = 100 * 10ms*/
#define ONE_SECOND							100						// 1s
#define TIME_TO_UPDATE_CURRENT_TIME			(1 * ONE_SECOND)		// 1s
#define ALARM_STATE_TIMEOUT					(60 * ONE_SECOND)		// 1min
#define TIME_TO_ENTER_IN_SETTING_MODE		(3 * ONE_SECOND)		// 3s
#define SETTING_STATE_TIMEOUT				(5 * ONE_SECOND			// 5s

/* current_time maximo = 23h 59min 59s */
#define MAX_CURRENT_TIME 					(86399 * ONE_SECOND)

typedef enum
{
	RUNNING_TIME_STATE = 1,
	RUNNING_ALARM_STATE,
	SETTING_TIME_HOURS_STATE,
	SETTING_TIME_MINUTES_STATE,
	SETTING_TIME_SECONDS_STATE,
	SETTING_ALARM_HOURS_STATE,
	SETTING_ALARM_MINUTES_STATE,
	SETTING_ALARM_SECONDS_STATE,
} m_state_t;

button button1, button2;
m_state_t m_state = TIME_RUNNING_STATE;
timer update_current_time_timer, general_timer, alarm_state_timeout, setting_state_timeout;

int alarm_on = 0;
int alarm_time = 0;
int current_time = 0;

int sys_init (void)
{
	timer_init();

	button_init();

	leds_init();
	
	return 0;
}

int m_state_task (void)
{
	static button old_button1 = {0, 0}, old_button2 = {0, 0};
	
	switch (m_state)
	{
		/* Estado padrao, no qual a hora eh mostrada */
		case RUNNING_TIME_STATE :
		{
			if (alarm_on && (current_time >= alarm_time) && (current_time < alarm_time + ALARM_TIMEOUT))
			{
				m_state = RUNNING_ALARM_STATE;
				
				alarm_state_timeout.start();
			}
			else if ((old_button1.value == BUTTON_PRESSED) && (button1.value == BUTTON_NOT_PRESSED))
			{
				if (old_button1.time <= TIME_TO_ENTER_IN_SETTING_MODE)
				{
					// alterna entre os modos 12h e 24h
					break;
				}
				else
				{
					m_state = SETTING_TIME_HOURS_STATE;
					
					setting_state_timeout.start();
				}
			}
			else if ((old_button2.value == BUTTON_PRESSED) && (button2.value == BUTTON_NOT_PRESSED))
			{
				if (old_button2.time <= TIME_TO_ENTER_IN_SETTING_MODE) alarm_on ^= 1;
				else m_state = SETTING_ALARM_HOURS_STATE;
			}
			
			break;
		}
		/* Estado de alarme tocando */
		case RUNNING_ALARM_STATE :
		{
			if (((button1.value == BUTTON_PRESSED) && (button2.value == BUTTON_PRESSED)) || (alarm_state_timeout.get_value() >= ALARM_STATE_TIMEOUT))
			{
				m_state = RUNNING_TIME_STATE;
				
				alarm_state_timeout.stop();
			}
			
			break;
		}
		/* Estado de ajuste das horas */
		case SETTING_TIME_HOURS_STATE :
		{
			if (setting_state_timeout.get_value() >= SETTING_STATE_TIMEOUT)
			{
				m_state = RUNNING_TIME_STATE;
				
				setting_state_timeout.stop();
			}
			else if ((old_button1.value == BUTTON_PRESSED) && (button1.value == BUTTON_NOT_PRESSED))
			{
				m_state = SETTING_TIME_MINUTES_STATE;
				
				setting_state_timeout.reset();
			}
			else if ((old_button2.value == BUTTON_PRESSED) && (button2.value == BUTTON_NOT_PRESSED))
			{
				if ()
				
				setting_state_timeout.reset();
			}
			
			break;
		}
		/* Estado de ajuste dos minutos */
		case SETTING_TIME_MINUTES_STATE :
		{
			if (setting_state_timeout.get_value() >= SETTING_STATE_TIMEOUT)
			{
				m_state = RUNNING_TIME_STATE;
				
				setting_state_timeout.stop();
			}
			else if ((old_button1.value == BUTTON_PRESSED) && (button1.value == BUTTON_NOT_PRESSED))
			{
				m_state = SETTING_TIME_SECONDS_STATE;
				
				setting_state_timeout.reset();
			}
			
			break;
		}
		/* Estado de ajuste dos segundos */
		case SETTING_TIME_SECONDS_STATE :
		{
			if (setting_state_timeout.get_value() >= SETTING_STATE_TIMEOUT)
			{
				m_state = RUNNING_TIME_STATE;
				
				setting_state_timeout.stop();
			}
			else if ((old_button1.value == BUTTON_PRESSED) && (button1.value == BUTTON_NOT_PRESSED))
			{
				m_state = SETTING_TIME_HOURS_STATE;
				
				setting_state_timeout.reset();
			}
			
			break;
		}
		/* Estado de ajuste das horas do alarme */
		case SETTING_ALARM_HOURS_STATE :
		{
			if (setting_state_timeout.get_value() >= SETTING_STATE_TIMEOUT)
			{
				m_state = RUNNING_TIME_STATE;
				
				setting_state_timeout.stop();
			}
			else if ((old_button1.value == BUTTON_PRESSED) && (button1.value == BUTTON_NOT_PRESSED))
			{
				m_state = SETTING_ALARM_MINUTES_STATE;
				
				setting_state_timeout.reset();
			}
			
			break;
		}
		/* Estado de ajuste dos minutos do alarme */
		case SETTING_ALARM_MINUTES_STATE :
		{
			if (setting_state_timeout.get_value() >= SETTING_STATE_TIMEOUT)
			{
				m_state = RUNNING_TIME_STATE;
				
				setting_state_timeout.stop();
			}
			else if ((old_button1.value == BUTTON_PRESSED) && (button1.value == BUTTON_NOT_PRESSED))
			{
				m_state = SETTING_ALARM_SECONDS_STATE;
				
				setting_state_timeout.reset();
			}
			
			break;
		}
		/* Estado de ajuste dos segundos do alarme */
		case SETTING_ALARM_SECONDS_STATE :
		{
			if (setting_state_timeout.get_value() >= SETTING_STATE_TIMEOUT)
			{
				m_state = RUNNING_TIME_STATE;
				
				setting_state_timeout.stop();
			}
			else if ((old_button1.value == BUTTON_PRESSED) && (button1.value == BUTTON_NOT_PRESSED))
			{
				m_state = SETTING_ALARM_HOURS_STATE;
				
				setting_state_timeout.reset();
			}
			
			break;
		}
	}

	xmemcpy(&old_button1, &button1, BUTTON_STRUCT_SIZE_IN_BYTES);
	xmemcpy(&old_button2, &button2, BUTTON_STRUCT_SIZE_IN_BYTES);
}

int main (void)
{	
	sys_init();

	update_current_time_timer = new_timer();
	update_current_time_timer.start();

	general_timer = new_timer();
	general_timer.start();
	
	alarm_state_timeout = new_timer();
	setting_state_timeout = new_timer();
	
	while (1)
	{
		/************************************************************************/
		/* Atualizacao do horario atual */
		/************************************************************************/
		// Versao com uC nao tera esta funcao. Os timers serao atualizados via interrupcao
		timer_task();
		
		if (update_current_time_timer.get_value() >= TIME_TO_UPDATE_CURRENT_TIME)
		{
			update_current_time_timer.reset();
			
			current_time += ONE_SECOND;
		}
		/************************************************************************/
		
		/************************************************************************/
		/* Botao */
		/************************************************************************/
		buttons_task();
		button_read(&button1, BUTTON_1);
		button_read(&button2, BUTTON_2);
		/************************************************************************/
		
		/************************************************************************/
		/* Maquina de estados */
		/************************************************************************/
		m_state_task();
		/************************************************************************/
		
		/************************************************************************/
		/* LEDs */
		/************************************************************************/
		leds_task();
		/************************************************************************/
	}
	
	return 0;
}

