# LinuxProgramming
## General
### Makefile 
- Là một script có chứa các thông tin:
    - Cấu trúc một project
    - Các command line dùng để tạo-huỷ file
- Chương trình make sẽ đọc nội dung trong Makefile và thực thi nó
- Quản lý mã nguồn và xây dựng chương trình dựa trên cấu trúc mã nguồn của dự án 
- Đặt tên: Makefile, makefile, .mk 
- Tạo các rule thường sử dụng ví dụ: 
    - all: tạo ra file thực thi cuối
    - clean: xoá sạch các file đã build
- Cấu trúc của một rule trong Makefile:
```  
hellomake: hello.c main.c
    gcc -o hellomake hello.c main.c -I 
```  
- Sử dụng Makefile: 
    - make + rule
    - make không thì thực hiện rule đầu tiên trong Makefile
    - Nếu ngoài thư mục chứa Makefile có file trùng tên với rule dễ xảy ra lỗi: sử  dụng `.PHONY: rule1 rule2 ...` trong Makefile để liệt kê các rule ra tránh lỗi  
### 4 stage compiling C
- Pre-processor: Tiền xử lý -> xử lý các macro 
- Compilation: Dịch ra hợp ngữ
- Assembly: Dịch ra mã máy 0, 1
- Linking: Hợp với các thư viện ra file thực thi
### Static & Shared library
- Thư viện là một tập hợp các đoạn mã đuợc biên dịch sẵn để có thể sử dụng trong tương lai
- Được chia làm 2 loại:
    - Static lib (.a)
    - Shared lib (.so)
#### Static library  
- Các file thư viện sẽ được copy vào file thực thi tại thời điểm compile -> tăng kính thước chương trình thực thi -> nếu file thư viện thay đổi thì file thực thi cũng phải biên dịch lại
#### Shared library
- Các file thư viện sẽ được load vào trên ram khi link thì tất cả các file thực thi đều có thể chỉ đến thư viện (Dynamic lịking) -> không cần biên dịch lại file thực thi nếu thay đổi file thư viện
## File
- Linux quản lý tất cả mọi thứ như một file
- Sử dụng các system call để quản lý file: 
    - int open(const char *pathname, int flags, mode_t mode);
    - ssize_t read(int fd, void* buffer, size_t count);
    - ssize_t write(int fd, void* buffer, size_t count);
    - off_t lseek(int fd, off_t offset, int whence);
    - int close(int fd);
- System call: các cơ chế để bên user space gọi xuống phần kernel space
- Quản lý file qua ba bảng: fd, open, inode (1 inode chứa thông tin của 1 file)
- Cơ chế đọc ghi dữ liệu vào 1 file: ghi vào page cache rồi mới ghi vào hasd disk (sync: ghi file từ cache vào hd)
- Cache: Tác dụng làm tuổi thọ của bộ nhớ cao hơn (giảm số lần ghi trực tiếp vào bộ nhớ), đồng bộ tốc độ đọc ghi giữa các bên như CPU - RAM và từ RAM - HDD/Flash/SSD
### Đồng bộ/Bất đồng bộ
- Đồng bộ: các tác vụ được thực hiện tuần tự  
- Bất đồng bộ: một kỹ thuật cho phép thực hiện các tác vụ mà không cần phải chờ đợi tác vụ đó hoàn thành  
### Đồng bộ đọc/ghi file:
- flock(): Thông tin ghi vào i-node là trạng thái lock -> khoá toàn bộ file khi đang có truy cập -> tại 1 thời điểm chỉ có 1 tiến trình đọc/ghi  
    - LOCK_SH: chỉ đọc, chia sẻ việc đọc giữa các tiến trình
    - LOCK_EX: độc quyền với file này -> process có quyền đọc và ghi -> 1 tiến trình khác phải đợi tiến trình trên bỏ khoá  
    - LOCK_NB: Nếu không có khoá này thì 1 tiến trình truy cập vào 1 file đang bị 1 tiến trình khác độc quyền thì sẽ phải đợi đến khi tiến trình kia nhả khoá
- fcntl(): Thông tin ghi vào i-node là trạng thái lock, khu vực lock, tiến trình lock -> lock được từng khu vực của file -> nhiều tiến trình có thể đọc/ghi cùng 1 file mà không xung đột  
## Process
- Tiến trình là một chương trình đang được thực thi và sử dụng tài nguyên của hệ thống
- Process được định danh bằng 1 process ID (PID) nguyên dương, sử dụng lệnh `ps -aux` để kiểm tra các tiến trình đang chạy trong hệ thống  
- Tham số môi trường tham khảo trong b3_process/arg-env
### Memory layout
- Text segment: Chứa các chỉ lệnh ngôn ngữ máy (machine-language) -> Read-only
- Initialized data segment: Chứa các biến global và static đã khởi tạo tường minh (flash)-> Read, write
- Uninitialized data segment: Chứa các biến global và static không được khởi tạo tường minh (bss -> ram) -> Read, write   
- Stack&Heap segment : Chia sẻ cùng phân vùng nhớ -> Read, write
    - Stack: biến cục bộ 
    - Heap: Cấp phát động
- Argv, environ: tham số môi trường
- Kernel  
### Virtual memory:  
Bộ nhớ ảo (virtual memory) là một kỹ thuật quản lý bộ nhớ trong hệ điều hành hiện đại, cho phép máy tính "ảo hóa" bộ nhớ vật lý (RAM) thành một không gian bộ nhớ liên tục và rộng lớn hơn so với bộ nhớ vật lý sẵn có  
- Hệ điều hành sử dụng bảng trang (page table) để chuyển đổi địa chỉ ảo (virtual addresses) mà chương trình sử dụng thành địa chỉ vật lý (physical addresses) trong RAM 
- Page table: bảng ánh xạ vd page 0 -> frame 1, page 1 -> frame 3 ...
- Khi một trang dữ liệu không nằm trong RAM (do bị swap ra ổ đĩa), hệ điều hành sẽ thực hiện cơ chế gọi là "paging" hay "swapping" để đưa dữ liệu cần thiết về RAM và chuyển dữ liệu không cần thiết xuống ổ đĩa  
- Cơ chế virtual memory: Quản lý theo frame, chia nhr process load lên frame còn trống
### Exec-family: 
- execl("/bin/ls", "ls", "-l", "-a", "-h", NULL) -> chạy lệnh ls -lah
- execl("/bin/ls", "ls", "-l", "-a", NULL) -> chạy lệnh ls -la
- Chạy 1 tiến trình trong 1 tiến trình đang chạy
### Thao tác với process
#### Tạo process
- Sử dụng system call `int fork()` từ 1 tiến trình cha để tạo ra tiến trình con 
- Tiến trình con là bản sao của tiến trình cha (Toàn bộ dữ liệu trong tiến trình cha trước lệnh fork() thì tiến trình con sẽ sao chép hết)
- Tiến trình init là tiến trình đầu tiên được chạy là cha của mọi tiến trình có pid = 1 
#### Kết thúc tiến trình
- Kết thúc tiến trình bình thường: 1 tiến trình hoàn thành việc thực thi của nó bằng cách gọi system call `void _exit(int status)`
- Kết thúc bất thường: đang chạy thì kết thúc vd dùng command `kill`
#### Quản lý tiến trình con
- Sử dụng system call: `int wait(int* status)` trả về pid của tiến trình con kết thúc, khi gọi hàm wait() thì tiến trình cha sẽ block tại hàm đó đợi trả về  
- `pid_t waitpid(pid_t pid, int *status, int options)`: đợi giá trị trả về của 1 pid cụ thể  
#### Tiến trình orphane và zombie
- Orphane: tiến trình cha kết thúc trước tiến trình con -> tiến trình con sẽ chuyển cho tiến trình init pid = 1 quản lý
- Zombie: tiến trình con kết thúc trước tiến trình cha trước hàm wait để nhận giá trị trả về từ tiến trình con để  tiến trình con kết thúc -> sinh ra tiến trình con sẽ không kill được và không được hoàn toàn giải phóng khỏi hệ thống -> nếu sinh nhiều zombie process pid bị đầy ảnh hưởng đến việc tạo process mới
- Ngăn chặn zombie process:
    - Sử dụng wait(): Luôn gọi wait() ở tiến trình cha
    - Sử dụng signal SIGCHLD: Tiến trình con kết thúc, một tín hiệu SIGCHLD sẽ được gửi tới tiến trình cha của nó  
## Thread
- Là một lightweight process có thể được quản lý độc lập bởi một bộ lập lịch
- Tương tự như process, thread được tạo ra với mục đích xử lý đồng thời nhiều công việc cùng một lúc (mutil-task)
- 1 hệ thống có nhiều process, 1 process có nhiều thread
- Định danh trong process bằng thread id
- Nếu 1 thread bị block thì các thread khác vẫn hoạt động bình thường
- 1 thread được tạo sẽ nằm trong stack segment
### So sánh với process
- Context swiching(chuyển trạng thái): thread nhanh hơn vì nhẹ hơn
- Trao đổi dữ liệu, giao tiếp giữa 2 thread dễ hơn vì nằm trong cùng 1 vùng nhớ  
- Crashed: 
    - Các process khác vẫn hoạt động bình thuờng
    - Các thread khác cũng bị crash
- ID: 
    - process id: duy nhất trong toàn hệ thống
    - thread id: duy nhất trong process
### Các hàm sử dụng thread
- Hàm về thread id: 
    - pthread_self() <=> getpid()
    - pthread_equal() -> so sánh 2 thread id
- Tạo mới: `int pthread_create(pthread_t *threadID, const pthread_attr_t *attr, void*(*start)(void*), void *arg);`
    - Đối số đầu: 1 tt mới được gọi thành công, đối số đầu tiên sẽ giữ thread ID của thread mới được tạo
    - Đối số 2: thường là NULL
    - Đối số 3: 1 con hàm trỏ, mỗi 1 thread sẽ chạy riêng 1 func, địa chỉ của func sẽ được truyền vào đối số thứ 3 để linux biết bđ chạy từ đâu
    - Đối số 4: truyền dữ liệu bất kỳ để xử lý hàm
- Kết thúc thread:
    - pthread_exit(void *retval);
    - pthread_cancel(pthread_t pthread);
- Dọn dẹp và thu về giá trị kết thúc của thread:
    - pthread_join();
    - pthread_detach(pthread_t pthread); -> tu dong don dep thread  
### Đồng bộ dữ liệu
#### Mutex
- Sử dụng khoá khi 1 thread sử dụng dữ liệu
- Cấp phát tĩnh: pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
- Cấp phát động: int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
    - Giải phóng: pthread_mutex_destroy()  
- Lock: pthread_mutex_lock();
- Unlock: pthread_mutex_unlock();
#### Condition variables
- Biến gửi tín hiệu thông báo để 2 thread làm việc với nhau  
- Khai báo biến:
    - Tĩnh: pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
    - Động: int pthread_cond_init(pthread_cond_t *cond, const pthread_condattr_t *attr);
    - Giải phóng khi khai báo động: pthread_cond_destroy();  
- Sử dụng:
    - pthread_cond_signal(pthrea_cond_t *cond); -> gửi tín hiệu nhả mutex cho thread khác sử dụng
    - pthread_cond_wait(pthrea_cond_t *cond); -> đợi tín hiệu từ cond_signal để lấy khoá mutex và thực hiện chương trình  
### Tool debug
- gdb, valgrind, strace