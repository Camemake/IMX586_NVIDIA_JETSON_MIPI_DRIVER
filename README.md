# Sony IMX586 – V4L2 Driver for NVIDIA Jetson (4-lane CSI)

Linux V4L2 sub-device driver for Sony IMX586 integrated into Jetson platforms with 4-lane CSI interfaces.

## Supported Jetson Boards

| Jetson Model       | Interface | Notes                        |
|--------------------|-----------|------------------------------|
| Nano (B01)         | CSI A/B   | Dual 2-lane, use B for 4-lane |
| Xavier NX          | CSI A/B   | Both support 4 lanes         |
| TX2 NX             | CSI       | 4-lane supported             |
| AGX Xavier         | CSI       | 6-lane total (3x2 or 2x4)    |
| Orin NX / Nano     | CSI       | Up to 4-lane supported       |

## Sensor Integration

### I²C and GPIO

| Signal    | Value          |
|-----------|----------------|
| I²C addr  | 0x1a (7-bit)   |
| RESET     | GPIO (board DT specific) |
| XCLK      | 37.125 MHz     |
| DOVDD     | 1.8 V          |
| AVDD      | 2.8 V          |
| DVDD      | 1.1 V (on-chip LDO) |

Set appropriate regulators and clocks in DTSI according to carrier board.

## DTSI Example (Fragment)

```dts
imx586_a@1a {
    compatible = "sony,imx586";
    reg = <0x1a>;
    devnode = "video0";
    physical_w = "6.287";
    physical_h = "4.712";
    sensor_model = "imx586";

    reset-gpios = <&gpio TEGRA_GPIO(Z, 4) GPIO_ACTIVE_HIGH>;
    clocks = <&tegra_car TEGRA210_CLK_CLK_OUT_3>;
    clock-names = "xclk";
    clock-frequency = <37125000>;

    mode0 {
        mclk_khz = "37125";
        num_lanes = "4";
        tegra_sinterface = "serial_a";
        phy_mode = "DPHY";
        discontinuous_clk = "no";
        dpcm_enable = "false";
        cil_settletime = "0";

        active_w = "4000";
        active_h = "3000";
        pixel_t = "bayer_bggr10";
        readout_orientation = "0";
        line_length = "4400";
        inherent_gain = "1";
        mclk_multiplier = "2";
        pix_clk_hz = "445500000";

        gain_factor = "16";
        min_gain_val = "16";
        max_gain_val = "170";
        step_gain_val = "1";
        default_gain = "16";

        min_hdr_ratio = "1";
        max_hdr_ratio = "1";
        framerate_factor = "1000000";
        min_framerate = "15000000";
        max_framerate = "30000000";
        step_framerate = "1";
        default_framerate = "30000000";
    };
};
```

## Driver Installation

```bash
sudo apt install dkms build-essential
./setup.sh
```

Then rebuild and flash DT to integrate the `.dtsi`. This is platform-specific (`flash.sh`, JetPack SDK, etc.).

## libcamera / V4L2 Use

Check detection:

```bash
v4l2-ctl --list-devices
```

Stream test:

```bash
libcamera-vid -t 0 --width 4000 --height 3000 --framerate 30 -o out.h264
```

## Notes

- Use correct CSI interface index (`serial_a`, `serial_b`, etc.)
- Modify GPIO and regulator entries to match carrier board layout.
- Driver supports IMX586 QBC 12MP @30fps. Add modes in `reg_tables.h`.

## TODO

- Add 4K60 and HDR modes
- Full libcamera tuning support
- C-PHY mode support (future Jetsons only)

---

