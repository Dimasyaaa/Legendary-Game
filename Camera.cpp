#include <iostream>
#include <conio.h>
using namespace std;
const int max_map=10;

class Camera{
private:
    int camera_pos_x; //Позиция камеры по х и у
    int camera_pos_y;
    int zoom;         //Величена приближения
public:
    Camera(int coord_x, int coord_y, int zom): camera_pos_x(coord_x), camera_pos_y(coord_y), zoom(zom){}

    //Трансляция. Внутрь передаётся обьект трансляции - двумерный массив символов.
    //Количество выводимы символов соответствует формуле(max_map/zoom) ( при максимальном размере
    // карты 10, если зум равен 2 то выведится 5 символов. Если zoom  равен 3 то 3)
    void broadcast (  unsigned char broadcast_object[max_map][max_map]){
        for (int i = camera_pos_x ; i < camera_pos_x + max_map/zoom ; i++) {
          for (int j = camera_pos_y; j < camera_pos_y + max_map/zoom; j++)
                cout << broadcast_object[i][j] << ' ';
          cout << endl;
        }

    }
    // метод для установки позиции камеры. Символы выводятся начиная с сивмовла находящегося на позиции камеры
    void link(int coord_x, int coord_y){  //привязка камеры к точке
        camera_pos_x = coord_x;
        camera_pos_y = coord_y;
    }


};
///TEST
int main(){
    //Тестовый лабиринт
 setlocale(LC_ALL, "");
unsigned char mapp [max_map][max_map];
 for(int i = 0; i < max_map ; i++){
    for(int j = 0; j < max_map ; j++){
        mapp[i][j]= '#';
    }
 }
// Тестовый участок который поpволит разлечить кадры камеры
 for(int i = 3; i < 5 ; i++){
    for(int j = 3; j < 6 ; j++){
        mapp[i][j]= '*';
    }
 }

char button = '/';
 Camera sone(3,3,3);
int buf_x;
int buf_y;
// Цикл в котором всё должно происходит
while (button != '=') {

// Вывод всей карты для сравнения
for(int i = 0; i < max_map ; i++){
    for(int j = 0; j < max_map ; j++){
        cout << mapp[i][j] << ' ';
    }
    cout<<endl;
 }

cout<<endl;

   sone.broadcast(mapp);
   cout<< "введите новую позицию"<<endl;
   cout<<"поз_1: "; cin >> buf_x;
   cout<<"поз_1: "; cin >> buf_y;
   sone.link(buf_x,buf_y);
   cout<<"выход?";
   button = (char)_getch();
   system("cls");

}
}
///TEST
