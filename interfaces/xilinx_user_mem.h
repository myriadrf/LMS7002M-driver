/***********************************************************************
 * Userspace memory access utils (uses /dev/mem)
 **********************************************************************/

#pragma once
#include <stdint.h>

/*!
 * Write a 32 bit register value.
 * \param base virtual memory pointing to the register space
 * \param offset an offset in bytes to the register
 * \param val the new value of the register
 */
static inline void xumem_write32(char *base, int offset, uint32_t val);

/*!
 * Read a 32 bit register value.
 * \param base virtual memory pointing to the register space
 * \param offset an offset in bytes to the register
 * \return the value of the register
 */
static inline uint32_t xumem_read32(char *base, int offset);

/*!
 * Map a physical address range into userspace.
 * \param base the physical address
 * \param size the size in bytes
 * \return the virtual address or NULL on error
 */
static inline void *xumem_map_phys(const size_t base, const size_t size);

/*!
 * Unmap a physical address range.
 * \param base the pointer from map
 * \param size the size in bytes
 * \return 0 to indicate success
 */
static inline int xumem_unmap_phys(void *base, const size_t size);

/***********************************************************************
 * Implementation details
 **********************************************************************/
#include <sys/types.h> //open
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h> //mmap
#include <unistd.h> //close

static inline void xumem_write32(char *base, int offset, uint32_t val)
{
    volatile uint32_t *p = (volatile uint32_t *)(base + offset);
    *p = val;
}

static inline uint32_t xumem_read32(char *base, int offset)
{
    volatile uint32_t *p = (volatile uint32_t *)(base + offset);
    return *p;
}

static inline void *xumem_map_phys(const size_t base, const size_t size)
{
    int memfd = open("/dev/mem", O_RDWR | O_SYNC);
    if (memfd < 0) return NULL;

    void *p = mmap(NULL, size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_SHARED, memfd, base);

    close(memfd);

    return p;
}

static inline int xumem_unmap_phys(void *base, const size_t size)
{
    return munmap(base, size);
}
