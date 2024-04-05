#include <iostream>
#include<conio.h>
#include <cstdlib>
#include <Windows.h>  //thêm thư viện này để set sleep cho game chậm lại
using namespace std;
bool gameOver; 
const int width = 40; // sử dụng hằng số để set up map - thiết lập bản đồ 20x20
const int height = 20;
int x, y, fruitX, fruitY, score; // khai báo biến tạo độ x,y , thức ăn ,điểm
int tailX[100], tailY[100]; // tọa độ của phần thân rắn taiX là phần O to, tailY là phần ooo nhỏ
							//set cho 2 mảng có giới hạn thân đuôi = 100
int nTail; // chỉ định tổng độ dài của đuôi
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN }; // set phương hướng cho snake 
eDirection dir; // sử dụng để đổi tên thôi - dir viết gọn lại của eDirection 
				// hàm enum đc gán vào 1 giá trị nhất định bắt buộc p viết hoa
void Setup()
{
	gameOver = false;
	dir = STOP; // set direction cho con rắn dừng lại
	x = width / 2; //cho x là đầu rắn = w/2 và y là thân rắn = h/2 để rắn ở giữa trung tâm
	y = height / 2;
	fruitX = rand() % width; // set thức ăn random số từ 0 đến chiều rộng
	fruitY = rand() % height; 
	score = 0;
	nTail = 0;
}


void Draw()
{
	system("cls"); // sử dụng hàm CLS để clear windown

	/*bản đồ của cta sẽ dạng như này
	######
	#    #
	######*/

	//tường trên cùng-top
	for (int i = 0; i < width+2; i++) { //sử dụng vl for để tạo border top -viền trên cùng của map
		cout << "#";   //in ra bức tường trên cùng của bản đồ
	}
	cout << endl;


	// ở giữa là map -middle
	//sử dụng 2 vòng lặp lồng nhau
	for (int i = 0; i < height; i++) { //đặt height trước width vì đã set dc 2 bức tường
										//rồi giờ set bước tường ở giữa theo chiều rộng 
										//nên set width trong vòng lặp j
		for (int j = 0; j < width; j++) {
			if (j == 0) { //Nếu j ở kí tự đầu tiên index = 0 thì in ra # 
				cout << "#";
			}
			// in ra đầu rắn và fruit
			if (i == y && j == x) { // y = height/2 => i sẽ có tọa độ = 10; 
									// x = width/2 => j sẽ có tọa độ = 10;   => con rắn sẽ ở giữa trung tâm bản đồ
				cout << "O"; // đầu rắn
			}
			else if (i == fruitY && j == fruitX) { //set random thức ăn theo tọa độ i,j
				cout << "F";
			}
			else {
				bool print = false;			  // muốn in ra phần tử đuôi đi theo phía sau đầu thì ta cần set kdl bool
				for (int k = 0; k < nTail; k++) { //vì có vòng lăpj for i rồi nên phải đổi tên
					if (tailX[k] == j && tailY[k] == i) {	// khi index của cái đuôi ở tọa độ i,j thì nó sẽ in ra phần tử đuôi o nhỏ
						cout << "o";
						print = true;   // nếu print =true thì sẽ chạy vùng else bên dưới sử dụng kdl bool để tách 2 thứ là khoảng trống và phần đuôi ra
					}
					
				}
				if (!print) {	// set như vậy vì trong kdl bool thì đang = true khi set đk if tự khắc nhẩy sang false nên ta phải set (!print)
					cout << " "; //nếu i,j ở những index tiếp theo khác 0 thì in ra kí tự trống
				}
			}
			if (j == width-1) {
				cout << "#";
			}
			
		}
		cout << endl;
	}

	//tường dưới cùng -bottom
	for (int i = 0; i < width+2;i++) {
		cout << '#';
	}
	cout << endl;
	cout << "Score : " << score <<endl;
}

/*	    
* kí tự của bảng ASCII

		w // là lên

a//sang trái		d //là sang phải

	    s // là xuống   */


void Input()
{							//hàm _kbhit() là hàm ktra sự kiện nhấn phím
	if (_kbhit()) {			//hàm _getch() là hàm bắt sự kiện 1 phím
		switch (_getch())	// vì khi dùng hàm _getch() thì trả về kí tự ASCII nên cta dùng switch case để biến đổi
		{
		case'a':
			dir = LEFT;
			break;
		case'd':
			dir = RIGHT;
			break;
		case'w':
			dir = UP;
			break;
		case's':
			dir = DOWN;
			break;
		case'x':			// nếu trường hợp muốn dừng game thoát ra thì chúng ta sẽ ấn x
			gameOver = true;
			break;
		}
		
	}
}

void Logic()
{
	int prevX = tailX[0];  // tọa độ x trước đó sẽ = phần đuôi tailX thứ 1
	int prevY = tailY[0];  // tọa độ y trước đó sẽ = phần đuôi tailY thứ 1
	tailX[0] = x;			// sau khi tạo kdl bool vẫn k chạy dc ta cần :
	tailY[0] = y;			// prevX dc gán bằng các pt đuôi, ta gán pt đuôi cho x vì x = i => khi pt đuôi tăng thì prevX tăng thì x tăng lúc đấy sẽ in ra các pt đuôi nhỏ phía sau đầu
	int prev2X, prev2Y;
	for (int i = 1; i < nTail; i++) {   //set i =1 bởi vì cta đã có vị trí đuôi đầu tiên index 0 rồi 
		prev2X = tailX[i];				// cta phải tạo ra biến prev2X chỉ để gán gtri tailX[i] cho prevX
		prev2Y = tailY[i];				// để khi vòng lặp duyệt qua từng phần tử nuôi nó sẽ tự động tăng index của tailX[0] đã đc gán từ trước
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)	  // điều khiển phương hướng
	{
	case LEFT:
		x--;			// x là đầu rắn , x-- => lùi vè 1 đơn vị
		break;
	case RIGHT:
		x++;			// tiến lên 1 đơn vị
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:			// dafault chạy khi không có case nào hợp lệ
		break;
	};
	if (x >= width || x<0 || y>=height || y < 0) {
		
			gameOver = true;
	}
	for (int i = 0; i < nTail; i++) {      // set để nếu con rắn chạm vào thân nó thì gameOver
		if (tailX[i] == x && tailY[i] == y) { 
			gameOver = true;
		}
	}
	if (x >= width) {			// set để khi con  rắn đi ra khỏi bản đồ thì quay lại ở đầu bên kia
		x == 0;					// có 2 cách 1 là cho nó đâm vào tường thì chết 2 là đi xuyên qua tường
	}
	else if (x==0)
	{
		x = width - 1;
	}
	if (y >= height) {
		y == 0;
	}
	else if (y == 0) {
		y == height - 1;
	}
	if (x == fruitX && y == fruitY) {		// khi đầu rắn là x di chuyển đến fruitX thì lúc đó sẽ random nhảy sang số khác
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
}
int main()
{
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(20);
	}
}