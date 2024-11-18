struct operandos{
    int x;
    int y;
};
program CALCULA_PROG{
    version CALCULA_VERS{
        int adicao(operandos) = 1;
        int subtracao(operandos) = 2;
        int multiplicacao(operandos) = 3;
        int divisao(operandos) = 4;
    } = 1;
} = 55555;