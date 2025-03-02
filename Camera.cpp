#include <iostream>
#include <conio.h>
using namespace std;
class Camera{
private:
    int camera_pos_x;
    int camera_pos_y;
    int zoom;
public:
    Camera(int coord_x, int coord_y, int zom): camera_pos_x(coord_x), camera_pos_y(coord_y), zoom(zom){}

    void broadcast ( unsigned char **broadcast_object, int size_object){  //трансляция
        for (int i = camera_pos_x ; i < size_object/zoom ; i++) {
          for (int j = camera_pos_y; j < size_object/zoom; j++)
                cout << broadcast_object[i][j] << endl;
        }
    }
    void link(int coord_x, int coord_y){  //привязка камеры к точке
        camera_pos_x = coord_x;
        camera_pos_y = coord_y;
    }


};
///TEST
int main(){
    //Тестовый лабиринт
   int max_map=10;
unsigned char mapp [max_map][max_map];
 for(int i = 0; i < max_map ; i++){
    for(int j = 0; j < max_map ; j++){
        mapp[i][j]= '#';
    }
 }
// Тестовый участок который похволит разлечить кадры камеры
 for(int i = 3; i < 5 ; i++){
    for(int j = 3; j < 6 ; j++){
        mapp[i][j]= '*';
    }
 }



char button = '/';


// Цикл в котором всё должно происходит
while (button != '=') {
   button = (char)_getch();
   system("cls");

}
}
///TEST
