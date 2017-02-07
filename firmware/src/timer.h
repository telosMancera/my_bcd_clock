#ifndef TIMER_H_
#define TIMER_H_

typedef struct timer timer;

struct timer
{
	int stopped;
	int base_value;
	int value;

	int (*start) (timer *);
	int (*stop) (timer *);
	int (*reset) (timer *);
	int (*get_value) (timer *);
};

timer new_timer (void);

int timer_init (void);
int timer_task (void);

#endif
