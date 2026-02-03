# Interrupt Handling with libgpiod on Raspberry Pi (Yocto Project)

Dự án này là một ví dụ minh họa cách xử lý ngắt (Interrupt) GPIO trên Raspberry Pi 4 sử dụng thư viện `libgpiod` trong môi trường **Yocto Project**.

##  Giới thiệu
Các thư viện Linux GPIO hiện đại như `libgpiod` thường hoạt động theo cơ chế **blocking** (chờ đợi sự kiện). Điều này gây khó khăn khi muốn xử lý ngắt mà không làm treo chương trình chính.

Giải pháp của dự án này là sử dụng **Multithreading (pthread)**:
* **Main Thread:** Chạy các tác vụ chính (ví dụ: in log định kỳ, xử lý dữ liệu...).
* **Interrupt Thread:** Chạy song song, sử dụng `gpiod_line_event_wait()` để lắng nghe sự kiện từ phần cứng mà không ảnh hưởng đến luồng chính.

##  Phần cứng yêu cầu
* **Board:** Raspberry Pi 3b(hoặc tương đương).
* **Nút nhấn (Button):** Kết nối với **GPIO 17**.
* **Debug:** Module USB-to-TTL (CP2102) kết nối vào cổng UART (GPIO 14, 15).
##  link tài liệu đi kèm 
https://docs.google.com/document/d/1V5N0JOUkMtZXlG4FXpyfuZYMr2KX70fu/edit

##  link video demo
https://www.youtube.com/watch?v=fsdjQryTgJk


##  Cấu trúc dự án
Dự án bao gồm mã nguồn C và Recipe cho Yocto để cross-compile ứng dụng.

```text
/
├── button_int.c       # Mã nguồn chương trình chính
├── button-int_1.0.bb  # Bitbake recipe để build app
└── README.md          # Tài liệu hướng dẫn
