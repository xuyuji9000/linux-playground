// This file contains netlink related struct definition and macros

// byte alignment technique is used optimize for CPU access
// here also function as a convention to communicate with kernel
#define MNL_ALIGNTO 4
#define MNL_ALIGN(len) (((len)+MNL_ALIGNTO-1) & ~(MNL_ALIGNTO-1))

