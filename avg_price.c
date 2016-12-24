/* See LICENSE.txt for license and copyright information. */

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdint.h>
#include <unistd.h> /* For the sleep function. */
#include <stdarg.h>
#include "avg_price.h"
#include "docopt.c"
#include "c_generic/functions.h"


void print_if_verbose(uint32_t *a_verbose, char *format, ...);

/*
 * Main
 */
int main(int argc, char *argv[])
{
    uint32_t l_verbose = 0;

    /*
     * Parse arguments
     */
    DocoptArgs args = docopt(
        argc,
        argv,
        1, /* help */
        AVG_PRICE_VERSION /* version */
    );

    if (argc == 1)
    {
        printf("%s\n", args.help_message);
        return EXIT_FAILURE;
    }

    l_verbose = args.verbose ? 1 : 0;

    /*
     * Preparation of data.
     */
    uint32_t l_status = EXIT_SUCCESS; // Note: To make sure the cleanup runs.
    print_if_verbose(&l_verbose, ">>> Calculating data...\n");
    //if (prepare_data_file(args.file, l_plot_type, l_plot_timeframe, l_start_year, l_end_year) != SUCCEEDED)
    print_if_verbose(&l_verbose, ">>> Done.\n");
    return l_status;
}
