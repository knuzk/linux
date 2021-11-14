#include <raspi/peripherals.h>
#include <raspi/print.h>

void print_c(char c)
{
    if (c == '\n') {
        uart_send('\r');
    }
    uart_send(c);
}

void print_s(const char *s)
{
    while (*s) {
        print_c(*s++);
    }
}

void print_u8(u8 n)
{
    char* hex = "0123456789ABCDEF";
    uart_send(hex[n>>4]);
    uart_send(hex[n&0xF]);
}

void print_u16(u16 n)
{
    print_u8(n >> 8);
    print_u8((u8)n);
}

void print_u32(u32 n)
{
    print_u16((u16)(n >> 16));
    print_u16((u16)n);
}

void print_u64(u64 n)
{
    print_u32((u32)(n >> 32));
    print_u32((u32)n);
}