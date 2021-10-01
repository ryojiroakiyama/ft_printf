# Description
ft_printf function program that reproduces libc's printf function.  
`int		ft_printf(const char *fmt, ...);`
- Interpret the following format　(fmt in the prototype shown above).  
`%[flags][minimum field width].[precision][conversion specifier]`  
    - flags  
    '-0'
    - conversion specifier  
    'cspdiuxX%'

# Usage  
Type "make" in this repository.  
Then, the library libftprintf.a will be created.  
You can use ft_printf by including ft_printf.h and compiling with libftprintf.a together.
