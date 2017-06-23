/**
*This program is free software: you can redistribute it and/or modify
*it under the terms of the GNU General Public License as published by
*the Free Software Foundation, either version 3 of the License, or
*(at your option) any later version.
*
*This program is distributed in the hope that it will be useful,
*but WITHOUT ANY WARRANTY; without even the implied warranty of
*MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*GNU General Public License for more details.
*
*You should have received a copy of the GNU General Public License
*along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// Finds base address of a shared object
// Finds function address in a shared object
// Also finds if a pattern exists in memory by scanning all loaded modules (does not scan stack and heap)
// Each segment in a loaded module is scanned only once for a pattern
// For stack and heap parsing as well, see https://github.com/ouadev/proc_maps_parser
// TODO: Pattern Scan without memory maps
// TODO: Include entire memory for pattern scanning
// TODO: Remove memmem function
// TODO: Extend to remote processes

#define _GNU_SOURCE		/* for RTLD_NEXT */
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>
#include <link.h>
#include <stdlib.h>
#include <unistd.h>
#define PATTERNSIZEMAX 150
#define handle_error(msg) \
do { perror(msg); exit(EXIT_FAILURE); } while (0)
#define fprintf_ fprintf
#define DEBUG 0
#define debug_print(fmt, ...) \
            do { if (DEBUG) fprintf_(stderr, fmt, __VA_ARGS__); } while (0)


struct p_struct
{
  char pattern[PATTERNSIZEMAX];
  unsigned int patternlen;
  void *pattern_addr;     //This field is not used anywhere, Use it to store all addresses found
  char lib[PATTERNSIZEMAX];
  char func[PATTERNSIZEMAX];
};
void *
find_pattern_in_memory (void *address, size_t memsize, char *pattern,
			size_t patternlen)
{
  debug_print("%s\n",__func__);
  void *p = memmem (address, memsize, pattern, patternlen);
  return p;
}

static int
callback (struct dl_phdr_info *info, size_t size, void *data)
{
  debug_print("%s\n",__func__);
  int j;
  void *current;
  //void *save;

  debug_print("name=%s (%d segments)\n", info->dlpi_name,info->dlpi_phnum);
  char *p;
  p = strstr (info->dlpi_name,"test");
  if(p)
  {
  debug_print("string found in %s \n",info->dlpi_name);
  //printf("string found\n");
	strncpy(((struct p_struct *) data)->lib,info->dlpi_name,PATTERNSIZEMAX);
  }

  for (j = 0; j < info->dlpi_phnum; j++)
    {
      if (j == 0)
	{
	  current = (void *) info->dlpi_addr + info->dlpi_phdr[j].p_vaddr;
	  //save = current;
	}
      //printf("\t\t header %2d: address=%10p\n", j,(void *) (info->dlpi_addr + info->dlpi_phdr[j].p_vaddr));
      current = (void *) info->dlpi_addr + info->dlpi_phdr[j].p_vaddr;
      void *found =
	find_pattern_in_memory (current, info->dlpi_phdr[j].p_memsz,
				((struct p_struct *) data)->pattern,
				((struct p_struct *) data)->patternlen);
      if (found)
	{
	  ((struct p_struct *) data)->pattern_addr = found;
	  printf ("%s found at %p\n",
		  ((struct p_struct *) data)->pattern,
		  ((struct p_struct *) data)->pattern_addr);
	}
      //save = current;
    }

  return 0;
}

void
find_pattern_init(struct p_struct *p)
{
  debug_print("%s\n",__func__);
  dl_iterate_phdr (callback, p);	//iterate modules to find the pattern
}


void *
find_lib_base (char *lib)
{
  debug_print("%s\n",__func__);
  struct link_map *lm = (struct link_map *) dlopen (lib, RTLD_NOW);
  return (void *) lm->l_addr;
}

void *
find_func_address (char *func, char *lib)
{
  void *handle = dlopen (lib, RTLD_LAZY);
  if (handle)
    {
      return dlsym (handle, func);
    }
  else
    {
      return NULL;
    }
}
