`int getopt(int argc, char * const argv[],
                  const char *optstring);`

`optstring` is a string containing the legitimate option characters. If such a character is followed by a colon, the option requires an argument, so `getopt()` places a pointer to the following text in the same `argv`-element, or the text of the following `argv`-element, in `optarg`. Two colons means an option takes an optional arg; if there is text in the current `argv`-element, then it is returned in `optarg`, otherwise `optarg` is set to zero.