/*
 * pwm_general.h
 *
 * Created: 22/08/2013 7:13:04 AM
 *  Author: THIET KE 3
 */ 


#ifndef PWM_GENERAL_H_
#define PWM_GENERAL_H_
#define resolution	50
uint8_t  check_equ(uint8_t bot,uint8_t top, uint8_t *gray,uint8_t val);
void pwm_gen(uint8_t rate,uint8_t *gray);
void rotatal(uint8_t bot,uint8_t top,uint8_t *gray,uint8_t step,uint8_t direct);
void set_value(uint8_t bot,uint8_t top,uint8_t value,uint8_t *gray);
void set_value_slowly(uint8_t bot,uint8_t top,uint8_t value,uint8_t *gray,uint8_t speed,uint8_t direct) ;
void radian_gen(uint8_t bot,uint8_t top,uint8_t *gray, uint8_t resolut,uint8_t direct, uint8_t adj,uint8_t adj2);
void brighness_down(uint8_t bot, uint8_t top, uint8_t *gray,uint8_t speed,uint8_t step,uint8_t level);
void brighness_up(uint8_t bot, uint8_t top, uint8_t *gray,uint8_t step,uint8_t speed,uint8_t level);
void light_change(uint8_t bot, uint8_t top, uint8_t *gray,uint8_t step,uint8_t style);
void auto_change(uint8_t bot,uint8_t top,uint8_t *gray,uint8_t speed,uint8_t step,uint8_t val);
void random_light(uint8_t bot,uint8_t top,uint8_t *gray);
void light_appear(uint8_t bot,uint8_t top, uint8_t *gray,uint8_t speed,uint8_t step,uint8_t style);
void pendul(uint8_t bot,uint8_t top,uint8_t *gray,uint8_t speed,uint8_t repeat,uint8_t back_light,uint8_t front_light,uint8_t style);
void fill_pendul(uint8_t bot,uint8_t top,uint8_t *gray,uint8_t speed,uint8_t back_light,uint8_t style);
void soft_flash(uint8_t bot,uint8_t top,uint8_t speed,uint8_t repeat,uint8_t val1,uint8_t val2);
void fill_drop(uint8_t bot,uint8_t top,uint8_t *gray,uint8_t speed,uint8_t size,uint8_t direct );
void shooting_star(uint8_t bot,uint8_t top,uint8_t *gray,uint8_t speed,uint8_t size,uint8_t direct );
void bytwo(uint8_t bot,uint8_t top,uint8_t *gray,uint8_t speed,uint8_t repeat,uint8_t brigness,uint8_t type_radian,uint8_t direct);
void growing(uint8_t bot,uint8_t top,uint8_t *gray,uint8_t speed,uint8_t step,uint8_t size,uint8_t type);
void downing(uint8_t bot,uint8_t top,uint8_t *gray,uint8_t speed,uint8_t step,uint8_t size,uint8_t type);
void twopoint(uint8_t point1,uint8_t point2,uint8_t *gray,uint8_t speed,uint8_t repeat,uint8_t type);
void seed(uint8_t bot,uint8_t top,uint8_t *gray,uint8_t speed,uint8_t step,uint8_t type);
void fill_seed(uint8_t bot,uint8_t top,uint8_t *gray,uint8_t speed,uint8_t step,uint8_t type);
void combine(uint8_t bot,uint8_t top,uint8_t *gray,uint8_t speed,uint8_t repeat,uint8_t backgound,uint8_t type);
void fill_combine(uint8_t bot,uint8_t top,uint8_t *gray,uint8_t speed,uint8_t backgound,uint8_t type);
void sleep(uint16_t interval,uint8_t *gray);
void running_flash(uint8_t bot,uint8_t top,uint8_t *gray,uint8_t speed,uint8_t repeat,uint8_t back_gound,uint8_t type);
void hard_flash(uint8_t bot,uint8_t top,uint8_t *gray,uint8_t speed,uint8_t repeat,uint8_t type);
void odd_even(uint8_t bot,uint8_t top,uint8_t *gray,uint8_t speed,uint8_t repeat,uint8_t step);
void n_rota(uint8_t bot,uint8_t top,uint8_t *gray,uint8_t direct,uint8_t speed,uint16_t repeat );
void border(uint8_t bot,uint8_t top,uint8_t *gray,uint8_t speed,uint8_t repeat,const uint8_t *point,uint8_t type);
void load_value(uint8_t bot,uint8_t top,uint8_t *gray,const uint8_t *point);
void random_light_st1(uint8_t bot,uint8_t top,uint8_t *gray,uint8_t speed,uint16_t repeat,uint8_t max_sleep);
void random_light_st2(uint8_t bot,uint8_t top,uint8_t *gray,uint8_t speed,uint16_t repeat);
#endif /* PWM_GENERAL_H_ */