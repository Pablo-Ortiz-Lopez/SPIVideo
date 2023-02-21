/*
 * SPDX-FileCopyrightText: 2018-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "soc/gpio_periph.h"

const uint32_t GPIO_PIN_MUX_REG[] = {
    IO_MUX_GPIO0_REG,
    IO_MUX_GPIO1_REG,
    IO_MUX_GPIO2_REG,
    IO_MUX_GPIO3_REG,
    IO_MUX_GPIO4_REG,
    IO_MUX_GPIO5_REG,
    IO_MUX_GPIO6_REG,
    IO_MUX_GPIO7_REG,
    IO_MUX_GPIO8_REG,
    IO_MUX_GPIO9_REG,
    IO_MUX_GPIO10_REG,
    IO_MUX_GPIO11_REG,
    IO_MUX_GPIO12_REG,
    IO_MUX_GPIO13_REG,
    IO_MUX_GPIO14_REG,
    IO_MUX_GPIO15_REG,
    IO_MUX_GPIO16_REG,
    IO_MUX_GPIO17_REG,
    IO_MUX_GPIO18_REG,
    IO_MUX_GPIO19_REG,
    IO_MUX_GPIO20_REG,
    IO_MUX_GPIO21_REG,
    0,
    0,
    0,
    0,
    IO_MUX_GPIO26_REG,
    IO_MUX_GPIO27_REG,
    IO_MUX_GPIO28_REG,
    IO_MUX_GPIO29_REG,
    IO_MUX_GPIO30_REG,
    IO_MUX_GPIO31_REG,
    IO_MUX_GPIO32_REG,
    IO_MUX_GPIO33_REG,
    IO_MUX_GPIO34_REG,
    IO_MUX_GPIO35_REG,
    IO_MUX_GPIO36_REG,
    IO_MUX_GPIO37_REG,
    IO_MUX_GPIO38_REG,
    IO_MUX_GPIO39_REG,
    IO_MUX_GPIO40_REG,
    IO_MUX_GPIO41_REG,
    IO_MUX_GPIO42_REG,
    IO_MUX_GPIO43_REG,
    IO_MUX_GPIO44_REG,
    IO_MUX_GPIO45_REG,
    IO_MUX_GPIO46_REG,
    IO_MUX_GPIO47_REG,
    IO_MUX_GPIO48_REG,
};

_Static_assert(sizeof(GPIO_PIN_MUX_REG) == SOC_GPIO_PIN_COUNT * sizeof(uint32_t), "Invalid size of GPIO_PIN_MUX_REG");

const uint32_t GPIO_HOLD_MASK[] = {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    BIT(1),
    BIT(2),
    BIT(3),
    BIT(4),
    BIT(5),
    BIT(6),
    BIT(7),
    BIT(8),
    BIT(9),
    BIT(10),
    BIT(11),
    BIT(12),
    BIT(13),
    BIT(14),
    BIT(15),
    BIT(16),
    BIT(17),
    BIT(18),
    BIT(19),
    BIT(20),
    BIT(21),
    BIT(22),
    BIT(23),
    BIT(24),
    BIT(25),
    BIT(26),
    BIT(27),
};

_Static_assert(sizeof(GPIO_HOLD_MASK) == SOC_GPIO_PIN_COUNT * sizeof(uint32_t), "Invalid size of GPIO_HOLD_MASK");
