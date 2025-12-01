#include <stdio.h>   // Thu vien nhap xuat co ban
#include <stdlib.h>  // Thu vien ham tien ich chuan
#include <string.h>  // Thu vien xu li chuoi
#include <ctype.h>   // Thu vien kiem tra ki tu 
#define MAXTICKETS 100   // So luong ve toi da 
#define MAX_TRIPS 100    // So luong chuyen xe toi da

struct Location {
    char name[50];      // ten dia diem
    char address[100];  // dia chi dia diem
};
struct Trip {
    char tripId[20];                // ma chuyen xe
    struct Location departure;      // thong tin diem khoi hanh
    struct Location destination;    // thong tin diem den
    char date[20];                  // ngay gio chuyen xe
    int totalSeats;                 // tong so ghe tren xe
    int bookedSeats;                // so ghe da dat 
};
// Mang luu thong tin cac chuyen xe
struct Trip trips[MAX_TRIPS] = {
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
    char name[50];   // ten hanh khach
    char phone[20];  // so dien thoai hanh khach
};
struct Ticket {
    char ticketId[20];            // ma ve
    char tripId[20];              // ma chuyen xe
    struct Passenger passenger;   // thong tin hanh khach
    int seatNumber;               // so ghe
    double price;                 // gia ve
    int paymentStatus;            // trang thai thanh toan
    char date[32];                // ngay dat ve
    int status;                   // trang thai ve: 0 hoat dong, 1 da huy, 2 bi khoa
};
// Mang ve xe
struct Ticket tickets[MAXTICKETS] = {
    {
        "V001", "TX001", {"Nguyen Van A", "0912345678"},
        1, 250000.0, 1, "2024-06-28 07:30"
    },
    {
        "V002", "TX002", {"Tran Thi B", "0922233344"},
        5, 300000.0, 0, "2024-07-01 09:00"
    },
    {
        "V003", "TX003", {"Le Van C", "0933456789"},
        10, 350000.0, 1, "2024-07-02 09:30"
    },
    {
        "V004", "TX004", {"Pham Thi D", "0944556677"},
        2, 200000.0, 1, "2024-07-03 07:45"
    },
    {
        "V005", "TX005", {"Hoang Van E", "0955667788"},
        8, 270000.0, 0, "2024-07-04 10:00"
    }
};
int ticketCount = 5; // so luong ve hien tai
int tripCount = 5;   // so luong chuyen xe hien tai

// Danh sach khai bao nguyen mau ham
void inputString(char *prompt, char *str, int size); // Nhap chuoi, khong cho nhap rong
int isTripIdUnique(const char *tripId); // Kiem tra ma chuyen xe da ton tai chua
int isEmptyString(const char *str); // Kiem tra chuoi rong
void showMenu(); // Hien thi menu
void addTrip(); // Them chuyen xe moi
void updateTripInfo(); // Cap nhat thong tin chuyen xe
void bookTicket(); // Dat ve
int isValidPhone(const char* phone); // Kiem tra dinh dang so dien thoai
int findTripIndexById(const char* tripId); // Tim chi so chuyen xe theo ma
int isSeatBooked(const char* tripId, int seatNumber, struct Ticket* tickets, int ticketCount); // Kiem tra so ghe da dat
void checkTicketStatus(struct Ticket tickets[], int ticketCount, struct Trip trips[], int tripCount); // Kiem tra tinh trang ve
void listTrips(); // Liet ke chuyen xe
void payTicket(); // Thanh toan ve
void cancel_lockTicket(); // Huy hoac khoa ve
void revenue_Ticketstatistic_report(); // Bao cao thong ke va doanh thu
int isValidDateFormat(const char *str); // Kiem tra dinh dang ngay gio
int isValidName(const char *s); // Kiem tra dinh dang ten
int isValidNamepassenger(const char *s); // Kiem tra ten hanh khach 
int isValidNumberlist(const char *s); // kiem tra so trang 
// Ham main, vong lap chinh chuong trinh
int main() {
    int choice;
    while (1) {
        showMenu();
        printf("Moi ban nhap lua chon: ");
        char line[64];
        if (fgets(line, sizeof(line), stdin) == NULL || line[0] == '\n') {
            printf("Khong duoc de trong, vui long nhap lai!\n");
            continue;
        }
        if (sscanf(line, "%d", &choice) != 1) {
            printf("Loi cu phap, vui long nhap lai so!\n");
            continue;
        }
        switch (choice) {
            case 1: 
			addTrip(); 
			break;
            case 2: 
			updateTripInfo(); 
			break;
            case 3: 
			bookTicket(); 
			break;
            case 4: 
			checkTicketStatus(tickets, ticketCount, trips, tripCount); 
			break;
            case 5: 
			listTrips(); 
			break;
            case 6: 
			payTicket(); 
			break;
            case 7: 
			cancel_lockTicket(); 
			break;
            case 8: 
			revenue_Ticketstatistic_report(); 
			break;
            case 9: 
                printf("Thoat chuong trinh...!\n");
                return 0;
            default: printf("Loi! Moi ban nhap lai\n");
        }
    }
    return 0;
}

// Ham nhap chuoi, loai bo khoang trang dau cuoi, khong cho nhap rong
void inputString(char *prompt, char *str, int size) {
    while (1) {
        printf("%s", prompt);
        if (fgets(str, size, stdin) == NULL) {
            str[0] = '\0';
        } else {
            str[strcspn(str, "\n")] = '\0';
        }
        // Xoa khoang trang cuoi chuoi
        int len = strlen(str);
        while (len > 0 && isspace((unsigned char)str[len-1])) str[--len]=0;
        // Xoa khoang trang dau chuoi
        int start = 0;
        while (str[start] && isspace((unsigned char)str[start])) ++start;
        if (start > 0) memmove(str, str+start, strlen(str+start)+1);
        if (strlen(str) == 0) {
            printf("Khong duoc bo trong.\n");
            continue;
        }
        int onlyspace = 1;
        for (int i = 0; str[i]; ++i) if (!isspace((unsigned char)str[i])) onlyspace = 0;
        if (onlyspace) {
            printf("Khong duoc nhap toan khoang trang!\n");
            continue;
        }
        break;
    }
}

// Kiem tra ma chuyen xe co bi trung khong
int isTripIdUnique(const char *tripId) {
    for (int i = 0; i < tripCount; i++) {
        if (strcasecmp(trips[i].tripId, tripId) == 0)
            return 0;
    }
    return 1;
}

// Kiem tra chuoi rong (toan khoang trang hoac NULL)
int isEmptyString(const char *str) {
    if (str == NULL) return 1;
    while (*str) {
        if (!isspace((unsigned char)*str)) return 0;
        ++str;
    }
    return 1;
}

// Hien thi menu
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
// Ham kiem tra ten chi la chu cai, so, khoang trang, khong co ky tu dac biet hay dau toan hoc
int isValidName(const char *s) {
    while (*s) {
        if (!(isalnum((unsigned char)*s) || *s == ' '))
            return 0;
        s++;
    }
    return 1;
}
// Kiem tra dinh dang ngay gio YYYY-MM-DD HH:MM
int isValidDateFormat(const char *str) {
    if (strlen(str) != 16) return 0;
    if (!isdigit(str[0]) || !isdigit(str[1]) || !isdigit(str[2]) || !isdigit(str[3])) return 0;
    if (str[4] != '-') return 0;
    if (!isdigit(str[5]) || !isdigit(str[6])) return 0;
    if (str[7] != '-') return 0;
    if (!isdigit(str[8]) || !isdigit(str[9])) return 0;
    if (str[10] != ' ') return 0;
    if (!isdigit(str[11]) || !isdigit(str[12])) return 0;
    if (str[13] != ':') return 0;
    if (!isdigit(str[14]) || !isdigit(str[15])) return 0;
    int yyyy = atoi(str);
    int mm = atoi(str+5);
    int dd = atoi(str+8);
    int HH = atoi(str+11);
    int MI = atoi(str+14);
    if (yyyy < 0 || mm < 1 || mm > 12 || dd < 1 || dd > 31 || HH < 0 || HH > 23 || MI < 0 || MI > 59)
        return 0;
    return 1;
}

// Them chuyen xe moi 
void addTrip() {
    if (tripCount >= MAX_TRIPS) {
        printf("Them chuyen xe that bai: Danh sach chuyen xe da day.\n");
        return;
    }
    struct Trip newTrip;
    char temp[100];
    while (1) {
        inputString("Nhap ma chuyen xe (chi a-z A-Z 0-9 khong chua khoang trang, duy nhat, <= 19 ky tu): ", temp, sizeof(temp));
        int valid = 1;
        if (strlen(temp) > 19) valid = 0;
        for (int i = 0; temp[i]; ++i)
            if (!isalnum((unsigned char)temp[i])){
                valid = 0;
				break;
            }
        if (!valid) {
            printf("Ma chuyen xe chi duoc gom chu so va chu cai, khong khoang trang, toi da 19 ky tu. Vui long nhap lai.\n");
            continue;
        }
        if (!isTripIdUnique(temp)) {
            printf("Ma chuyen xe da ton tai. Vui long nhap lai.\n");
            continue;
        }
        strncpy(newTrip.tripId, temp, sizeof(newTrip.tripId)-1);
        newTrip.tripId[sizeof(newTrip.tripId)-1]= '\0';
        break;
    }
    while (1) {
        inputString("Nhap ten diem khoi hanh: ", newTrip.departure.name, sizeof(newTrip.departure.name));
        if (isEmptyString(newTrip.departure.name)) {
            printf("Ten diem khoi hanh khong duoc de trong. Vui long nhap lai.\n");
            continue;
        }
        if (!isalpha((unsigned char)newTrip.departure.name[0])) {
            printf("Ten diem khoi hanh phai bat dau bang chu cai. Vui long nhap lai.\n");
            continue;
        }
        if (!isValidName(newTrip.departure.name)) {
            printf("Ten diem khoi hanh khong duoc chua ky tu dac biet hoac dau toan hoc. Vui long nhap lai.\n");
            continue;
        }
        break;
    }
    while (1) {
        inputString("Nhap dia chi diem khoi hanh: ", newTrip.departure.address, sizeof(newTrip.departure.address));
        int isValid = 1;
        for (int i = 0; newTrip.departure.address[i]; ++i) {
            char c = newTrip.departure.address[i];
            if (!isalnum((unsigned char)c) && !isspace((unsigned char)c) && c != ',' && c != '.') {
                isValid = 0;
                break;
            }
            if (c == '+' || c == '*' || c == '/' || c == '=' || c == '<' || c == '>' || c == '%' || c == '^' || c == '|' ||
                c == '&' || c == '~' || c == '!' || c == '?' || c == '@' || c == '#' ||
                c == '$' || c == ':' || c == ';' || c == '[' || c == ']' || c == '{' || c == '}' || c == '(' || c == ')' || c == '/' || c == '-' 
                ) { 
				isValid = 0; 
				break; 
			}
        }
        if (!isValid) {
            printf("Dia chi diem khoi hanh khong duoc chua ky tu dac biet hoac dau toan hoc. Vui long nhap lai.\n");
            continue;
        }
        break;
    }
    while (1) {
        inputString("Nhap ten diem den: ", newTrip.destination.name, sizeof(newTrip.destination.name));
        if (isEmptyString(newTrip.destination.name)) {
            printf("Ten diem den khong duoc de trong. Vui long nhap lai.\n");
            continue;
        }
        if (!isalpha((unsigned char)newTrip.destination.name[0])) {
            printf("Ten diem den phai bat dau bang chu cai. Vui long nhap lai.\n");
            continue;
        }
        if (!isValidName(newTrip.destination.name)) {
            printf("Ten diem den khong duoc chua ky tu dac biet hoac dau toan hoc. Vui long nhap lai.\n");
            continue;
        }
        break;
    }
    while (1) {
        inputString("Nhap dia chi diem den: ", newTrip.destination.address, sizeof(newTrip.destination.address));
        int isValid = 1;
        for (int i = 0; newTrip.destination.address[i]; ++i) {
            char c = newTrip.destination.address[i];
            if (!isalnum((unsigned char)c) && !isspace((unsigned char)c) && c != ',' && c != '.' ) {
                isValid = 0; 
				break;
            }
            if (c == '+' || c == '*' || c == '/' || c == '=' || c == '<' || c == '>' || c == '%' || c == '^' || c == '|' ||
                c == '&' || c == '~' || c == '!' || c == '?' || c == '@' || c == '#' ||
                c == '$' || c == ':' || c == ';' || c == '[' || c == ']' || c == '{' || c == '}' || c == '(' || c == ')' || c == '/' || c == '-' 
                ) { 
				isValid = 0; 
				break; 
			}
        }
        if (!isValid) {
            printf("Dia chi diem den khong duoc chua ky tu dac biet hoac dau toan hoc. Vui long nhap lai.\n");
            continue;
        }
        break;
    }
    while (1) {
        inputString("Nhap ngay gio chuyen xe (YYYY-MM-DD HH:MM): ", newTrip.date, sizeof(newTrip.date));
        if (!isValidDateFormat(newTrip.date)) {
            printf("Ngay gio chuyen xe khong dung dinh dang hoac du lieu. Dinh dang dung: YYYY-MM-DD HH:MM\n");
            continue;
        }
        break;
    }
    while (1) {
        inputString("Nhap tong so ghe: ", temp, sizeof(temp));
        char *endptr;
        long seatInput = strtol(temp, &endptr, 10);
        if (*endptr != '\0' || seatInput <= 0) {
            printf("Tong so ghe phai la so nguyen > 0. Moi nhap lai.\n");
            continue;
        }
        newTrip.totalSeats = (int)seatInput;
        break;
    }
    newTrip.bookedSeats = 0;

    if (tripCount < MAX_TRIPS) {
        trips[tripCount++] = newTrip;
        printf("Them chuyen xe thanh cong!\n");
    } else {
        printf("Them chuyen xe that bai: Danh sach chuyen xe da day.\n");
    }
}

// Cap nhat thong tin chuyen xe
void updateTripInfo() {
    char tripId[20];
    inputString("Nhap ma chuyen xe can cap nhat: ", tripId, sizeof(tripId));
    if (isEmptyString(tripId)) {
        printf("Ma chuyen xe khong duoc de trong.\n");
        return;
    }
    int foundIdx = -1;
    for (int i = 0; i < tripCount; ++i) {
        if (strcmp(trips[i].tripId, tripId) == 0) {
            foundIdx = i;
            break;
        }
    }
    if (foundIdx == -1) {
        printf("Khong tim thay chuyen xe\n");
        return;
    }
    int i = foundIdx;
    char newDepartureName[50], newDepartureAddr[100], newDestinationName[50], newDestinationAddr[100], newDate[32], temp[32];
    int newTotalSeats;
    while (1) {
        inputString("Nhap ten diem khoi hanh moi: ", newDepartureName, sizeof(newDepartureName));
        if (isEmptyString(newDepartureName)) {
            printf("Ten diem khoi hanh khong duoc de trong. Vui long nhap lai.\n");
            continue;
        }
        if (!isalpha((unsigned char)newDepartureName[0])) {
            printf("Ten diem khoi hanh phai bat dau bang chu cai. Vui long nhap lai.\n");
            continue;
        }
        if (!isValidName(newDepartureName)) {
            printf("Ten diem khoi hanh khong duoc chua ky tu dac biet hoac dau toan hoc. Vui long nhap lai.\n");
            continue;
        }
        break;
    }
    while (1) {
    	inputString("Nhap dia chi diem khoi hanh moi: ", newDepartureAddr, sizeof(newDepartureAddr));
    	int isValid = 1;
        for (int j = 0; newDepartureAddr[j]; ++j) {
            char c = newDepartureAddr[j];
            if (!isalnum((unsigned char)c) && !isspace((unsigned char)c) && c != ',' && c != '.' ) {
                isValid = 0; 
				break;
            }
            if (c == '+' || c == '*' || c == '/' || c == '=' || c == '<' || c == '>' || c == '%' || c == '^' || c == '|' ||
                c == '&' || c == '~' || c == '!' || c == '?' || c == '@' || c == '#' ||
                c == '$' || c == ':' || c == ';' || c == '[' || c == ']' || c == '{' || c == '}' || c == '(' || c == ')' || c == '/' || c == '-' 
                ) { 
				isValid = 0; 
				break; 
			}
        }
        if (!isValid) {
            printf("Dia chi diem den khong duoc chua ky tu dac biet hoac dau toan hoc. Vui long nhap lai.\n");
            continue;
        }
        break;
    	
	}
    while (1) {
        inputString("Nhap ten diem den moi: ", newDestinationName, sizeof(newDestinationName));
        if (isEmptyString(newDestinationName)) {
            printf("Ten diem den khong duoc de trong. Vui long nhap lai.\n");
            continue;
        }
        if (!isalpha((unsigned char)newDestinationName[0])) {
            printf("Ten diem den phai bat dau bang chu cai. Vui long nhap lai.\n");
            continue;
        }
        if (!isValidName(newDestinationName)) {
            printf("Ten diem khoi den khong duoc chua ky tu dac biet hoac dau toan hoc. Vui long nhap lai.\n");
            continue;
        }
        break;
    } 
    while (1) {
    	inputString("Nhap dia chi diem den moi: ", newDestinationAddr, sizeof(newDestinationAddr));
    	int isValid = 1; 
    	for (int j;newDestinationAddr[j];j++) {
    		char c = newDepartureAddr[j];
            if (!isalnum((unsigned char)c) && !isspace((unsigned char)c) && c != ',' && c != '.' ) {
                isValid = 0; 
				break;
            }
            if (c == '+' || c == '*' || c == '/' || c == '=' || c == '<' || c == '>' || c == '%' || c == '^' || c == '|' ||
                c == '&' || c == '~' || c == '!' || c == '?' || c == '@' || c == '#' ||
                c == '$' || c == ':' || c == ';' || c == '[' || c == ']' || c == '{' || c == '}' || c == '(' || c == ')' || c == '/' || c == '-' 
                ) { 
				isValid = 0; 
				break; 
			}
        }
        if (!isValid) {
            printf("Dia chi diem den khong duoc chua ky tu dac biet hoac dau toan hoc. Vui long nhap lai.\n");
            continue;
        }
        break;
	} 
    while (1) {
        inputString("Nhap ngay gio moi cho chuyen xe (YYYY-MM-DD HH:MM): ", newDate, sizeof(newDate));
        if (!isValidDateFormat(newDate)) {
            printf("Ngay gio chuyen xe khong dung dinh dang hoac du lieu. Dinh dang dung: YYYY-MM-DD HH:MM\n");
            continue;
        }
        break;
    }
    while (1) {
        inputString("Nhap tong so ghe moi: ", temp, sizeof(temp));
        char *endptr;
        long seatInput = strtol(temp, &endptr, 10);
        if (*endptr != '\0' || seatInput <= 0) {
            printf("Tong so ghe phai la so nguyen > 0.\n");
            continue;
        }
        if (seatInput < trips[i].bookedSeats) {
            printf("Tong so ghe khong duoc nho hon so ghe da dat (%d).\n", trips[i].bookedSeats);
            continue;
        }
        newTotalSeats = (int)seatInput;
        break;
    }
    strncpy(trips[i].departure.name, newDepartureName, sizeof(trips[i].departure.name)-1);
    trips[i].departure.name[sizeof(trips[i].departure.name)-1] = 0;
    strncpy(trips[i].departure.address, newDepartureAddr, sizeof(trips[i].departure.address)-1);
    trips[i].departure.address[sizeof(trips[i].departure.address)-1] = 0;
    strncpy(trips[i].destination.name, newDestinationName, sizeof(trips[i].destination.name)-1);
    trips[i].destination.name[sizeof(trips[i].destination.name)-1] = 0;
    strncpy(trips[i].destination.address, newDestinationAddr, sizeof(trips[i].destination.address)-1);
    trips[i].destination.address[sizeof(trips[i].destination.address)-1] = 0;
    strncpy(trips[i].date, newDate, sizeof(trips[i].date)-1);
    trips[i].date[sizeof(trips[i].date)-1] = 0;
    trips[i].totalSeats = newTotalSeats;
    printf("Cap nhat chuyen xe thanh cong\n");
}

// Kiem tra dinh dang so dien thoai
int isValidPhone(const char* phone) {
    int len = strlen(phone);
    if (len < 8 || len > 15) return 0;
    if (phone[0] != '0') return 0;
    for (int i = 0; i < len; ++i)
        if (!isdigit((unsigned char)phone[i])) return 0;
    return 1;
}

// Tim chi so chuyen xe tu ma chuyen (khong phan biet hoa thuong)
int findTripIndexById(const char* tripId) {
    for (int i = 0; i < tripCount; ++i)
        if (strcasecmp(trips[i].tripId, tripId) == 0)
            return i;
    return -1;
}

// Kiem tra so ghe da dat chua tren chuyen xe
int isSeatBooked(const char* tripId, int seatNumber, struct Ticket* tickets, int ticketCount) {
    for (int i = 0; i < ticketCount; ++i)
        if (strcasecmp(tickets[i].tripId, tripId) == 0 && tickets[i].seatNumber == seatNumber)
            return 1;
    return 0;
}
// kiem tra ten khach hang: chi chu, khong so, khong ky tu dac biet, khong ky tu toan hoc 
int isValidNamepassenger(const char *s) {
    while (*s) {
        if (!(((*s >= 'A' && *s <= 'Z') || (*s >= 'a' && *s <= 'z')) || *s == ' ')) {
            return 0;
        }
        s++;
    }
    return 1;
}
// Dat ve
void bookTicket() {
    extern struct Ticket tickets[];
    extern int ticketCount;

    if (tripCount == 0) {
        printf("Dat ve that bai: Khong co chuyen xe nao!\n");
        return;
    }
    printf("----- Danh sach cac chuyen xe -----\n");
    for (int i = 0; i < tripCount; ++i) {
        printf("%d. Ma chuyen xe: %s | Khoi hanh: %s | Den: %s | Ghe trong: %d\n",
            i + 1, trips[i].tripId,
            trips[i].departure.name, trips[i].destination.name,
            trips[i].totalSeats - trips[i].bookedSeats);
    }
    char inputTripId[32]; int tripIdx = -1;
    while (1) {
        inputString("Nhap ma chuyen xe muon dat ve: ", inputTripId, sizeof(inputTripId));
        if (isEmptyString(inputTripId)) {
            printf("Ma chuyen xe khong duoc de trong!\nDat ve that bai!\n");
            return;
        }
        tripIdx = findTripIndexById(inputTripId);
        if (tripIdx == -1) {
            printf("Khong tim thay chuyen xe.\nDat ve that bai!\n");
            return;
        }
        if (trips[tripIdx].bookedSeats >= trips[tripIdx].totalSeats) {
            printf("Chuyen xe da het ghe!\nDat ve that bai!\n");
            return;
        }
        break;
    }
    struct Ticket newTicket;
    memset(&newTicket, 0, sizeof(struct Ticket));
    strncpy(newTicket.tripId, trips[tripIdx].tripId, sizeof(newTicket.tripId) - 1);
    newTicket.tripId[sizeof(newTicket.tripId) - 1] = '\0';
    while (1) {
        inputString("Nhap ten hanh khach: ", newTicket.passenger.name, sizeof(newTicket.passenger.name));
        if (isEmptyString(newTicket.passenger.name)) {
            printf("Ten hanh khach khong duoc de trong!\n");
            continue;
    	}
       if (!isValidNamepassenger(newTicket.passenger.name)){
       		printf("Ten hanh khach chua dung dinh dang ten! Vui long nhap lai!\n");
			continue; 
	   }
        break;
    }
    while (1) {
        inputString("Nhap so dien thoai hanh khach (So bat dau bang 0, chi chua chu so 0-9): ",
                    newTicket.passenger.phone, sizeof(newTicket.passenger.phone));
        if (!isValidPhone(newTicket.passenger.phone)) {
            printf("So dien thoai khong dung dinh dang hoac khong hop le! (ex: 0912345678)\n");
            continue;
        }
        break;
    }
    int seatNumber;
    while (1) {
        char tempSeat[16];
        printf("Nhap so ghe (1-%d, chua duoc dat): ", trips[tripIdx].totalSeats);
        inputString("", tempSeat, sizeof(tempSeat)); 
        char *endptr;
        long seatInput = strtol(tempSeat, &endptr, 10);
        if (*endptr != '\0' || seatInput < 1 || seatInput > trips[tripIdx].totalSeats) {
            printf("So ghe khong hop le!\n");
            continue;
        }
        seatNumber = (int)seatInput;
        if (isSeatBooked(trips[tripIdx].tripId, seatNumber, tickets, ticketCount)) {
            printf("So ghe nay da duoc dat trong chuyen xe nay!\n");
            continue;
        }
        break;
    }
    newTicket.seatNumber = seatNumber;
    newTicket.paymentStatus = 0;
    newTicket.status = 0;
    while (1) {
        inputString("Nhap ngay dat ve (YYYY-MM-DD HH:MM): ", newTicket.date, sizeof(newTicket.date));
        if (!isValidDateFormat(newTicket.date)) {
            printf("Ngay dat ve khong dung dinh dang hoac du lieu. Dinh dang dung: YYYY-MM-DD HH:MM\n");
            continue;
        }
        break;
    }
    while (1) {
        char tempPrice[32];
        inputString("Nhap gia ve (chi nhap so): ", tempPrice, sizeof(tempPrice));
        char *endptr;
        double pr = strtod(tempPrice, &endptr);
        if (*endptr != '\0' || pr <= 0) {
            printf("Gia ve phai la so > 0!\n");
            continue;
        }
        newTicket.price = pr;
        break;
    }
    snprintf(newTicket.ticketId, sizeof(newTicket.ticketId), "V%03d", ticketCount + 1);
    tickets[ticketCount++] = newTicket;
    trips[tripIdx].bookedSeats++;
    printf("Dat ve thanh cong\n");
    printf("----- Danh sach ve da dat -----\n");
    for (int i = 0; i < ticketCount; ++i) {
        printf("Ma ve: %s | Ma chuyen xe: %s | Ten khach: %s | SDT: %s | Ghe: %d | Gia: %.2f | Ngay dat: %s\n",
            tickets[i].ticketId, tickets[i].tripId, tickets[i].passenger.name,
            tickets[i].passenger.phone, tickets[i].seatNumber, tickets[i].price, tickets[i].date
        );
    }
}

// Kiem tra thong tin ve theo ma ve
void checkTicketStatus(struct Ticket tickets[], int ticketCount, struct Trip trips[], int tripCount) {
    char inputId[32];
    inputString("Nhap ma ve can kiem tra: ", inputId, sizeof(inputId));
    if (isEmptyString(inputId)) {
        printf("Ma ve khong duoc de trong!\n");
        return;
    }
    for (int i = 0; i < ticketCount; ++i) {
        if (strcasecmp(tickets[i].ticketId, inputId) == 0) {
            printf("\n===== THONG TIN VE =====\n");
            printf("Ma ve        : %s\n", tickets[i].ticketId);
            printf("Ten khach    : %s\n", tickets[i].passenger.name);
            printf("SDT          : %s\n", tickets[i].passenger.phone);
            printf("Chuyen xe    : %s\n", tickets[i].tripId);
            for (int t = 0; t < tripCount; ++t) {
                if (strcmp(trips[t].tripId, tickets[i].tripId) == 0) {
                    printf("Tuyen xe     : %s - %s\n", trips[t].departure.name, trips[t].destination.name);
                    printf("Dia chi khoi hanh : %s\n", trips[t].departure.address);
                    printf("Dia chi diem den  : %s\n", trips[t].destination.address);
                    printf("Ngay gio chuyen xe: %s\n", trips[t].date);
                    break;
                }
            }
            printf("So ghe       : %d\n", tickets[i].seatNumber);
            printf("Gia ve       : %.0f\n", tickets[i].price);
            printf("Ngay dat     : %s\n", tickets[i].date);
            printf("Trang thai   : %s\n", tickets[i].paymentStatus == 1 ? "Da thanh toan" : "Chua thanh toan");
            printf("========================\n");
            return;
        }
    }
    printf("Khong tim thay ve!\n");
}
// Kiem tra dinh dang so trang chi so tu 1-99
int isValidNumberlist(const char *s){
    while (*s) {
        if (!(*s >= '1' && *s <= '99')) {
            return 0; 
        }
        s++;
    } 
    return 1;
} 
// Liet ke chuyen xe co phan trang
void listTrips() {
    int pageNumber = 1, pageSize = 10;
    char input[32];
    if (tripCount <= 0) {
        printf("Khong co chuyen xe de hien thi\n");
        return;
    }
    while (1) {
    	printf("Nhap so dong moi trang (1-99, mac dinh 10, nhan Enter de bo qua): ");
    	fgets(input, sizeof(input), stdin);
    	input[strcspn(input, "\n")] = 0;
    	if(!isValidNumberlist(input)){
    		printf("Yeu cau nhap lai theo dieu kien(1-99)\n");
			continue; 
		} 
		if(isValidNamepassenger(input)){
			printf("Khong duoc chua chu hay ky tu khac ngoai so!\n");
			continue; 
		} 
		break; 
	}
    if (strlen(input) > 0 && sscanf(input, "%d", &pageSize) == 1 && pageSize > 0 && pageSize < 100) {} else { pageSize = 10; }
    while (1) {
    	printf("Nhap so trang muon xem (mac dinh 1, nhan Enter de bo qua): ");
    	fgets(input, sizeof(input), stdin);
    	input[strcspn(input, "\n")] = 0;
    		if(!isValidNumberlist(input)){
    		printf("Yeu cau nhap lai theo dieu kien(1-99)\n");
			continue; 
		} 
		if(isValidNamepassenger(input)){
			printf("Khong duoc chua chu hay ky tu khac ngoai so!\n");
			continue;
	  	}
	  	break; 
	}
    if (strlen(input) > 0 && sscanf(input, "%d", &pageNumber) == 1 && pageNumber > 0) {} else { pageNumber = 1; }
    int totalPages = (tripCount + pageSize - 1) / pageSize;
    if (totalPages <= 0) totalPages = 1;
    while (1) {
        if (pageNumber <= 0 || pageNumber > totalPages) {
            printf("So trang khong hop le. Co tong cong %d trang.\n", totalPages);
            pageNumber = 1;
            continue;
        }
        int startIdx = (pageNumber - 1) * pageSize;
        int endIdx = startIdx + pageSize - 1;
        if (endIdx >= tripCount) endIdx = tripCount - 1;
        printf("\n%-10s | %-20s | %-20s | %-16s | %-13s\n",
                "tripId", "Noi di", "Noi den", "Ngay gio", "Da dat/Tong");
        printf("-------------------------------------------------------------------------------\n");
        for (int i = startIdx; i <= endIdx; ++i) {
            printf("%-10s | %-20s | %-20s | %-16s | %3d/%-8d\n",
                trips[i].tripId, trips[i].departure.name, trips[i].destination.name,
                trips[i].date, trips[i].bookedSeats, trips[i].totalSeats);
        }
        printf("Trang %d / %d\n", pageNumber, totalPages);
        printf("\nNhap 'n' (Next), 'p' (Previous), 'q' (Quit), hoac so trang de chuyen: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        if (strcasecmp(input, "q") == 0) {
            break;
        } else if (strcasecmp(input, "n") == 0) {
            if (pageNumber < totalPages) pageNumber++;
            else printf("Da o trang cuoi cung!\n");
        } else if (strcasecmp(input, "p") == 0) {
            if (pageNumber > 1) pageNumber--;
            else printf("Da o trang dau tien!\n");
        } else {
            int newPage = 0;
            if (sscanf(input, "%d", &newPage) == 1 && newPage > 0 && newPage <= totalPages)
                pageNumber = newPage;
            else printf("So trang khong hop le.\n");
        }
    }
}

// Tim ticket theo ma ve (khong phan biet hoa thuong)
int findTicketIndexById(const char* ticketId) {
    for (int i = 0; i < ticketCount; ++i) {
        if (strcasecmp(tickets[i].ticketId, ticketId) == 0)
            return i;
    }
    return -1;
}

// Thanh toan ve 
void payTicket() {
    char ticketId[25];
    printf("Nhap ma ve can thanh toan: ");
    fgets(ticketId, sizeof(ticketId), stdin);
    ticketId[strcspn(ticketId, "\n")] = 0;

    if (isEmptyString(ticketId)) {
        printf("Ma ve khong duoc de trong\n");
        return;
    }
    int idx = findTicketIndexById(ticketId);
    if (idx == -1) {
        printf("Khong tim thay ve\n");
        return;
    }
    if (tickets[idx].status == 1 || tickets[idx].status == 2) {
        printf("Ve khong the thanh toan vi da bi vo hieu hoa\n");
        return;
    }
    if (tickets[idx].paymentStatus == 1) {
        printf("Ve da thanh toan truoc do\n");
        return;
    }
    tickets[idx].paymentStatus = 1;
    printf("Thanh toan thanh cong\n");
}

// Huy hoac khoa ve 
void cancel_lockTicket() {
    char ticketId[25];
    int action;
    printf("Nhap ma ve can thao tac (huy/khoa): ");
    fgets(ticketId, sizeof(ticketId), stdin);
    ticketId[strcspn(ticketId, "\n")] = 0;
    if (isEmptyString(ticketId)) {
        printf("Ma ve khong duoc de trong\n");
        return;
    }
    int idx = findTicketIndexById(ticketId);
    if (idx == -1) {
        printf("Khong tim thay ve\n");
        return;
    }
    if (tickets[idx].status == 1 || tickets[idx].status == 2) {
        printf("Ve da bi vo hieu hoa\n");
        return;
    }
    while (1) {
        printf("Chon thao tac: (1 = Khoa ve, 2 = Huy ve): ");
        char line[32];
        if (!fgets(line, sizeof(line), stdin)) {
            printf("Lua chon khong hop le\n");
            continue;
        }
        if (sscanf(line, "%d", &action) != 1) {
            printf("Lua chon khong hop le\n");
            continue;
        }
        if (action == 1) {
            tickets[idx].status = 2;
            printf("Khoa ve thanh cong\n");
            break;
        } else if (action == 2) {
            if (tickets[idx].paymentStatus == 1) {
                printf("Khong the huy vi ve da thanh toan\n");
                return;
            }
            int tripIdx = findTripIndexById(tickets[idx].tripId);
            if (tripIdx != -1 && trips[tripIdx].bookedSeats > 0) {
                trips[tripIdx].bookedSeats -= 1;
            }
            tickets[idx].status = 1;
            printf("Huy ve thanh cong\n");
            break;
        } else {
            printf("Lua chon khong hop le\n");
        }
    }
}

// Bao cao thong ke va doanh thu
void revenue_Ticketstatistic_report() {
    int type;
    char fromDate[32]="";
    char toDate[32]="";
    printf("=== BAO CAO DOANH THU & THONG KE VE ===\n");
    while (1) {
    printf("Nhap loai bao cao (1 = Doanh thu, 2 = Thong ke theo chuyen xe, 3 = Theo khoang thoi gian): ");
    char line[40];
    if (!fgets(line, sizeof(line), stdin)) continue;
    if (sscanf(line, "%d", &type) != 1) {
        printf("Loai bao cao khong hop le\n");
        continue;
    }
    if (ticketCount == 0) {
        printf("Khong co du lieu de bao cao\n");
        continue;
    }
    if (type == 1) {
        double totalRevenue = 0;
        int paidTickets = 0;
        for (int i = 0; i < ticketCount; ++i)
            if (tickets[i].paymentStatus == 1) {
                totalRevenue += tickets[i].price; paidTickets++;
            }
        printf("== BAO CAO DOANH THU ==\nTong doanh thu: %.0f VND\nTong ve da thanh toan: %d\n",
            totalRevenue, paidTickets);
    } else if (type == 2) {
        printf("== THONG KE VE THEO CHUYEN XE ==\n");
        printf("%-10s %-10s %-15s %-6s %-15s %-12s\n",
            "tripId", "Tong ve", "Da thanh toan", "Huy", "Con hieu luc", "Doanh thu");
        for (int t = 0; t < tripCount; ++t) {
            int totalTicket = 0, paid = 0, canceled = 0, valid = 0;
            double tripRevenue = 0;
            for (int i = 0; i < ticketCount; ++i) {
                if (strcasecmp(tickets[i].tripId, trips[t].tripId) == 0) {
                    totalTicket++;
                    if (tickets[i].status == 1) canceled++;
                    else if (tickets[i].status == 0) {
                        valid++;
                        if (tickets[i].paymentStatus == 1) {
                            paid++;
                            tripRevenue += tickets[i].price;
                        }
                    }
                }
            }
            printf("%-10s %-10d %-15d %-6d %-15d %-12.0f\n",
                trips[t].tripId, totalTicket, paid, canceled, valid, tripRevenue);
        }
    } else if (type == 3) {
        printf("Nhap ngay bat dau (YYYY-MM-DD HH:MM), bo qua neu khong loc theo ngay: ");
        fgets(fromDate, sizeof(fromDate), stdin);
        fromDate[strcspn(fromDate, "\n")] = 0;
        if (strlen(fromDate) > 0 && !isValidDateFormat(fromDate)) {
            printf("Ngay bat dau khong dung dinh dang (YYYY-MM-DD HH:MM)\n"); continue;
        }
        printf("Nhap ngay ket thuc (YYYY-MM-DD HH:MM), bo qua neu khong loc theo ngay: ");
        fgets(toDate, sizeof(toDate), stdin);
        toDate[strcspn(toDate, "\n")] = 0;
        if (strlen(toDate) > 0 && !isValidDateFormat(toDate)) {
            printf("Ngay ket thuc khong dung dinh dang (YYYY-MM-DD HH:MM)\n"); continue;
        }
        int filterByDate = strlen(fromDate) > 0 && strlen(toDate) > 0;
        if (filterByDate && strcmp(fromDate, toDate) > 0) {
            printf("Ngay bat dau phai nho hon hoac bang ngay ket thuc\n");
            continue;
        }
        int filtered = 0, canceled = 0, valid = 0;
        double revenue = 0;
        for (int i = 0; i < ticketCount; ++i) {
            int inside = 1;
            if (strlen(fromDate) > 0 && strcmp(tickets[i].date, fromDate) < 0) inside = 0;
            if (strlen(toDate) > 0 && strcmp(tickets[i].date, toDate) > 0) inside = 0;
            if (inside) {
                filtered++;
                if (tickets[i].status == 1) canceled++;
                else if (tickets[i].status == 0) {
                    valid++;
                    if (tickets[i].paymentStatus == 1)
                        revenue += tickets[i].price;
                }
            }
        }
        if (filtered == 0) {
            printf("Khong co du lieu trong khoang thoi gian chi dinh\n");
            continue;
        }
        printf("== BAO CAO VE TRONG KHOANG THOI GIAN ==\n");
        printf("Tong ve trong khoang thoi gian: %d\n", filtered);
        printf("Tong doanh thu: %.0f VND\n", revenue);
        printf("So ve huy: %d\n", canceled);
        printf("So ve con hieu luc: %d\n", valid);
    } else {
        printf("Loai bao cao khong hop le\n");
        continue; 
    }
    break; 
	}
}
