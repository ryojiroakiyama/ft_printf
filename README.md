# Description
This is a ft_printf program that reproduces libc's printf function.  
`int	ft_printf(const char *format, ...);`
- Interpret the following format rules.  
`%[flags][minimum field width].[precision][conversion specifier]`  
    - flags  
    '-0'
    - conversion specifier  
    'cspdiuxX%'

# Usage  
Type "make" in this repository.  
Then, the library libftprintf.a will be created.  
You can use ft_printf function by including ft_printf.h and compiling your code with libftprintf.a.
