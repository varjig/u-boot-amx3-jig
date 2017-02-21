/*
 * am335x_evm.h
 *
 * Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef __CONFIG_VAR_SOM_AM33_H
#define __CONFIG_VAR_SOM_AM33_H

#include <configs/ti_am335x_common.h>

#define CONFIG_MACH_TYPE		MACH_TYPE_VAR_AM335X

/* Clock Defines */
#define V_OSCK				24000000  /* Clock output from T2 */
#define V_SCLK				(V_OSCK)


/* Always 128 KiB env size */
#define CONFIG_ENV_SIZE			(128 << 10)

#define CONFIG_ENV_VARS_UBOOT_RUNTIME_CONFIG

#ifndef CONFIG_SPL_BUILD
#define CONFIG_EXTRA_ENV_SETTINGS \
	"loadaddr=0x80200000\0" \
	"fdtaddr=0x80F80000\0" \
	"fdt_high=0xa0000000\0" \
	"boot_fdt=try\0" \
	"rdaddr=0x81000000\0" \
	"bootpart=0:2\0" \
	"bootdir=/boot\0" \
	"bootfile=zImage\0" \
	"fdtfile=undefined\0" \
	"console=ttyO0,115200n8\0" \
	"partitions=" \
		"uuid_disk=${uuid_gpt_disk};" \
		"name=rootfs,start=2MiB,size=-,uuid=${uuid_gpt_rootfs}\0" \
	"optargs=\0" \
	"dfu_alt_info_mmc=" DFU_ALT_INFO_MMC "\0" \
	"dfu_alt_info_emmc=rawemmc mmc 0 3751936\0" \
	"mmcdev=0\0" \
	"mmcroot=/dev/mmcblk0p2 ro\0" \
	"mmcrootfstype=ext4 rootwait\0" \
	"usbroot=/dev/sda2 rw\0" \
	"usbrootfstype=ext4 rootwait\0" \
	"rootpath=/export/rootfs\0" \
	"nfsopts=nolock\0" \
	"static_ip=${ipaddr}:${serverip}:${gatewayip}:${netmask}:${hostname}" \
		"::off\0" \
	"ramroot=/dev/ram0 rw ramdisk_size=65536 initrd=${rdaddr},64M\0" \
	"ramrootfstype=ext2\0" \
	"mmcargs=setenv bootargs console=${console} " \
		"${optargs} " \
		"root=${mmcroot} " \
		"rootfstype=${mmcrootfstype}\0" \
	"usbargs=setenv bootargs console=${console} " \
		"${optargs} " \
		"root=${usbroot} " \
		"rootfstype=${usbrootfstype}\0" \
	"netargs=setenv bootargs console=${console} " \
		"${optargs} " \
		"root=/dev/nfs " \
		"nfsroot=${serverip}:${rootpath},${nfsopts} rw " \
		"ip=dhcp\0" \
	"bootenv=uEnv.txt\0" \
	"loadbootenv=load mmc ${mmcdev} ${loadaddr} ${bootenv}\0" \
	"importbootenv=echo Importing environment from mmc ...; " \
		"env import -t $loadaddr $filesize\0" \
	"dfu_alt_info_ram=" DFU_ALT_INFO_RAM "\0" \
	"ramargs=setenv bootargs console=${console} " \
		"${optargs} " \
		"root=${ramroot} " \
		"rootfstype=${ramrootfstype}\0" \
	"loadimage=load mmc ${bootpart} ${loadaddr} ${bootdir}/${bootfile}\0" \
	"loadfdt=load mmc ${bootpart} ${fdtaddr} ${bootdir}/${fdtfile}\0" \
	"mmcloados=run mmcargs; " \
		"if test ${boot_fdt} = yes || test ${boot_fdt} = try; then " \
			"if run loadfdt; then " \
				"bootz ${loadaddr} - ${fdtaddr}; " \
			"else " \
				"if test ${boot_fdt} = try; then " \
					"bootz; " \
				"else " \
					"echo WARN: Cannot load the DT; " \
				"fi; " \
			"fi; " \
		"else " \
			"bootz; " \
		"fi;\0" \
	"mmcboot=mmc dev ${mmcdev}; " \
		"if mmc rescan; then " \
			"echo SD/MMC found on device ${mmcdev};" \
			"if run loadbootenv; then " \
				"echo Loaded environment from ${bootenv};" \
				"run importbootenv;" \
			"fi;" \
			"if test -n $uenvcmd; then " \
				"echo Running uenvcmd ...;" \
				"run uenvcmd;" \
			"fi;" \
			"if run loadimage; then " \
				"run mmcloados;" \
			"fi;" \
		"fi;\0" \
	"netboot=echo Booting from network ...; " \
		"setenv autoload no; " \
		"dhcp; " \
		"tftp ${loadaddr} ${bootfile}; " \
		"tftp ${fdtaddr} ${fdtfile}; " \
		"run netargs; " \
		"bootz ${loadaddr} - ${fdtaddr}\0" \
	"findfdt=setenv fdtfile var-som-am33.dtb\0" \
	BOOTCMD_COMMON \
	BOOTCMD_NAND \
	BOOTCMD_MMC \
	BOOTCMD_USB
#endif

/* NS16550 Configuration */
#define CONFIG_SYS_NS16550_COM1		0x44e09000	/* Base EVM has UART0 */
#define CONFIG_SYS_NS16550_COM2		0x48022000	/* UART1 */
#define CONFIG_SYS_NS16550_COM3		0x48024000	/* UART2 */
#define CONFIG_SYS_NS16550_COM4		0x481a6000	/* UART3 */
#define CONFIG_SYS_NS16550_COM5		0x481a8000	/* UART4 */
#define CONFIG_SYS_NS16550_COM6		0x481aa000	/* UART5 */
#define CONFIG_BAUDRATE			115200

/* I2C Configuration */
#define CONFIG_CMD_EEPROM
#define CONFIG_ENV_EEPROM_IS_ON_I2C
#define CONFIG_SYS_I2C_EEPROM_ADDR	0x50	/* Main EEPROM */
#define CONFIG_SYS_I2C_EEPROM_ADDR_LEN	2
#define CONFIG_SYS_I2C_MULTI_EEPROMS

/* PMIC support */
#define CONFIG_POWER_TPS65217
#define CONFIG_POWER_TPS65910

/* SPL */
#ifndef CONFIG_NOR_BOOT
#define CONFIG_SPL_POWER_SUPPORT
#define CONFIG_SPL_YMODEM_SUPPORT

/* CPSW support */
#define CONFIG_SPL_ETH_SUPPORT

/* USB gadget RNDIS */
#define CONFIG_SPL_MUSB_NEW_SUPPORT

/* General network SPL, both CPSW and USB gadget RNDIS */
#define CONFIG_SPL_NET_SUPPORT
#define CONFIG_SPL_ENV_SUPPORT
#define CONFIG_SPL_NET_VCI_STRING	"AM335x U-Boot SPL"


#define CONFIG_SPL_LDSCRIPT		"$(CPUDIR)/am33xx/u-boot-spl.lds"
#endif

/* Enhance our eMMC support / experience. */
#define CONFIG_CMD_GPT
#define CONFIG_EFI_PARTITION
#define CONFIG_PARTITION_UUIDS
#define CONFIG_CMD_PART

/* NAND support */
#ifdef CONFIG_NAND
/* NAND: device related configs */
#define CONFIG_SYS_NAND_PAGE_SIZE		2048
#define CONFIG_SYS_NAND_OOBSIZE			64
#define CONFIG_SYS_NAND_BLOCK_SIZE		(128*1024)
#define CONFIG_SPL_NAND_DEVICE_WIDTH		8
#define CONFIG_SYS_NAND_5_ADDR_CYCLE
#define CONFIG_SYS_NAND_PAGE_COUNT		(CONFIG_SYS_NAND_BLOCK_SIZE / \
						 CONFIG_SYS_NAND_PAGE_SIZE)
/* NAND: driver related configs */
#define CONFIG_NAND_OMAP_GPMC
#define CONFIG_NAND_OMAP_ELM
#define CONFIG_CMD_NAND
#define CONFIG_SYS_NAND_BASE			0x8000000
#define CONFIG_SYS_MAX_NAND_DEVICE		1
#define CONFIG_SYS_NAND_ONFI_DETECTION
#define CONFIG_SYS_NAND_BAD_BLOCK_POS		NAND_LARGE_BADBLOCK_POS
#define CONFIG_SYS_NAND_ECCPOS		      { 2, 3, 4, 5, 6, 7, 8, 9, \
					       10, 11, 12, 13, 14, 15, 16, 17, \
					       18, 19, 20, 21, 22, 23, 24, 25, \
					       26, 27, 28, 29, 30, 31, 32, 33, \
					       34, 35, 36, 37, 38, 39, 40, 41, \
					       42, 43, 44, 45, 46, 47, 48, 49, \
					       50, 51, 52, 53, 54, 55, 56, 57, }
#define CONFIG_SYS_NAND_ECCSIZE			512
#define CONFIG_SYS_NAND_ECCBYTES		14
#define CONFIG_NAND_OMAP_ECCSCHEME		OMAP_ECC_BCH8_CODE_HW
#if !defined(CONFIG_SPI_BOOT) && !defined(CONFIG_NOR_BOOT) && \
	!defined(CONFIG_EMMC_BOOT)
  #define MTDIDS_DEFAULT		      "nand0=nand.0"
  #define MTDPARTS_DEFAULT		      "mtdparts=nand.0:" \
					      "128k(NAND.SPL)," \
					      "128k(NAND.SPL.backup1)," \
					      "128k(NAND.SPL.backup2)," \
					      "128k(NAND.SPL.backup3)," \
					      "256k(NAND.u-boot-spl-os)," \
					      "1m(NAND.u-boot)," \
					      "128k(NAND.u-boot-env)," \
					      "128k(NAND.u-boot-env.backup1)," \
					      "8m(NAND.kernel)," \
					      "-(NAND.rootfs)"
  #undef CONFIG_ENV_IS_NOWHERE
  #if defined(CONFIG_ENV_IS_IN_FAT)
       #define FAT_ENV_FILE                    "u-boot_env.txt"
       #define FAT_ENV_INTERFACE               "mmc"
       #define FAT_ENV_DEVICE                  0
       #define FAT_ENV_PART                    1
  #else
       #define CONFIG_ENV_IS_IN_NAND
       #define CONFIG_ENV_OFFSET                       0x001C0000
       #define CONFIG_ENV_OFFSET_REDUND                0x001E0000
       #define CONFIG_SYS_ENV_SECT_SIZE                CONFIG_SYS_NAND_BLOCK_SIZE
  #endif /* CONFIG_VAR_MMC_BOOT */
#endif
/* NAND: SPL related configs */
#if !defined(CONFIG_SPI_BOOT) && !defined(CONFIG_NOR_BOOT) && \
	!defined(CONFIG_EMMC_BOOT)
  #define CONFIG_SPL_NAND_AM33XX_BCH
  #define CONFIG_SPL_NAND_SUPPORT
  #define CONFIG_SPL_NAND_BASE
  #define CONFIG_SPL_NAND_DRIVERS
  #define CONFIG_SPL_NAND_ECC
  #define CONFIG_SYS_NAND_U_BOOT_START		CONFIG_SYS_TEXT_BASE
  #define CONFIG_SYS_NAND_U_BOOT_OFFS		0x000C0000
/* NAND: SPL falcon mode related configs */
  #ifdef CONFIG_SPL_OS_BOOT
    #define CONFIG_CMD_SPL_NAND_OFS		0x00080000 /* os parameters */
    #define CONFIG_SYS_NAND_SPL_KERNEL_OFFS	0x00A00000 /* kernel offset */
    #define CONFIG_CMD_SPL_WRITE_SIZE		0x2000
  #endif
#endif
#else
#define NANDARGS ""
#endif /* !CONFIG_NAND */


/*
 * USB configuration.  We enable MUSB support, both for host and for
 * gadget.  We set USB0 as peripheral and USB1 as host, based on the
 * board schematic and physical port wired to each.  Then for host we
 * add mass storage support and for gadget we add both RNDIS ethernet
 * and DFU.
 */
#define CONFIG_USB_MUSB_DSPS
#define CONFIG_ARCH_MISC_INIT
#define CONFIG_MUSB_GADGET
#define CONFIG_MUSB_PIO_ONLY
#define CONFIG_MUSB_DISABLE_BULK_COMBINE_SPLIT
#define CONFIG_USB_GADGET
#define CONFIG_USBDOWNLOAD_GADGET
#define CONFIG_USB_GADGET_DUALSPEED
#define CONFIG_USB_GADGET_VBUS_DRAW	2
#define CONFIG_MUSB_HOST
#define CONFIG_AM335X_USB0
#define CONFIG_AM335X_USB0_MODE	MUSB_PERIPHERAL
#define CONFIG_AM335X_USB1
#define CONFIG_AM335X_USB1_MODE MUSB_HOST

#ifdef CONFIG_MUSB_HOST
#define CONFIG_CMD_USB
#define CONFIG_USB_STORAGE
#endif

#ifdef CONFIG_MUSB_GADGET
#define CONFIG_USB_ETHER
#define CONFIG_USB_ETH_RNDIS
#define CONFIG_USBNET_HOST_ADDR	"de:ad:be:af:00:00"

/* USB TI's IDs */
#define CONFIG_G_DNL_VENDOR_NUM 0x0403
#define CONFIG_G_DNL_PRODUCT_NUM 0xBD00
#define CONFIG_G_DNL_MANUFACTURER "Texas Instruments"
#endif /* CONFIG_MUSB_GADGET */

#if defined(CONFIG_SPL_BUILD) && defined(CONFIG_SPL_USBETH_SUPPORT)
/* disable host part of MUSB in SPL */
#undef CONFIG_MUSB_HOST
/*
 * Disable CPSW SPL support so we fit within the 101KiB limit.
 */
#undef CONFIG_SPL_ETH_SUPPORT
#endif

/* USB Device Firmware Update support */
#define CONFIG_DFU_FUNCTION
#define CONFIG_DFU_MMC
#define CONFIG_CMD_DFU
#define DFU_ALT_INFO_MMC \
	"boot part 0 1;" \
	"rootfs part 0 2;" \
	"MLO fat 0 1;" \
	"MLO.raw mmc 100 100;" \
	"u-boot.img.raw mmc 300 400;" \
	"spl-os-args.raw mmc 80 80;" \
	"spl-os-image.raw mmc 900 2000;" \
	"spl-os-args fat 0 1;" \
	"spl-os-image fat 0 1;" \
	"u-boot.img fat 0 1;" \
	"uEnv.txt fat 0 1"
#ifdef CONFIG_NAND
#define CONFIG_DFU_NAND

#ifdef DFU_ALT_INFO_NAND
#undef DFU_ALT_INFO_NAND
#endif
#define DFU_ALT_INFO_NAND \
	"NAND.SPL part 0 1;" \
	"NAND.SPL.backup1 part 0 2;" \
	"NAND.SPL.backup2 part 0 3;" \
	"NAND.SPL.backup3 part 0 4;" \
	"NAND.u-boot-spl-os part 0 5;" \
	"NAND.u-boot part 0 6;" \
	"NAND.u-boot-env part 0 7;" \
	"NAND.u-boot-env.backup1 part 0 8;" \
	"NAND.kernel part 0 9;" \
	"NAND.rootfs part 0 10"
#endif
#define CONFIG_DFU_RAM
#define DFU_ALT_INFO_RAM \
	"kernel ram 0x80200000 0xD80000;" \
	"fdt ram 0x80F80000 0x80000;" \
	"ramdisk ram 0x81000000 0x4000000"




/* Network. */
#define CONFIG_PHYLIB
#define CONFIG_PHY_ADDR         0
#define CONFIG_PHY_MICREL


#ifdef CONFIG_MMC
#define BOOT_TARGETS_MMC "mmc0"
#else
#define BOOT_TARGETS_MMC ""
#endif

#ifdef CONFIG_USB_HOST
#define BOOT_TARGETS_USB "usb"
#else
#define BOOT_TARGETS_USB ""
#endif

#ifdef CONFIG_NAND
#define BOOT_TARGETS_NAND "nand"
#else
#define BOOT_TARGETS_NAND ""
#endif

#ifdef CONFIG_BOOTDELAY
#undef CONFIG_BOOTDELAY
#endif
#define CONFIG_BOOTDELAY       -1

#ifdef CONFIG_SPL_OS_BOOT
#undef CONFIG_SPL_OS_BOOT
#endif

#endif	/* ! __CONFIG_VAR_SOM_AM33_H */
