Directory structure:

- fork    : create new process with fork().
- arg-env : basic linux command line arguments.
 
*safe-fork: chống tạo ra zombie process

*normally termination: system call _exit() , function _exit

*abnormarlly termination: kill

*pid_t wait() -> trả về process đã kết thúc 
    return 0; -> exit(0);
    retval = wait(&status);

*pid_t waitpid(pid_t pid, int* status, NULL) -> đợi 1 process cụ thể 
    pid > 1 đợi 1 process cụ thể
    pid = -1 giống wait

*wait-waitpid -> tra ve gia tri exit

*orphane: when parent process dead before chill process dead

In each folder, perform the following instructions bellow:

- make: build excutable file.
- make clean: clean everything.

Cmd:
*top: tất cả các tiến trình đang chạy 

*ps aux | grep "name" : tra thông tin tiến trình "name" 

*argc : số lượng đối số chuyền vào 
    vd: ls -a -h -> argc = 3

*argv[]: lưu string 
    vd: ls -a -h -> argv[0] = ls -> argv[1] = -a -> ...

Memory layout:
1. Text segment: Chứa các chỉ lệnh ngôn ngữ máy (machine-language)
 -> Read-only
2. Initialized data segment: Chứa các biến global và static đã khởi tạo tường minh (flash)
 -> Read, write
3. Uninitialized data segment: Chứa các biến global và static không được khởi tạo tường minh (bss -> ram)
 -> Read, write   
4. Stack segment: Chứa các biến cục bộ
 -> Read, write
5. Heap segment: Cấp phát động 
 -> Read, write

Mỗi hàm sẽ được cấp 1 stack frame
