# SYS-205 Assessment 1 - Building a driver for heartydev
The goal of this assessment is to evaluate whether you briefly **understand** how applications and operating systems interact with devices. You will implement a simple character device driver to demonstrate this knowledge.

## Setting up

### Step 1 - Build a driver module
In this task, you will need to simply build a driver using the `Makefile`. Even though you can type the following commands, I would recommend you look at the commands in the `Makefile` to see how the compilation process work.

```sh
make
```

If you are not sure what is the kernel module, you can read more at https://sysprog21.github.io/lkmpg/.

### Step 2 - Load a driver
Since your driver is a C module, you can use `insmod` to load it as follows.

```sh
sudo insmod heartydev.ko
```

To verify, you can use the following commands.

```sh
cat /proc/modules | grep heartydev
cat /proc/devices | grep heartydev
```

Also, the `heartydev_init` function will be executed. The output will be printed out in the `/var/log/syslog` file. You can use the following commands to see.

```sh
tail /var/log/syslog
```

If you want to remove the module, you can use the following command.

```sh
sudo rmmod heartydev
```

## Code Quality (20 points)
You should follow a good coding convention. In this class, please stick with the *CMU 15-213's Code Style*.

https://www.cs.cmu.edu/afs/cs/academic/class/15213-f24/www/codeStyle.html

## Task 1 - Implement heartydev's `write` and `read` (20 points)
Since we do not have a real device, interacting with the device will be to read/write to the driver buffer instead.

### Task 1.1 - Implement `heartydev_write` (10 points)
Your task is to implement the `heartydev_write` by copying the text from the user buffer (`buf`) into the driver buffer. Note that you may need to create the driver buffer by yourself.

To verify, you should be able to call `heartydev_write` through the following command.

```sh
echo 'hello, heartydev!' > /dev/heartydev
```

### Task 1.2 - Implement `heartydev_read` (10 points)
Your task is to implement the `heartydev_read` by copying the text from the driver buffer into the user buffer. However, you need to capitalize all the lowercase English letters before copying.

To verify, you should be able to call `heartydev_read` through the following command.

```sh
cat /dev/heartydev
```

## Task 2 - Implement heartydev's `ioctl` (30 points)
You need to implement four `ioctl` commands and show that user applications can call this driver command. The commands are listed as follows:

### Task 2.1 - Implement the `HEARTYDEV_READ_CNT` command (10 points)
`HEARTYDEV_READ_CNT` must show the current number of `heartydev_read` function calls.

### Task 2.2 - Implement the `HEARTYDEV_WRITE_CNT` command (10 points)
`HEARTYDEV_WRITE_CNT` must show the current number of `heartydev_write` function calls.

### Task 2.3 - Implement the `HEARTYDEV_BUF_LEN` command (10 points)
`HEARTYDEV_BUF_LEN` must show the current length of the driver buffer. If there is nothing in the buffer, it should show `0`.

## Task 3 - Implement device modes (30 points)
You will need to implement two more *device modes* using the prior knowledge you learned.

### Task 3.1 - `ioctl` for changing the device's mode (10 points)
Your task is to implement the `ioctl` command that changes the device's mode. There will be in total of three modes. The driver we previously implemented should be in the mode called `UPPER`.

### Task 3.2 - Implement the `NORMAL` mode (10 points)
Your task is to implement the `NORMAL` mode, where the driver should not capitalize the text while doing `heartydev_read`.

### Task 3.3 - Implement the `LOWER` mode (10 points)
Your task is to implement the `LOWER` mode, where the driver should, instead of doing capitalization, change all capitalized English letters into lowercase letters while doing `heartydev_read`.

## Grading
- 20% - Task 1 
- 30% - Task 2 (If task 1 is not complete, task 2 will not be graded.)
- 30% - Task 3 (If tasks 1 and 2 are not complete, task 3 will not be graded.)
- 20% - Code Style (If tasks 1, 2, and 3 are not complete, the code style will not be graded.)

## References
- https://olegkutkov.me/2018/03/14/simple-linux-character-device-driver/
- https://github.com/backendeveloper/Linux-Character-Device
- https://embetronicx.com/tutorials/linux/device-drivers/ioctl-tutorial-in-linux/