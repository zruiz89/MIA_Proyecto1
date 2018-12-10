#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define EXIT "exit"
#define MKDISK "mkdisk"

struct Partition {
    char part_status;
    char part_type;
    char part_fit;
    int part_start;
    int part_size;
    char part_name[16];
};

struct MasterBootRecord {
    int mbr_tamano;
    char mbr_fecha_creacion[16];
    int mbr_disk_signature;
    char disk_fit;
    struct Partition mbr_partition_1;
    struct Partition mbr_partition_2;
    struct Partition mbr_partition_3;
    struct Partition mbr_partition_4;
};

struct ExtendedBootRecord {
    char part_status;
    char part_fit;
    int part_start;
    int part_size;
    int part_next;
    char part_name[16];
};

void createDisk(char *creationDate, char fitType, char *path, int size, char unit) {
    struct MasterBootRecord masterBootRecord;
    strcpy(masterBootRecord.mbr_fecha_creacion, creationDate);
    masterBootRecord.disk_fit = fitType;

    if (tolower(unit) != 'o') {
        switch(tolower(unit)) {
            case 'k':
                size *= 1000;
                printf("Unidad: Kilobytes.\n");
                break;
            case 'm':
                size *= 1000*1000;
                printf("Unidad: Megabytes.\n");
                break;
        }
    }

    masterBootRecord.mbr_tamano = size;
    
    FILE *disk = fopen(path, "w+b");
    
    if (disk != NULL) {
        fseek(disk, 0, SEEK_SET);
        fwrite(&masterBootRecord, sizeof(masterBootRecord), 1, disk);
        fseek(disk, masterBootRecord.mbr_tamano - 4, SEEK_SET);
        int zero = 0;
        fwrite(&zero, 4, 1, disk);
    }
    fclose(disk);
}

void createPrimaryPartition(char *name, char fitType, char *path, int size, char unit) {
    //Creamos la particion primary
    struct Partition partition;
    partition.part_status = '1';
    partition.part_type  = 'P';
    partition.part_start = 140;
    partition.part_size = size; //Convertir comparando con unit
    strcpy(partition.part_name, name);
    struct MasterBootRecord mbr;
    FILE *disk = fopen(path, "rb+");
    
    if (disk != NULL) {
        //Leemos el mbr del disco duro..
        fseek(disk, 0, SEEK_SET);
        fread(&mbr, sizeof(mbr), 1, disk);
        //Imprimiendo la fecha solo como prueba de que estamos leyendo bien el archivo
        printf("leyendo mbr fecha:%s",mbr.mbr_fecha_creacion);
        //Ahora el mbr leido del disco, agregamos la particion 
        //Como prueba se coloco en la primera particion...pero esto debe cambiar
        mbr.mbr_partition_1 = partition;
        fseek(disk, 0, SEEK_SET);
        fwrite(&mbr, sizeof(mbr), 1, disk);
    }
    fclose(disk);
}


void createPartition(char *name, char fitType, char *path, int size, char type, char unit) {

    createPrimaryPartition(name,fitType,path,size,unit);
    // switch(tolower(type)) {
    //     case 'p':
    //         break;
    //     case 'm':
    //         break;
    //     case 'm':
    //         break;
    //     default 'm':
    //         break;
    // }
}




int main() {
    printf("Partition size: %zu\n", sizeof(struct Partition));
    printf("MasterBootRecord size: %zu\n", sizeof(struct MasterBootRecord));
    printf("ExtendedBootRecord size: %zu\n", sizeof(struct ExtendedBootRecord));
    createDisk("2018-12-12 14:15", 'b', "/home/estuardo/GitHub/MIA_Proyecto1/disk1.dsk", 200, 'k');
    createPartition("hola",'W',"/home/estuardo/GitHub/MIA_Proyecto1/disk1.dsk",200, 'P', 'K');
    return 0;
}