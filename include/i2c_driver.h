#ifndef I2C_DRIVER_H
#define I2C_DRIVER_H
#include <stdint.h>

typedef enum i2c_error{
    I2C_FAIL = -1,
    I2C_SUCCESS = 0,
}i2c_err_t;

typedef struct {
    int fd;
    uint16_t i2c_addr;
    int i2c_lane;
}i2c_ctx_t;

i2c_err_t i2c_dev_init(i2c_ctx_t *, uint16_t, int);
i2c_err_t i2c_open_dev(i2c_ctx_t *);
i2c_err_t i2c_set(i2c_ctx_t *, uint8_t *, int);
i2c_err_t i2c_get(i2c_ctx_t *, uint8_t *, int);
#endif //I2C_DRIVER
