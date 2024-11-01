#include <iostream>
#include <thread>
#include "timer.cpp"
 using namespace std;

 
int main() {
    Timer timer1;
    timer1.start();
    this_thread::sleep_for(chrono::seconds(3));
    timer1.stop();
    cout << "Example 1: Elapsed time: " << timer1.elapsed() << " seconds" << endl;
    timer1.pretty_print();

   
    Timer timer2;
    timer2.start();
    this_thread::sleep_for(chrono::seconds(2));
    timer2.start(); 
    this_thread::sleep_for(chrono::seconds(1));
    timer2.stop();
    cout << "Example 2: Elapsed time: " << timer2.elapsed() << " seconds" << endl;
    timer2.pretty_print();

    Timer timer3;
    timer3.stop();
    cout << "Example 3: Elapsed time: " << timer3.elapsed() << " seconds" << endl;
    timer3.pretty_print();

    Timer timer4;
    timer4.start();
    this_thread::sleep_for(chrono::seconds(1));
    cout << "Example 4: Elapsed time (running): " << timer4.elapsed() << " seconds" << endl;
    this_thread::sleep_for(chrono::seconds(2));
    timer4.stop();
    cout << "Example 4: Elapsed time (stopped): " << timer4.elapsed() << " seconds" << endl;
    timer4.pretty_print();

    Timer timer5(5); 
    Timer timer6(2); 
    Timer timer7 = timer5.add(timer6);
    cout << "Example 5: Addition: " << timer7.elapsed() << " seconds" << endl;
    timer7.pretty_print();
    Timer timer8 = timer5.subtract(timer6);
    cout << "Example 5: Subtraction: " << timer8.elapsed() << " seconds" << endl;
    timer8.pretty_print();

    return 0;
}
