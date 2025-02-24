#ifndef SINH_VIEN_H
#define SINH_VIEN_H

/* Mảng chứa các chuỗi thể hiện giới tính */
extern char* sex[3];

/* Định nghĩa enum cho giới tính */
typedef enum {
    nam,
    nu,
    khong_xac_dinh
} sex_t;

/* Định nghĩa struct sinh viên */
typedef struct sinh_vien {
    char name[20];
    sex_t sex;
    int id_Uni;
    char university[30];
    unsigned char age;
    struct sinh_vien *pNext;
} SV_node_t;

/* Con trỏ đầu danh sách liên kết */
extern SV_node_t *head;

#endif // SINH_VIEN_H
