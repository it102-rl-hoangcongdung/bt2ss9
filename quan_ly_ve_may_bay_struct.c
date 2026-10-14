#include <stdio.h>
#include <string.h>

struct FlightTicket {
    char pnrCode[15];
    char passengerName[50];
    int ticketClass;
    float baggageWeight;
    float baggageFee;
};

int main() {
    struct FlightTicket danhSachVe[100];
    int soLuong = 0;
    int choice;

    do {
        printf("\n=== HỆ THỐNG BÁN VÉ VÀ CHECK-IN MÁY BAY ===\n");
        printf("1. Thêm vé máy bay mới\n");
        printf("2. Hiển thị danh sách vé\n");
        printf("3. Cập nhật hành lý theo PNR\n");
        printf("4. Xóa vé theo PNR\n");
        printf("5. Thoát\n");
        printf("Lựa chọn của bạn: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                if (soLuong >= 100) {
                    printf("Danh sách vé đã đầy, không thể thêm mới!\n");
                    break;
                }

                printf("Nhập mã PNR: ");
                scanf("%s", danhSachVe[soLuong].pnrCode);

                while (getchar() != '\n');

                printf("Nhập họ tên hành khách: ");
                fgets(danhSachVe[soLuong].passengerName, sizeof(danhSachVe[soLuong].passengerName), stdin);
                size_t len = strlen(danhSachVe[soLuong].passengerName);
                if (len > 0 && danhSachVe[soLuong].passengerName[len - 1] == '\n') {
                    danhSachVe[soLuong].passengerName[len - 1] = '\0';
                }

                printf("Nhập hạng vé (1-Eco, 2-Deluxe, 3-Business): ");
                scanf("%d", &danhSachVe[soLuong].ticketClass);

                printf("Nhập khối lượng hành lý (kg): ");
                scanf("%f", &danhSachVe[soLuong].baggageWeight);

                if (danhSachVe[soLuong].ticketClass == 3) {
                    danhSachVe[soLuong].baggageFee = 0.0;
                } else {
                    if (danhSachVe[soLuong].baggageWeight <= 7.0) {
                        danhSachVe[soLuong].baggageFee = 0.0;
                    } else {
                        danhSachVe[soLuong].baggageFee = (danhSachVe[soLuong].baggageWeight - 7.0) * 50000.0;
                    }
                }

                soLuong++;
                printf("=> Thêm vé thành công! Cước phạt hành lý quá cân: %.0f VNĐ.\n", danhSachVe[soLuong - 1].baggageFee);
                break;
            }
            case 2: {
                if (soLuong == 0) {
                    printf("Danh sách vé đang rỗng!\n");
                    break;
                }

                printf("========================================================================================\n");
                printf("%-4s | %-15s | %-25s | %-10s | %-15s | %-15s\n", "STT", "Mã PNR", "Họ tên hành khách", "Hạng vé", "Hành lý (kg)", "Cước quá cước");
                printf("========================================================================================\n");
                for (int i = 0; i < soLuong; i++) {
                    char className[20];
                    if (danhSachVe[i].ticketClass == 1) strcpy(className, "Eco");
                    else if (danhSachVe[i].ticketClass == 2) strcpy(className, "Deluxe");
                    else strcpy(className, "Business");

                    printf("%-4d | %-15s | %-25s | %-10s | %-13.1f | %.0f VNĐ\n", 
                           i + 1, danhSachVe[i].pnrCode, danhSachVe[i].passengerName, className, danhSachVe[i].baggageWeight, danhSachVe[i].baggageFee);
                }
                printf("========================================================================================\n");
                break;
            }
            case 3: {
                if (soLuong == 0) {
                    printf("Danh sách vé đang rỗng!\n");
                    break;
                }

                char pnrInput[15];
                printf("Nhập mã PNR cần cập nhật hành lý: ");
                scanf("%s", pnrInput);

                int foundIndex = -1;
                for (int i = 0; i < soLuong; i++) {
                    if (strcmp(danhSachVe[i].pnrCode, pnrInput) == 0) {
                        foundIndex = i;
                        break;
                    }
                }

                if (foundIndex == -1) {
                    printf("Không tìm thấy vé có mã PNR đã nhập!\n");
                } else {
                    printf("Tìm thấy hành khách: %s\n", danhSachVe[foundIndex].passengerName);
                    printf("Nhập trọng lượng hành lý mới (kg): ");
                    scanf("%f", &danhSachVe[foundIndex].baggageWeight);

                    if (danhSachVe[foundIndex].ticketClass == 3) {
                        danhSachVe[foundIndex].baggageFee = 0.0;
                    } else {
                        if (danhSachVe[foundIndex].baggageWeight <= 7.0) {
                            danhSachVe[foundIndex].baggageFee = 0.0;
                        } else {
                            danhSachVe[foundIndex].baggageFee = (danhSachVe[foundIndex].baggageWeight - 7.0) * 50000.0;
                        }
                    }
                    printf("=> Cập nhật thành công! Phí hành lý quá cước mới: %.0f VNĐ.\n", danhSachVe[foundIndex].baggageFee);
                }
                break;
            }
            case 4: {
                if (soLuong == 0) {
                    printf("Danh sách vé đang rỗng!\n");
                    break;
                }

                char pnrInput[15];
                printf("Nhập mã PNR cần xóa: ");
                scanf("%s", pnrInput);

                int foundIndex = -1;
                for (int i = 0; i < soLuong; i++) {
                    if (strcmp(danhSachVe[i].pnrCode, pnrInput) == 0) {
                        foundIndex = i;
                        break;
                    }
                }

                if (foundIndex == -1) {
                    printf("Không tìm thấy vé có mã PNR đã nhập!\n");
                } else {
                    for (int i = foundIndex; i < soLuong - 1; i++) {
                        danhSachVe[i] = danhSachVe[i + 1];
                    }
                    soLuong--;
                    printf("=> Đã xóa thành công vé có mã PNR: %s ra khỏi hệ thống.\n", pnrInput);
                }
                break;
            }
            case 5:
                printf("Cảm ơn bạn đã sử dụng hệ thống quản lý vé máy bay. Tạm biệt!\n");
                break;
            default:
                printf("Lựa chọn không hợp lệ. Vui lòng chọn từ 1 đến 5.\n");
        }
    } while (choice != 5);

    return 0;
}
