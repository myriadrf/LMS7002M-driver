/*!
 * Test instantiating the LMS7002M through spidev on linux
 */

#include <LMS7002M/LMS7002M.h>
#include <LMS7002M/LMS7002M_impl.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

typedef struct
{
    int fd;
} my_spidev_data_t;

my_spidev_data_t *my_spidev_init(const char *path)
{
    int fd = open(path, O_RDWR);
    if (fd < 0)
    {
        perror("open spidev");
        return NULL;
    }
    my_spidev_data_t *data = malloc(sizeof(my_spidev_data_t));
    data->fd = fd;
    return data;
}

void my_spidev_exit(my_spidev_data_t *data)
{
    close(data->fd);
    free(data);
}

uint32_t my_spidev_transact(void *user, const uint32_t data, const bool readback)
{
    my_spidev_data_t *sdata = (my_spidev_data_t *)user;

    //transaction data structures
    struct spi_ioc_transfer xfer[1];
    unsigned char txbuf[4];
    unsigned char rxbuf[4];

    //setup transaction
    memset(xfer, 0, sizeof(xfer));
    xfer[0].tx_buf = (unsigned long)txbuf;
    //only specify rx buffer when readback is specified
    if (readback) xfer[0].rx_buf = (unsigned long)rxbuf;
    xfer[0].len = 4; //bytes

    //load tx data
    txbuf[0] = (data >> 24);
    txbuf[1] = (data >> 16);
    txbuf[2] = (data >> 8);
    txbuf[3] = (data >> 0);

    long status = ioctl(sdata->fd, SPI_IOC_MESSAGE(1), xfer);
    if (status < 0)
    {
        perror("SPI_IOC_MESSAGE");
    }

    //load rx data
    return \
        (((uint32_t)rxbuf[0]) << 24) |
        (((uint32_t)rxbuf[1]) << 16) |
        (((uint32_t)rxbuf[2]) << 8) |
        (((uint32_t)rxbuf[3]) << 0);
}

int main(int argc, char **argv)
{
    printf("=========================================================\n");
    printf("== Test LMS7002M through spidev                          \n");
    printf("=========================================================\n");
    if (argc < 2)
    {
        printf("Usage %s /dev/spidevXXXXXX\n", argv[0]);
        return EXIT_FAILURE;
    }

    my_spidev_data_t *sdata = my_spidev_init(argv[1]);
    if (sdata == NULL) return EXIT_FAILURE;

    //create and test lms....
    LMS7002M_t *lms = LMS7002M_create(my_spidev_transact, (void *)sdata);
    LMS7002M_destroy(lms);

    my_spidev_exit(sdata);

    return EXIT_SUCCESS;
}
