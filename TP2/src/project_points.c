#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <math.h>

#include "Utils/imageFormationUtils.h"
#include "Utils/Util.h"


int main(int argc, char *argv[])
{
    if (argc != 16)
    {
        printf("\nUsage: %s off_file_name.off "
                            "f width height u_0 v_0 alpha_u alpha_v "
                            "gama beta alpha T_x T_y T_z "
                            "use_depth\n",
         argv[0]);
        exit(0);
    }

    // Reading the input parameters
    char* off_filename = argv[1];
    // Intrinsics
    float f = atof(argv[2]);

    int width = atoi(argv[3]);
    int height = atoi(argv[4]);

    float u_0 = atof(argv[5]);
    float v_0 = atof(argv[6]);

    float alpha_u = atof(argv[7]);
    float alpha_v = atof(argv[8]);

    // Extrinsics
    float gama = atof(argv[9]);
    float beta = atof(argv[10]);
    float alpha = atof(argv[11]);
    float T_x = atof(argv[12]);
    float T_y = atof(argv[13]);
    float T_z = atof(argv[14]);

    // Use depth map
    int use_depth = atoi(argv[15]);

    // The output filename is generated from the input
    char output_filename[512];
    sprintf(output_filename, "results/%c_%.0f_%d_%d_%.1f_%.1f_%.2f_%.2f_%.1f_%.1f_%.1f_%.1f_%.1f_%.1f_%d.ppm",
            off_filename[7], // hack: use first letter of model to create output (f or h in this TP)
            f, width, height, u_0, v_0, alpha_u, alpha_v,
            gama, beta, alpha, T_x, T_y, T_z,
            use_depth);

    // Start processing
    // Read the pointcloud
    struct point3d *points;
    int N_v = 0;
    points = readOff(off_filename, &N_v);

    // and center it
    centerThePCL(points, N_v);
    float *result = malloc(sizeof(float)*16);
    computeTrans(gama,beta, alpha, T_x, T_y, T_z, result);

    for (int i = 0; i<16; i++){
        printf("%f ", result[i]);
    }
    // allocate output image and initialize with white colors
    ppm_file image;
    image.rows = height;
    image.cols = width;
    image.maxval = 255;
    image.magic_number = '6';

    // Allocate what you think you need

    image.pixmap = (pixel*)malloc(sizeof(pixel)*image.rows *image.cols);
    float* distances = (float*)malloc(sizeof(float)*image.rows * image.cols);
    for(int i = 0; i < image.rows*image.cols; ++i){
      distances[i] = FLT_MAX; // initialising distance array to big values 
    }

    // Print if depth buffer is being used
    if (use_depth) {
        printf("Using Depth Buffer\n");
    }

    int orthogonal = 0;
    if (f==0) {
        printf("Using Orthogonal camera\n");
        orthogonal = 1;
    }

    // Go through the point-cloud
    for (int i = 0; i < N_v; i++) {

        struct point3d p;

        p.x = points[i].x*result[0] + points[i].y*result[1] + points[i].z*result[2] + result[3];
        p.y = points[i].x*result[4] + points[i].y*result[5] + points[i].z*result[6] + result[7];
        p.z = points[i].x*result[8] + points[i].y*result[9] + points[i].z*result[10] + result[11];

        points[i].x = p.x;
        points[i].y = p.y;
        points[i].z = p.z;

        float x_cam;
        float y_cam;

        // Project the point
        if (orthogonal) {
            // implement orthogonal projection here

            x_cam = points[i].x;
            y_cam = points[i].y;

        } else {
            // implement pinhole projection here

            x_cam = (points[i].x * f) / (points[i].z + f);
            y_cam = (points[i].y * f) / (points[i].z + f);

        }

        int u_cam = (int)(x_cam / alpha_u + u_0);
        int v_cam = (int)(y_cam / alpha_v + v_0);

        // Check if the point is inside the image
        if (u_cam < 0 || u_cam >= image.cols || v_cam < 0 || v_cam >= image.rows)
        continue;

        // Do something about the depth
        if (use_depth && points[i].z >= distances[v_cam * image.cols + u_cam])
        continue;

        // allow us to only take into account the points closest to the camera in case of overlapping points that are further away 
        distances[v_cam * image.cols + u_cam] = points[i].z; 

        // If ok, update the image pixel color

        image.pixmap[v_cam * image.cols + u_cam].red = points[i].r;
        image.pixmap[v_cam * image.cols + u_cam].blue = points[i].b;
        image.pixmap[v_cam * image.cols + u_cam].green = points[i].g;
    }

    // Save the image
    printf("Writting output file %s", output_filename);
    write_ppm(image, output_filename);
}