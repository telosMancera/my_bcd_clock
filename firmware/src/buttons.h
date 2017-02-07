#ifndef BUTTONS_H_
#define BUTTONS_H_

typedef enum
{
	BUTTON_1,
	BUTTON_2
} button_id;

typedef enum
{
	BUTTON_PRESSED,
	BUTTON_NOT_PRESSED
} button_value;

typedef struct
{
	int value;
	int time;
} button;

#define BUTTON_STRUCT_SIZE				(sizeof(button) / sizeof(int))
#define	BUTTON_STRUCT_SIZE_IN_BYTES		(sizeof(button) / sizeof(char))

int buttons_init (void);
int buttons_task (void);
int button_read (button *b, button_id id);

#endif
