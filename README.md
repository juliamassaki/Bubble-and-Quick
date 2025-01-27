# Bubble-and-Quick

### A Escolha do Pivô

**Identificação das posições**:

   O pivô é selecionado entre três elementos da lista: o primeiro elemento (posição `low`), o elemento do meio (posição `mid`), e o último elemento (posição `high`).

**Comparação e troca dos elementos**:
   - O elemento da posição `low` é comparado com o elemento da posição `mid`. Se o valor em `low` for maior que o valor em `mid`, os dois são trocados.
   - O valor em `low` é comparado com o valor em `high`. Se o valor em `low` for maior que o valor em `high`, os dois são trocados.
   - O valor em `mid` é comparado com o valor em `high`. Se o valor em `mid` for maior que o valor em `high`, os dois são trocados.

**Resultado da escolha do pivô**:

O valor em `mid` é o elemento do meio entre os três. Este valor é escolhido como o pivô. Isso evita que ocorra uma escolha de pivô que torne o quicksort menos eficiente.

*função `escolher_pivo`:*

```
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
```

## observações
- Não há atualizações do codigo no github, porque quando soube que era necessário entregar via github o codigo já estava pronto, assim não houveram mudanças.
- Tempo de execucao do Bubble Sort: 4494.919363 segundos
- Tempo de execucao do Quick Sort: 0.539955 segundos
