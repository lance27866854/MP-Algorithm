#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <iomanip>
#define IN_FILE_NAME "text.txt"
#define OUT_FILE_NAME "report.txt"
#define SIZE 100

///Actually, it is the implement of MP algorithm.
///1.The input only for the English characters(26 items).
///For example, "aass" is legal, while "$$%^&++--" is illegal.
///2.You can use () and + to represent repeat in the pattern.
///For example, "s(aa)+" means that we need to find a 's' and even numbers of 'a'. (Not including 0 time.)
///3.It can only reads one layer. No recursion in the project.
///For example, "s(s(aa)+)+" is illegal.
///4.Be careful when you come up with a pattern. The repeat part should be well arranged.
///For example, "as(as)+a" is illegal, and the right one is "(as)+a"

class Pattern_detector{
    public:
        Pattern_detector();
        ~Pattern_detector();
        void start();

    private:
        bool analyze();
        bool run();
        void build_default_function();
        void print();

        std::ifstream in_file;
        std::ofstream out_file;
        int default_function[SIZE]={0};
        char pattern[SIZE]={0};
        char pattern_ori[SIZE]={0};
        int state;
        int pattern_size,pattern_ori_size;
        int repeat_start, repeat_end;
        int sum, repeat_sum;
        bool pattern_tail_repeat;
};
