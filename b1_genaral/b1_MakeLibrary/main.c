#include <stddef.h>
#include "inc/input.h"
#include "inc/output.h"

char* sex[3] = {"nam", "nu", "khong xac dinh"};

/* Khởi tạo biến head cho danh sách liên kết */
SV_node_t *head = NULL; 

int main(void)
{
    Create_Node();
    Create_Node();
    output();
    Free_Nodes();
    return 0;
}
