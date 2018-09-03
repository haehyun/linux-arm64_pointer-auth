// SPDX-License-Identifier: GPL-2.0
/*
 * Texas Instruments PCM186x Universal Audio ADC
 *
 * Copyright (C) 2015-2017 Texas Instruments Incorporated - http://www.ti.com
 *	Andreas Dannenberg <dannenberg@ti.com>
 *	Andrew F. Davis <afd@ti.com>
 */

#ifndef _PCM186X_H_
#define _PCM186X_H_

#include <linux/pm.h>
#include <linux/regmap.h>

enum pcm186x_type {
	PCM1862,
	PCM1863,
	PCM1864,
	PCM1865,
};

#define PCM186X_RATES	SNDRV_PCM_RATE_8000_192000
#define PCM186X_FORMATS	(SNDRV_PCM_FMTBIT_S16_LE | \
			 SNDRV_PCM_FMTBIT_S20_3LE |\
			 SNDRV_PCM_FMTBIT_S24_LE | \
			 SNDRV_PCM_FMTBIT_S32_LE)

#define PCM186X_PAGE_LEN		0x0100
#define PCM186X_PAGE_BASE(n)		(PCM186X_PAGE_LEN * n)

/* The page selection register address is the same on all pages */
#define PCM186X_PAGE			0

/* Register Definitions - Page 0 */
#define PCM186X_PGA_VAL_CH1_L		(PCM186X_PAGE_BASE(0) +   1)
#define PCM186X_PGA_VAL_CH1_R		(PCM186X_PAGE_BASE(0) +   2)
#define PCM186X_PGA_VAL_CH2_L		(PCM186X_PAGE_BASE(0) +   3)
#define PCM186X_PGA_VAL_CH2_R		(PCM186X_PAGE_BASE(0) +   4)
#define PCM186X_PGA_CTRL		(PCM186X_PAGE_BASE(0) +   5)
#define PCM186X_ADC1_INPUT_SEL_L	(PCM186X_PAGE_BASE(0) +   6)
#define PCM186X_ADC1_INPUT_SEL_R	(PCM186X_PAGE_BASE(0) +   7)
#define PCM186X_ADC2_INPUT_SEL_L	(PCM186X_PAGE_BASE(0) +   8)
#define PCM186X_ADC2_INPUT_SEL_R	(PCM186X_PAGE_BASE(0) +   9)
#define PCM186X_AUXADC_INPUT_SEL	(PCM186X_PAGE_BASE(0) +  10)
#define PCM186X_PCM_CFG			(PCM186X_PAGE_BASE(0) +  11)
#define PCM186X_TDM_TX_SEL		(PCM186X_PAGE_BASE(0) +  12)
#define PCM186X_TDM_TX_OFFSET		(PCM186X_PAGE_BASE(0) +  13)
#define PCM186X_TDM_RX_OFFSET		(PCM186X_PAGE_BASE(0) +  14)
#define PCM186X_DPGA_VAL_CH1_L		(PCM186X_PAGE_BASE(0) +  15)
#define PCM186X_GPIO1_0_CTRL		(PCM186X_PAGE_BASE(0) +  16)
#define PCM186X_GPIO3_2_CTRL		(PCM186X_PAGE_BASE(0) +  17)
#define PCM186X_GPIO1_0_DIR_CTRL	(PCM186X_PAGE_BASE(0) +  18)
#define PCM186X_GPIO3_2_DIR_CTRL	(PCM186X_PAGE_BASE(0) +  19)
#define PCM186X_GPIO_IN_OUT		(PCM186X_PAGE_BASE(0) +  20)
#define PCM186X_GPIO_PULL_CTRL		(PCM186X_PAGE_BASE(0) +  21)
#define PCM186X_DPGA_VAL_CH1_R		(PCM186X_PAGE_BASE(0) +  22)
#define PCM186X_DPGA_VAL_CH2_L		(PCM186X_PAGE_BASE(0) +  23)
#define PCM186X_DPGA_VAL_CH2_R		(PCM186X_PAGE_BASE(0) +  24)
#define PCM186X_DPGA_GAIN_CTRL		(PCM186X_PAGE_BASE(0) +  25)
#define PCM186X_DPGA_MIC_CTRL		(PCM186X_PAGE_BASE(0) +  26)
#define PCM186X_DIN_RESAMP_CTRL		(PCM186X_PAGE_BASE(0) +  27)
#define PCM186X_CLK_CTRL		(PCM186X_PAGE_BASE(0) +  32)
#define PCM186X_DSP1_CLK_DIV		(PCM186X_PAGE_BASE(0) +  33)
#define PCM186X_DSP2_CLK_DIV		(PCM186X_PAGE_BASE(0) +  34)
#define PCM186X_ADC_CLK_DIV		(PCM186X_PAGE_BASE(0) +  35)
#define PCM186X_PLL_SCK_DIV		(PCM186X_PAGE_BASE(0) +  37)
#define PCM186X_BCK_DIV			(PCM186X_PAGE_BASE(0) +  38)
#define PCM186X_LRK_DIV			(PCM186X_PAGE_BASE(0) +  39)
#define PCM186X_PLL_CTRL		(PCM186X_PAGE_BASE(0) +  40)
#define PCM186X_PLL_P_DIV		(PCM186X_PAGE_BASE(0) +  41)
#define PCM186X_PLL_R_DIV		(PCM186X_PAGE_BASE(0) +  42)
#define PCM186X_PLL_J_DIV		(PCM186X_PAGE_BASE(0) +  43)
#define PCM186X_PLL_D_DIV_LSB		(PCM186X_PAGE_BASE(0) +  44)
#define PCM186X_PLL_D_DIV_MSB		(PCM186X_PAGE_BASE(0) +  45)
#define PCM186X_SIGDET_MODE		(PCM186X_PAGE_BASE(0) +  48)
#define PCM186X_SIGDET_MASK		(PCM186X_PAGE_BASE(0) +  49)
#define PCM186X_SIGDET_STAT		(PCM186X_PAGE_BASE(0) +  50)
#define PCM186X_SIGDET_LOSS_TIME	(PCM186X_PAGE_BASE(0) +  52)
#define PCM186X_SIGDET_SCAN_TIME	(PCM186X_PAGE_BASE(0) +  53)
#define PCM186X_SIGDET_INT_INTVL	(PCM186X_PAGE_BASE(0) +  54)
#define PCM186X_SIGDET_DC_REF_CH1_L	(PCM186X_PAGE_BASE(0) +  64)
#define PCM186X_SIGDET_DC_DIFF_CH1_L	(PCM186X_PAGE_BASE(0) +  65)
#define PCM186X_SIGDET_DC_LEV_CH1_L	(PCM186X_PAGE_BASE(0) +  66)
#define PCM186X_SIGDET_DC_REF_CH1_R	(PCM186X_PAGE_BASE(0) +  67)
#define PCM186X_SIGDET_DC_DIFF_CH1_R	(PCM186X_PAGE_BASE(0) +  68)
#define PCM186X_SIGDET_DC_LEV_CH1_R	(PCM186X_PAGE_BASE(0) +  69)
#define PCM186X_SIGDET_DC_REF_CH2_L	(PCM186X_PAGE_BASE(0) +  70)
#define PCM186X_SIGDET_DC_DIFF_CH2_L	(PCM186X_PAGE_BASE(0) +  71)
#define PCM186X_SIGDET_DC_LEV_CH2_L	(PCM186X_PAGE_BASE(0) +  72)
#define PCM186X_SIGDET_DC_REF_CH2_R	(PCM186X_PAGE_BASE(0) +  73)
#define PCM186X_SIGDET_DC_DIFF_CH2_R	(PCM186X_PAGE_BASE(0) +  74)
#define PCM186X_SIGDET_DC_LEV_CH2_R	(PCM186X_PAGE_BASE(0) +  75)
#define PCM186X_SIGDET_DC_REF_CH3_L	(PCM186X_PAGE_BASE(0) +  76)
#define PCM186X_SIGDET_DC_DIFF_CH3_L	(PCM186X_PAGE_BASE(0) +  77)
#define PCM186X_SIGDET_DC_LEV_CH3_L	(PCM186X_PAGE_BASE(0) +  78)
#define PCM186X_SIGDET_DC_REF_CH3_R	(PCM186X_PAGE_BASE(0) +  79)
#define PCM186X_SIGDET_DC_DIFF_CH3_R	(PCM186X_PAGE_BASE(0) +  80)
#define PCM186X_SIGDET_DC_LEV_CH3_R	(PCM186X_PAGE_BASE(0) +  81)
#define PCM186X_SIGDET_DC_REF_CH4_L	(PCM186X_PAGE_BASE(0) +  82)
#define PCM186X_SIGDET_DC_DIFF_CH4_L	(PCM186X_PAGE_BASE(0) +  83)
#define PCM186X_SIGDET_DC_LEV_CH4_L	(PCM186X_PAGE_BASE(0) +  84)
#define PCM186X_SIGDET_DC_REF_CH4_R	(PCM186X_PAGE_BASE(0) +  85)
#define PCM186X_SIGDET_DC_DIFF_CH4_R	(PCM186X_PAGE_BASE(0) +  86)
#define PCM186X_SIGDET_DC_LEV_CH4_R	(PCM186X_PAGE_BASE(0) +  87)
#define PCM186X_AUXADC_DATA_CTRL	(PCM186X_PAGE_BASE(0) +  88)
#define PCM186X_AUXADC_DATA_LSB		(PCM186X_PAGE_BASE(0) +  89)
#define PCM186X_AUXADC_DATA_MSB		(PCM186X_PAGE_BASE(0) +  90)
#define PCM186X_INT_ENABLE		(PCM186X_PAGE_BASE(0) +  96)
#define PCM186X_INT_FLAG		(PCM186X_PAGE_BASE(0) +  97)
#define PCM186X_INT_POL_WIDTH		(PCM186X_PAGE_BASE(0) +  98)
#define PCM186X_POWER_CTRL		(PCM186X_PAGE_BASE(0) + 112)
#define PCM186X_FILTER_MUTE_CTRL	(PCM186X_PAGE_BASE(0) + 113)
#define PCM186X_DEVICE_STATUS		(PCM186X_PAGE_BASE(0) + 114)
#define PCM186X_FSAMPLE_STATUS		(PCM186X_PAGE_BASE(0) + 115)
#define PCM186X_DIV_STATUS		(PCM186X_PAGE_BASE(0) + 116)
#define PCM186X_CLK_STATUS		(PCM186X_PAGE_BASE(0) + 117)
#define PCM186X_SUPPLY_STATUS		(PCM186X_PAGE_BASE(0) + 120)

/* Register Definitions - Page 1 */
#define PCM186X_MMAP_STAT_CTRL		(PCM186X_PAGE_BASE(1) +   1)
#define PCM186X_MMAP_ADDRESS		(PCM186X_PAGE_BASE(1) +   2)
#define PCM186X_MEM_WDATA0		(PCM186X_PAGE_BASE(1) +   4)
#define PCM186X_MEM_WDATA1		(PCM186X_PAGE_BASE(1) +   5)
#define PCM186X_MEM_WDATA2		(PCM186X_PAGE_BASE(1) +   6)
#define PCM186X_MEM_WDATA3		(PCM186X_PAGE_BASE(1) +   7)
#define PCM186X_MEM_RDATA0		(PCM186X_PAGE_BASE(1) +   8)
#define PCM186X_MEM_RDATA1		(PCM186X_PAGE_BASE(1) +   9)
#define PCM186X_MEM_RDATA2		(PCM186X_PAGE_BASE(1) +  10)
#define PCM186X_MEM_RDATA3		(PCM186X_PAGE_BASE(1) +  11)

/* Register Definitions - Page 3 */
#define PCM186X_OSC_PWR_DOWN_CTRL	(PCM186X_PAGE_BASE(3) +  18)
#define PCM186X_MIC_BIAS_CTRL		(PCM186X_PAGE_BASE(3) +  21)

/* Register Definitions - Page 253 */
#define PCM186X_CURR_TRIM_CTRL		(PCM186X_PAGE_BASE(253) +  20)

#define PCM186X_MAX_REGISTER		PCM186X_CURR_TRIM_CTRL

/* PCM186X_PAGE */
#define PCM186X_RESET			0xff

/* PCM186X_ADCX_INPUT_SEL_X */
#define PCM186X_ADC_INPUT_SEL_POL	BIT(7)
#define PCM186X_ADC_INPUT_SEL_MASK	GENMASK(5, 0)

/* PCM186X_PCM_CFG */
#define PCM186X_PCM_CFG_RX_WLEN_MASK	GENMASK(7, 6)
#define PCM186X_PCM_CFG_RX_WLEN_SHIFT	6
#define PCM186X_PCM_CFG_RX_WLEN_32	0x00
#define PCM186X_PCM_CFG_RX_WLEN_24	0x01
#define PCM186X_PCM_CFG_RX_WLEN_20	0x02
#define PCM186X_PCM_CFG_RX_WLEN_16	0x03
#define PCM186X_PCM_CFG_TDM_LRCK_MODE	BIT(4)
#define PCM186X_PCM_CFG_TX_WLEN_MASK	GENMASK(3, 2)
#define PCM186X_PCM_CFG_TX_WLEN_SHIFT	2
#define PCM186X_PCM_CFG_TX_WLEN_32	0x00
#define PCM186X_PCM_CFG_TX_WLEN_24	0x01
#define PCM186X_PCM_CFG_TX_WLEN_20	0x02
#define PCM186X_PCM_CFG_TX_WLEN_16	0x03
#define PCM186X_PCM_CFG_FMT_MASK	GENMASK(1, 0)
#define PCM186X_PCM_CFG_FMT_SHIFT	0
#define PCM186X_PCM_CFG_FMT_I2S		0x00
#define PCM186X_PCM_CFG_FMT_LEFTJ	0x01
#define PCM186X_PCM_CFG_FMT_RIGHTJ	0x02
#define PCM186X_PCM_CFG_FMT_TDM		0x03

/* PCM186X_TDM_TX_SEL */
#define PCM186X_TDM_TX_SEL_2CH		0x00
#define PCM186X_TDM_TX_SEL_4CH		0x01
#define PCM186X_TDM_TX_SEL_6CH		0x02
#define PCM186X_TDM_TX_SEL_MASK		0x03

/* PCM186X_CLK_CTRL */
#define PCM186X_CLK_CTRL_SCK_XI_SEL1	BIT(7)
#define PCM186X_CLK_CTRL_SCK_XI_SEL0	BIT(6)
#define PCM186X_CLK_CTRL_SCK_SRC_PLL	BIT(5)
#define PCM186X_CLK_CTRL_MST_MODE	BIT(4)
#define PCM186X_CLK_CTRL_ADC_SRC_PLL	BIT(3)
#define PCM186X_CLK_CTRL_DSP2_SRC_PLL	BIT(2)
#define PCM186X_CLK_CTRL_DSP1_SRC_PLL	BIT(1)
#define PCM186X_CLK_CTRL_CLKDET_EN	BIT(0)

/* PCM186X_PLL_CTRL */
#define PCM186X_PLL_CTRL_LOCK		BIT(4)
#define PCM186X_PLL_CTRL_REF_SEL	BIT(1)
#define PCM186X_PLL_CTRL_EN		BIT(0)

/* PCM186X_POWER_CTRL */
#define PCM186X_PWR_CTRL_PWRDN		BIT(2)
#define PCM186X_PWR_CTRL_SLEEP		BIT(1)
#define PCM186X_PWR_CTRL_STBY		BIT(0)

/* PCM186X_CLK_STATUS */
#define PCM186X_CLK_STATUS_LRCKHLT	BIT(6)
#define PCM186X_CLK_STATUS_BCKHLT	BIT(5)
#define PCM186X_CLK_STATUS_SCKHLT	BIT(4)
#define PCM186X_CLK_STATUS_LRCKERR	BIT(2)
#define PCM186X_CLK_STATUS_BCKERR	BIT(1)
#define PCM186X_CLK_STATUS_SCKERR	BIT(0)

/* PCM186X_SUPPLY_STATUS */
#define PCM186X_SUPPLY_STATUS_DVDD	BIT(2)
#define PCM186X_SUPPLY_STATUS_AVDD	BIT(1)
#define PCM186X_SUPPLY_STATUS_LDO	BIT(0)

/* PCM186X_MMAP_STAT_CTRL */
#define PCM186X_MMAP_STAT_DONE		BIT(4)
#define PCM186X_MMAP_STAT_BUSY		BIT(2)
#define PCM186X_MMAP_STAT_R_REQ		BIT(1)
#define PCM186X_MMAP_STAT_W_REQ		BIT(0)

extern const struct regmap_config pcm186x_regmap;

int pcm186x_probe(struct device *dev, enum pcm186x_type type, int irq,
		  struct regmap *regmap);
int pcm186x_remove(struct device *dev);

#endif /* _PCM186X_H_ */
