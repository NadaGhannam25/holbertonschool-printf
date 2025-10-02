# holbertonschool-printf - (_printf.c)

This project implements a **custom version of the C **printf** function**, named **_printf**.  
It is designed to produce output according to a format string and write to **stdout**, the standard output stream.

---

## Overview of **_printf**

The **_printf** function allows you to print characters, strings, integers, and the percent sign.  
It works by interpreting a **format string**, composed of zero or more **directives**, and producing output accordingly.  

- **Mandatory specifiers supported:**
  - **%c** — print a single character
  - **%s** — print a string
  - **%%** — print a percent sign
  - **%d** and **%i** — print signed integers

- **Custom specifiers:**
  - **%b** — print unsigned integers in binary
  - **%u** — print unsigned integers
  - **%o** — print unsigned integers in octal
  - **%x** / **%X** — print unsigned integers in hexadecimal (lowercase/uppercase)
  - **%S** — print strings and escape non-printable characters (\xNN)
  - **%p** — print pointer addresses

---

## Capabilities

- Handles **variadic arguments** using **va_list**, allowing multiple values in a single call.
- Safely prints **NULL** strings as **(null)** to avoid crashes.
- Returns the **number of characters printed**, excluding the null byte.
- Can be extended to support more specifiers.
- Focuses on output accuracy and simplicity.

---

<p align="center">
  <img src="3.png" width="400" height="400" />
</p>
