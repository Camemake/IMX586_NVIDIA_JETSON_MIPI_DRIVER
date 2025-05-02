// SPDX-License-Identifier: GPL-2.0-only
#ifndef _IMX586_REG_TABLES_H
#define _IMX586_REG_TABLES_H
#include <linux/regmap.h>
#define REG_NULL 0xFFFF
static const struct reg_sequence imx586_mode_12mp_30fps[] = {
    {0x0136, 0x12},
    {0x0137, 0x00},
    {0x0100, 0x00},
    {REG_NULL, 0x00},
};
#endif
