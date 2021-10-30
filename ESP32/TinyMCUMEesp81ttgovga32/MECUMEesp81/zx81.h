#ifndef _GB_ZX81_H
 #define _GB_ZX81_H
void z81_Init(void);
void z81_Step(void);
void z81_Start(char * filename);

void load_p(int a);

void z81_Start_Flash(unsigned char id);
void load_p_flash(int a,unsigned char id);
void z81_Init_Flash(unsigned char id);
void ResetZ80_Flash(unsigned char id);
void bitbufBlit(unsigned char * buf);
void frame_pause(void);
unsigned int out(int h,int l,int a);
unsigned int in(int h, int l);
void save_p(int a);
void do_interrupt();
#endif



