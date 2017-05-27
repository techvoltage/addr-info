# addr-info
* Address Scanner for Linux (Also see https://github.com/scanmem/scanmem)
* Finds base address of a shared object
* Finds function address in a shared object
* Also finds if a pattern exists in memory by scanning all loaded modules (does not scan stack and heap)
* Each segment in a loaded module is scanned only once for a pattern
* For stack and heap parsing as well, see https://github.com/ouadev/proc_maps_parser
 #### To Do: 
 * Pattern scan without memory maps
 * Include entire memory for pattern scanning
 * Remove memmem function
 * Extend to remote processes
 * Repair Makefile. Add entry for samples
