#include "TP5_funcs.h"
#include "../Utils/Util.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>

#define MAX_ITER 100 // maximum number of iterations

// Helper function: compute squared Euclidean distance
static double dist2(double *a, double *b, int dim) {
    double d = 0.0;
    for (int i = 0; i < dim; i++)
        d += (a[i] - b[i]) * (a[i] - b[i]);
    return d;
}

// Helper: compute mean for a given cluster
static void compute_mean(double *mean, double **points, int *assignments,
                         int cluster_id, int N, int dim) {
    int count = 0;
    for (int d = 0; d < dim; d++)
        mean[d] = 0.0;

    for (int i = 0; i < N; i++) {
        if (assignments[i] == cluster_id) {
            for (int d = 0; d < dim; d++)
                mean[d] += points[i][d];
            count++;
        }
    }

    if (count > 0) {
        for (int d = 0; d < dim; d++)
            mean[d] /= count;
    }
}

ppm_file kmeans(ppm_file image, int K, int init, int stop, int location) {
    ppm_file output_image = image; // copy metadata

    int width = image.cols;
    int height = image.rows;
    int N = width * height;
    int dim = (location == 0) ? 3 : 5; // RGB or RGB + XY

    // Allocate feature vectors
    double **points = malloc(N * sizeof(double *));
    for (int i = 0; i < N; i++)
        points[i] = malloc(dim * sizeof(double));

    // Fill feature vectors
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int idx = y * width + x;
            points[idx][0] = image.pixmap[idx].red;
            points[idx][1] = image.pixmap[idx].green;
            points[idx][2] = image.pixmap[idx].blue;
            if (dim == 5) {
                points[idx][3] = (double)x;
                points[idx][4] = (double)y;
            }
        }
    }

    // Initialize cluster centers
    double **centers = malloc(K * sizeof(double *));
    for (int k = 0; k < K; k++) {
        centers[k] = malloc(dim * sizeof(double));
        int rand_idx = rand() % N;
        memcpy(centers[k], points[rand_idx], dim * sizeof(double));
    }

    int *assignments = malloc(N * sizeof(int));
    for (int i = 0; i < N; i++)
        assignments[i] = -1;

    double prev_error = DBL_MAX;
    int iter = 0;

    while (iter < MAX_ITER) {
        iter++;

        // Step 1: Assign each pixel to nearest center
        for (int i = 0; i < N; i++) {
            double best_dist = DBL_MAX;
            int best_k = 0;
            for (int k = 0; k < K; k++) {
                double d = dist2(points[i], centers[k], dim);
                if (d < best_dist) {
                    best_dist = d;
                    best_k = k;
                }
            }
            assignments[i] = best_k;
        }

        // Step 2: Recompute cluster means
        for (int k = 0; k < K; k++)
            compute_mean(centers[k], points, assignments, k, N, dim);

        // Step 3: Compute total error
        double total_error = 0.0;
        for (int i = 0; i < N; i++)
            total_error += dist2(points[i], centers[assignments[i]], dim);

        // Step 4: Stop if converged (if stop == 1)
        if (stop == 1 && fabs(prev_error - total_error) < 1e-3) {
            printf("Converged after %d iterations.\n", iter);
            break;
        }

        prev_error = total_error;
    }

    // Step 5: Assign pixel colors by cluster center RGB
    for (int i = 0; i < N; i++) {
        int k = assignments[i];
        output_image.pixmap[i].red   = (unsigned char)centers[k][0];
        output_image.pixmap[i].green = (unsigned char)centers[k][1];
        output_image.pixmap[i].blue  = (unsigned char)centers[k][2];
    }

    // Free memory
    for (int i = 0; i < N; i++)
        free(points[i]);
    free(points);

    for (int k = 0; k < K; k++)
        free(centers[k]);
    free(centers);
    free(assignments);

    return output_image;
}
