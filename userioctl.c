#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define DEVICE "/dev/ioctl_device"

// IOCTL Commands
#define IOCTL_GET_DATA _IOR('c', 1, char)
#define IOCTL_SET_DATA _IOW('c', 2, char)

int main()
{
    int fd, result;
    char data,data1;

    fd = open(DEVICE, O_RDWR);
    if (fd < 0) {
        perror("Failed to open the device");
        return -1;
    }

    // Set data using IOCTL
    data = 'D';
    result = ioctl(fd, IOCTL_SET_DATA, &data);
    if (result < 0) {
        perror("Failed to set data");
        close(fd);
        return -1;
    }
    printf("Data sent to kernel: %c\n", data);

    // Get data using IOCTL
    result = ioctl(fd, IOCTL_GET_DATA, &data1);
    if (result < 0) {
        perror("Failed to get data");
        close(fd);
        return -1;
    }
    printf("Data received from kernel: %c\n", data1);

    close(fd);
    return 0;
}
