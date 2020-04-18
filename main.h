#define NOT_LEGAL -1
#define LEGAL 1
int check(int num, std::string mode){ //TODO: add validiations
    if (num < 0){
        std::cout << "proper message" << mode;
        return NOT_LEGAL;
    }
    return LEGAL;
}