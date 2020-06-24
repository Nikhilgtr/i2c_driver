#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <i2c_driver.h>


i2c_err_t i2c_dev_init(i2c_ctx_t *self, uint16_t addr, int lane)
{
    self->i2c_addr = addr;
    self->i2c_lane = lane;
    self->fd = 0;
}


/*
 *This function is used for opening the i2c device
 *IN @
 * i2c_ctx_t
 *OUT @
 * i2c_err_t = error code for i2c device
 */

i2c_err_t i2c_open_dev(i2c_ctx_t *ctx)
{

    char buff[20];
    int rc;

    sprintf(buff, "/dev/i2c-%d", ctx->i2c_lane);
    ctx->fd = open(buff, O_RDWR);
    if(ctx->fd == -1) { 
        printf("Error!! Device Unavailable\n");
        return I2C_FAIL;
    }

    rc = ioctl(ctx->fd, I2C_SLAVE, ctx->i2c_addr);
    if(rc == -1) {
        printf("IOCTL Error!!\n");
        return I2C_FAIL;
    }
    return I2C_SUCCESS;
}

/*
 *This function send data to i2c device after opening the device
 *with address passed in the open i2c function
 */

i2c_err_t i2c_get_reg(i2c_ctx_t *ctx, uint8_t *buff, int len)
{
    int rc;
    rc = read(ctx->fd, buff, len);
    if(rc == -1) {
        printf("Read Failed!!\n");
        return I2C_FAIL;   
    }
    return I2C_SUCCESS;
}

/*
 *This function receive data from i2c device after opening the device
 *with address passed in the open i2c function
 */

i2c_err_t i2c_set_reg(i2c_ctx_t *ctx, uint8_t *buff, int len)
{
    int rc;
    rc = write(ctx->fd, buff, len);
    if(rc == -1) {
        printf("write Failed!!\n");
        return I2C_FAIL;   
    }
    return I2C_SUCCESS;
}
