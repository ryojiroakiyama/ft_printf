# Description
ft_printf is the program that reproduces libc's printf function.  
`int	ft_printf(const char *format, ...);`
- Interpret the following format rules.  
`%[flags][minimum field width].[precision][conversion specifier]`  
    - flags  
    '-0'
    - conversion specifier  
    'cspdiuxX%'

# Usage  
## Build libftprintf.a (the library name of ft_printf)  
```
git clone "URL"
cd ft_printf
make
```
## Use
include ft_printf.h and compile your code with libftprintf.a.
#### sample code
```
#include "ft_printf.h"

int main(void)
{
    ft_printf("%010.5d\n", 42);
    return (0);
}
```
#### compile and execute  
```
gcc "sample code file name" libftprintf.a
./a.out
```
