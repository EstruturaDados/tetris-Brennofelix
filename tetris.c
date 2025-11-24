#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define MAX 5

// ---------------------------------------------
// Struct da peça
// ---------------------------------------------
typedef struct {
    char tipo;   // Tipo da peça (char)
    int id;      // ID sequencial
} Peca;

// ---------------------------------------------
// Fila circular
// ---------------------------------------------
typedef struct {
    Peca itens[MAX];
    int inicio;
    int fim;
    int total;
} Fila;


// ---------------------------------------------
// Funções da fila
// ---------------------------------------------
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

bool filaCheia(Fila *f) {
    return f->total == MAX;
}

bool filaVazia(Fila *f) {
    return f->total == 0;
}

void enqueue(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("Fila cheia! Não é possível inserir.\n");
        return;
    }
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX;
    f->total++;
}

Peca dequeue(Fila *f) {
    Peca removida = {'-', -1};
    if (filaVazia(f)) {
        printf("Fila vazia! Nada para remover.\n");
        return removida;
    }

    removida = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;
    return removida;
}

// ---------------------------------------------
// Gerar peça automaticamente
// ---------------------------------------------
Peca gerarPeca(int *idGlobal) {
    char tipos[] = {'I', 'O', 'T', 'L', 'S'};
    int r = rand() % 5;

    Peca p;
    p.tipo = tipos[r];
    p.id = (*idGlobal)++;
    return p;
}

// ---------------------------------------------
// Mostrar fila
// ---------------------------------------------
void mostrarFila(Fila *f) {
    printf("\n=== FILA DE PEÇAS FUTURAS ===\n");

    if (filaVazia(f)) {
        printf("Fila vazia!\n");
        return;
    }

    int idx = f->inicio;
    for (int i = 0; i < f->total; i++) {
        printf("[%d] Tipo: %c | ID: %d\n", i, f->itens[idx].tipo, f->itens[idx].id);
        idx = (idx + 1) % MAX;
    }
    printf("==============================\n");
}

// ---------------------------------------------
// Programa principal
// ---------------------------------------------
int main() {
    srand(time(NULL));

    Fila fila;
    inicializarFila(&fila);

    int idGlobal = 1;

    // Preencher fila inicial com 5 peças
    for (int i = 0; i < MAX; i++) {
        enqueue(&fila, gerarPeca(&idGlobal));
    }

    int opcao;

    do {
        mostrarFila(&fila);

        printf("\nMenu:\n");
        printf("1 - Jogar peça (remover da frente)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            Peca removida = dequeue(&fila);
            if (removida.id != -1) {
                printf("Peça jogada: Tipo %c, ID %d\n", removida.tipo, removida.id);

                // Inserir nova peça automaticamente
                enqueue(&fila, gerarPeca(&idGlobal));
            }
        }

    } while (opcao != 0);

    printf("\nEncerrando...\n");
    return 0;
}
