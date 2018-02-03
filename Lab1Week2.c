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
	// your code here
	printk("Loading...");
	//pointer to hold
	unsigned long *SelectPin= (unsigned long)*ioremap((0x3F200000),4096);
	iowrite32((*SelectPin | 0x00049240), SelectPin);
	SelectPin+=7;
	iowrite((0x0000003C),SelectPin);
	printk("Loading Done!");

	return 0;
}

void cleanup_module(void)
{
	// your code here
	printk("Stopping...");
	unsigned long *SelectPin= (unsigned long)*ioremap((0x3F200000),4096);
	iowrite32((*SelectPin | 0x00049240), SelectPin);
	SelectPin+=10;
	iowrite((0x0000003C),SelectPin);
	printk("Stopped");
}

MODULE_init(init_module);
MODULE_exit(cleanup_module);
