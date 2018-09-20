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
#include "c_generic/enum.h"


static double calculate_avg_price(uint32_t *a_verbose, uint32_t a_nargs, ...);

/*
 * Main
 */
int main(int argc, char *argv[])
{
    uint32_t l_verbose = 0;
    char *l_dataset;

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
    l_dataset = args.dataset ? args.dataset : "";
    trim_whitespace(l_dataset, l_dataset, SIZE_MAX);

    /*
     * Preparation of data.
     */
    printf("Result:\n%.2lf\n", calculate_avg_price(&l_verbose, 1, l_dataset));
    return EXIT_SUCCESS;
}

static double calculate_avg_price(uint32_t *a_verbose, uint32_t a_nargs, ...)
{
    va_list l_args;
    register uint32_t l_i;
    char *l_current;
    double l_enumerator, l_denominator, l_result;
   
    // TODO: find a correct way to parse "shares_int,price_int" entries 
    l_result = 0.0;
    l_enumerator = 0.0;
    l_denominator = 0.0;
    va_start(l_args, a_nargs);
    for (l_i = 0; l_i < a_nargs; l_i++)
    {
        l_current = va_arg(l_args, char *);
        printf("%s ", l_current);
        if (l_current != 0)
        {
            fprintf(stderr, "Invalid data: %s.\n", l_current);
            break;
        }
    }
    va_end(l_args);
    printf("\n");
    if (l_denominator <= 0)
        l_result = 0.0;
    return l_result;
}
