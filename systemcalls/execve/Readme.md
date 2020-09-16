# Questions

- How does the register parameter is injected?

``` C
int do_execve(const char * filename,
	const char __user *const __user *argv,
	const char __user *const __user *envp,
	struct pt_regs * regs)
```

# Reference

- [C Program to print environment variables](https://www.geeksforgeeks.org/c-program-print-environment-variables)
- [execve(2) — Linux manual page](https://man7.org/linux/man-pages/man2/execve.2.html)

