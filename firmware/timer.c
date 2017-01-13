#include "timer.h"

int time_in_10ms = 0;

int timer_start (timer *self)
{
	self->stopped = 0;
		
	self->base_value = time_in_10ms;
	self->value = 0;
	
	return 0;
}

int timer_stop (timer *self)
{
	self->stopped = 1;

	return 0;
}

int timer_reset (timer *self)
{	
	self->base_value = time_in_10ms;
	self->value = 0;

	return 0;
}

int timer_get_value (timer *self)
{
	if (!self->stopped) self->value = time_in_10ms - self->base_value;

	return self->value;
}

timer new_timer (void)
{
	timer t;

	t.stopped = 1;
	t.base_value = time_in_10ms;
	t.value = 0;
	
	t.start = timer_start;
	t.stop = timer_stop;
	t.reset = timer_reset;
	t.get_value = timer_get_value;

	return t;
}

int time_init (void)
{
	time_in_10ms = 0;

	return 0;
}

int timer_task (void)
{
	static int timer_task_cnt = 0;
	
	if (timer_task_cnt < 1000) timer_task_cnt++;
	else
	{
		timer_task_cnt = 0;
		time_in_10ms++;
	}

	return 0;
}
