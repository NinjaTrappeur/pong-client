#include "mainwindow.h"

#include <QApplication>
#include <iostream>
#include <cstring>

int main(int argc, char *argv[])
{
    //Verification des parametres
    int i=1;
    bool correctParameter=true;
    bool port= false, add=false, host=false;
    while(i<argc && correctParameter==true)
    {
        if( strcmp(argv[i], "-p") == 0 )
            port=true;
        else if( strcmp(argv[i],"-h"))
            host=true;
        else if( strcmp(argv[i],"-a"))
            add=true;
        else
            correctParameter=false;
        i+=2;
    }
    if(port == false)
        correctParameter=false;
    if(host== false && add==false)
        correctParameter=false;
    if(host==true && add==true)
        correctParameter=false;

    if(correctParameter)
    {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    return a.exec();
    }

    else{
        std::cout<<std::endl;
        std::cout<<"Merci d'utiliser le client pong comme suit:"<<std::endl;
        std::cout<<"-p PORT avec PORT le port sur lequel le serveur écoute"<<std::endl;
        std::cout<<"-h HOSTNAME avec HOSTNAME le nom de domaine du serveur"<<std::endl;
        std::cout<<"-A ADRESS avec ADRESS l'adresse ipv4 du serveur"<<std::endl;
        std::cout<<"Merci de ne pas spécifier en meme temps une adresse ipv4 et un nom de domaine."<<std::endl;
        return 1;
    }
}
