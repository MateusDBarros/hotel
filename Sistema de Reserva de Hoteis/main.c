#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Struct
struct Reservation
{
    int id;
    char name[50];
    char checkin[10];
    char checkout[10];
    char room[15];
};

//Funçoes
void create(struct Reservation room[100], int *numRooms);
void all(struct Reservation room[100], int *numRooms);
void read(struct Reservation room[100], int *numRooms, int index);
int search(struct Reservation room[100], int L, char target, int R);
int sort(struct Reservation room[100], int *numRooms);
void delete(struct Reservation room[100], int *numRooms);

int main(void) {
    struct Reservation room[100]; //Escolher um nome melhor depois kkkk
    int numRooms = 0;
    int escolha;
    int index;
    char target[50];

    do
    {
        printf("---Menu Principal---\n");
        printf("1. Criar Reserva.\n");
        printf("2. Procurar Hospede.\n"); 
        printf("3. Exibir todas as Reserva.\n");
        printf("4. Apagar Reserva.\n");
        printf("5. Sair.\n");
        printf("O que faremos hoje?\n");
        scanf("%d", &escolha);

        switch (escolha)
        {
        case 1:
            system("cls");
            create(room, &numRooms);
            sort(room, &numRooms);
            break;
        case 2:
            system("cls");
            printf("Digite o nome do hospede que deseja procurar: ");
            scanf(" %s", target);
            index = search(room, 0, target, &numRooms);
            read(room, &numRooms, index);
            break;
        case 3:
            system("cls");
            all(room, &numRooms);
            break;
        case 4:
            system("cls");
            delete(room, &numRooms);
        break;
        case 5:
            system("cls");
            printf("Finalizando o Programa...\n");
            return 0;
            break;
        default:
            printf("Opcao invalida!\n");
            break;
        }
    } while (5 != escolha);
    
}

//Funçoes
void create(struct Reservation room[100], int *numRooms) {
    printf("\t---Registrando---\n");
    printf("Digite o nome do hospede:\n");
    scanf(" %s", room[*numRooms].name);
    printf("Digite data do check-in(ano-mes-dia): ");
    scanf("%s", room[*numRooms].checkin);
    printf("Digite data do check-out(ano-mes-dia): ");
    scanf("%s", room[*numRooms].checkout);
    printf("Digite o quarto do hospede: ");
    scanf("%s", room[*numRooms].room);
    room[*numRooms].id = *numRooms + 1; //Define a ID contando do primeiro ate a ultima entrada
    printf("Hospede registrado com sucesso!\n");
    (*numRooms)++;
    return;
}  

void all(struct Reservation room[100], int *numRooms) {
    if (*numRooms == 0) {//Checar caso não haja nenhuma reserva
        printf("Nenhuma reserva realizada!\n");
        return;
    }
    printf("| %-8s | %-20s | %-10s | %-10s | %-10s\n", "ID", "Hospede", "Check-In", "Check-Out", "Quarto");
    printf("-------------------------------------------------------\n");
    for (int i = 0; i < *numRooms; i++) {
        printf("| %-8d | %-20s | %-10s | %-10s | %-10s\n", room[i].id, room[i].name, room[i].checkin, room[i].checkout, room[i].room);
        printf("-------------------------------------------------------\n");
    }
    return;
}
void read(struct Reservation room[100], int *numRooms, int index) {

    if (*numRooms == 0) {//Checar caso não haja nenhuma reserva
        printf("Nenhuma reserva realizada!\n");
        return;
    }
    printf("| %-8s | %-20s | %-10s | %-10s | %-10s\n", "ID", "Hospede", "Check-In", "Check-Out", "Quarto");
    printf("| %-8d | %-20s | %-10s | %-10s | %-10s\n", room[index].id, room[index].name, room[index].checkin, room[index].checkout, room[index].room);
    printf("-------------------------------------------------------\n");
    return;
}

int sort(struct Reservation room[100], int *numRooms) { //Por ser mais facil de se orientar, a função ordena por nome

    struct Reservation temp;
    if (*numRooms == 0) { //Checar caso não haja nenhuma reserva
        printf("Nenhuma reserva realizada!\n");
        return 1;
    }

    for (int i = 0; i < *numRooms; i++) {
        for (int j = i; j < *numRooms; j++) {
            if (strcmp(room[j].name, room[j + 1].name) > 0 ) {
                temp = room[j];
                room[j] = room[j + 1];
                room[j + 1] = temp;
            }
        }
    }
    return 0;
}
int search(struct Reservation room[100], int l, char target, int r) {
    
    if (l > r) //Previne que continue procurando mesmo depois de passar por toda a array
        return -1;
    int mid = l + (r - l) / 2; //Achar o meio da array

    if(strcmp(room[mid].name, target) == 0)
        return mid;

    if (strcmp(room[mid].name, target) > 0)
        return search(room, l, target, mid - 1);
    else
        return search(room, l + 1, target, r);
}
void delete(struct Reservation room[100], int *numRooms) {
    if (*numRooms == 0) { //Checar caso não haja nenhuma reserva
        printf("Nenhuma reserva realizada!\n");
        return 1;
    }

    char escolha;
    char name[50];
    printf("Digite o nome do Hospede que deseja apagar: ");
    scanf("%s");
    for (int i = 0; i < *numRooms; i++) {
        if(strcmp(room[i].name, name) == 0) {
            printf("Tem certeza que deseja excluir a reserva?(y/n) ");
            scanf("%c", &escolha);
            if ('y' == escolha) {
                for (int j = i; j < *numRooms - 1 - i; j++) {
                    room[j] = room[j + 1];
                }  
            }
            else if ('n' == escolha)
                return;
            else {
                printf("Opção invalida\n");
                return;
            }            
        }
    }
    printf("Hospede nao encontrado, por favor verifique o nome digitado.\n");
    return;
}