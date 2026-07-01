## Tên ứng dụng
Hệ thống Quản lý Vé Xe buýt Giảm thiểu Ô nhiễm Môi trường (Bus Ticket Management System).

## Cấu trúc dữ liệu sử dụng
- BST: dùng để quản lý, lưu trữ danh sách hành khách đã có ghế... vì giúp tối ưu hóa tốc độ tra cứu hành khách theo ID với độ phức tạp trung bình $O(\log n)$.
- Queue: dùng để quản lý danh sách hành khách đang chờ khi xe đã hết chỗ... vì cấu trúc hàng đợi ưu tiên (`priority_queue`) giúp tự động sắp xếp thứ tự ưu tiên từ cao xuống thấp (Người già > Bà bầu > Phổ thông).
- Mảng 2 chiều (`seatMap`): dùng để lưu trữ sơ đồ ghế ngồi xe buýt... vì giúp trực quan hóa trạng thái trống `[O]` hoặc đã đặt `[X]` của từng vị trí ghế theo hàng và cột.
- Stack: dùng để lưu trữ lịch sử giao dịch (`Transaction`)... vì cơ chế LIFO giúp hệ thống dễ dàng theo vết các thao tác đặt/hủy vé để phục vụ tính năng hoàn tác.

## Compile và chạy
g++ -std=c++17 src/main.cpp src/functions.cpp -o app && ./app

## Chức năng
1. Xem sơ đồ ghế ngồi theo thời gian thực.
2. Đăng ký chỗ ngồi (Cấp vé miễn phí hoặc đưa vào hàng đợi ưu tiên khi hết chỗ).
3. Hủy cho (Tự động đôn người có mức ưu tiên cao nhất trong hàng đợi vào thế chỗ).
4. Tra cứu hành khách theo Ma/CCCD dựa trên cấu trúc cây BST.
5. In toàn bộ danh sách hành khách đã có ghế (được sắp xếp theo ID tăng dần).
6. Thống kê số lượng ghế, ngân sách thành phố trợ giá và lượng CO2 tiết kiệm được.

## Test cases
Mô tả 5 test case chính.
- **Test case 1**: Đặt vé thành công khi xe còn chỗ (Hệ thống báo cấp vé thành công, xếp vào ghế trống đầu tiên và chuyển trạng thái sơ đồ sang `[X]`).
- **Test case 2**: Xe hết chỗ, hệ thống tự động đẩy khách hàng mới vào hàng đợi ưu tiên dựa theo diện đối tượng (Mức 1, 2 hoặc 3).
- **Test case 3**: Hủy chỗ của một hành khách đang có ghế, hệ thống tự động bốc hành khách có độ ưu tiên cao nhất từ hàng đợi thế vào vị trí trống đó.
- **Test case 4**: Tra cứu chính xác thông tin hành khách (Tên, mã ghế) khi nhập đúng ID đã tồn tại trên hệ thống cây BST; báo lỗi nếu không tìm thấy.
- **Test case 5**: Xem thống kê hiệu quả, hệ thống tính toán chính xác số ghế đầy/trống, ngân sách trợ giá (số khách $\times$ 7,000 VND) và lượng CO2 giảm thiểu (số khách $\times$ 0.5 kg).

## Cấu trúc file
src/
  main.cpp       - Menu và điều khiển
  structures.h   - Khai báo struct + nguyên mẫu hàm
  functions.cpp  - Cài đặt chi tiết