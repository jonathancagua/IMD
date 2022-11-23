#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/i2c.h>
#include <linux/delay.h>
#include <linux/kernel.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/err.h>
#include <linux/cdev.h>
#include <linux/device.h>

 
#define I2C_BUS_AVAILABLE   (          1 )              // I2C Bus available in our Raspberry Pi
#define SLAVE_DEVICE_NAME   ( "ETX_SENS" )              // Device and Driver Name
#define CAP1188_SLAVE_ADDR  (       0x29 )              // CAP1188 Slave Address
 
static struct i2c_adapter *etx_i2c_adapter     = NULL;  // I2C Adapter Structure
static struct i2c_client  *etx_i2c_client_cap_sense = NULL;  // I2C Cient Structure (In our case it is CAP1188)
 
dev_t dev = 0;
static struct class *dev_class;
static struct cdev etx_cdev;

/*************** Driver functions **********************/
static int etx_open(struct inode *inode, struct file *file);
static int etx_release(struct inode *inode, struct file *file);
static ssize_t etx_read(struct file *filp, 
                char __user *buf, size_t len,loff_t * off);
static ssize_t etx_write(struct file *filp, 
                const char *buf, size_t len, loff_t * off);
/******************************************************/
static void CAP1188_write(unsigned char reg, unsigned char data);
static int I2C_read(unsigned char *out_buf, unsigned int len);
static int I2C_write(unsigned char *buf, unsigned int len);
//File operation structure 
static struct file_operations fops =
{
  .owner          = THIS_MODULE,
  .read           = etx_read,
  .write          = etx_write,
  .open           = etx_open,
  .release        = etx_release,
};
/********************************************************/

static int etx_open(struct inode *inode, struct file *file)
{
    /*
    ** This function will be called when we open the Device file
    */ 
    pr_info("Device File Opened...!!!\n");
    return 0;
}


static int etx_release(struct inode *inode, struct file *file)
{
    /*
    ** This function will be called when we close the Device file
    */
    pr_info("Device File Closed...!!!\n");
    return 0;
}

static ssize_t etx_read(struct file *filp, 
                char __user *buf, size_t count, loff_t *off)
{
    /*
    ** This function will be called when we read the Device file
    */ 
    uint8_t *data = "Touch is: \n";
    uint8_t sensor_data = 0x00;
    uint8_t lectura_reg= 0x03;
    size_t datalen = strlen(data);
    CAP1188_write(0x00,0x01); //sensitivity control
    CAP1188_write(0x00,0x00);
    I2C_write(&lectura_reg, 1);
    I2C_read(&sensor_data, 1);
    if (count > datalen) {
        count = datalen;
    }

    if (copy_to_user(buf, data, count)) {
        return -EFAULT;
    }
    pr_info("Driver Read Function Called...!!!\n");
    pr_info("Driver Read Data %d ...!!!\n",sensor_data);
    return count;
}

static ssize_t etx_write(struct file *filp, 
                const char __user *buf, size_t len, loff_t *off)
{
    /*
    ** This function will be called when we write the Device file
    */ 
    pr_info("Writting device file...!!!\n");
    return 0;
}

/*******************************************************/
static int I2C_write(unsigned char *buf, unsigned int len)
{
    /*
    ** Sending Start condition, Slave address with R/W bit, 
    ** ACK/NACK and Stop condtions will be handled internally.
    */ 
    int ret = i2c_master_send(etx_i2c_client_cap_sense, buf, len);
    
    return ret;
}

static int I2C_read(unsigned char *out_buf, unsigned int len)
{
    /*
    ** Sending Start condition, Slave address with R/W bit, 
    ** ACK/NACK and Stop condtions will be handled internally.
    */ 
    int ret = i2c_master_recv(etx_i2c_client_cap_sense, out_buf, len);
    
    return ret;
}

static void CAP1188_write(unsigned char reg, unsigned char data)
{
    unsigned char buf[2] = {0};
    int ret;
    buf[0] = reg;
    buf[1] = data;
    
    ret = I2C_write(buf, 2);
}

static int CAP1188_display_init(void)
{
    msleep(100);/*delay*/
 
    /*
    ** Commands to initialize the CAP1188
    */
    CAP1188_write(0x00,0x80); /*sensitivity control*/
    CAP1188_write(0x26,0x1f);
    CAP1188_write(0x71,0xff);/*Led output register*/
    CAP1188_write(0x72,0x1f);/*Led linking register*/
    CAP1188_write(0x73,0xff);/*Led polarity register*/
    CAP1188_write(0x81,0x00);/*Set led breath or pulse.*/
    CAP1188_write(0x82,0x00);
    CAP1188_write(0x86,0x40);/* Breathing speed*/
    CAP1188_write(0x93,0xf0);/* Max-min duty cycle set*/
    CAP1188_write(0x92,0xf0);/* Max-min breathing duty cycle.*/
    CAP1188_write(0x94,0x00);/*Ramp rise and fall rate at touch*/
    CAP1188_write(0x95,0x60);/*Led off time between breathing*/
    CAP1188_write(0x81,0x00);/*Disable all breathing leds.*/
    
    return 0;
}

/*
** This function getting called when the slave has been found
** Note : This will be called only once when we load the driver.
*/
static int etx_cap_probe(struct i2c_client *client,
                         const struct i2c_device_id *id)
{
    CAP1188_display_init();
 
    pr_info("cap1188 Probed!!!\n");
    
    return 0;
}

/*
** This function getting called when the slave has been removed
** Note : This will be called only once when we unload the driver.
*/
static int etx_cap_remove(struct i2c_client *client)
{   
    pr_info("cap1188 Removed!!!\n");
    return 0;
}

/*
** Structure that has slave device id
*/
static const struct i2c_device_id etx_cap_id[] = {
        { SLAVE_DEVICE_NAME, 0 },
        { }
};
MODULE_DEVICE_TABLE(i2c, etx_cap_id);

static struct i2c_driver etx_cap_driver = {
        .driver = {
            .name   = SLAVE_DEVICE_NAME,
            .owner  = THIS_MODULE,
        },
        .probe          = etx_cap_probe,
        .remove         = etx_cap_remove,
        .id_table       = etx_cap_id,
};
/*
** I2C Board Info strucutre
*/
static struct i2c_board_info cap_i2c_board_info = {
        I2C_BOARD_INFO(SLAVE_DEVICE_NAME, CAP1188_SLAVE_ADDR)
};

/*
** Module Exit function
*/
static void __exit etx_driver_exit(void)
{
    i2c_unregister_device(etx_i2c_client_cap_sense);
    i2c_del_driver(&etx_cap_driver);
    device_destroy(dev_class,dev);
    class_destroy(dev_class);
    cdev_del(&etx_cdev);
    unregister_chrdev_region(dev, 1);
    pr_info("Driver Removed!!!\n");
}

static int __init etx_driver_init(void)
{
    int ret = -1;
    /*Allocating Major number*/
    if((alloc_chrdev_region(&dev, 0, 1, "etx_Dev")) <0){
        pr_err("Cannot allocate major number\n");
        return -1;
    }
    pr_info("Major = %d Minor = %d \n",MAJOR(dev), MINOR(dev));

    /*Creating cdev structure*/
    cdev_init(&etx_cdev,&fops);

    /*Adding character device to the system*/
    if((cdev_add(&etx_cdev,dev,1)) < 0){
        pr_err("Cannot add the device to the system\n");
        return -1;
    }

    /*Creating struct class*/
    if((dev_class = class_create(THIS_MODULE,"etx_class")) == NULL){
        pr_err("Cannot create the struct class\n");
        return -1;
    }

    /*Creating device*/
    if((device_create(dev_class,NULL,dev,NULL,"etx_device")) == NULL){
        pr_err( "Cannot create the Device \n");
        return -1;
    }
    etx_i2c_adapter     = i2c_get_adapter(I2C_BUS_AVAILABLE);
    
    if( etx_i2c_adapter != NULL )
    {
        etx_i2c_client_cap_sense = i2c_new_client_device(etx_i2c_adapter, &cap_i2c_board_info);
        
        if( etx_i2c_client_cap_sense != NULL )
        {
            i2c_add_driver(&etx_cap_driver);
            ret = 0;
        }
        
        i2c_put_adapter(etx_i2c_adapter);
    }
    
    pr_info("Driver Added!!!\n");
    return ret;
}

module_init(etx_driver_init);
module_exit(etx_driver_exit);
 
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("JC<jonathan.cagua@gmail.com>");
MODULE_DESCRIPTION("hello world, i2c driver");
MODULE_VERSION("1:1.0");