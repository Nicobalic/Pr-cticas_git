#include <iostream>
#include <fstream>
#include <cstdlib>//para exit(1)
#include <string>

#define FILAS 3
#define COLUMNAS 3

    using namespace std;

    struct partida {
    char tablero_estructura[FILAS][COLUMNAS]={{'-','-','-'},{'-','-','-'},{'-','-','-'}};
    int valor_x;
    int valor_y;
    string ganador="None";
    int *victorias;
    int rondas =1;
    }; 

    char indicador_empate='F';
    char bandera='F';
    char abrir_archivo='n';

void archivo_torneo(string nombre_archivo, partida *J1){

    ifstream archivo2(nombre_archivo.c_str(), ios::binary);

    ofstream archivo_torneo1("Puntajes.bin", ios::binary);
    if(!archivo_torneo1){
    cerr<<" \n error en la creacion del archivo \n";
    }

    archivo2.read(reinterpret_cast<char*>(&J1->ganador), sizeof(J1->ganador));
    archivo2.read(reinterpret_cast<char*>(&J1->rondas), sizeof(J1->rondas));

    archivo_torneo1.write(reinterpret_cast<char*>(&J1->ganador), sizeof(J1->ganador));
    archivo_torneo1.write(reinterpret_cast<char*>(&J1->rondas), sizeof(J1->rondas));

    archivo2.close();
    archivo_torneo1.close();

}

void archivo_partida(partida *J1){
    
    string nombre_archivo;
    J1->victorias=new int[2];

    if(abrir_archivo=='T'){
    cout<<"\n que nombre le desea poner al archivo, por favor con la extension.bin\n";
    cin>>nombre_archivo;
    }
    ofstream archivo1(nombre_archivo.c_str(), ios::binary);
    if(!archivo1){
    cerr<<" error en la apertura del archivo"<<endl;
    }

    archivo1.write(reinterpret_cast<char*>(&J1->ganador), sizeof(J1->ganador));
    archivo1.write(reinterpret_cast<char*>(&J1->rondas), sizeof(J1->rondas));
    archivo1.close();

    ifstream archivo2(nombre_archivo.c_str(), ios::binary);
    if(!archivo2){
    cerr<<" error en la apertura del archivo"<<endl;
    }

    archivo2.read(reinterpret_cast<char*>(&J1->ganador), sizeof(J1->ganador));
    archivo2.read(reinterpret_cast<char*>(&J1->rondas), sizeof(J1->rondas));
    cout<<"\n leyendo datos \n"<<J1->ganador<<" Ronda: "<<J1->rondas<<endl;
    archivo2.close();
    archivo_torneo(nombre_archivo, J1);
    
}

void tablero (partida *J1){
    int eje_y[]={1,2,3};
    int *apuntador_eje_y=eje_y;

    cout<<"  1 "<<"2 "<<"3"<<endl;

    for(int i=0;i<FILAS;i++){
    cout<<*(apuntador_eje_y+i)<<" ";
    for(int j=0;j<COLUMNAS;j++){
        cout<<J1->tablero_estructura[i][j]<<" ";
            } 
    cout<<endl;
        }       
}

void algoritmo(partida *J1, partida *J2, partida *valor_x, partida*valor_y, int **apuntador_rondas){
    char *apuntador_bandera;
    apuntador_bandera=&bandera;
    for(int i=0;i<FILAS;i++){
        for(int j=0;j<COLUMNAS;j++){

                if(j<=COLUMNAS-3){
                if((J1->tablero_estructura[i][j]=='X'&&J1->tablero_estructura[i][j+1]=='X'&&J1->tablero_estructura[i][j+2]=='X')||
                (J1->tablero_estructura[i][j]=='O'&&J1->tablero_estructura[i][j+1]=='O'&&J1->tablero_estructura[i][j+2]=='O'))
                {
                    bandera='T';
                }
                }

                if(i<=FILAS-3){
                if((J1->tablero_estructura[i][j]=='X'&&J1->tablero_estructura[i+1][j]=='X'&&J1->tablero_estructura[i+2][j]=='X')||
                (J1->tablero_estructura[i][j]=='O'&&J1->tablero_estructura[i+1][j]=='O'&&J1->tablero_estructura[i+2][j]=='O'))
                {
                    bandera='T';
                }
                }

                if(i<=FILAS-3&&j<=COLUMNAS-3){
                if((J1->tablero_estructura[i][j]=='X'&&J1->tablero_estructura[i+1][j+1]=='X'&&J1->tablero_estructura[i+2][j+2]=='X')||
                (J1->tablero_estructura[i][j]=='O'&&J1->tablero_estructura[i+1][j+1]=='O'&&J1->tablero_estructura[i+2][j+2]=='O'))
                {
                    bandera='T';
                }
                }

                if(i<=FILAS-3&&j>=2){
                if((J1->tablero_estructura[i][j]=='X'&&J1->tablero_estructura[i+1][j-1]=='X'&&J1->tablero_estructura[i+2][j-2]=='X')||
                (J1->tablero_estructura[i][j]=='O'&&J1->tablero_estructura[i+1][j-1]=='O'&&J1->tablero_estructura[i+2][j-2]=='O'))
                {
                    bandera='T';
                }
                } 

                //--------------------------------------------------------------------------------------------------------------------------

                /*if(j<=COLUMNAS-3){
                    if((J1->tablero_estructura[i][j]=='X'&&J1->tablero_estructura[i][j+1]=='O'&&J1->tablero_estructura[i][j+2]=='-')||
                    (J1->tablero_estructura[i][j]=='O'&&J1->tablero_estructura[i][j+1]=='X'&&J1->tablero_estructura[i][j+2]=='X'))
                    {
                        indicador_empate='V';
                    }
                        indicador_empate='F';
                    }

                    if(i<=FILAS-3){
                    if((J1->tablero_estructura[i][j]=='X'&&J1->tablero_estructura[i+1][j]=='X'&&J1->tablero_estructura[i+2][j]=='X')||
                    (J1->tablero_estructura[i][j]=='O'&&J1->tablero_estructura[i+1][j]=='O'&&J1->tablero_estructura[i+2][j]=='O'))
                    {
                        indicador_empate='V';
                    }
                        indicador_empate='F';   
                    }

                    if(i<=FILAS-3&&j<=COLUMNAS-3){
                    if((J1->tablero_estructura[i][j]=='X'&&J1->tablero_estructura[i+1][j+1]=='X'&&J1->tablero_estructura[i+2][j+2]=='X')||
                    (J1->tablero_estructura[i][j]=='O'&&J1->tablero_estructura[i+1][j+1]=='O'&&J1->tablero_estructura[i+2][j+2]=='O'))
                    {
                        indicador_empate='V'; 
                    }
                         indicador_empate='F';
                    }

                    if(i<=FILAS-3&&j>=2){
                    if((J1->tablero_estructura[i][j]=='X'&&J1->tablero_estructura[i+1][j-1]=='X'&&J1->tablero_estructura[i+2][j-2]=='X')||
                    (J1->tablero_estructura[i][j]=='O'&&J1->tablero_estructura[i+1][j-1]=='O'&&J1->tablero_estructura[i+2][j-2]=='O'))
                    {
                        indicador_empate='V'; 
                    }
                        indicador_empate='F';
                    } */

            }
            cout<<endl; 
        }
        cout<<bandera;
    }   

void juego(partida *J1, partida *J2, partida *valor_x, partida*valor_y, int **apuntador_rondas){

    int binario=0;
    J1->victorias=new int[2];

    tablero(J1);
    while(bandera=='F'){

    cout<<endl<<" jugador 1 el tablero es el siguiente "<<endl;
    tablero(J1);
    cout<<endl<<" digite su X y Y"<<endl;

    do{
    cout<<"\ndigite valores dentro del rango\n";
    cin>>J1->valor_x;
    cin>>J1->valor_y;
    }while((J1->tablero_estructura[J1->valor_x-1][J1->valor_y-1]=='X')||(J1->tablero_estructura[J1->valor_x-1][J1->valor_y-1]=='O'));

    for(int i=1;i<=FILAS;i++){
        for(int j=1;j<=COLUMNAS;j++){
        J1->tablero_estructura[J1->valor_x-1][J1->valor_y-1]='O';
    }
    cout<<endl;
    }
    algoritmo(J1,J2, valor_x, valor_y, &(*apuntador_rondas));
        if(bandera=='T'){
        J1->ganador="J1";
        break;
        } 
        if(indicador_empate== 'V'){
        bandera='E';
        }

    cout<<endl<<" jugador 2 el tablero es el siguiente "<<endl;
    tablero(J1);
    cout<<endl<<" digite su X y Y"<<endl;

    do{
    cout<<"\ndigite valores dentro del rango\n";
    cin>>J2->valor_x;
    cin>>J2->valor_y;
    }while((J1->tablero_estructura[J2->valor_x-1][J2->valor_y-1]=='X')||(J1->tablero_estructura[J2->valor_x-1][J2->valor_y-1]=='O'));

    for(int i=1;i<=FILAS;i++){
        for(int j=1;j<=COLUMNAS;j++){
        J1->tablero_estructura[J2->valor_x-1][J2->valor_y-1]='X';
    }
    cout<<endl;
    }

    algoritmo(J1,J2, valor_x, valor_y, &(*apuntador_rondas));
    if(indicador_empate== 'V'){
    bandera='E';
    }

    if(bandera=='T'){
        J1->ganador="J2";
        break;
    }

    tablero(J1); 

        }

    if(J1->ganador=="J1"){
        cout<<"\n Felicidades jugador uno, has ganado\n";
        J1->victorias[0]=1;
        J1->victorias[1]=0;
        for(int i=0;i<FILAS;i++){
            for(int j=0;j<COLUMNAS;j++){
            J1->tablero_estructura[i][j]='-';
            }
            cout<<endl;
        }
        bandera='F';
        J1->ganador="none";
    }else if(J1->ganador=="J2"){
        cout<<"\n Felicidades jugador dos, has ganado\n";
        J1->victorias[0]=0;
        J1->victorias[1]=1;
        for(int i=0;i<FILAS;i++){
        for(int j=0;j<COLUMNAS;j++){
        J1->tablero_estructura[i][j]='-';
        }
        cout<<endl;
        }
        bandera='F';
        J1->ganador="none";
    }else{
        cout<<"\n Hubo un empate\n";
        J1->victorias[0]=0;
        J1->victorias[1]=0;
        for(int i=0;i<FILAS;i++){
        for(int j=0;j<COLUMNAS;j++){
        J1->tablero_estructura[i][j]='-';
        }
         cout<<endl;
        }
        bandera='F';
        J1->ganador="none";
    }

    cout<<"\n\ndesea guardar los puntajes en un archivo binario?  1.si   2.no\n";
    cin>>binario;
    if(binario==1){
        archivo_partida(J1);
        abrir_archivo='T';
    }else{
    cout<<" \nNo se van a gurdar los datos\n";
        abrir_archivo='F';
        archivo_partida(J1);
    }

}   

void lobby(int *apuntador_rondas, partida *J1, partida *J2, partida *valor_x, partida *valor_y, string nombre_archivo){
    int opcion =0;

    cout<<endl<<"JUGAR(1) VER PUNTAJES(2) SALIR DEL JUEGO(3) "<<endl;
    cin>>opcion;

    while(J1->rondas<*apuntador_rondas+1){
        if(opcion==1){
    for(int j=1;j<=*apuntador_rondas;j++){
    cout<<"\n RONDA: "<<j<<"\n\n\n";
    juego(J1, J2, valor_x, valor_y, &apuntador_rondas);       
        }
        }else if(opcion==2){
    archivo_torneo(nombre_archivo, &(*J1));
        }else if(opcion==3){

    cout<<"\nsaliendo del juego........\n";
    exit(1);

    }	
    J1->rondas++;
        }
    }       
int main(){
    int *apuntador_rondas=NULL;
    int rondas = 0;
    partida J1;
    partida J2;
    partida valor_x;
    partida valor_y;
    string nombre_archivo;

    cout<<" cuantas rondas desean jugar"<<endl;
    cin>>rondas;

    apuntador_rondas=&rondas;
    lobby(&rondas, &J1, &J2, &valor_x, &valor_y, nombre_archivo);
    return 0;
    }