/* e400 LCD support.
 * (c) 2005 Ian Molton <spyro@f2s.com>
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>

#include <asm/mach-types.h>
#include <asm/arch/pxa-regs.h>
#include <asm/arch/pxafb.h> 

static struct pxafb_mode_info e400_pxafb_mode_info = {
	.pixclock       = 140703,
	.xres           = 240,
	.yres           = 320,
	.bpp            = 16,
	.hsync_len      = 4,
	.left_margin    = 28,
	.right_margin   = 8,
	.vsync_len      = 3,
	.upper_margin   = 5,
	.lower_margin   = 6,
	.sync           = 0,
};

static struct pxafb_mach_info e400_pxafb_mach_info = {
	.modes          = &e400_pxafb_mode_info,
	.num_modes      = 1,
	.lccr0          = LCCR0_Color | LCCR0_Sngl | LCCR0_Act,
	.lccr3          = 0,
	.pxafb_backlight_power  = NULL,
};

static int __init e400_lcd_init( void )
{
	if(!machine_is_e400())
		return -ENODEV;

	set_pxa_fb_info(&e400_pxafb_mach_info);
	return 0;
}

module_init(e400_lcd_init);

MODULE_AUTHOR("Ian Molton <spyro@f2s.com>");
MODULE_DESCRIPTION("e400 lcd driver");
MODULE_LICENSE("GPLv2");

