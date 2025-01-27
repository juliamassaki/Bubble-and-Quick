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
        printf("%s\n", itens[i].nome);
    }
}

int comparar(const void *a, const void *b) {
    Item *itemA = (Item *)a;
    Item *itemB = (Item *)b;

    if (itemB->prioridade != itemA->prioridade)
        return itemB->prioridade - itemA->prioridade;

    return itemA->tempo - itemB->tempo;
}

void trocar(Item *a, Item *b) {
    Item temp = *a;
    *a = *b;
    *b = temp;
}

int escolher_pivo(Item *itens, int low, int high) {
    int mid = low + (high - low) / 2;
    if (comparar(&itens[low], &itens[mid]) > 0)
        trocar(&itens[low], &itens[mid]);
    if (comparar(&itens[low], &itens[high]) > 0)
        trocar(&itens[low], &itens[high]);
    if (comparar(&itens[mid], &itens[high]) > 0)
        trocar(&itens[mid], &itens[high]);
    return mid;
}

void quick_sort(Item *itens, int low, int high) {
    if (low < high) {
        int pivotIndex = escolher_pivo(itens, low, high);
        trocar(&itens[pivotIndex], &itens[high]);

        int pivot = high;
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (comparar(&itens[j], &itens[pivot]) <= 0) {
                i++;
                trocar(&itens[i], &itens[j]);
            }
        }
        trocar(&itens[i + 1], &itens[high]);

        quick_sort(itens, low, i);
        quick_sort(itens, i + 2, high);
    }
}

void process_csv(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    char line[MAX_LINE];
    int capacity = 1000;
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

    printf("\nOrdenando com Quick Sort:\n");
    struct timeval start_quick, end_quick;
    gettimeofday(&start_quick, NULL);
    quick_sort(itens, 0, item_count - 1);
    gettimeofday(&end_quick, NULL);
    double time_quick = (end_quick.tv_sec - start_quick.tv_sec) + (end_quick.tv_usec - start_quick.tv_usec) / 1E6;

    exibir_items(itens, item_count);
    printf("Tempo de execucao do Quick Sort: %f segundos\n", time_quick);

    free(itens);
}

int main() {
    const char *filename = "restaurante.csv";
    process_csv(filename);
    return 0;
}
