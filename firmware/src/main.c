#include <stdint.h>
#include "buttons.h"
#include "timer.h"
#include "leds.h"
#include "utils.h"

/* Os tempos abaixo sao calculados numa base de tempo de 10ms 
 * Por exemplo: timer = 1s = 100 * 10ms */
#define ONE_SECOND							100						// 1s
#define ONE_MINUTE							(60 * ONE_SECOND)		// 1min
#define	ONE_HOUR							(3600 * ONE_SECOND)		// 1h
#define TIME_TO_UPDATE_CURRENT_TIME			(1 * ONE_SECOND)		// 1s
#define ALARM_STATE_TIMEOUT					ONE_MINUTE				// 1min
#define TIME_TO_ENTER_IN_SETTING_MODE		(3 * ONE_SECOND)		// 3s
#define SETTING_STATE_TIMEOUT				(5 * ONE_SECOND)		// 5s

/* Horario maximo */
#define MAX_TIME		 					(86399 * ONE_SECOND)	// 23h 59min 59s

typedef enum
{
	RUNNING_TIME_STATE = 1,
	RUNNING_ALARM_STATE,
	SETTING_TIME_HOURS_STATE,
	SETTING_TIME_MINUTES_STATE,
	SETTING_TIME_SECONDS_STATE,
	SETTING_ALARM_HOURS_STATE,
	SETTING_ALARM_MINUTES_STATE,
	SETTING_ALARM_SECONDS_STATE
} m_state_t;

button button1, button2;
m_state_t m_state = RUNNING_TIME_STATE;
timer update_current_time_timer, alarm_state_timeout, setting_state_timeout;

int alarm_on = 0;
int alarm_time = 0;
int current_time = 0;

int sys_init (void);
int update_time (int *current_value, int increment);
int m_state_task (void);

int main (void)
{	
	sys_init();
	
	update_current_time_timer = new_timer();
	update_current_time_timer.start(&update_current_time_timer);
	
	alarm_state_timeout = new_timer();
	setting_state_timeout = new_timer();
	
	while (1)
	{
		/************************************************************************/
		/* Atualizacao do horario atual */
		/************************************************************************/
		// Versao com uC nao tera esta funcao. Os timers serao atualizados via interrupcao
		timer_task();
		
		if (update_current_time_timer.get_value(&update_current_time_timer) >= TIME_TO_UPDATE_CURRENT_TIME)
		{
			update_current_time_timer.reset(&update_current_time_timer);
			
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
	} // Fim while
	
	return 0;
} // Fim main

/* Inicializacao do sistema */
int sys_init (void)
{
	timer_init();
	
	button_init();
	
	leds_init();
	
	return 0;
}

/* Funcao para incremento de current_time, temp_current_time e alarm_time */
int update_time (int *current_value, int increment)
{
	*current_value += increment;
	
	if (*current_value > MAX_TIME) *current_value -= (MAX_TIME + 1);
	else if (*current_value < 0) *current_value += (MAX_TIME + 1);
	
	return 0;
}

/* Maquina de estado */
int m_state_task (void)
{
	static button old_button1 = {0, 0}, old_button2 = {0, 0};
	static int temp_current_time = 0;
	
	switch (m_state)
	{
		/* Estado padrao, no qual a hora eh mostrada */
		case RUNNING_TIME_STATE :
		{
			/* Horario atual atingiu o horario do alarme --> tocar alarme */
			if (alarm_on && (current_time >= alarm_time) && (current_time < alarm_time + ALARM_STATE_TIMEOUT))
			{
				m_state = RUNNING_ALARM_STATE;
				
				alarm_state_timeout.start(&alarm_state_timeout);
			}
			/* Botao 1 pressionado */
			else if ((old_button1.value == BUTTON_PRESSED) && (button1.value == BUTTON_NOT_PRESSED))
			{
				/* Botao 1 pressionado por MENOS de TIME_TO_ENTER_IN_SETTING_MODE ms --> alternar entre os modos 12 e 24h */
				if (old_button1.time <= TIME_TO_ENTER_IN_SETTING_MODE)
				{
					break;
				}
				/* Botao 1 pressionado por MAIS de TIME_TO_ENTER_IN_SETTING_MODE ms --> mudar para o estado de ajuste das horas */
				else
				{
					m_state = SETTING_TIME_HOURS_STATE;
					
					temp_current_time = current_time;
					
					setting_state_timeout.start(&setting_state_timeout);
				}
			}
			/* Botao 2 pressionado */
			else if ((old_button2.value == BUTTON_PRESSED) && (button2.value == BUTTON_NOT_PRESSED))
			{
				/* Botao 2 pressionado por MENOS de TIME_TO_ENTER_IN_SETTING_MODE ms --> ligar/desligar o alarme */
				if (old_button2.time <= TIME_TO_ENTER_IN_SETTING_MODE)
				{
					alarm_on ^= 1;
					
					// FIXME implementar led indicativo de alarme ativo e depois liga-lo
				}
				/* Botao 2 pressionado por MAIS de TIME_TO_ENTER_IN_SETTING_MODE ms --> mudar para o estado de ajuste das horas do alarme */
				else
				{
					m_state = SETTING_ALARM_HOURS_STATE;
					
					setting_state_timeout.start(&setting_state_timeout);
				}
			}
			
			break;
		}
		/* Estado de alarme tocando */
		case RUNNING_ALARM_STATE :
		{
			/* Botaos 1 e 2 pressionados simultaneamente OU timeout estorou --> voltar para o estado padrao */
			if (((button1.value == BUTTON_PRESSED) && (button2.value == BUTTON_PRESSED)) || (alarm_state_timeout.get_value(&alarm_state_timeout) >= ALARM_STATE_TIMEOUT))
			{
				m_state = RUNNING_TIME_STATE;
				
				alarm_state_timeout.stop(&alarm_state_timeout);
			}
			
			break;
		}
		/* Estado de ajuste das horas */
		case SETTING_TIME_HOURS_STATE :
		{
			/* Timeout estorou --> voltar para o estado padrao */
			if (setting_state_timeout.get_value(&setting_state_timeout) >= SETTING_STATE_TIMEOUT)
			{
				m_state = RUNNING_TIME_STATE;
				
				current_time = temp_current_time;
				
				setting_state_timeout.stop(&setting_state_timeout);
			}
			/* Botao 1 pressionado --> mudar para o estado de ajuste dos minutos */
			else if ((old_button1.value == BUTTON_PRESSED) && (button1.value == BUTTON_NOT_PRESSED))
			{
				m_state = SETTING_TIME_MINUTES_STATE;
				
				setting_state_timeout.reset(&setting_state_timeout);
			}
			/* Botao 2 pressionado --> incrementar o horario atual em 1 hora */
			else if ((old_button2.value == BUTTON_PRESSED) && (button2.value == BUTTON_NOT_PRESSED))
			{
				update_time(&temp_current_time, ONE_HOUR);
				
				setting_state_timeout.reset(&setting_state_timeout);
			}
			
			break;
		}
		/* Estado de ajuste dos minutos */
		case SETTING_TIME_MINUTES_STATE :
		{
			/* Timeout estorou --> voltar para o estado padrao */
			if (setting_state_timeout.get_value(&setting_state_timeout) >= SETTING_STATE_TIMEOUT)
			{
				m_state = RUNNING_TIME_STATE;
				
				current_time = temp_current_time;
				
				setting_state_timeout.stop(&setting_state_timeout);
			}
			/* Botao 1 pressionado --> mudar para o estado de ajuste dos segundos */
			else if ((old_button1.value == BUTTON_PRESSED) && (button1.value == BUTTON_NOT_PRESSED))
			{
				m_state = SETTING_TIME_SECONDS_STATE;
				
				setting_state_timeout.reset(&setting_state_timeout);
			}
			/* Botao 2 pressionado --> incrementar o horario atual em 1 minuto */
			else if ((old_button2.value == BUTTON_PRESSED) && (button2.value == BUTTON_NOT_PRESSED))
			{
				update_time(&temp_current_time, ONE_MINUTE);
				
				setting_state_timeout.reset(&setting_state_timeout);
			}
			
			break;
		}
		/* Estado de ajuste dos segundos */
		case SETTING_TIME_SECONDS_STATE :
		{
			/* Timeout estorou --> voltar para o estado padrao */
			if (setting_state_timeout.get_value(&setting_state_timeout) >= SETTING_STATE_TIMEOUT)
			{
				m_state = RUNNING_TIME_STATE;
				
				current_time = temp_current_time;
				
				setting_state_timeout.stop(&setting_state_timeout);
			}
			/* Botao 1 pressionado --> mudar para o estado de ajuste das horas */
			else if ((old_button1.value == BUTTON_PRESSED) && (button1.value == BUTTON_NOT_PRESSED))
			{
				m_state = SETTING_TIME_HOURS_STATE;
				
				setting_state_timeout.reset(&setting_state_timeout);
			}
			/* Botao 2 pressionado --> incrementar o horario atual em 1 segundo */
			else if ((old_button2.value == BUTTON_PRESSED) && (button2.value == BUTTON_NOT_PRESSED))
			{
				update_time(&temp_current_time, ONE_SECOND);
				
				setting_state_timeout.reset(&setting_state_timeout);
			}
			
			break;
		}
		/* Estado de ajuste das horas do alarme */
		case SETTING_ALARM_HOURS_STATE :
		{
			/* Timeout estorou --> voltar para o estado padrao */
			if (setting_state_timeout.get_value(&setting_state_timeout) >= SETTING_STATE_TIMEOUT)
			{
				m_state = RUNNING_TIME_STATE;
				
				setting_state_timeout.stop(&setting_state_timeout);
			}
			/* Botao 1 pressionado --> mudar para o estado de ajuste dos minutos do alarme */
			else if ((old_button1.value == BUTTON_PRESSED) && (button1.value == BUTTON_NOT_PRESSED))
			{
				m_state = SETTING_ALARM_MINUTES_STATE;
				
				setting_state_timeout.reset(&setting_state_timeout);
			}
			/* Botao 2 pressionado --> incrementar o horario do alarme em 1 hora */
			else if ((old_button2.value == BUTTON_PRESSED) && (button2.value == BUTTON_NOT_PRESSED))
			{
				update_time(&temp_current_time, ONE_HOUR);
				
				setting_state_timeout.reset(&setting_state_timeout);
			}
			
			break;
		}
		/* Estado de ajuste dos minutos do alarme */
		case SETTING_ALARM_MINUTES_STATE :
		{
			/* Timeout estorou --> voltar para o estado padrao */
			if (setting_state_timeout.get_value(&setting_state_timeout) >= SETTING_STATE_TIMEOUT)
			{
				m_state = RUNNING_TIME_STATE;
				
				setting_state_timeout.stop(&setting_state_timeout);
			}
			/* Botao 1 pressionado --> mudar para o estado de ajuste dos segundos do alarme */
			else if ((old_button1.value == BUTTON_PRESSED) && (button1.value == BUTTON_NOT_PRESSED))
			{
				m_state = SETTING_ALARM_SECONDS_STATE;
				
				setting_state_timeout.reset(&setting_state_timeout);
			}
			/* Botao 2 pressionado --> incrementar o horario do alarme em 1 minuto */
			else if ((old_button2.value == BUTTON_PRESSED) && (button2.value == BUTTON_NOT_PRESSED))
			{
				update_time(&temp_current_time, ONE_MINUTE);
				
				setting_state_timeout.reset(&setting_state_timeout);
			}
			
			break;
		}
		/* Estado de ajuste dos segundos do alarme */
		case SETTING_ALARM_SECONDS_STATE :
		{
			/* Timeout estorou --> voltar para o estado padrao */
			if (setting_state_timeout.get_value(&setting_state_timeout) >= SETTING_STATE_TIMEOUT)
			{
				m_state = RUNNING_TIME_STATE;
				
				setting_state_timeout.stop(&setting_state_timeout);
			}
			/* Botao 1 pressionado --> mudar para o estado de ajuste das horas do alarme */
			else if ((old_button1.value == BUTTON_PRESSED) && (button1.value == BUTTON_NOT_PRESSED))
			{
				m_state = SETTING_ALARM_HOURS_STATE;
				
				setting_state_timeout.reset(&setting_state_timeout);
			}
			/* Botao 2 pressionado --> incrementar o horario do alarme em 1 segundo */
			else if ((old_button2.value == BUTTON_PRESSED) && (button2.value == BUTTON_NOT_PRESSED))
			{
				update_time(&temp_current_time, ONE_SECOND);
				
				setting_state_timeout.reset(&setting_state_timeout);
			}
			
			break;
		}
	}
	
	xmemcpy(&old_button1, &button1, BUTTON_STRUCT_SIZE_IN_BYTES);
	xmemcpy(&old_button2, &button2, BUTTON_STRUCT_SIZE_IN_BYTES);
}
