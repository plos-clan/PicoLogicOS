#pragma once

// $$$                 00xx                 $$$ //
// %%%              Undefined               %%% //
#define PCI_BASE_CLASS_UNDEFINED            0x00
#define PCI_CLASS_UNDEFINED                 0x0000
#define PCI_CLASS_UNDEFINED_VGA             0x0001
// $$$                 01xx                 $$$ //
// %%%              Mass Storage            %%% //
#define PCI_BASE_CLASS_STORAGE              0x01
#define PCI_CLASS_STORAGE_SCSI              0x0100
#define PCI_CLASS_STORAGE_IDE               0x0101
#define PCI_CLASS_STORAGE_FLOPPY            0x0102
#define PCI_CLASS_STORAGE_IPI               0x0103
#define PCI_CLASS_STORAGE_RAID              0x0104
#define PCI_CLASS_STORAGE_SATA              0x0106
#define PCI_CLASS_STORAGE_SATA_AHCI         0x010601
#define PCI_CLASS_STORAGE_SAS               0x0107
#define PCI_CLASS_STORAGE_EXPRESS           0x010802
#define PCI_CLASS_STORAGE_OTHER             0x0180
// $$$                 02xx                 $$$ //
// %%%               Network                %%% //
#define PCI_BASE_CLASS_NETWORK              0x02
#define PCI_CLASS_NETWORK_ETHERNET          0x0200
#define PCI_CLASS_NETWORK_TOKEN_RING        0x0201
#define PCI_CLASS_NETWORK_FDDI              0x0202
#define PCI_CLASS_NETWORK_ATM               0x0203
#define PCI_CLASS_NETWORK_OTHER             0x0280
// $$$                 03xx                 $$$ //
// %%%               Display                %%% //
#define PCI_BASE_CLASS_DISPLAY              0x03
#define PCI_CLASS_DISPLAY_VGA               0x0300
#define PCI_CLASS_DISPLAY_XGA               0x0301
#define PCI_CLASS_DISPLAY_3D                0x0302
#define PCI_CLASS_DISPLAY_OTHER             0x0380
// $$$                 04xx                 $$$ //
// %%%              Multimedia              %%% //
#define PCI_BASE_CLASS_MULTIMEDIA           0x04
#define PCI_CLASS_MULTIMEDIA_VIDEO          0x0400
#define PCI_CLASS_MULTIMEDIA_AUDIO          0x0401
#define PCI_CLASS_MULTIMEDIA_PHONE          0x0402
#define PCI_CLASS_MULTIMEDIA_HD_AUDIO       0x0403
#define PCI_CLASS_MULTIMEDIA_OTHER          0x0480
// $$$                 05xx                 $$$ //
// %%%                Memory                %%% //
#define PCI_BASE_CLASS_MEMORY               0x05
#define PCI_CLASS_MEMORY_RAM                0x0500
#define PCI_CLASS_MEMORY_FLASH              0x0501
#define PCI_CLASS_MEMORY_OTHER              0x0580
// $$$                 06xx                 $$$ //
// %%%                Bridge                %%% //
#define PCI_BASE_CLASS_BRIDGE               0x06
#define PCI_CLASS_BRIDGE_HOST               0x0600
#define PCI_CLASS_BRIDGE_ISA                0x0601
#define PCI_CLASS_BRIDGE_EISA               0x0602
#define PCI_CLASS_BRIDGE_MC                 0x0603
#define PCI_CLASS_BRIDGE_PCI                0x0604
#define PCI_CLASS_BRIDGE_PCI_NORMAL         0x060400
#define PCI_CLASS_BRIDGE_PCI_SUBTRACTIVE    0x060401
#define PCI_CLASS_BRIDGE_PCMCIA             0x0605
#define PCI_CLASS_BRIDGE_NUBUS              0x0606
#define PCI_CLASS_BRIDGE_CARDBUS            0x0607
#define PCI_CLASS_BRIDGE_RACEWAY            0x0608
#define PCI_CLASS_BRIDGE_OTHER              0x0680
// $$$                 07xx                 $$$ //
// %%%          Simple Communication        %%% //
#define PCI_BASE_CLASS_COMMUNICATION        0x07
#define PCI_CLASS_COMMUNICATION_SERIAL      0x0700
#define PCI_CLASS_COMMUNICATION_PARALLEL    0x0701
#define PCI_CLASS_COMMUNICATION_MULTISERIAL 0x0702
#define PCI_CLASS_COMMUNICATION_MODEM       0x0703
#define PCI_CLASS_COMMUNICATION_OTHER       0x0780
// $$$                 08xx                 $$$ //
// %%%          Base System Peripheral      %%% //
#define PCI_BASE_CLASS_SYSTEM               0x08
#define PCI_CLASS_SYSTEM_PIC                0x0800
#define PCI_CLASS_SYSTEM_PIC_IOAPIC         0x080010
#define PCI_CLASS_SYSTEM_PIC_IOXAPIC        0x080020
#define PCI_CLASS_SYSTEM_DMA                0x0801
#define PCI_CLASS_SYSTEM_TIMER              0x0802
#define PCI_CLASS_SYSTEM_RTC                0x0803
#define PCI_CLASS_SYSTEM_PCI_HOTPLUG        0x0804
#define PCI_CLASS_SYSTEM_SDHCI              0x0805
#define PCI_CLASS_SYSTEM_OTHER              0x0880
// $$$                 09xx                 $$$ //
// %%%                Input                 %%% //
#define PCI_BASE_CLASS_INPUT                0x09
#define PCI_CLASS_INPUT_KEYBOARD            0x0900
#define PCI_CLASS_INPUT_PEN                 0x0901
#define PCI_CLASS_INPUT_MOUSE               0x0902
#define PCI_CLASS_INPUT_SCANNER             0x0903
#define PCI_CLASS_INPUT_GAMEPORT            0x0904
#define PCI_CLASS_INPUT_OTHER               0x0980
// $$$                 0Axx                 $$$ //
// %%%             Docking Station          %%% //
#define PCI_BASE_CLASS_DOCKING              0x0a
#define PCI_CLASS_DOCKING_GENERIC           0x0a00
#define PCI_CLASS_DOCKING_OTHER             0x0a80
// $$$                 0Bxx                 $$$ //
// %%%              Processor               %%% //
#define PCI_BASE_CLASS_PROCESSOR            0x0b
#define PCI_CLASS_PROCESSOR_386             0x0b00
#define PCI_CLASS_PROCESSOR_486             0x0b01
#define PCI_CLASS_PROCESSOR_PENTIUM         0x0b02
#define PCI_CLASS_PROCESSOR_ALPHA           0x0b10
#define PCI_CLASS_PROCESSOR_POWERPC         0x0b20
#define PCI_CLASS_PROCESSOR_MIPS            0x0b30
#define PCI_CLASS_PROCESSOR_CO              0x0b40
// $$$                 0Cxx                 $$$ //
#define PCI_BASE_CLASS_SERIAL               0x0c
#define PCI_CLASS_SERIAL_FIREWIRE           0x0c00
#define PCI_CLASS_SERIAL_FIREWIRE_OHCI      0x0c0010
#define PCI_CLASS_SERIAL_ACCESS             0x0c01
#define PCI_CLASS_SERIAL_SSA                0x0c02
#define PCI_CLASS_SERIAL_USB                0x0c03
#define PCI_CLASS_SERIAL_USB_UHCI           0x0c0300
#define PCI_CLASS_SERIAL_USB_OHCI           0x0c0310
#define PCI_CLASS_SERIAL_USB_EHCI           0x0c0320
#define PCI_CLASS_SERIAL_USB_XHCI           0x0c0330
#define PCI_CLASS_SERIAL_FIBER              0x0c04
#define PCI_CLASS_SERIAL_SMBUS              0x0c05
// $$$                 0Dxx                 $$$ //
#define PCI_BASE_CLASS_WIRELESS             0x0d
#define PCI_CLASS_WIRELESS_RF_CONTROLLER    0x0d10
#define PCI_CLASS_WIRELESS_WHCI             0x0d1010
// $$$                 0Exx                 $$$ //
#define PCI_BASE_CLASS_INTELLIGENT          0x0e
#define PCI_CLASS_INTELLIGENT_I2O           0x0e00
// $$$                 0Fxx                 $$$ //
#define PCI_BASE_CLASS_SATELLITE            0x0f
#define PCI_CLASS_SATELLITE_TV              0x0f00
#define PCI_CLASS_SATELLITE_AUDIO           0x0f01
#define PCI_CLASS_SATELLITE_VOICE           0x0f03
#define PCI_CLASS_SATELLITE_DATA            0x0f04
// $$$                 10xx                 $$$ //
#define PCI_BASE_CLASS_CRYPT                0x10
#define PCI_CLASS_CRYPT_NETWORK             0x1000
#define PCI_CLASS_CRYPT_ENTERTAINMENT       0x1001
#define PCI_CLASS_CRYPT_OTHER               0x1080
// $$$                 11xx                 $$$ //
#define PCI_BASE_CLASS_SIGNAL_PROCESSING    0x11
#define PCI_CLASS_SP_DPIO                   0x1100
#define PCI_CLASS_SP_OTHER                  0x1180
// $$$                 FFxx                 $$$ //
#define PCI_BASE_CLASS_OTHERS               0xff
