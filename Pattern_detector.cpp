#include "Pattern_detector.h"

Pattern_detector::Pattern_detector(){
    in_file.open(IN_FILE_NAME,std::ios::in);
    out_file.open(OUT_FILE_NAME,std::ios::out);
    state=0;
    pattern_size=0;
    pattern_ori_size=0;
    repeat_start=0;
    repeat_end=0;
    sum=0;
    repeat_sum=0;
    pattern_tail_repeat=false;
}
Pattern_detector::~Pattern_detector(){
    in_file.close();
    out_file.close();
}
void Pattern_detector::build_default_function(){
    int j=0;
    default_function[0]=-1;
    for(int i=1;i<pattern_size;i++){
        if(pattern[i]==pattern[j]){
            default_function[i]=j;
            j++;
        }else{
            default_function[i]=-1;
            j=0;
        }
    }
}

bool Pattern_detector::analyze(){
    ///Read the pattern to detect.
    char sym=' ';
    std::string str;
    std::cout<<"Please input the pattern: ";
    std::cin>>str;
    for(auto c:str){
        if(c=='(') {sym='(';repeat_start=pattern_size;}
        else if(c==')') {if(sym!='(') {break;} else {sym=')';repeat_end=pattern_size-1;}}
        else if(c=='+') {if(sym!=')') {break;} else {sym='+';}}
        else {pattern[pattern_size++]=c;}
        pattern_ori[pattern_ori_size++]=c;
    }
    if((sym!='+'&&sym!=' ')||(!pattern[0])) return false;//Detect weather the user input correctly.
    if(repeat_end==pattern_size-1) pattern_tail_repeat=true;

    ///Build the default function.
    build_default_function();

    return true;
}

void Pattern_detector::print(){
    std::cout<<"\n\n--------------------------<      Count Report      >--------------------------\n\n";
    std::cout<<"The function is successfully loaded and operated.\n";
    std::cout<<"Pattern Sequence  : ";
    for(int i=0;i<pattern_ori_size;i++) std::cout<<" "<<pattern_ori[i];
    std::cout<<"\n"<<"Default Function  : ";
    for(int i=0;i<pattern_size;i++){
        std::cout<<" ["<<pattern[i]<<"->"<<std::setw(2)<<default_function[i]<<"] ";
        if(i%5==4) std::cout<<"\n                    ";
    }
    std::cout<<"\n"<<"Repeat Times      :  "<<repeat_sum<<"\n";

    out_file<<"\n\n--------------------------<      Count Report      >--------------------------\n\n";
    out_file<<"The function is successfully loaded and operated.\n";
    out_file<<"Pattern Sequence  : ";
    for(int i=0;i<pattern_ori_size;i++) out_file<<" "<<pattern_ori[i];
    out_file<<"\n"<<"Default Function  : ";
    for(int i=0;i<pattern_size;i++){
        out_file<<" ["<<pattern[i]<<"->";
        out_file<<(default_function[i]==-1?"":" ");
        out_file<<default_function[i]<<"] ";
        if(i%5==4) out_file<<"\n                    ";
    }
    out_file<<"\n"<<"Repeat Times      :  "<<repeat_sum<<"\n";
}

bool Pattern_detector::run(){
    ///examine if the file doesn't work.
    if(!in_file) return false;

    ///Get every character in the text and analyze it.
    ///Priority: repeat part > default function > normal compare.
    char ch;
    int i=0;
    bool repeat_add=false;

    std::cout<<"\n--------------------------<    Original contain    >--------------------------\n\n";
    while(!in_file.eof()){
        in_file.get(ch);
        std::cout<<ch;
        sum++;
        if(ch==pattern[i]){
            if(i==repeat_end&&pattern_tail_repeat){
                i=repeat_start;
                if(!repeat_add){repeat_add=true;repeat_sum++;}
            }
            else if(i==pattern_size-1) {i=0;repeat_sum++;}
            else {i++;}
        }
        else if(ch!=pattern[i]&&i){
            while(i>0&&pattern[i]!=ch){
                i=default_function[i-1]+1;
            }
            i++;
        }
        else{repeat_add=false;}
    }
    print();
    return true;
}

void Pattern_detector::start(){
    ///Analyze the input and build default function.
    if(!analyze()){
        std::cout<<"\n--------------------------< The pattern is illegal >--------------------------\n";
        std::cout<<"Message: 01; The input format is not correct.\n";
        return;
    }

    ///Start to detect the pattern exiting in the text.
    if(!run()){
        std::cout<<"\n--------------------------<Failing to read the file>--------------------------\n";
        std::cout<<"Message: 02; Something wrong with the file loading.\n";
        return;
    }
}
