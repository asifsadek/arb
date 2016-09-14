/*
    Copyright (C) 2016 Pascal Molin

    This file is part of Arb.

    Arb is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/

#include "acb_dirichlet.h"

void
acb_dirichlet_gauss_sum_theta(acb_t res, const acb_dirichlet_group_t G, const acb_dirichlet_char_t chi, slong prec)
{
    if (chi->conductor < G->q || (G->q == 300 && (chi->x->n == 71 || chi->x->n == 131))
            || (G->q == 600 && (chi->x->n == 11 || chi->x->n == 491)))
    {
        flint_printf("gauss_sum_theta: non available for non primitive character"
                "or exceptional characters chi_300(71,.), chi_300(131,.), "
                "chi_600(11,.) and chi_600(491,.)\n");
        abort();
    }
    else
    {
        acb_t iq;
        acb_init(iq);
        acb_dirichlet_gauss_sum_order2(iq, chi, prec);
        _acb_dirichlet_root_number(res, G, chi, prec);
        acb_mul(res, res, iq, prec);
        acb_clear(iq);
    }
}