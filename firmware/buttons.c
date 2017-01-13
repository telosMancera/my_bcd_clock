#include "buttons.h"
#include "timer.h"

timer button1_timer;
timer button2_timer;

button_value button1_value = 0;
button_value button2_value = 0;

int button1_time = 0;
int button2_time = 0;

int button_read (button *b, button_id id)
{
	if (id == BUTTON_1)
	{
		b->value = button1_value;
		b->time = button1_time;
	}
	else if (id == BUTTON_2)
	{
		b->value = button2_value;
		b->time = button2_time;
	}
	
	return b;
}

int buttons_init (void)
{
	button1_timer = new_timer();
	button1_value = 0;
	button1_time = 0;

	button2_timer = new_timer();
	button2_value = 0;
	button2_time = 0;
	
	button1_timer.start();
	button2_timer.start();
}

button_value my_pio_read (button_id id)
{
	// Funcao temporaria utilizada para simular a leitura do pino
	if (id == BUTTON_1) return BUTTON_NOT_PRESSED;
	else if (id == BUTTON_2) return BUTTON_PRESSED;
}

int buttons_task (void)
{
	static int button1_cnt = 0, button2_cnt = 0, old_button1_value = 0, old_button2_value = 0;

	/* Botao 1 */
	/* Debounce do botao */
	if (my_pio_read(BUTTON_1) == BUTTON_PRESSED)
	{
		if (button1_cnt >= 50) button1_cnt = 100;
		else button1_cnt++;
	}
	else
	{
		if (button1_cnt < 50) button1_cnt = 0;
		else button1_cnt--;
	}
	
	/* Valor do botao */
	if (button1_cnt >= 50) button1_value = BUTTON_PRESSED;
	else button1_value = BUTTON_NOT_PRESSED;

	/* Tempo no qual o botao esta no valor */
	if (button1_value != old_button1_value) button1_timer.reset();
	button1_time = button1_timer.get_value();
	
	/* Botao 2 */
	/* Debounce do botao */
	if (my_pio_read(BUTTON_2) == BUTTON_PRESSED)
	{
		if (button2_cnt >= 50) button2_cnt = 100;
		else button2_cnt++;
	}
	else
	{
		if (button2_cnt < 50) button2_cnt = 0;
		else button2_cnt--;
	}
	
	/* Valor do botao */
	if (button2_cnt >= 50) button2_value = BUTTON_PRESSED;
	else button2_value = BUTTON_NOT_PRESSED;

	/* Tempo no qual o botao esta no valor */
	if (button2_value != old_button2_value) button2_timer.reset();
	button2_time = button2_timer.get_value();

	return 0;
}
