/*
 * ioperm - start another program with access to I/O ports
 *
 * Copyright (C) 2017 Alex Henrie
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

#include <stdio.h>
#include <sys/io.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    if (ioperm(0, 65536, 1) == -1)
    {
        perror("ioperm");
        return 1;
    }

    if (execvp(argv[1], argv + 1) == -1)
    {
        perror("execvp");
        return 1;
    }

    return 0;
}
