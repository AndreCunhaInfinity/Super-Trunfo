#include <stdio.h>

/* ===== Tipo que representa uma carta ===== */
typedef struct {
    char  estado[3];
    int   codigo;
    char  nome[41];

    unsigned long int populacao;
    float   area;                 /* km²             */
    double  pib;                  /* bilhões US$     */
    int     pontos_turisticos;

    /* calculados */
    double densidade;
    double pib_per_capita;
    float  super_poder;
} Carta;

/* ---------- Funções de cálculo ---------- */
void calcular_derivados(Carta *c)
{
    c->densidade      = (double)c->populacao / c->area;
    c->pib_per_capita = (c->pib * 1e9) / c->populacao;

    /* Super Poder = soma de atributos “positivos” + 1/densidade          */
    c->super_poder = (float)(
        (double)c->populacao   +
        c->area                +
        c->pib                 +
        c->pontos_turisticos   +
        c->pib_per_capita      +
        (1.0 / c->densidade)
    );
}

/* ---------- Entrada de dados ---------- */
void ler_carta(Carta *c)
{
    printf("Estado (sigla): ");      scanf(" %2s",  c->estado);
    printf("Codigo: ");              scanf("%d",   &c->codigo);
    printf("Nome: ");                scanf(" %40[^\n]", c->nome);

    printf("Populacao: ");           scanf("%lu",  &c->populacao);
    printf("Area (km2): ");          scanf("%f",   &c->area);
    printf("PIB (bilhoes US$): ");   scanf("%lf",  &c->pib);
    printf("Pontos turisticos: ");   scanf("%d",   &c->pontos_turisticos);

    calcular_derivados(c);
    puts("");
}

/* ---------- Comparadores (1 = Carta1 vence) ---------- */
#define CMP_MAIOR(c1, c2, campo) ((c1)->campo > (c2)->campo)
#define CMP_MENOR(c1, c2, campo) ((c1)->campo < (c2)->campo)

void comparar(const Carta *c1, const Carta *c2)
{
    puts("\nComparacao de Cartas:\n");

    printf("Populacao: Carta %d venceu (%d)\n",
           CMP_MAIOR(c1,c2,populacao)?1:2, CMP_MAIOR(c1,c2,populacao));

    printf("Area: Carta %d venceu (%d)\n",
           CMP_MAIOR(c1,c2,area)?1:2, CMP_MAIOR(c1,c2,area));

    printf("PIB: Carta %d venceu (%d)\n",
           CMP_MAIOR(c1,c2,pib)?1:2, CMP_MAIOR(c1,c2,pib));

    printf("Pontos Turisticos: Carta %d venceu (%d)\n",
           CMP_MAIOR(c1,c2,pontos_turisticos)?1:2,
           CMP_MAIOR(c1,c2,pontos_turisticos));

    printf("Densidade Populacional: Carta %d venceu (%d)\n",
           CMP_MENOR(c1,c2,densidade)?1:2, CMP_MENOR(c1,c2,densidade));

    printf("PIB per Capita: Carta %d venceu (%d)\n",
           CMP_MAIOR(c1,c2,pib_per_capita)?1:2,
           CMP_MAIOR(c1,c2,pib_per_capita));

    printf("Super Poder: Carta %d venceu (%d)\n",
           CMP_MAIOR(c1,c2,super_poder)?1:2,
           CMP_MAIOR(c1,c2,super_poder));
}

/* ---------- main ---------- */
int main(void)
{
    Carta c1, c2;

    puts("=== Cadastro da Carta 1 ==="); ler_carta(&c1);
    puts("=== Cadastro da Carta 2 ==="); ler_carta(&c2);

    comparar(&c1, &c2);

    return 0;
}
