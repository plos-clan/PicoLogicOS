#include <driver/pci.h>

static const cstr PCI_BASE_CLASS_NAMES[256] = {
    [PCI_BASE_CLASS_UNDEFINED]         = "Build before PCI Rev2.0",
    [PCI_BASE_CLASS_STORAGE]           = "Mass storage controller",
    [PCI_BASE_CLASS_NETWORK]           = "Network controller",
    [PCI_BASE_CLASS_DISPLAY]           = "Display controller",
    [PCI_BASE_CLASS_MULTIMEDIA]        = "Multimedia device",
    [PCI_BASE_CLASS_MEMORY]            = "Memory controller",
    [PCI_BASE_CLASS_BRIDGE]            = "Bridge device",
    [PCI_BASE_CLASS_COMMUNICATION]     = "Simple comm. controller",
    [PCI_BASE_CLASS_SYSTEM]            = "Base system peripheral",
    [PCI_BASE_CLASS_INPUT]             = "Input device",
    [PCI_BASE_CLASS_DOCKING]           = "Docking station",
    [PCI_BASE_CLASS_PROCESSOR]         = "Processor",
    [PCI_BASE_CLASS_SERIAL]            = "Serial bus controller",
    [PCI_BASE_CLASS_INTELLIGENT]       = "Intelligent controller",
    [PCI_BASE_CLASS_SATELLITE]         = "Satellite controller",
    [PCI_BASE_CLASS_CRYPT]             = "Cryptographic device",
    [PCI_BASE_CLASS_SIGNAL_PROCESSING] = "DSP",
    [PCI_BASE_CLASS_OTHERS]            = "Does not fit any class",
};
