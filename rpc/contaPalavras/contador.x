/* contador.x */
struct Palavra {
    string texto<128>;
};

struct Resposta {
    string resultado<1024>;
};

program CONTADOR_PROG {
    version CONTADOR_VERS {
        Resposta contabilizar_palavra(Palavra) = 1;
    } = 1;
} = 55555555;
