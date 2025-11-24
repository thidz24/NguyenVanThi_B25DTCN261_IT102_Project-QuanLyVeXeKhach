#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXTICKETS 100
#define MAX_TRIPS 100

struct Location {
    char name[50];       // ten dia diem
    char address[100];   // dia chi cua dia diem
};
struct Trip {
    char tripId[20]; // Ma chuyen xe
    struct Location departure; // Diem khoi hanh
    struct Location destination; // Diem den
    char date[20]; // Ngay gio chuyen xe
    int totalSeats; // Tong so ghe
    int bookedSeats; // So ghe da dat
};
// Danh sach Trip
struct Trip sampleTrips[5] = {
    {
        "TX001",
        {"Ha Noi", "So 1 Trang Tien, Hoan Kiem, Ha Noi"},
        {"Hai Phong", "So 2 Le Hong Phong, Hai Phong"},
        "2024-07-01 08:00",
        40,
        10
    },
    {
        "TX002",
        {"Da Nang", "So 3 Nguyen Van Linh, Da Nang"},
        {"Hue", "So 4 Hung Vuong, Hue"},
        "2024-07-02 09:30",
        45,
        20
    },
    {
        "TX003",
        {"TP HCM", "So 5 Ly Tu Trong, Quan 1, TP HCM"},
        {"Nha Trang", "So 6 Tran Phu, Nha Trang"},
        "2024-07-03 07:45",
        50,
        15
    },
    {
        "TX004",
        {"Can Tho", "So 7 Cach Mang Thang 8, Can Tho"},
        {"Bac Lieu", "So 8 Tran Huynh, Bac Lieu"},
        "2024-07-04 10:00",
        35,
        12
    },
    {
        "TX005",
        {"Vinh", "So 9 Nguyen Du, TP Vinh"},
        {"Thanh Hoa", "So 10 Hac Thanh, Thanh Hoa"},
        "2024-07-05 13:15",
        30,
        5
    }
};

struct Passenger {
    char name[50]; // Ten hanh khach
    char phone[20]; // So dien thoai hanh khach
};
struct Ticket {
    char ticketId[20]; // Ma ve (Sinh ngau nhien hooac tu dong)
    char tripId[20]; // Ma chuyen xe
    struct Passenger passenger; // Thong tin hanh khach
    int seatNumber; // so ghe da dat
    double price; // Gia ve
    int paymentStatus; // Trang thai thanh toan (0: chua thanh toan,1: da thanh toan)
    char date[20]; // Ngay gio dat ve
};

// Gan gia tri
struct Trip trips[MAX_TRIPS];
int tripCount = 0;

// khai bao ham
void clearInputBuffer();
void inputString(char *prompt, char *str, int size);
int isTripIdUnique(const char *tripId);
int isEmptyString(const char *str);
void showMenu();
void addTrip();
void updateTripInfo();
void bookTicket();

int main() {
    int choice;
    while(1){
        showMenu();
        printf("Moi ban nhap lua chon: ");
        char choiceBuf[32];
        if (fgets(choiceBuf, sizeof(choiceBuf), stdin) == NULL) {
            printf("Loi! Vui long thu lai\n");
            clearInputBuffer();
            continue;
        }
        choice = atoi(choiceBuf);
        switch(choice){
            case 1:
                addTrip();
                break;
            case 2:
                    updateTripInfo();
                break;
            case 3:
                    bookTicket();
                break;
            case 9:
                printf("Thoat chuong trinh...!\n");
                return 0;
            default :
                printf("Loi! Moi ban nhap lailai\n");
        }
    }
    return 0;
}
// Function definitions (viet phan than ham o duoi)
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Giup nhap chuoi voi loai bo dau '\n' cuoi
void inputString(char *prompt, char *str, int size) {
    while(1) {
        printf("%s", prompt);
        if (fgets(str, size, stdin) == NULL) {
            str[0] = '\0';
        } else {
            str[strcspn(str, "\n")] = '\0'; // xoa \n cuoi
        }
        if(strlen(str) == 0) {
            printf("Khong duoc bo trong.\n");
            continue;
        }
        break;
    }
}

// Ham kiem tra su duy nhat cua TripID
int isTripIdUnique(const char *tripId) {
    for (int i = 0; i < tripCount; i++) {
        if (strcmp(trips[i].tripId, tripId) == 0) {
            return 0; // Khong duy nhat
        }
    }
    return 1; // Duy nhat
}

// Ham kiem tra chuoi rong (bo trong)
int isEmptyString(const char *str) {
    return (str == NULL) || (strlen(str) == 0);
}

void showMenu() {
    const char *menuLines[] = {
        "========== QUAN LY VE XE KHACH ==========",
        "| 1. Them chuyen xe moi                  |",
        "| 2. Cap nhat thong tin chuyen xe        |",
        "| 3. Dat ve                              |",
        "| 4. Kiem tra tinh trang ve              |",
        "| 5. Liet ke chuyen xe                   |",
        "| 6. Thanh toan ve                       |",
        "| 7. Quan ly trang thai ve (Khoa, Huy)   |",
        "| 8. Bao cao thong ke va doanh thu       |",
        "| 9. Thoat                               |",
        "=========================================="
    };
    int n = sizeof(menuLines) / sizeof(menuLines[0]);
    for (int i = 0; i < n; i++) {
        printf("%s\n", menuLines[i]);
    }
}

// Ham them chuyen xe moi voi thong bao thanh cong/that bai ro rang
void addTrip() {
    if (tripCount >= MAX_TRIPS) {
        printf("Them chuyen xe that bai: Danh sach chuyen xe da day.\n");
        return;
    }

    struct Trip newTrip;
    char temp[100];
    int valid = 1; // Gia su du lieu hop le ban dau

    // Nhap va kiem tra ma chuyen xe (TripID): khong rong, khong trung
    inputString("Nhap ma chuyen xe (duy nhat): ", temp, sizeof(temp));
    if (isEmptyString(temp)) {
        printf("Them chuyen xe that bai: Ma chuyen xe khong duoc de trong.\n");
        valid = 0;
    } else if (!isTripIdUnique(temp)) {
        printf("Them chuyen xe that bai: Ma chuyen xe da ton tai.\n");
        valid = 0;
    } else {
        strcpy(newTrip.tripId, temp);
    }

    // Nhap va kiem tra ten diem khoi hanh (khong rong)
    if (valid) {
        inputString("Nhap ten diem khoi hanh: ", newTrip.departure.name, sizeof(newTrip.departure.name));
        if (isEmptyString(newTrip.departure.name)) {
            printf("Them chuyen xe that bai: Ten diem khoi hanh khong duoc de trong.\n");
            valid = 0;
        }
    }

    // Nhap dia chi diem khoi hanh (khong kiem tra rong)
    if (valid) 
        inputString("Nhap dia chi diem khoi hanh: ", newTrip.departure.address, sizeof(newTrip.departure.address));

    // Nhap va kiem tra ten diem den (khong rong)
    if (valid) {
        inputString("Nhap ten diem den: ", newTrip.destination.name, sizeof(newTrip.destination.name));
        if (isEmptyString(newTrip.destination.name)) {
            printf("Them chuyen xe that bai: Ten diem den khong duoc de trong.\n");
            valid = 0;
        }
    }

    // Nhap dia chi diem den (khong kiem tra rong)
    if (valid) 
        inputString("Nhap dia chi diem den: ", newTrip.destination.address, sizeof(newTrip.destination.address));

    // Nhap ngay gio chuyen xe (khong rong)
    if (valid) {
        inputString("Nhap ngay gio chuyen xe: ", newTrip.date, sizeof(newTrip.date));
        if (isEmptyString(newTrip.date)) {
            printf("Them chuyen xe that bai: Ngay gio chuyen xe khong duoc de trong.\n");
            valid = 0;
        }
    }

    // Nhap tong so ghe (kiem tra > 0)
    if (valid) {
        inputString("Nhap tong so ghe: ", temp, sizeof(temp));
        newTrip.totalSeats = atoi(temp);
        if (isEmptyString(temp)) {
            printf("Them chuyen xe that bai: Tong so ghe khong duoc de trong.\n");
            valid = 0;
        } else if (newTrip.totalSeats <= 0) {
            printf("Them chuyen xe that bai: Tong so ghe phai lon hon 0.\n");
            valid = 0;
        }
    }

    if (valid) {
        newTrip.bookedSeats = 0;
        trips[tripCount++] = newTrip;
        printf("Them chuyen xe thanh cong!\n");
    } else {
        printf("Them chuyen xe that bai: Du lieu khong hop le.\n");
    }
}

void updateTripInfo() {
    char tripId[20];
    inputString("Nhap ma chuyen xe can cap nhat: ", tripId, sizeof(tripId));

    // Validate tripId: Khong de trong
    if (isEmptyString(tripId)) {
        printf("Ma chuyen xe khong duoc de trong.\n");
        return;
    }

    int found = 0;
    for (int i = 0; i < tripCount; ++i) {
        if (strcmp(trips[i].tripId, tripId) == 0) {
            found = 1;

            char newDepartureName[100];
            char newDestinationName[100];
            char newDate[30];
            char temp[32];
            int newTotalSeats;

            // Nhap va kiem tra ten diem khoi hanh moi (khong de trong)
            inputString("Nhap ten diem khoi hanh moi: ", newDepartureName, sizeof(newDepartureName));
            if (isEmptyString(newDepartureName)) {
                printf("Ten diem khoi hanh khong duoc de trong.\n");
                return;
            }

            // Nhap va kiem tra ten diem den moi (khong de trong)
            inputString("Nhap ten diem den moi: ", newDestinationName, sizeof(newDestinationName));
            if (isEmptyString(newDestinationName)) {
                printf("Ten diem den khong duoc de trong.\n");
                return;
            }

            // Nhap dia chi diem den moi (khong bat buoc rong, theo de khong yeu cau validate)
            inputString("Nhap dia chi diem den moi: ", trips[i].destination.address, sizeof(trips[i].destination.address));

            // Nhap ngay gio chuyen xe moi (khong de trong)
            inputString("Nhap ngay gio moi cho chuyen xe: ", newDate, sizeof(newDate));
            if (isEmptyString(newDate)) {
                printf("Ngay gio chuyen xe khong duoc de trong.\n");
                return;
            }

            // Nhap tong so ghe moi (> 0 va >= bookedSeats)
            while (1) {
                inputString("Nhap tong so ghe moi: ", temp, sizeof(temp));
                if (isEmptyString(temp)) {
                    printf("Tong so ghe khong duoc de trong.\n");
                    continue;
                }
                newTotalSeats = atoi(temp);
                if (newTotalSeats < trips[i].bookedSeats) {
                    printf("Tong so ghe khong duoc nho hon so ghe da dat (%d).\n", trips[i].bookedSeats);
                } else if (newTotalSeats <= 0) {
                    printf("Tong so ghe phai lon hon 0.\n");
                } else {
                    break;
                }
            }

            // Cap nhat du lieu chuyen xe
            strncpy(trips[i].departure.name, newDepartureName, sizeof(trips[i].departure.name));
            strncpy(trips[i].destination.name, newDestinationName, sizeof(trips[i].destination.name));
            strncpy(trips[i].date, newDate, sizeof(trips[i].date));
            trips[i].totalSeats = newTotalSeats;

            printf("Cap nhat chuyen xe thanh cong\n");
            return;
        }
    }
    // Neu khong tim thay chuyen xe
    if (!found) {
        printf("Khong tim thay chuyen xe\n");
    }
}

// Ham dat ve

// Ham kiem tra so dien thoai (chi cho phep so va do dai tu 8-15)
int isValidPhone(const char* phone) {
    int len = strlen(phone);
    if (len < 8 || len > 15)
        return 0;
    for (int i = 0; i < len; ++i)
        if (!isdigit((unsigned char)phone[i]))
            return 0;
    return 1;
}

// Kiem tra ma chuyen xe ton tai (theo tripId) - tra ve index, khong thi -1
int findTripIndexById(const char* tripId) {
    for (int i = 0; i < tripCount; ++i)
        if (strcmp(trips[i].tripId, tripId) == 0)
            return i;
    return -1;
}

// Kiem tra ghe da dat cho tripId, seatNumber
int isSeatBooked(const char* tripId, int seatNumber, struct Ticket* tickets, int ticketCount) {
    for (int i = 0; i < ticketCount; ++i)
        if (strcmp(tickets[i].tripId, tripId) == 0 && tickets[i].seatNumber == seatNumber)
            return 1;
    return 0;
}

// Ham dat ve thoa validation yeu cau
void bookTicket() {
    static struct Ticket tickets[MAXTICKETS];
    static int ticketCount = 0;

    if (tripCount == 0) {
        printf("Them sach that bai\n");
        return;
    }

    printf("Danh sach cac chuyen xe:\n");
    for (int i = 0; i < tripCount; ++i) {
        printf("%d. Ma chuyen xe: %s | Khoi hanh: %s | Den: %s | Ghe trong: %d\n",
            i + 1, trips[i].tripId,
            trips[i].departure.name, trips[i].destination.name,
            trips[i].totalSeats - trips[i].bookedSeats);
    }

    char inputTripId[20];
    int tripIdx = -1;
    do {
        inputString("Nhap ma chuyen xe muon dat ve: ", inputTripId, sizeof(inputTripId));
        if (isEmptyString(inputTripId)) {
            printf("Ma chuyen xe khong duoc de trong!\n");
            continue;
        }
        tripIdx = findTripIndexById(inputTripId);
        if (tripIdx == -1) {
            printf("Ma chuyen xe khong ton tai!\n");
            continue;
        }
        if (trips[tripIdx].bookedSeats >= trips[tripIdx].totalSeats) {
            printf("Chuyen xe da het ghe!\n");
            printf("Them sach that bai\n");
            return;
        }
        break;
    } while (1);

    struct Ticket newTicket;
    strcpy(newTicket.tripId, trips[tripIdx].tripId);

    // Nhap ten hanh khach
    while (1) {
        inputString("Nhap ten hanh khach: ", newTicket.passenger.name, sizeof(newTicket.passenger.name));
        if (isEmptyString(newTicket.passenger.name)) {
            printf("Ten hanh khach khong duoc de trong!\n");
            continue;
        }
        break;
    }

    // Nhap so dien thoai hanh khach
    while (1) {
        inputString("Nhap so dien thoai hanh khach: ", newTicket.passenger.phone, sizeof(newTicket.passenger.phone));
        if (isEmptyString(newTicket.passenger.phone)) {
            printf("So dien thoai khong duoc de trong!\n");
            continue;
        }
        if (!isValidPhone(newTicket.passenger.phone)) {
            printf("So dien thoai khong dung dinh dang so hoac khong hop le (8-15 ky tu)!\n");
            continue;
        }
        break;
    }

    // Nhap so ghe muon dat (validate tat ca dieu kien lien quan)
    int seatNumber;
    while (1) {
        char temp[20];
        printf("Nhap so ghe (1-%d): ", trips[tripIdx].totalSeats);
        inputString("", temp, sizeof(temp));
        seatNumber = atoi(temp);
        if (seatNumber < 1 || seatNumber > trips[tripIdx].totalSeats) {
            printf("So ghe phai > 0 va <= tong so ghe!\n");
            continue;
        }
        if (isSeatBooked(trips[tripIdx].tripId, seatNumber, tickets, ticketCount)) {
            printf("So ghe nay da duoc dat trong chuyen xe nay!\n");
            continue;
        }
        break;
    }
    newTicket.seatNumber = seatNumber;

    // Nhap gia ve
    while (1) {
        char tempPrice[32];
        inputString("Nhap gia ve: ", tempPrice, sizeof(tempPrice));
        newTicket.price = atof(tempPrice);
        if (newTicket.price <= 0) {
            printf("Gia ve phai lon hon 0!\n");
            continue;
        }
        break;
    }

    newTicket.paymentStatus = 0;
    inputString("Nhap ngay gio dat ve: ", newTicket.date, sizeof(newTicket.date));

    // Tao ticketId
    sprintf(newTicket.ticketId, "TICKET%03d", ticketCount + 1);

    // Them ve vao danh sach va tang bookedSeats
    tickets[ticketCount++] = newTicket;
    trips[tripIdx].bookedSeats++;

    printf("Them sach thanh cong\n");

    // Danh sach sach (ve) sau khi them
    printf("----- Danh sach ve da dat -----\n");
    for (int i = 0; i < ticketCount; ++i) {
        printf("Ma ve: %s | Ma chuyen xe: %s | Ten khach: %s | SDT: %s | Ghe: %d | Gia: %.2f | Ngay dat: %s\n",
            tickets[i].ticketId, tickets[i].tripId, tickets[i].passenger.name,
            tickets[i].passenger.phone, tickets[i].seatNumber, tickets[i].price, tickets[i].date);
    }
}



