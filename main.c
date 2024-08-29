#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A simple character device driver");
MODULE_AUTHOR("... <...@cmkl.ac.th>");

static int heartydev_open(struct inode *inode, struct file *file);
static int heartydev_release(struct inode *inode, struct file *file);
static long heartydev_ioctl(struct file *file, unsigned int cmd,
                            unsigned long arg);
static ssize_t heartydev_read(struct file *file, char __user *buf, size_t count,
                              loff_t *offset);
static ssize_t heartydev_write(struct file *file, const char __user *buf,
                               size_t count, loff_t *offset);

static const struct file_operations heartydev_fops = {
    .open = heartydev_open,
    .release = heartydev_release,
    .unlocked_ioctl = heartydev_ioctl,
    .read = heartydev_read,
    .write = heartydev_write};

dev_t dev = 0;
static struct class *heartydev_class = NULL;
static struct cdev heartydev_cdev;

static int heartydev_uevent(struct device *dev, struct kobj_uevent_env *env) {
    add_uevent_var(env, "DEVMODE=%#o", 0666);
    return 0;
}

static int __init heartydev_init(void) {
    if (alloc_chrdev_region(&dev, 0, 1, "heartydev") < 0) {
        printk(KERN_ALERT "heartydev registration failed\n");
        return -1;
    }

    heartydev_class = class_create(THIS_MODULE, "heartydev");
    heartydev_class->dev_uevent = heartydev_uevent;
    cdev_init(&heartydev_cdev, &heartydev_fops);
    cdev_add(&heartydev_cdev, MKDEV(MAJOR(dev), 0), 1);
    device_create(heartydev_class, NULL, MKDEV(MAJOR(dev), 0), NULL,
                  "heartydev");

    printk(KERN_ALERT "heartydev registered\n");
    return 0;
}

static void __exit heartydev_exit(void) {
    device_destroy(heartydev_class, MKDEV(MAJOR(dev), 0));
    class_unregister(heartydev_class);
    class_destroy(heartydev_class);
    unregister_chrdev_region(MKDEV(MAJOR(dev), 0), MINORMASK);
}

static int heartydev_open(struct inode *inode, struct file *file) {
    printk("heartydev_open\n");
    return 0;
}

static int heartydev_release(struct inode *inode, struct file *file) {
    printk("heartydev_release\n");
    return 0;
}

static long heartydev_ioctl(struct file *file, unsigned int cmd,
                            unsigned long arg) {
    printk("heartydev_ioctl\n");
    return 0;
}

static ssize_t heartydev_read(struct file *file, char __user *buf, size_t count,
                              loff_t *offset) {
    printk("heartydev_read\n");
    return 0;
}

static ssize_t heartydev_write(struct file *file, const char __user *buf,
                               size_t count, loff_t *offset) {
    printk("heartydev_write\n");
    return count;
}

module_init(heartydev_init);
module_exit(heartydev_exit);
