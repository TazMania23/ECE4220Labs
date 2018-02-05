/*
 ============================================================================
 Name        : Lab1Week2.c
 Author      : Tsiania Hughes
 Version     :
 Copyright   : Your copyright notice: it's mine, Taz
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <asm/io.h>
#include <linux/printk.h>
#include <linux/module.h>
#include <linux/kernel.h>

#ifndef MODULE
#define MODULE
#endif

#ifndef __KERNEL__
#define __KERNEL__
#endif

MODULE_LICENSE("GPL");

int init_module(void)
{
//pointer to hold
unsigned long *SelectPin= (unsigned long*)ioremap((0x3F200000),4096);
//could make this a global variable to set to specific registers to different names
// your code here
printk("Loading...");

iowrite32((*SelectPin | 0x00049240), SelectPin);
SelectPin+=7;//to move to register GPIO Set
iowrite32((0x0000003C),SelectPin);
printk("Loading Done!");

return 0;
}

void cleanup_module(void)
{
unsigned long *SelectPin= (unsigned long*)ioremap((0x3F200000),4096);

// your code here
printk("Stopping...");

iowrite32((*SelectPin | 0x00049240), SelectPin);
SelectPin+=10;//to move to GPIO clear
iowrite32((0x0000003C),SelectPin);
printk("Stopped");
}


/*MODULE_init(init_module);
MODULE_exit(cleanup_module);*/ 
//That is only needed if you dont specifiy the name
