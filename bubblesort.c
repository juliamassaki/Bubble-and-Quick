#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define MAX_LINE 1024

typedef struct {
    int prioridade;
    int tempo;
    char nome[MAX_LINE];
} Item;

void exibir_items(Item *itens, int count) {
    for (int i = 0; i < count; i++) {
        printf("Nome: %s\n", itens[i].nome);
    }
}

int comparar(const void *a, const void *b) {
    Item *itemA = (Item *)a;
    Item *itemB = (Item *)b;

    if (itemB->prioridade != itemA->prioridade)
        return itemB->prioridade - itemA->prioridade;

    return itemA->tempo - itemB->tempo;
}

void bubble_sort(Item *itens, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1 - i; j++) {
            if (comparar(&itens[j], &itens[j + 1]) > 0) {
                Item temp = itens[j];
                itens[j] = itens[j + 1];
                itens[j + 1] = temp;
            }
        }
    }
}

void process_csv(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    char line[MAX_LINE];
    int capacity = 1000000;
    Item *itens = (Item *)malloc(capacity * sizeof(Item));
    if (itens == NULL) {
        perror("Erro ao alocar memória");
        fclose(file);
        return;
    }
    int item_count = 0;

    if (fgets(line, sizeof(line), file)) {
    }

    while (fgets(line, sizeof(line), file)) {
        if (line[0] == '\0' || line[0] == '\n') continue;

        int prioridade, tempo;
        char nome[MAX_LINE];
        if (sscanf(line, "%d,%d,%s", &prioridade, &tempo, nome) == 3) {
            Item item;
            item.prioridade = prioridade;
            item.tempo = tempo;
            strncpy(item.nome, nome, sizeof(item.nome) - 1);
            item.nome[sizeof(item.nome) - 1] = '\0';

            if (item_count >= capacity) {
                capacity *= 2;
                itens = (Item *)realloc(itens, capacity * sizeof(Item));
                if (itens == NULL) {
                    perror("Erro ao realocar memória");
                    fclose(file);
                    return;
                }
            }
            itens[item_count++] = item;
        }
    }
    fclose(file);

    printf("Ordenando com Bubble Sort:\n");
    struct timeval start_bubble, end_bubble;
    gettimeofday(&start_bubble, NULL);
    bubble_sort(itens, item_count);
    gettimeofday(&end_bubble, NULL);
    double time_bubble = (end_bubble.tv_sec - start_bubble.tv_sec) + (end_bubble.tv_usec - start_bubble.tv_usec) / 1E6;
    exibir_items(itens, item_count);
    printf("Tempo de execucao do Bubble Sort: %f segundos\n", time_bubble);
}

int main() {
    const char *filename = "restaurante.csv";
    process_csv(filename);
    return 0;
}
