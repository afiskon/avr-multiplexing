#define F_CPU 1000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

char dice1 = 5;
char dice2 = 5;

char rand1 = 1;
char rand2 = 1;

#define BTN_PIN 4
char button_pressed = 0;


#define ANIMATION_LENGTH 6
char dice1_animation[ANIMATION_LENGTH] = { 5, 4, 1, 3, 2, 6 };
char dice2_animation[ANIMATION_LENGTH] = { 3, 6, 4, 1, 5, 2 };
char animation_playing = 0;
char animation_index = 0;
char animation_last_updated_index = 0;
short animation_time = 0;

void setup()
{
  /* Do nothing */
}

void out_if(char high, char low, char cond)
{
  if(!cond)
    return;

  DDRB = (1 << low) | (1 << high);
  PORTB = (1 << high);
  _delay_ms(1);
}

void loop()
{
  _delay_ms(1);

  /* Random number generation */
  rand1++;
  if(rand1 > 6)
  {
    rand1 = 1;
    rand2++;
    if(rand2 > 6)
    {
      rand2 = 1;
    }
  }

  if(animation_playing)
  {
    animation_time++;
    if(animation_time >= 25)
    {
      if(animation_index >= ANIMATION_LENGTH)
      {
        /* End playing animation, display random numbers */
        animation_playing = 0;
        dice1 = rand1;
        dice2 = rand2;
      }
      else
      {
        /* Play the next animation frame */
        animation_time = 0;
        animation_index++;
        dice1 = dice1_animation[animation_index];
        dice2 = dice2_animation[animation_index];
      }
    }
  }
  else /* ! animation_playing */
  {
    /* If button was pressed and then released, change dice1 and dice2 */
    if((PINB & (1 << BTN_PIN)) == 0)
      button_pressed = 1;
    else if(button_pressed)
    {
      button_pressed = 0;

      /* Play animation first */
      animation_playing = 1;
      animation_time = 0;
      animation_index = 0;

      dice1_animation[animation_last_updated_index] = dice1;
      dice2_animation[animation_last_updated_index] = dice2;

      animation_last_updated_index++;
      if(animation_last_updated_index >= ANIMATION_LENGTH)
        animation_last_updated_index = 0;
    }
  }

  /* Display dice1 */
  out_if(1, 0, dice1 != 1);
  out_if(3, 2, dice1 == 4 || dice1 == 5 || dice1 == 6);
  out_if(3, 0, dice1 & 1);
  out_if(2, 1, dice1 == 6);

  /* Display dice2 */
  out_if(0, 1, dice2 != 1);
  out_if(2, 3, dice2 == 4 || dice2 == 5 || dice2 == 6);
  out_if(0, 3, dice2 & 1);
  out_if(1, 2, dice2 == 6);
}

void main()
{
  setup();
  while(1)
  {
    loop();
  }
}
