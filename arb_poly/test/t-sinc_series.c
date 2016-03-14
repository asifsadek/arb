/*=============================================================================

    This file is part of ARB.

    ARB is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    ARB is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with ARB; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2012, 2013 Fredrik Johansson

******************************************************************************/

#include "arb_poly.h"

int main()
{
    slong iter;
    flint_rand_t state;

    flint_printf("sinc_series....");
    fflush(stdout);

    flint_randinit(state);

    for (iter = 0; iter < 200; iter++)
    {
        slong m, n1, n2, rbits1, rbits2, rbits3;
        arb_poly_t a, b, c, d;

        rbits1 = 2 + n_randint(state, 300);
        rbits2 = 2 + n_randint(state, 300);
        rbits3 = 2 + n_randint(state, 300);

        m = n_randint(state, 15);
        n1 = n_randint(state, 15);
        n2 = n_randint(state, 15);

        arb_poly_init(a);
        arb_poly_init(b);
        arb_poly_init(c);
        arb_poly_init(d);

        arb_poly_randtest(a, state, m, rbits1, 10);
        arb_poly_randtest(b, state, 10, rbits1, 10);
        arb_poly_randtest(c, state, 10, rbits1, 10);

        arb_poly_sinc_series(b, a, n1, rbits2);
        arb_poly_sinc_series(c, a, n2, rbits3);

        arb_poly_set(d, b);
        arb_poly_truncate(d, FLINT_MIN(n1, n2));
        arb_poly_truncate(c, FLINT_MIN(n1, n2));

        if (!arb_poly_overlaps(c, d))
        {
            flint_printf("FAIL\n\n");
            flint_printf("n1 = %wd, n2 = %wd, bits2 = %wd, bits3 = %wd\n", n1, n2, rbits2, rbits3);
            flint_printf("a = "); arb_poly_printd(a, 50); flint_printf("\n\n");
            flint_printf("b = "); arb_poly_printd(b, 50); flint_printf("\n\n");
            flint_printf("c = "); arb_poly_printd(c, 50); flint_printf("\n\n");
            abort();
        }

        /* check x sinc(x) = sin(x) */
        arb_poly_mullow(c, b, a, n1, rbits2);
        arb_poly_sin_series(d, a, n1, rbits2);

        if (!arb_poly_overlaps(c, d))
        {
            flint_printf("FAIL (functional equation)\n\n");
            flint_printf("a = "); arb_poly_printd(a, 15); flint_printf("\n\n");
            flint_printf("b = "); arb_poly_printd(b, 15); flint_printf("\n\n");
            flint_printf("c = "); arb_poly_printd(c, 15); flint_printf("\n\n");
            flint_printf("d = "); arb_poly_printd(d, 15); flint_printf("\n\n");
            abort();
        }

        arb_poly_sinc_series(a, a, n1, rbits2);

        if (!arb_poly_overlaps(a, b))
        {
            flint_printf("FAIL (aliasing)\n\n");
            abort();
        }

        arb_poly_clear(a);
        arb_poly_clear(b);
        arb_poly_clear(c);
        arb_poly_clear(d);
    }

    flint_randclear(state);
    flint_cleanup();
    flint_printf("PASS\n");
    return EXIT_SUCCESS;
}
