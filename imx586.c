// SPDX-License-Identifier: GPL-2.0-only
/*
 * Sony IMX586 CMOS sensor driver for NVIDIA Jetson
 */
#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/regmap.h>
#include <media/v4l2-ctrls.h>
#include <media/v4l2-subdev.h>
#include "imx586_reg_tables.h"
#define IMX586_REG_CHIP_ID_H 0x0016
#define IMX586_REG_CHIP_ID_L 0x0017
#define IMX586_CHIP_ID 0x0586
struct imx586 { struct regmap *regmap; struct v4l2_subdev sd; };
static int imx586_probe(struct i2c_client *client,
                        const struct i2c_device_id *id)
{
    struct imx586 *priv;
    priv = devm_kzalloc(&client->dev, sizeof(*priv), GFP_KERNEL);
    if (!priv) return -ENOMEM;
    priv->regmap = devm_regmap_init_i2c(client, &(struct regmap_config){
        .reg_bits = 16, .val_bits = 8, .max_register = 0xFFFF});
    if (IS_ERR(priv->regmap)) return PTR_ERR(priv->regmap);
    v4l2_i2c_subdev_init(&priv->sd, client, NULL);
    dev_info(&client->dev, "IMX586 probed");
    return 0;
}
static const struct of_device_id imx586_of_match[] = {
    { .compatible = "sony,imx586" }, { }
};
MODULE_DEVICE_TABLE(of, imx586_of_match);
static struct i2c_driver imx586_i2c_driver = {
    .driver = { .name = "imx586", .of_match_table = imx586_of_match },
    .probe  = imx586_probe,
};
module_i2c_driver(imx586_i2c_driver);
MODULE_LICENSE("GPL v2");
