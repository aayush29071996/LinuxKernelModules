#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/semaphore.h>
#include <asm/uaccess.h>
#include <linux/spinlock.h>


struct fake_device {
	char data[100];
	struct semaphore sem;
} virtual_device;

struct cdev *mcdev;
int major_number;
int ret;
dev_t dev_num;
spinlock_t my_lock;
rwlock_t my_rwlock;



#define DEVICE_NAME	"aayushdevice"

int device_open(struct inode *inode, struct file *filp){
void spin_lock(spinlock_t *lock);
printk(KERN_INFO "OPENED DEVICE");
return 0;
}

ssize_t device_read(struct file* filp, char* bufStoreData, size_t bufCount, loff_t* curOffset){
void read_lock(rwlock_t *lock);
printk(KERN_INFO "READING FROM DEVICE");
ret= copy_to_user(bufStoreData,virtual_device.data,bufCount);
void read_unlock(rwlock_t *lock);
return ret;
}

ssize_t device_write(struct file* filp, const char* bufSourceData, size_t bufCount, loff_t* curOffset){
void write_lock(rwlock_t *lock);
printk(KERN_INFO "WRITING TO DEVICE");
ret= copy_from_user(virtual_device.data,bufSourceData,bufCount);
void write_unlock(rwlock_t *lock);
return ret;
}

int device_close(void){
void spin_unlock(spinlock_t *lock);
printk(KERN_INFO "CLOSED DEVICE");
return 0;
}


struct file_operations fops={
.owner = THIS_MODULE,
.open = device_open,
.release = device_close,
.write = device_write,
.read = device_read
};


static int driver_entry(void){

ret = alloc_chrdev_region(&dev_num,0,1,DEVICE_NAME);
if(ret<0){
printk(KERN_ALERT "FAILED TO ALLOCATE A MAJOR NUMBER");
return ret;
}
major_number = MAJOR(dev_num);
printk(KERN_INFO "MAJOR NUMBER IS %d",major_number);
printk(KERN_INFO "\tuse \"mknod /dev/%s c %d 0\" for device file", DEVICE_NAME,major_number);

mcdev = cdev_alloc();
mcdev->ops=&fops;
mcdev->owner= THIS_MODULE;
ret= cdev_add(mcdev,dev_num,1);
if(ret<0){
printk(KERN_ALERT "UNABLE TO ADD CDEV TO KERNEL");
return ret;
}
sema_init(&virtual_device.sem,1);
spin_lock_init(&my_lock);
rwlock_init(&my_rwlock);
return 0;

}

static void driver_exit(void){
cdev_del(mcdev);
unregister_chrdev_region(dev_num,1);
printk(KERN_ALERT "UNLOADED THE MODULE");
}


module_init(driver_entry);
module_exit(driver_exit);






