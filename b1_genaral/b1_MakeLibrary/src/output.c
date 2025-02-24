#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "../inc/output.h"

void output(void)
{
    SV_node_t* ptr_temp = NULL;
    for(ptr_temp = head; ptr_temp != NULL; ptr_temp = ptr_temp->pNext)
    {
        printf("Ten: %s\r\n", ptr_temp->name);
        printf("Gioi tinh: %s\r\n", sex[ptr_temp->sex]);
        printf("MSSV: %d\r\n", ptr_temp->id_Uni);
        printf("Truong: %s\r\n", ptr_temp->university);
        printf("Tuoi: %d\r\n", ptr_temp->age);
    }
}
