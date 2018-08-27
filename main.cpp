#include "Pattern_detector.h"

int main(void){
    Pattern_detector* pd=new Pattern_detector;
    pd->start();
    delete pd;
    return 0;
}
