#ifndef _GaussianMixture_h_
#define _GaussianMixture_h_
/* GaussianMixture.h
 *
 * Copyright (C) 2010-2011, 2015-2016 David Weenink
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*
 djmw 20101021 initial version
 djmw 20110306 Latest modification.
*/

#include "ClassificationTable.h"
#include "Matrix.h"
#include "SSCP.h"
#include "TableOfReal_extensions.h"

#include "GaussianMixture_def.h"

/*
	Constraints for a Gaussian mixture:
	 all covariances have the same 'dimension' parameter
*/
autoGaussianMixture GaussianMixture_create (long numberOfComponents, long dimension, long storage);
/* Start each function with expand and end with unExpand */

void GaussianMixture_expandPCA (GaussianMixture me);

void GaussianMixture_unExpandPCA (GaussianMixture me);

void GaussianMixture_drawConcentrationEllipses (GaussianMixture me, Graphics g,
	double scale, int confidence, char32 *label, int pcaDirections, long d1, long d2,
	double xmin, double xmax, double ymin, double ymax, int fontSize, int garnish);

void GaussianMixture_and_PCA_drawConcentrationEllipses (GaussianMixture me, PCA him, Graphics g,
	double scale, int confidence, char32 *label, long d1, long d2,
	double xmin, double xmax, double ymin, double ymax, int fontSize, int garnish);

void GaussianMixture_drawMarginalPdf (GaussianMixture me, Graphics g, long d, double xmin, double xmax, double ymin, double ymax, long npoints, long nbins, int garnish);

void GaussianMixture_and_PCA_drawMarginalPdf (GaussianMixture me, PCA him, Graphics g, long d, double xmin, double xmax, double ymin, double ymax, long npoints, long nbins, int garnish);

autoGaussianMixture TableOfReal_to_GaussianMixture_fromRowLabels (TableOfReal me, long storage);

void GaussianMixture_initialGuess (GaussianMixture me, TableOfReal thee, double nSigmas, double ru_range);
/*
	Give an initial guess for the centroids and covariances of the GaussianMixture based on the data in the table.
	Position centroids on the nSigma-ellips in the pc1-pc2 plane with some random variation and the covariances as
	a scaled down version of the total covariance.
	The randomly varied position of a centroid on the ellipse is parametrized as:
		x = a * (1 + randomUniform (-ru_range, ru_range)) * cos (alpha)
		y = b * (1 + randomUniform (-ru_range, ru_range)) * sin (alpha).
	where a and b are the axes of the ellipse and 0<= alpha <= 2pi.
*/

#define GaussianMixture_LIKELIHOOD 0
#define GaussianMixture_MML 1
#define GaussianMixture_BIC 2
#define GaussianMixture_AIC 3
#define GaussianMixture_AICC 4
#define GaussianMixture_CD_LIKELIHOOD 5

const char32 *GaussianMixture_criterionText (int criterion);

autoGaussianMixture TableOfReal_to_GaussianMixture (TableOfReal me, long numberOfComponents, double delta_lnp, long maxNumberOfIterations, double lambda, int storage, int criterion);

void GaussianMixture_and_TableOfReal_improveLikelihood (GaussianMixture me, TableOfReal thee, double delta_lnp, long maxNumberOfIterations, double lambda, int criterion);

autoGaussianMixture GaussianMixture_and_TableOfReal_to_GaussianMixture_CEMM (GaussianMixture me, TableOfReal thee, long minNumberOfComponents, double delta_l, long maxNumberOfIterations, double lambda, int criterion);

void GaussianMixture_splitComponent (GaussianMixture me, long component);

autoClassificationTable GaussianMixture_and_TableOfReal_to_ClassificationTable (GaussianMixture me, TableOfReal thee);

autoTableOfReal GaussianMixture_and_TableOfReal_to_TableOfReal_BHEPNormalityTests (GaussianMixture me, TableOfReal thee, double h);

double GaussianMixture_and_TableOfReal_getLikelihoodValue (GaussianMixture me, TableOfReal thee, int criterion);

double GaussianMixture_getProbabilityAtPosition (GaussianMixture me, double *vector);

double GaussianMixture_getProbabilityAtPosition_string (GaussianMixture me, const char32 *vector);

double GaussianMixture_getMarginalProbabilityAtPosition (GaussianMixture me, double *vector, double x);

autoCorrelation GaussianMixture_and_TableOfReal_to_Correlation (GaussianMixture me, TableOfReal thee);
/* Correlation between components based on the data in the table */

autoCovariance GaussianMixture_to_Covariance_total (GaussianMixture me);

autoCovariance GaussianMixture_to_Covariance_between (GaussianMixture me);

autoCovariance GaussianMixture_to_Covariance_within (GaussianMixture me);


autoCovariance GaussianMixture_extractComponent(GaussianMixture me, long component);

autoTableOfReal GaussianMixture_extractCentroids (GaussianMixture me);

autoTableOfReal GaussianMixture_extractMixingProbabilities (GaussianMixture me);

autoPCA GaussianMixture_to_PCA (GaussianMixture me);

autoMatrix GaussianMixture_and_PCA_to_Matrix_density (GaussianMixture me, PCA pca, long d1, long d2, double xmin, double xmax, long nx, double ymin, double ymax, long ny);

void GaussianMixture_and_PCA_getIntervalsAlongDirections (GaussianMixture me, PCA thee, long d1, long d2, double nsigmas, double *xmin, double *xmax, double *ymin, double *ymax);

void GaussianMixture_and_PCA_getIntervalAlongDirection (GaussianMixture me, PCA thee, long d, double nsigmas, double *xmin, double *xmax);

void GaussianMixture_getIntervalAlongDirection (GaussianMixture me, long d, double nsigmas, double *xmin, double *xmax);

void GaussianMixture_getIntervalsAlongDirections (GaussianMixture me, long d1, long d2, double nsigmas, double *xmin, double *xmax, double *ymin, double *ymax);

/* with on demand expand of pca ! */
int GaussianMixture_generateOneVector (GaussianMixture me, double *c, char32 **covname, double *buf);

autoTableOfReal GaussianMixture_to_TableOfReal_randomSampling (GaussianMixture me, long numberOfPoints);

#endif /* _GaussianMixture_h_ */
