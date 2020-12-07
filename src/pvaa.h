//funcoes para mudar cor
void vermelho(){
    printf("\033[0;31m");
}
void bVermelho(){
    printf("\033[1;31m");
}
void verde(){
    printf("\033[0;32m");
}
void amarelo(){
    printf("\033[0;33m");
}
void azul(){
    printf("\033[0;34m");
}
void magenta(){
    printf("\033[0;35m");
}
void ciano(){
    printf("\033[0;36m");
}
void reset (){
    printf("\033[0m");
}
void estetica1(){
    azul();
    printf("=--------====----=======--=========--=======----====--------=\n");
    reset();
}
