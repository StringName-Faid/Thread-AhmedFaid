#include <iostream>
#include <thread>
#include <vector>
#include <stdlib.h>
#include <mutex>

using namespace std;

mutex print;

int NumGenerator(int max, int min){
     int n = (max - min + 1);
     int random = rand()%n + min;

     return random;
}

void filler(vector<int> *container, mutex *m){

    m->lock();
    container->resize(NumGenerator(10000, 100000));

    for(int i=0; i < container->size(); i++){
        (*container)[i] = NumGenerator(0,100000);
    }
    m->unlock();

}

void printer(vector<int> *container, mutex *m){

    while(container->size() == 0)
        ;
    m->lock();
    print.lock();
    for(int i=0; i < container->size(); i++){
        cout << (*container)[i] << endl;
    }
    print.unlock();
    m->unlock();
}

int main(){

    mutex cont1, cont2, cont3;

    vector<int> firstContainer;
    vector<int> secondContainer;
    vector<int> thirdContainer;

    thread t1(&filler, &firstContainer, &cont1);
    thread t2(&filler, &secondContainer, &cont2);
    thread t3(&filler, &thirdContainer, &cont3);

    thread t4(&printer, &firstContainer, &cont1);
    thread t5(&printer, &secondContainer, &cont2);
    thread t6(&printer, &thirdContainer, &cont3);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();

    return 0;
}
