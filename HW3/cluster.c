#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "cluster.h"

// get the cluster_centroid / normalized_cluster_centroid 
void get_cluster_centroid(double *data_array, int k, double *cluster_points, int nCols, double *normalized_data_array, double *normalized_cluster_points) {
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < nCols; j++) {
            *(cluster_points + i * nCols + j) = *(data_array + i * nCols + j);
            *(normalized_cluster_points + i * nCols + j) = *(normalized_data_array + i * nCols + j);
        }
    }
}

/* Assign data to each cluster_group, e.g. data[0][0] & data[0][1] belongs to first cluster point, 
then we put cluster_group[0][0] = 0 (index 0 means the first item in the array) */
// Original data part
void assign_cluster(int *cluster_group, double *data_array, double *cluster_points, int nRows, int nCols, int k) {
    for (int i = 0; i < nRows; i++) {
        double min = INFINITY;

        for (int j = 0; j < k; j++) {
            double distance = 0;

            int index = 0;

            for (int l = 0; l < nCols; l++) {
                distance += pow((*(data_array + i * nCols + l) - *(cluster_points + j * nCols + l)),2); // distance = x^2 + y^2
            }

            if (distance < min) {
                min = distance;
                index = j;
                *(cluster_group + i) = index;
            } 
        }
    }
}

// Normalized data part
void normalized_assign_cluster(int nRows, int nCols, int k, int *normalized_cluster_group, double *normalized_data_array, double *normalized_cluster_points) {
    for (int i = 0; i < nRows; i++) {
        double normalized_min = INFINITY;

        for (int j = 0; j < k; j++) {
            double normalized_distance = 0;

            int normalized_index = 0;

            for (int l = 0; l < nCols; l++) {
                normalized_distance += pow((*(normalized_data_array + i * nCols + l) - *(normalized_cluster_points + j * nCols + l)),2); // distance = x^2 + y^2
            }

            if (normalized_distance < normalized_min) {
                normalized_min = normalized_distance;
                normalized_index = j;
                *(normalized_cluster_group + i) = normalized_index;
            } 
        }
    }
}

// get the new cluster points
void get_new_cluster_points(double *data_array, int *cluster_group, double *cluster_points, int nRows, int nCols, int k, double *old_cluster_points) {

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < nCols; j++) {
            *(old_cluster_points + i * nCols + j) = *(cluster_points + i * nCols + j);
        }
    }

    for (int l = 0; l < nCols; l++) {
        for (int j = 0; j < k; j++) {
            double total = 0;
            int len = 0;

            for (int i = 0; i < nRows; i++) {
                if (*(cluster_group + i) == j) {
                    total += *(data_array + i * nCols + l);
                    len += 1;
                }
            }

            if (len != 0) {
                *(cluster_points + j * nCols + l) = total/len;
            }
        }
    }

    // check old and new cluster
    printf(" check old and new cluster points: \n");
    printf(" ==============================================\n");
    printf("        old                  new\n");
    for (int a = 0; a < k; a++) {
        for (int b = 0; b < nCols; b++) {
            printf(" %.2f ", *(old_cluster_points + a * nCols + b));
        }
        for (int c = 0; c < nCols; c++) {
            printf(" %.2f ", *(cluster_points + a * nCols + c));
        }
        printf("\n");
    }
    printf(" ==============================================\n");

    // check RMSE
    printf("Check for RMSE : \n");
    printf(" ==============================================\n");
    double sum = 0;
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < nRows; j++) {
            double dist = 0;
            int index_of_cluster_group = *(cluster_group + j);

            if (index_of_cluster_group == i) {
                // dist += sqrt(pow((*(data_array + j * nCols + 0) - *(cluster_points + index_of_cluster_group * nCols + 0)),2) + pow((*(data_array + j * nCols + 1) - *(cluster_points + index_of_cluster_group * nCols + 1)),2));
                // printf("%f \n", dist);
                for (int l = 0; l < nCols; l++) {
                    dist += pow((*(data_array + j * nCols + l) - *(cluster_points + index_of_cluster_group * nCols + l)),2);
                }
            }
            sum += sqrt(dist);
        }
    }

    // printf("Sum : %f \n", sum);

    double avg = sum/nRows;
    double rmse = sqrt(avg);
    printf("RMSE result : %f \n", rmse);
    printf(" ==============================================\n");
}

// get the new normalized cluster points
void get_new_normalized_cluster_points(int nRows, int nCols, int k, double *normalized_data_array, int *normalized_cluster_group, double *normalized_cluster_points, double *old_normalized_cluster_points) {

    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            *(old_normalized_cluster_points + i * nCols + j) = *(normalized_cluster_points + i * nCols + j);
        }
    }

    for (int l = 0; l < nCols; l++) {
        for (int j = 0; j < k; j++) {
            double normalized_total = 0;
            int normalized_len = 0;

            for (int i = 0; i < nRows; i++) {
                if (*(normalized_cluster_group + i) == j) {
                    normalized_total += *(normalized_data_array + i * nCols + l);
                    normalized_len += 1;
                }
            }

            if (normalized_len != 0) {
                *(normalized_cluster_points + j * nCols + l) = normalized_total/normalized_len;
            }
        }
    }

    // check old and new cluster
    printf(" check old and new cluster points: \n");
    printf(" ==============================================\n");
    printf("        old                  new\n");
    for (int a = 0; a < k; a++) {
        for (int b = 0; b < nCols; b++) {
            printf(" %.2f ", *(old_normalized_cluster_points + a * nCols + b));
        }
        for (int c = 0; c < nCols; c++) {
            printf(" %.2f ", *(normalized_cluster_points + a * nCols + c));
        }
        printf("\n");
    }
    printf(" ==============================================\n");

    // check RMSE
    printf("Check for RMSE : \n");
    printf(" ==============================================\n");
    double sum = 0;
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < nRows; j++) {
            double dist = 0;
            int index_of_cluster_group = *(normalized_cluster_group + j);

            if (index_of_cluster_group == i) {
                // dist += sqrt(pow((*(normalized_data_array + j * nCols + 0) - *(normalized_cluster_points + index_of_cluster_group * nCols + 0)),2) + pow((*(normalized_data_array + j * nCols + 1) - *(normalized_cluster_points + index_of_cluster_group * nCols + 1)),2));
                for (int l = 0; l < nCols; l++) {
                    dist += pow((*(normalized_data_array + j * nCols + l) - *(normalized_cluster_points + index_of_cluster_group * nCols + l)),2);
                }
            }
            sum += sqrt(dist);
        }
    }

    // printf("Sum : %f \n", sum);

    double avg = sum/nRows;
    double rmse = sqrt(avg);
    printf("RMSE result : %f \n", rmse);
    printf(" ==============================================\n");
}

// return final clusters after iteration, max iter = 5 or if the distance < ...
void final_cluster(int iter, int *cluster_group, double *data_array, double *cluster_points, int nRows, int nCols, int k, double *normalized_data_array, int *normalized_cluster_group, double *normalized_cluster_points, double *old_cluster_points, double *old_normalized_cluster_points) {
    
    // First, get initial centroid points
    get_cluster_centroid(data_array, k, cluster_points, nCols, normalized_data_array, normalized_cluster_points);
    
    printf("\n The initial cluster points for original data array (data_array): \n");
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < nCols; j++) {
            printf(" %.2f ", *(cluster_points + i * nCols + j));
        }
        printf("\n");
    }
    printf("\n The initial cluster points for normalized data array (normalized_data_array): \n");
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < nCols; j++) {
            printf(" %.2f ", *(normalized_cluster_points + i * nCols + j));
        }
        printf("\n");
    }

    // Second, iterate, assign to cluster group and get new centroid points
    // Original data part
    int iter_count = 0; 
    for (int i = 0; i < iter; i++) {

        // Assign to cluster group
        assign_cluster(cluster_group, data_array, cluster_points, nRows, nCols, k);
        
        if (i == 0) {
            printf(" The Original Cluster Group index sample: \n");
            int num = 0;
            for (int a = 0; a < 10; a++) {
                printf("%d \n", *(cluster_group + a));
                num += 1;
            }
            // printf("Length of cluster group : %d \n", num);
        }

        // Get new centroid points
        get_new_cluster_points(data_array, cluster_group, cluster_points, nRows, nCols, k, old_cluster_points);

        // printf("\n The new cluster points: \n");
        // printf(" =================================================\n");
        // for (int s = 0; s < k; s++) {
        //     for (int t = 0; t < nCols; t++) {
        //         printf(" %.2f ", *(cluster_points + s * nCols + t));
        //     }
        //     printf("\n");
        // }
        // printf(" =================================================\n");

        // if cluster points == old cluster points, break
        int check = 0;

        for (int p = 0; p < k; p++) {
            for (int j = 0; j < nCols; j++) {
                if (*(cluster_points + p * nCols + j) != *(old_cluster_points + p * nCols + j)) {
                    check = 1;
                    break;
                }
            }

            if (check == 1) {
                break;
            }
        }

        if (check != 1) {
            break;
        }
        printf(" Now iterate %d times. \n", (i+1));
        iter_count++;
    }
    
    // Normalized data part
    int normalized_iter_count = 0;
    for (int i = 0; i < iter; i++) {

        // Assign to cluster group
        normalized_assign_cluster(nRows, nCols, k, normalized_cluster_group, normalized_data_array, normalized_cluster_points);
        
        if (i == 0) {
            printf(" The Normalized Cluster Group index sample: \n");
            int num = 0;
            for (int a = 0; a < 10; a++) {
                printf("%d \n", *(normalized_cluster_group + a));
                num += 1;
            }
            // printf("Length of cluster group : %d \n", num);
        }

        // Get new centroid points
        get_new_normalized_cluster_points(nRows, nCols, k, normalized_data_array, normalized_cluster_group, normalized_cluster_points, old_normalized_cluster_points);
        
        // printf("\n The new normalized cluster points: \n");
        // printf(" =================================================\n");
        // for (int s = 0; s < k; s++) {
        //     for (int t = 0; t < nCols; t++) {
        //         printf("     %.2f       ", *(normalized_cluster_points + s * nCols + t));
        //     }
        //     printf("\n");
        // }
        // printf(" =================================================\n");

        // if normalized cluster points == old normalized cluster points, break
        // if cluster points == old cluster points, break
        int normalized_check = 0;

        for (int p = 0; p < k; p++) {
            for (int j = 0; j < nCols; j++) {
                if (*(normalized_cluster_points + p * nCols + j) != *(old_normalized_cluster_points + p * nCols + j)) {
                    normalized_check = 1;
                    break;
                }
            }

            if (normalized_check == 1) {
                break;
            }
        }

        // check whether there are different values in the old and new cluster points
        if (normalized_check != 1) {
            // if all cluster points matches, break
            break;
        }
        printf(" Now iterate %d times. \n", (i+1));
        normalized_iter_count++;
    }

    // print the final iteration times
    printf(" The Final iteration times : \n");
    printf(" ============================================== \n");
    printf(" Original iteration        Normalized iteration\n");
    printf("         %d                           %d\n", iter_count, normalized_iter_count);
    printf(" ============================================== \n");
}

// Creating the normalized data 
void create_normalized_data(double *normalized_data_array, double *avg_array, double *std_array, double *data_array, int nRows, int nCols) {
    // Assign the mean value of each item in the original data sets into avg_array
    for (int i = 0; i < nCols; i++) {
        double sum = 0;

        for (int j = 0; j < nRows; j++) {
            sum += *(data_array + j * nCols + i);
        }

        *(avg_array + i) = sum/nRows;
        printf("Mean : %f \n", *(avg_array + i));
    }

    // Assign the standard deviation value of each item in the original data sets into std_array
    for (int i = 0; i < nCols; i++) {
        double square_sum = 0;

        for (int j = 0; j < nRows; j++) {
            square_sum += pow((*(data_array + j * nCols + i) - *(avg_array + i)), 2);
        }

        *(std_array + i) = sqrt(square_sum/nRows);
        printf("Standard deviation : %f \n", *(std_array + i));
    }
     
    // Assign the normalized data into normalized_data_array
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            *(normalized_data_array + i * nCols + j) = (*(data_array + i * nCols + j) - *(avg_array + j))/(*(std_array + j));
        }
    }

    // print the normalized
    // printf("Normalized sample data : \n");
    // for (int i = 0; i < 10; i++) {
    //     for (int j = 0; j < nCols; j++) {
    //         printf(" %f ", *(normalized_data_array + i * nCols + j));
    //     }
    //     printf("\n");
    // }
}






