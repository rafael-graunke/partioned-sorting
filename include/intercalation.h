#ifndef _INTERCALATION_H_
#define _INTERCALATION_H_

typedef int (*__min_fn_t) (const void *, FILE **files, int n);

void delete_partition(int last_partition);

int merge_product_files(int num_partitions);
int merge_product_final_files(int num_partition, int last_partition);

int merge_category_files(int num_partitions);
int merge_category_final_files(int num_partition, int last_partition);

int merge_session_files(int num_partitions);
int merge_session_final_files(int num_partition, int last_partition);


#endif