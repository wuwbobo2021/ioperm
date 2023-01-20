/*
 * ioperm - start another program with access to I/O ports
 *
 * Copyright (C) 2017 Alex Henrie
 *
 * Copyright (C) 2023 wuwbobo2021 <wuwbobo@outlook.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <stdint.h>
#include <stdio.h>
#include <sys/io.h>
#include <unistd.h>

char str_usage[] =
"Usage: ioperm [-p <hex-l>-<hex-h>] <your-prog> [<your-prog-args>]\n";

int main(int argc, char* argv[])
{
    /* access to all ports is permitted by default */
    uint16_t portnum_l = 0, portnum_h = 0xffff;
    char *new_argc, **new_argv;
    
    if (argc < 2)
    {
    	printf("%s", str_usage);
    	return 0;
    }
    
    /* determine new_argc and new_argv */
    if (argv[1][0] == '-' && argv[1][1] == 'p') {
    	if (argc < 4
        ||  sscanf(argv[2], "%hx-%hx", &portnum_l, &portnum_h) < 2
        ||  portnum_h < portnum_l)
        {
            printf("%s", str_usage);
            return 0;
        }
        
        /* 0:ioperm  1:-p  2:l-h  3:new_argc  [4~n]:new_argv  NULL */
        new_argc = argv[3];
        new_argv = argv + 3;
    }
    else
    {
        /* 0:ioperm  1:new_argc  [2-n]:new_argv  NULL */
        new_argc = argv[1];
        new_argv = argv + 1;
    }
    
    /* try to gain permission */
    if (ioperm(portnum_l, portnum_h - portnum_l + 1, 1) == -1)
    {
        perror("try 'sudo setcap cap_sys_rawio=ep ioperm'");
        return 1;
    }
    
    /* execvp is based on execve, but the environment table is preserved */
    if (execvp(new_argc, new_argv) == -1)
    {
        perror("execvp failed");
        return 1;
    }
    
    return 0;
}
