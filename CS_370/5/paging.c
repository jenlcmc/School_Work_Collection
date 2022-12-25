/*
  Assignment: proj 5A
  Description: Implement a memory access simulator
◦ Where the page size (in bytes) is configurable
◦ Where the frame table size (in pages) is configurable
◦ The frame replacement algorithm is configurable
- First-In-First-Out (FIFO)
- Least Recently Used (LRU)
- Input to the simulator is a sequence of memory accesses.
- Each memory access is recorded as a page hit or fault while maintaining the frame table
- for a single process.
  Input: ./paging-start <page size> <frame table size> <replacement algorithm> <trace file>
  Output: similar to pdf
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <errno.h>
// for bool
#include <stdbool.h>

/* Argument Parsing Related */
void usage(void)
{
	static const char *msg =
		"USAGE: paging [OPTION] <ACCESS 1> <ACC. 2> ... <ACC. N>\n\n"
		//"Simulates the impact of memory accesses with respect to\n"
		"Simulates the impact of memory accesses for a given frame\n"
		"replacement algorithm, frame table size, memory access\nsequence."
		//"are limited of a specific page replacement algorithm\n"
		"\n\n"
		"OPTIONS:\n"
		"  -p, --page-size    number of bytes in each page\n"
		"  -f, --frame-size   number of frames for the process\n"
		"  -t, --tlb-size     number of entries in the TLB\n"
		"  --fifo             first-in-first-out policy\n"
		"  --lru              least-recently-used policy\n"
		"  -v, --verbose      display the frame table at each step\n"
		//"                     each step\n"
		"  --help             this message\n"
		"\n"
		"Every <ACCESS> is recorded as a hit or miss in the frame\n"
		"table. The output of the program is the number of total\n"
		"frame table hits and page table faults\n";
	//"TLB misses\n";

	printf("%s", msg);
}

const struct option longopts[] = {
	{"fcfs", no_argument, 0, 'F'},
	{"frame-size", required_argument, 0, 'f'},
	{"lru", no_argument, 0, 'l'},
	{"page-size", required_argument, 0, 'p'},
	{"verbose", no_argument, 0, 'v'},
	{"help", no_argument, 0, 'h'},
	{0, 0, 0, 0}};

typedef enum
{
	FCFS, /* First Come First Serve */
	LRU,  /* Least Recently Used */
} policy_t;

const char *POLICY[] = {
	"FIFO",
	"LRU"};

struct _context
{
	unsigned int page_size;
	unsigned int frame_size;
	unsigned int verbose;
	policy_t policy;
} ctx;

struct _data
{
	unsigned int page_hits;
	unsigned int page_faults;
} data;

// making a struct array to hold the age,page number and valid bit
// this will be use for FIFO and LRU
struct frame
{
	int age;
	int page;
	bool fault;
};

/* Program Body */

int record_access(struct _context *, struct _data *,
				  unsigned int access, struct frame *frame_table);
int FIFO_implement(struct _context *ctx, struct _data *data, unsigned int access, struct frame *frame_table);
int LRU_implement(struct _context *ctx, struct _data *data, unsigned int access, struct frame *frame_table);

int main(int argc, char **argv)
{
	int idx = 0;
	char rv;

	memset(&data, 0, sizeof(data));

	ctx.page_size = 4096;
	ctx.frame_size = 4;
	ctx.verbose = 0;
	ctx.policy = FCFS;

	while ((rv = getopt_long(argc, argv, "f:p:n:t:lvh", longopts, &idx)) != -1)
	{
		switch (rv)
		{
		case 'f':
			ctx.frame_size = atoi(optarg);
			break;
		case 'F':
			ctx.policy = FCFS;
			break;
		case 'l':
			ctx.policy = LRU;
			break;
		case 'p':
			ctx.page_size = atoi(optarg);
			break;
		case 'v':
			ctx.verbose = 1;
			break;
		case 'h':
			usage();
			return 0;
		default:
			fprintf(stderr, "Unknown argument %c\n", rv);
			return 0;
		}
	}

	int counter = 0;
	// this is the frame table and we need to make it dynamic
	struct frame *frame_table;
	frame_table = (struct frame *)malloc(ctx.frame_size * sizeof(struct frame));
	// init it
	for (int i = 0; i < ctx.frame_size; i++)
	{
		frame_table[i].age = -1;
		frame_table[i].page = -1;
		frame_table[i].fault = false;
	}

	if (ctx.verbose)
	{
		printf("page-size: %u\nframe-size: %u\npolicy: %s\n",
			   ctx.page_size, ctx.frame_size, POLICY[ctx.policy]);

		printf("\nInitial table\n");
		printf("Frame | Page | Age\n");
		printf("------+------+----\n");
		for (int i = 0; i < ctx.frame_size; i++)
			// if page or age == -1 then we will output "-"
			printf("%4d  | %2s   |%2s\n", i, "-", "-");
	}

	printf("\nBeginning simulation\n");

	for (int i = optind; i < argc; i++)
	{
		int access = atoi(argv[i]);
		if (access < 0)
		{
			fprintf(stderr, "Unable to parse %s - %s", argv[i], strerror(errno));
		}

		int rv = record_access(&ctx, &data, access, frame_table);
		// print the frame table
		if (!ctx.verbose)
			// print the frame table for FIFO
			printf("[%2d] Access    %5d (dec) 0x%08x (hex) page %-5dframe %-4d fault %s\n", counter, access, access, access / ctx.page_size, rv, frame_table[rv].fault ? "yes" : "no");
		else
		{
			// print the frame table for FIFO
			printf("[%2d] Access    %5d (dec) 0x%08x (hex) page %-5dframe %d    fault %s\n", counter, access, access, access / ctx.page_size, rv, frame_table[rv].fault ? "yes" : "no");
			// print initial frame table include frame number, page number, age
			// frame will run from 0 -> frame_size - 1
			printf("Frame | Page | Age\n");
			printf("------+------+----\n");
			for (int j = 0; j < ctx.frame_size; j++)
			{
				// if page or age == -1 then we will output "-"
				if (frame_table[j].page == -1 || frame_table[j].age == -1)
					printf("%4d  | %2s   |%2s\n", j, "-", "-");
				else
					printf("%4d  | %2d   |%2d  \n", j, frame_table[j].page, frame_table[j].age);
			}
			printf("\n");
		}
		counter++;
	}
	printf("Page Hits:   %-4d\n", data.page_hits);
	printf("Page Faults: %-4d\n", data.page_faults);
	// clean up the frame table
	free(frame_table);
	return 0;
}

/**
 * @brief FIFO page replacement algorithm
 *	general idea: find the oldest page and replace it with the new page
	otherword -> replace the 1st elem with new page and move the the rest down

	Algo:
		-Step 1. Start to traverse the pages to check if the page is already in the memory.
		-Step 2. If the page is already in the memory, then it is a page hit.
		Then we will return the frame number.
		-Step 3. If the page is not in the memory, then it is a page fault.
		Then we will return 0.
		-Step 4. If the page is not in the memory, then we will replace the first page in the memory with the new page.
		-Step 5. Then we will move the rest of the pages down.
		-Step 6. We also need to check if we fill all of the frame page in the memory or not
		-We will then start from the beginning of the frame page in the memory.
		Example: 1st run: 3 -1 -1 -1 -> 2nd run: 4 3 -1 -1 -> 3rd run: 4 3 -1 -1 -> 4th run: 0 4 3 -1 -> 5th run: 1 0 4 3 -> 6th run: 1 0 4 3
		-Step 7. Return the frame number or 0 if it is a page fault

 * @param ctx - pointer to context
 * @param data - pointer to data
 * @param access - the page number
 * @param frame_table - pointer to frame table
 * @return int - the frame number
 */
int FIFO_implement(struct _context *ctx, struct _data *data, unsigned int access, struct frame *frame_table)
{
	// Step 1. Start to traverse the pages.
	int page = access / ctx->page_size;
	int frame_ret = -1;

	// Check if the page is already in the memory
	for (int i = 0; i < ctx->frame_size; i++)
	{
		// Step 2. If the page is already in the memory, then it is a page hit.
		if (frame_table[i].page == page)
		{
			// Step 3. If the page is already in the memory, then it is a page hit.
			// Then we will return the frame number.
			frame_ret = i;
			data->page_hits++;
			frame_table[i].fault = 0;
			break;
		}
		// If it is not
		else
			// Step 4. If the page is not in the memory, then it is a page fault.
			// Then we will return 0.
			frame_ret = 0;
	}

	// Step 5. If the page is not in the memory, then we will replace the first page in the memory with the new page.
	if (frame_ret == 0)
	{
		// we need to check if the 1st page have same value with new page or not -> if yes then we do nothing
		if (page != frame_table[0].page)
		{
			frame_table[0].fault = 1;
			data->page_faults++;
			// Step 6. Then we will move the rest of the pages down.
			int tmp = frame_table[0].page;
			frame_table[0].page = page;
			for (int j = 1; j < ctx->frame_size; j++)
			{
				int tmp2 = frame_table[j].page;
				frame_table[j].page = tmp;
				tmp = tmp2;
				frame_table[j].fault = 0;
			}
		}
	}
	// step 6. we will need to update the age to 0
	for (int i = 0; i < ctx->frame_size; i++)
	{
		frame_table[i].age = 0;
	}

	// Step 7. Return the frame number or 0 if it is a page fault
	return frame_ret;
}

/**
 * @brief LRU page replacement algorithm
 *	general idea: find the least recently used page and replace it with the new page
	otherword -> replace the page that has not been used for the longest period of time - age
	we will need to update the age of the page too. 0 = youngest and frame_size - 1 = oldest

	Algo:
		-Step 1. Start to traverse the pages.
		-step 2. Check if the page is already in the memory
		-stpe 3. If the page is already in the memory, then it is a page hit.
		if page hit, then we will return the frame number, update the age of all pages in the
		frame table, and set the age of hit page to 0
		we won't have to insert hit page into the frame table
		for example, if page 3 already in the frame table, then we will just update the ages of page 3
		to 0 and the rest of the pages in frame table is + 1
		-step 4. If the page is not in the memory, then it is a page fault.
		-step 5. If the page is not in the memory, then we will replace the page with the oldest time value.
		-Step 6. But we need to check if all of the frame is full or not.
		-Step 7. If the page is full, then we will replace the page with the oldest time value.
		and set it age to 0 while set the age of all other pages to age + 1
		-Step 8. If the page is not full, then we will find the first empty frame and put the page in it.
		and set it age to 0 while set the age of all other pages to age + 1
		usually, we will want to insert new page at the end of the frame table
		-step 9. we will return frame number or 0 if  page fault
 * @param ctx - pointer to context
 * @param data - pointer to data
 * @param access - the page number
 * @param frame_table - pointer to frame table
 * @return int - the frame number
 */
int LRU_implement(struct _context *ctx, struct _data *data, unsigned int access, struct frame *frame_table)
{
	// Step 1. Start to traverse the pages.
	int page = access / ctx->page_size;
	int frame_ret = 0;
	int page_hit = 0;
	int frame_full = 1;
	int oldest_time = 0;
	int oldest_time_index = 0;
	int empty_frame_index = 0;

	// step 2. Check if the page is already in the memory
	for (int i = 0; i < ctx->frame_size; i++)
	{
		if (frame_table[i].page == page)
		{
			page_hit = 1;
			data->page_hits++;
			frame_ret = i;
			frame_table[i].fault = 0;
			break;
		}
	}

	// stpe 3. If the page is already in the memory, then it is a page hit.
	if (page_hit == 1)
	{
		// if page hit, then we will return the frame number, update the age of all pages in the
		// frame table, and set the age of hit page to 0
		// we won't have to insert hit page into the frame table
		// for example, if page 3 already in the frame table, then we will just update the ages of page 3
		// to 0 and the rest of the pages in frame table is + 1
		for (int i = 0; i < ctx->frame_size; i++)
		{
			if (frame_table[i].page == page)
				frame_table[i].age = 0;
			else if (frame_table[i].page != -1)
				frame_table[i].age++;
		}
		return frame_ret;
	}

	// step 4. If the page is not in the memory, then it is a page fault.
	// step 5. If the page is not in the memory, then we will replace the page with the oldest time value.
	// Step 6. But we need to check if all of the frame is full or not.
	for (int i = 0; i < ctx->frame_size; i++)
	{
		if (frame_table[i].page == -1)
		{
			frame_table[i].fault = 1;
			data->page_faults++;
			frame_full = 0;
			empty_frame_index = i;
			break;
		}
	}

	// Step 7. If the page is full, then we will replace the page with the oldest time value.
	// and set it age to 0 while set the age of all other pages to age + 1
	if (frame_full == 1)
	{
		data->page_faults++;
		oldest_time = frame_table[0].age;
		oldest_time_index = 0;
		// find the oldest time
		for (int i = 1; i < ctx->frame_size; i++)
		{
			if (frame_table[i].age > oldest_time)
			{
				oldest_time = frame_table[i].age;
				oldest_time_index = i;
			}
		}
		// replace the page with the oldest time value
		frame_table[oldest_time_index].page = page;
		frame_table[oldest_time_index].age = 0;
		frame_table[oldest_time_index].fault = 1;
		// set the age of all other pages to age + 1
		for (int i = 0; i < ctx->frame_size; i++)
		{
			if (i != oldest_time_index && frame_table[i].page != -1)
				frame_table[i].age++;
		}
		return oldest_time_index;
	}

	// Step 8. If the page is not full, then we will find the first empty frame and put the page in it.
	// and set it age to 0 while set the age of all other pages to age + 1
	// usually, we will want to insert new page at the end of the frame table
	frame_table[empty_frame_index].page = page;
	frame_table[empty_frame_index].age = 0;
	frame_table[empty_frame_index].fault = 1;
	// set the age of all other pages to age + 1
	for (int i = 0; i < ctx->frame_size; i++)
	{
		if (i != empty_frame_index && frame_table[i].page != -1)
			frame_table[i].age++;
	}

	// step 9. we will return frame number or 0 if  page fault
	return empty_frame_index;
}

/**
 * @brief - This function will implement call either FIFO or LRU
 *	This will control the logic of the program and call the FIFO or LRU function
 * 	Then return back the frame number
 * @param ctx - pointer to context
 * @param data - pointer to data
 * @param access - the page number
 * @param frame_table - pointer to frame table
 * @return int - the frame number
 */
int record_access(struct _context *ctx, struct _data *data,
				  unsigned int access, struct frame *frame_table)
{
	// general idea: find the frame number for the page

	int rv = -1;
	if (ctx->policy == FCFS)
		rv = FIFO_implement(ctx, data, access, frame_table);
	else if (ctx->policy == LRU)
		rv = LRU_implement(ctx, data, access, frame_table);

	return rv;
}
