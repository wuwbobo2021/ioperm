all:
	cc ioperm.c -o ioperm
	sudo setcap cap_sys_rawio=ep ioperm
