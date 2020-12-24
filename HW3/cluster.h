#ifndef MY_ClUSTER_H
#define MY_ClUSTER_H

// get the cluster_centroid
void get_cluster_centroid(double *data_array, int k, double *cluster_points, int nCols, double *normalized_data_array, double *normalized_cluster_points);

/* Assign data to each cluster_group, e.g. data[0][0] & data[0][1] belongs to first cluster point, 
then we put cluster_group[0][0] = 0 (index 0 means the first item in the array) */
// Original data part
void assign_cluster(int *cluster_group, double *data_array, double *cluster_points, int nRows, int nCols, int k);

// Normalized data part
void normalized_assign_cluster(int nRows, int nCols, int k, int *normalized_cluster_group, double *normalized_data_array, double *normalized_cluster_points);

// get the new cluster points
void get_new_cluster_points(double *data_array, int *cluster_group, double *cluster_points, int nRows, int nCols, int k, double *old_cluster_points);

// get the new normalized cluster points
void get_new_normalized_cluster_points(int nRows, int nCols, int k, double *normalized_data_array, int *normalized_cluster_group, double *normalized_cluster_points, double *old_normalized_cluster_points);

// iterate to get the final clusters after iteration, e.g. max iter = 5 or if the distance < ...
void final_cluster(int iter, int *cluster_group, double *data_array, double *cluster_points, int nRows, int nCols, int k, double *normalized_data_array, int *normalized_cluster_group, double *normalized_cluster_points, double *old_cluster_points, double *old_normalized_cluster_points);

// Creating the normalized data 
void create_normalized_data(double *normalized_data_array, double *avg_array, double *std_array, double *data_array, int nRows, int nCols);

#endif