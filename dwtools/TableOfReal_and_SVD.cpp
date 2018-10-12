/* TableOfReal_and_SVD.cpp
 *
 * Copyright (C) 1993-2017 David Weenink
 *
 * This code is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This code is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this work. If not, see <http://www.gnu.org/licenses/>.
 */

/*
 djmw 20021009 GPL header
 djmw 20031107 Added TablesOfReal_to_GSVD.
 djmw 20051202 Extract left/right singular vectors.
*/

#include "TableOfReal_and_SVD.h"

autoTableOfReal SVD_to_TableOfReal (SVD me, integer from, integer to) {
	try {
		autoTableOfReal thee = TableOfReal_create (my isTransposed ? my numberOfColumns : my numberOfRows, 
												   my isTransposed ? my numberOfRows : my numberOfColumns);
		SVD_synthesize (me, from, to, thy data.at_deprecated);
		return thee;
	} catch (MelderError) {
		Melder_throw (me, U": no TableOfReal synthesized.");
	}
}

autoSVD TableOfReal_to_SVD (TableOfReal me) {
	try {
		autoSVD thee = SVD_createFromGeneralMatrix (my data.get());
		return thee;
	} catch (MelderError) {
		Melder_throw (me, U": no SVD created.");
	}
}

autoTableOfReal SVD_extractLeftSingularVectors (SVD me) {
	try {
		autoTableOfReal thee = TableOfReal_create (my numberOfRows, my numberOfColumns);
		MATcopy_preallocated (thy data.get(), my u.get());
		return thee;
	} catch (MelderError) {
		Melder_throw (me, U": left singular vector not extracted.");
	}
}

autoTableOfReal SVD_extractRightSingularVectors (SVD me) {
	try {
		autoTableOfReal thee = TableOfReal_create (my numberOfColumns, my numberOfColumns);
		MATcopy_preallocated (thy data.get(), my v.get());
		return thee;
	} catch (MelderError) {
		Melder_throw (me, U": right singular vector not extracted.");
	}
}

autoTableOfReal SVD_extractSingularValues (SVD me) {
	try {
		autoTableOfReal thee = TableOfReal_create (1, my numberOfColumns);
		VECcopy_preallocated (thy data.row(1), my d.get());
		return thee;
	} catch (MelderError) {
		Melder_throw (me, U": singular values not extracted.");
	}
}

autoGSVD TablesOfReal_to_GSVD (TableOfReal me, TableOfReal thee) {
	try {
		Melder_require (my numberOfColumns == thy numberOfColumns,
			U"Both tables must have the same number of columns.");

		autoGSVD him = GSVD_create_d (my data.get(), thy data.get());
		return him;
	} catch (MelderError) {
		Melder_throw (U"GSVD not constructed from TablesOfReal.");
	}
}

/* End of file SVD_and_TableOfReal.cpp */
