#include <iostream>
#include <conio.h>
using namespace std;
const int max_map=10;

class Camera{
private:
    int camera_pos_x; //������� ������ �� � � �
    int camera_pos_y;
    int zoom;         //�������� �����������
public:
    Camera(int coord_x, int coord_y, int zom): camera_pos_x(coord_x), camera_pos_y(coord_y), zoom(zom){}

    //����������. ������ ��������� ������ ���������� - ��������� ������ ��������.
    //���������� �������� �������� ������������� �������(max_map/zoom) ( ��� ������������ �������
    // ����� 10, ���� ��� ����� 2 �� ��������� 5 ��������. ���� zoom  ����� 3 �� 3)
    void broadcast (  unsigned char broadcast_object[max_map][max_map]){
        for (int i = camera_pos_x ; i < camera_pos_x + max_map/zoom ; i++) {
          for (int j = camera_pos_y; j < camera_pos_y + max_map/zoom; j++)
                cout << broadcast_object[i][j] << ' ';
          cout << endl;
        }

    }
    // ����� ��� ��������� ������� ������. ������� ��������� ������� � �������� ������������ �� ������� ������
    void link(int coord_x, int coord_y){  //�������� ������ � �����
        camera_pos_x = coord_x;
        camera_pos_y = coord_y;
    }


};
///TEST
int main(){
    //�������� ��������
 setlocale(LC_ALL, "");
unsigned char mapp [max_map][max_map];
 for(int i = 0; i < max_map ; i++){
    for(int j = 0; j < max_map ; j++){
        mapp[i][j]= '#';
    }
 }
// �������� ������� ������� ��p����� ��������� ����� ������
 for(int i = 3; i < 5 ; i++){
    for(int j = 3; j < 6 ; j++){
        mapp[i][j]= '*';
    }
 }

char button = '/';
 Camera sone(3,3,3);
int buf_x;
int buf_y;
// ���� � ������� �� ������ ����������
while (button != '=') {

// ����� ���� ����� ��� ���������
for(int i = 0; i < max_map ; i++){
    for(int j = 0; j < max_map ; j++){
        cout << mapp[i][j] << ' ';
    }
    cout<<endl;
 }

cout<<endl;

   sone.broadcast(mapp);
   cout<< "������� ����� �������"<<endl;
   cout<<"���_1: "; cin >> buf_x;
   cout<<"���_1: "; cin >> buf_y;
   sone.link(buf_x,buf_y);
   cout<<"�����?";
   button = (char)_getch();
   system("cls");

}
}
///TEST
