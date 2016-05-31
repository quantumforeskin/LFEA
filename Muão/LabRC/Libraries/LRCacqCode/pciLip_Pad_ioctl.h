#ifndef _PCI_LIP_PAD_IOCTL_H_
#define _PCI_LIP_PAD_IOCTL_H_

/*
 * IOCTL definitions
 */
#define PCI_LIP_PAD_IOC_MAGIC 'm'  // /* Please use a different 8-bit number in your code */
/*See  /Documentation/ioctl-number.txt*/

/* S means "Set": thru a pointer
 * T means "Tell": directly with the argument value
 * G menas "Get": reply by setting thru a pointer
 * Q means "Qry": response is on the return value
 * X means "eXchange": G and S atomically
 * H means "sHift": T and Q atomically
 */

/**********************************************************************
 *                         IOCTL FUNCTIONS                            *
 *********************************************************************/
#define PCI_LIP_PAD_IOCS_WRITE_CONFIG      _IOW(PCI_LIP_PAD_IOC_MAGIC, 1, u_int32_t)
#define PCI_LIP_PAD_IOCG_READ_CONFIG       _IOR(PCI_LIP_PAD_IOC_MAGIC, 2, u_int32_t)
#define PCI_LIP_PAD_IOCS_WRITE_TRIGDELAY   _IOW(PCI_LIP_PAD_IOC_MAGIC, 3, u_int32_t)
#define PCI_LIP_PAD_IOCG_READ_TRIGDELAY    _IOR(PCI_LIP_PAD_IOC_MAGIC, 4, u_int32_t)
#define PCI_LIP_PAD_IOCT_START             _IO(PCI_LIP_PAD_IOC_MAGIC, 5)
#define PCI_LIP_PAD_IOCT_STOP              _IO(PCI_LIP_PAD_IOC_MAGIC, 6)
#define PCI_LIP_PAD_IOCT_FIFO1             _IO(PCI_LIP_PAD_IOC_MAGIC, 7)
#define PCI_LIP_PAD_IOCT_FIFO2             _IO(PCI_LIP_PAD_IOC_MAGIC, 8)
#define PCI_LIP_PAD_IOCS_TEST_PULSE        _IOW(PCI_LIP_PAD_IOC_MAGIC, 9, u_int32_t)
//#define PCI_LIP_PAD_IOCT_             _IO(PCI_LIP_PAD_IOC_MAGIC, 8)
#define PCI_LIP_PAD_IOCS_WRITE_THR1      _IOW(PCI_LIP_PAD_IOC_MAGIC, 10 , u_int32_t)
#define PCI_LIP_PAD_IOCG_READ_THR1       _IOR(PCI_LIP_PAD_IOC_MAGIC, 11, u_int32_t)
#define PCI_LIP_PAD_IOCS_WRITE_THR2      _IOW(PCI_LIP_PAD_IOC_MAGIC, 12 , u_int32_t)
#define PCI_LIP_PAD_IOCG_READ_THR2       _IOR(PCI_LIP_PAD_IOC_MAGIC, 13, u_int32_t)
#define PCI_LIP_PAD_IOCS_WRITE_THR3      _IOW(PCI_LIP_PAD_IOC_MAGIC, 14 , u_int32_t)
#define PCI_LIP_PAD_IOCG_READ_THR3       _IOR(PCI_LIP_PAD_IOC_MAGIC, 15, u_int32_t)
#define PCI_LIP_PAD_IOCS_WRITE_THR4      _IOW(PCI_LIP_PAD_IOC_MAGIC, 16 , u_int32_t)
#define PCI_LIP_PAD_IOCG_READ_THR4       _IOR(PCI_LIP_PAD_IOC_MAGIC, 17, u_int32_t)
#define PCI_LIP_PAD_IOCS_WRITE_THR5      _IOW(PCI_LIP_PAD_IOC_MAGIC, 18 , u_int32_t)
#define PCI_LIP_PAD_IOCG_READ_THR5       _IOR(PCI_LIP_PAD_IOC_MAGIC, 19, u_int32_t)
#define PCI_LIP_PAD_IOCS_WRITE_THR6      _IOW(PCI_LIP_PAD_IOC_MAGIC, 20 , u_int32_t)
#define PCI_LIP_PAD_IOCG_READ_THR6       _IOR(PCI_LIP_PAD_IOC_MAGIC, 21, u_int32_t)
#define PCI_LIP_PAD_IOCS_TDC_START        _IOW(PCI_LIP_PAD_IOC_MAGIC, 22, u_int32_t)
#define PCI_LIP_PAD_IOCG_READ_REGINIT       _IOR(PCI_LIP_PAD_IOC_MAGIC, 23, u_int32_t)
#define PCI_LIP_PAD_IOCG_READ_REGFINAL       _IOR(PCI_LIP_PAD_IOC_MAGIC, 24, u_int32_t)
#define PCI_LIP_PAD_IOCS_WRITE_CLR_CNT_TDC   _IOW(PCI_LIP_PAD_IOC_MAGIC, 25 , u_int32_t)
#define PCI_LIP_PAD_IOCS_WRITE_TDC_REG1      _IOW(PCI_LIP_PAD_IOC_MAGIC, 26 , u_int32_t)
#define PCI_LIP_PAD_IOCG_READ_TDC_REG1       _IOR(PCI_LIP_PAD_IOC_MAGIC, 27, u_int32_t)

#define PCI_LIP_PAD_IOC_MAXNR   27

#endif /* _PCI_LIP_PAD_IOCTL_H_ */
