#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define EXIT "exit"
#define MKDISK "mkdisk"

struct Partition {
    char part_status[1];
    char part_type[1];
    char part_fit[1];
    int part_start;
    int part_size;
    char part_name[16];
};

struct MasterBootRecord {
    int mbr_tamano;
    char mbr_fecha_creacion[10];
    int mbr_disk_signature;
    char disk_fit[1];
    struct Partition *mbr_partition_1;
    struct Partition *mbr_partition_2;
    struct Partition *mbr_partition_3;
    struct Partition *mbr_partition_4;
};

struct ExtendedBootRecord {
    char part_status[1];
    char part_fit[1];
    int part_start;
    int part_size;
    int part_next;
    char part_name[16];
};

int main() {
    struct MasterBootRecord masterBootRecord;
    struct ExtendedBootRecord extendedBootRecord;
    struct Partion partion;
    return 0;
}