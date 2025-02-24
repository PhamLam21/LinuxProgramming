#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <malloc.h>
#include "../inc/input.h"

void Create_Node(void)
{
    SV_node_t *ptr_NewNode = NULL;
    static uint8_t count = 0;
    count++;
    printf("Please enter the information for student %d\r\n", count);
    
    ptr_NewNode = (SV_node_t*) malloc(sizeof(SV_node_t));
    if(ptr_NewNode != NULL)
    {
        int temp_age;
        
        printf("Moi nhap ten sinh vien: \r\n");
        /* Sử dụng %19[^\n] để giới hạn số ký tự đọc vào */
        scanf("%19[^\n]%*c", ptr_NewNode->name);
        
        printf("Moi nhap gioi tinh: (0: nam , 1: nu, 2: khong xac dinh)\r\n");
        /* ép kiểu địa chỉ về int* nếu cần, hoặc có thể dùng biến tạm */
        scanf("%d%*c", (int *)&ptr_NewNode->sex);
        
        printf("Moi nhap mssv: \r\n");
        scanf("%d%*c", &ptr_NewNode->id_Uni);
        
        printf("Moi nhap ten truong: \r\n");
        scanf("%29[^\n]%*c", ptr_NewNode->university);
        
        printf("Moi nhap tuoi: \r\n");
        scanf("%d%*c", &temp_age);
        ptr_NewNode->age = (unsigned char) temp_age;
        
        /* Chèn node mới vào đầu danh sách */
        ptr_NewNode->pNext = head;
        head = ptr_NewNode;
    }
    else
    {
        printf("Can't create new node !!!\r\n");
    }
    
}
void Free_Nodes(void)
{
    SV_node_t *current = head;
    SV_node_t *next = NULL;
    
    while(current != NULL)
    {
        next = current->pNext;
        free(current);
        current = next;
    }
    
    head = NULL;  // Đặt lại head sau khi giải phóng
}
