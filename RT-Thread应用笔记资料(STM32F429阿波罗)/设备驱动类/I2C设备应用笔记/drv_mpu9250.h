/*
 * File      : drv_mpu9250.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2018, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-09-06     Wendell      first implementation.
 */

#ifndef __DRV_MPU9250_H__
#define __DRV_MPU9250_H__

#include <rthw.h>
#include <rtdevice.h>

rt_err_t mpu_write_reg(rt_uint8_t addr, rt_uint8_t reg, rt_uint8_t data);
rt_err_t mpu_read_reg(rt_uint8_t addr, rt_uint8_t reg, rt_uint8_t len, rt_uint8_t *buf);
rt_err_t mpu9250_gyro_fsr_set(rt_uint8_t fsr);
rt_err_t mpu9250_accel_fsr_set(rt_uint8_t fsr);
rt_err_t mpu9250_lpf_set(rt_uint16_t lpf);
rt_err_t mpu9250_sample_rate_set(rt_uint16_t rate);
rt_err_t mpu9250_temperature_get(rt_int16_t *temperature);
rt_err_t mpu9250_gyroscope_get(rt_int16_t *gx, rt_int16_t *gy, rt_int16_t *gz);
rt_err_t mpu9250_accelerometer_get(rt_int16_t *ax, rt_int16_t *ay, rt_int16_t *az);
rt_err_t mpu9250_magnetometer_get(rt_int16_t *mx,rt_int16_t *my,rt_int16_t *mz);
int mpu9250_hw_init(void);

#endif
