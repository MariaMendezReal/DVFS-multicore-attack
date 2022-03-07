
#include <linux/init.h>  
#include <linux/module.h> 
#include <linux/device.h> 
#include <linux/kernel.h> 
#include <linux/fs.h> 
#include <linux/uaccess.h> 
#include <linux/regulator/driver.h>
#include <linux/regulator/consumer.h>
#include <linux/regulator/machine.h>
#include <linux/delay.h>
#define  DEVICE_NAME "regul_com" 
#define  CLASS_NAME  "regul"  



static int    majorNumber;  
static char   message[256] = {0}; 
static char   message_sent[256] = {0}; 
static short  size_of_message;             
static int    numberOpens = 0;             
static struct class*  ebbcharClass  = NULL; 
static struct device* ebbcharDevice = NULL; 

static struct regulator * reg;
static int		voltage, new_voltage;

static int     dev_open(struct inode *, struct file *);
static int     dev_release(struct inode *, struct file *);
static ssize_t dev_read(struct file *, char *, size_t, loff_t *);
static ssize_t dev_write(struct file *, const char *, size_t, loff_t *);


static struct file_operations fops =
{
	
   .open = dev_open,
   .read = dev_read,
   .write = dev_write,
   .release = dev_release,
};


static int __init regul_init(void){

	majorNumber = register_chrdev(0, DEVICE_NAME, &fops);
	if (majorNumber<0){
		printk(KERN_ALERT "Regul: failed to register a major number %d\n", majorNumber);
		return majorNumber;
	}

	ebbcharClass = class_create(THIS_MODULE, CLASS_NAME);
	if (IS_ERR(ebbcharClass)){  
		unregister_chrdev(majorNumber, DEVICE_NAME);
		printk(KERN_ALERT "Failed to register device class\n");
		return PTR_ERR(ebbcharClass);
	}


	printk(KERN_INFO "Regul: device class registered correctly\n");
 

	ebbcharDevice = device_create(ebbcharClass, NULL, MKDEV(majorNumber, 0), NULL, DEVICE_NAME);
	if (IS_ERR(ebbcharDevice)){        
		class_destroy(ebbcharClass); 
		unregister_chrdev(majorNumber, DEVICE_NAME);
		printk(KERN_ALERT "Failed to create the device\n");
		return PTR_ERR(ebbcharDevice);
	}
	printk(KERN_INFO "Regul: device class created correctly\n"); 



	reg= regulator_get(ebbcharDevice, "VDD_CPU_L");



	if(IS_ERR(reg)){
		printk(KERN_ALERT "Regul: failed to acquire the device");
		return PTR_ERR(reg);
	}


	voltage=regulator_get_voltage(reg);
	 printk(KERN_INFO "Regul: Device volage %d\n", voltage);

	int sect = regulator_set_voltage_time(reg,1275000,1500000);
	printk(KERN_INFO "Regul: Time taken = %d!\n", sect);
	


	return 0;


}

static void __exit regul_exit(void){
	device_destroy(ebbcharClass, MKDEV(majorNumber, 0)); 
	class_unregister(ebbcharClass);
	class_destroy(ebbcharClass); 
	unregister_chrdev(majorNumber, DEVICE_NAME);
	regulator_put(reg);
	printk(KERN_INFO "Regul: Goodbye cruel world\n");
}

static int dev_open(struct inode *inodep, struct file *filep){
   numberOpens++;
   printk(KERN_INFO "Regul: Device has been opened %d time(s)\n", numberOpens);
   return 0;
}
 
static ssize_t dev_read(struct file *filep, char *buffer, size_t len, loff_t *offset){

   	int error_count = 0;
	voltage=regulator_get_voltage(reg);
	size_of_message=sprintf(message_sent, "Voltage is %d \n", voltage);
	printk(KERN_INFO "%s", message_sent);

	error_count = copy_to_user(buffer, message_sent, size_of_message);
	 
	if (error_count==0){ 
		printk(KERN_INFO "Regul: Sent %d characters to the user\n", size_of_message);
		return (size_of_message=0); 
	}
	else {
		printk(KERN_INFO "Regul: Failed to send %d characters to the user\n", error_count);
		return -EFAULT;       
	}
}
 



static ssize_t dev_write(struct file *filep, const char *buffer, size_t len, loff_t *offset){

   
	copy_from_user(message,buffer,len);
	kstrtoint(message,10,&new_voltage);
	printk(KERN_INFO "Regul: Received %s from user\n", message);
	
	if(len<8){
		regulator_set_voltage(reg,new_voltage,new_voltage);
		printk(KERN_INFO "Regul: Switching voltage tp %d\n", new_voltage);
	}else{

		printk(KERN_INFO "Regul: Voltage should be in uV\n");

	}
	
	



   return len;
}
 



static int dev_release(struct inode *inodep, struct file *filep){
   printk(KERN_INFO "Regul: Device successfully closed\n");
   return 0;
}

module_init(regul_init);
module_exit(regul_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(" Safouane N.");
MODULE_DESCRIPTION("Regulator controller");
MODULE_VERSION("0.01");
