/*
 * include/asm-arm/arch-pxa/palmt680-gpio.h
 *
 */

#ifndef _PALMT680_GPIO_H_
#define _PALMT680_GPIO_H_

#include <asm/arch/pxa-regs.h>

#define PALMT680_ASIC6_PHYS		(PXA_CS2_PHYS)
#define PALMT680_ASIC6_VIRT		(0xf0000000)
#define PALMT680_ASIC6_SIZE		(0x00100000)

/* ASIC 6 registers */
/* Note: the naming and purpose  of these registers is just a guess. */

#define __REG16(x)       (*((volatile u16 *)(x)))
#define __ASIC6_REG(x)	__REG16(PALMT680_ASIC6_VIRT + (x))

#define ASIC6_LED0_TBS		__REG(0x80)
#define ASIC6_LED0_U1		__ASIC6_REG(0x82) /* unknown=0 */
#define ASIC6_LED0_PERIOD	__ASIC6_REG(0x84)
#define ASIC6_LED0_U2		__ASIC6_REG(0x86) /* unknown=3 */
#define ASIC6_LED0_DUTY		__ASIC6_REG(0x88)
#define ASIC6_LED0_AUTOSTOP	__ASIC6_REG(0x8a)
#define ASIC6_LED1_TBS		__ASIC6_REG(0x90)
#define ASIC6_LED1_PERIOD	__ASIC6_REG(0x94)
#define ASIC6_LED1_DUTY		__ASIC6_REG(0x98)
#define ASIC6_LED1_AUTOSTOP	__ASIC6_REG(0x9a)
#define ASIC6_LED2_TBS		__ASIC6_REG(0xa0)
#define ASIC6_LED2_PERIOD	__ASIC6_REG(0xa4)
#define ASIC6_LED2_DUTY		__ASIC6_REG(0xa8)
#define ASIC6_LED2_AUTOSTOP	__ASIC6_REG(0xaa)

#define ASIC6_GPLR		__ASIC6_REG(0x48)
#define ASIC6_GPLR_GSM_POWER	(1<<6)
/* one of these will be reset the other power, not sure which is which */
#define ASIC6_GPLR_BT_PW1	(1<<4)
#define ASIC6_GPLR_BT_PW2	(1<<5)

#define SET_ASIC6_GPIO(gpio, setp) \
do { \
if (setp) \
		ASIC6_GPLR |= ASIC6_GPLR_ ## gpio; \
else \
		ASIC6_GPLR &= ~ASIC6_GPLR_ ## gpio; \
} while (0)

#define GET_ASIC6_GPIO(gpio) \
		(ASIC6_GPLR & ASIC6_GPLR_ ## gpio)


/* Palm Treo 680 GPIOs */
/* these values really are from Treo 680 */
#define GPIO_NR_PALMT680_BL_POWER               38
#define GPIO_NR_PALMT680_POWER_DETECT		0
#define GPIO_NR_PALMT680_SILENT_SWITCH		15
#define GPIO_NR_PALMT680_SD_DETECT_N            113     /* SD card inserted; RE FE; Input */

/* FIXME: these values are currently from 650. They will probably be
 * different for the 680. */
#define GPIO_NR_PALMT680_VIBRATE_EN		26
#define GPIO_NR_PALMT680_WM9712_IRQ		90


#define GPIO_NR_PALMT680_KP_MKIN0         100     
#define GPIO_NR_PALMT680_KP_MKIN1         101     
#define GPIO_NR_PALMT680_KP_MKIN2         102     
#define GPIO_NR_PALMT680_KP_MKIN3         97              
#define GPIO_NR_PALMT680_KP_MKIN4         98 
#define GPIO_NR_PALMT680_KP_MKIN5         99      
#define GPIO_NR_PALMT680_KP_MKIN6         17      
#define GPIO_NR_PALMT680_KP_MKIN7         13      
0
#define GPIO_NR_PALMT680_KP_MKOUT0        103
#define GPIO_NR_PALMT680_KP_MKOUT1        104
#define GPIO_NR_PALMT680_KP_MKOUT2        105
#define GPIO_NR_PALMT680_KP_MKOUT3        106
#define GPIO_NR_PALMT680_KP_MKOUT4        107
#define GPIO_NR_PALMT680_KP_MKOUT5        108
#define GPIO_NR_PALMT680_KP_MKOUT6        40 

#define IRQ_GPIO_PALMT680_SD_DETECT_N	IRQ_GPIO(GPIO_NR_PALMT680_SD_DETECT_N)
#define IRQ_GPIO_PALMT680_WM9712_IRQ	IRQ_GPIO(GPIO_NR_PALMT680_WM9712_IRQ)

#define GPIO_NR_PALMT680_KP_MKIN0_MD      (GPIO_NR_PALMT680_KP_MKIN0 | GPIO_ALT_FN_1_IN)
#define GPIO_NR_PALMT680_KP_MKIN1_MD      (GPIO_NR_PALMT680_KP_MKIN1 | GPIO_ALT_FN_1_IN)
#define GPIO_NR_PALMT680_KP_MKIN2_MD      (GPIO_NR_PALMT680_KP_MKIN2 | GPIO_ALT_FN_1_IN)
#define GPIO_NR_PALMT680_KP_MKIN3_MD      (GPIO_NR_PALMT680_KP_MKIN3 | GPIO_ALT_FN_3_IN)
#define GPIO_NR_PALMT680_KP_MKIN4_MD      (GPIO_NR_PALMT680_KP_MKIN4 | GPIO_ALT_FN_3_IN)
#define GPIO_NR_PALMT680_KP_MKIN5_MD      (GPIO_NR_PALMT680_KP_MKIN5 | GPIO_ALT_FN_3_IN)
#define GPIO_NR_PALMT680_KP_MKIN6_MD      (GPIO_NR_PALMT680_KP_MKIN6 | GPIO_ALT_FN_1_IN)
#define GPIO_NR_PALMT680_KP_MKIN7_MD      (GPIO_NR_PALMT680_KP_MKIN7 | GPIO_ALT_FN_3_IN)

#define GPIO_NR_PALMT680_KP_MKOUT0_MD (GPIO_NR_PALMT680_KP_MKOUT0 | GPIO_ALT_FN_2_OUT)
#define GPIO_NR_PALMT680_KP_MKOUT1_MD (GPIO_NR_PALMT680_KP_MKOUT1 | GPIO_ALT_FN_2_OUT)
#define GPIO_NR_PALMT680_KP_MKOUT2_MD (GPIO_NR_PALMT680_KP_MKOUT2 | GPIO_ALT_FN_2_OUT)
#define GPIO_NR_PALMT680_KP_MKOUT3_MD (GPIO_NR_PALMT680_KP_MKOUT3 | GPIO_ALT_FN_2_OUT)
#define GPIO_NR_PALMT680_KP_MKOUT4_MD (GPIO_NR_PALMT680_KP_MKOUT4 | GPIO_ALT_FN_2_OUT)
#define GPIO_NR_PALMT680_KP_MKOUT5_MD (GPIO_NR_PALMT680_KP_MKOUT5 | GPIO_ALT_FN_2_OUT)
#define GPIO_NR_PALMT680_KP_MKOUT6_MD (GPIO_NR_PALMT680_KP_MKOUT6 | GPIO_ALT_FN_1_OUT)

/* Utility macros */
#define GET_PALMT680_GPIO(gpio) \
        (GPLR(GPIO_NR_PALMT680_ ## gpio) & GPIO_bit(GPIO_NR_PALMT680_ ## gpio))

#define SET_PALMT680_GPIO(gpio, setp) \
do { \
if (setp) \
        GPSR(GPIO_NR_PALMT680_ ## gpio) = GPIO_bit(GPIO_NR_PALMT680_ ## gpio); \
else \
        GPCR(GPIO_NR_PALMT680_ ## gpio) = GPIO_bit(GPIO_NR_PALMT680_ ## gpio); \
} while (0)

#define SET_PALMT680_GPIO_N(gpio, setp) \
do { \
if (setp) \
        GPCR(GPIO_NR_PALMT680_ ## gpio) = GPIO_bit(GPIO_NR_PALMT680_ ## gpio); \
else \
        GPSR(GPIO_NR_PALMT680_ ## gpio) = GPIO_bit(GPIO_NR_PALMT680_ ## gpio); \
} while (0)


#define GET_GPIO(gpio) (GPLR(gpio) & GPIO_bit(gpio))


#endif /* _PALMT680_GPIO_H_ */
