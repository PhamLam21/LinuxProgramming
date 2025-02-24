.PHONY: rule1 rule2 rule3

# := phép gắn trực tiếp
# = $(biến) phép gắn đệ qui khi biến thay đổi thì biến được gắn cũng thay đổi
# $(biến) lấy ra giá trị của biến
# ?= kiếm tra biến được gắn có giá trị chưa nếu chưa thì gắn giá trị cho biến 
var := "var"
var3 := "var3"

include abcd.mk 
# Gắn toàn bộ file abcd.mk vào vị trí khai báo

var1 = $(var)
var2 := $(var)
var3 ?= $(var)

var := "changed"


rule3:
	@echo "$(var1)"
	@echo "$(var2)"
	@echo "$(var3)"

rule1:
	echo "Hi im rule 1"

rule2:
	@echo "Hi im rule 2"


# @ dùng cho debug xóa @ sẽ hiển thị cả câu lệnh
# có 3 cách viết makefile: Makefile makefile abc.mk độ ưu tiên giảm từ trái sang