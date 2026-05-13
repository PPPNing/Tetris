#include<stdio.h>
#include<stdlib.h>
#include<time.h>
struct listNode {
	int a[10];
	struct listNode* nextPtr;
};
typedef struct listNode listnode;
typedef listnode* listnodePtr;

listnodePtr createlist(int);
void putsquare(char, listnodePtr);
int countlist(listnodePtr*);
void addlist(listnodePtr, int);
void destroylist(listnodePtr);
void putI(listnodePtr);
void putT(listnodePtr);
void putO(listnodePtr);
void putJ(listnodePtr);
void putL(listnodePtr);
void putS(listnodePtr);
void putZ(listnodePtr);

int main() {
	listnodePtr headPtr = NULL;
	int line;
	long int score = 0;
	char S0, S1;
	clock_t start, finish;
	double interval;
	start = clock();
	headPtr = createlist(20);
	scanf("%c", &S0);
	while (S0 != 'X') {
		finish = clock();
		interval = ((double)(finish - start)) / CLOCKS_PER_SEC;
		if (interval > 9.99)
			exit(0);
		scanf("%c", &S1);
		getchar();
		if (S1 == 'E')
			break;
		putsquare(S0, headPtr);
		line = countlist(&headPtr);
		switch (line) {
		case 1:score += 100;
			break;
		case 2:score += 300;
			break;
		case 3:score += 500;
			break;
		case 4:score += 800;
			break;
		default:break;
		}
		printf("%ld\n", score);
		fflush(stdout);
		if (line > 0)
			addlist(headPtr, line);
		S0 = S1;
	}
	destroylist(headPtr);
	return 0;
}

listnodePtr createlist(int num) {
	listnodePtr headPtr = NULL, currentPtr = NULL, lastPtr = NULL;
	int i, j;
	for (i = 1; i <= num; i++) {
		currentPtr = malloc(sizeof(listnode));
		if (currentPtr != NULL) {
			for (j = 0; j < 10; j++)
				currentPtr->a[j] = 0;
			if (headPtr == NULL)
				headPtr = currentPtr;
			else
				lastPtr->nextPtr = currentPtr;
			lastPtr = currentPtr;
		}
	}
	if (lastPtr != NULL)
		lastPtr->nextPtr = NULL;
	return headPtr;
}

void putsquare(char s, listnodePtr headPtr) {
	switch (s) {
	case 'I':putI(headPtr);
		break;
	case 'T':putT(headPtr);
		break;
	case 'O':putO(headPtr);
		break;
	case 'J':putJ(headPtr);
		break;
	case 'L':putL(headPtr);
		break;
	case 'S':putS(headPtr);
		break;
	case 'Z':putZ(headPtr);
		break;
	default:break;
	}
	fflush(stdout);
}

int countlist(listnodePtr* headPtrPtr) {
	listnodePtr Ptr = *headPtrPtr, lastPtr = NULL, tempPtr;
	int i, j = 0, prem, judge;
	while (Ptr != NULL) {
		for (i = 0, prem = 1; i < 10; i++)
			if (Ptr->a[i] == 0) {
				prem = 0;
				break;
			}
		if (prem) {
			j++;
			if (lastPtr == NULL) {
				tempPtr = Ptr;
				Ptr = Ptr->nextPtr;
				free(tempPtr);
				*headPtrPtr = Ptr;
			}
			else {
				tempPtr = Ptr;
				lastPtr->nextPtr = Ptr->nextPtr;
				free(tempPtr);
				Ptr = lastPtr->nextPtr;
			}
		}
		else {
			lastPtr = Ptr;
			Ptr = Ptr->nextPtr;
		}
		for (i = 0, judge = 1; i < 10; i++)
			if (Ptr->a[i] == 1) {
				judge = 0;
				break;
			}
		if (judge == 1)
			break;
	}
	return j;
}

void addlist(listnodePtr headPtr, int num) {
	listnodePtr Ptr = headPtr, currentPtr = NULL;
	int i, j;
	while (Ptr->nextPtr != NULL) {
		Ptr = Ptr->nextPtr;
	}
	for (i = 1; i <= num; i++) {
		currentPtr = malloc(sizeof(listnode));
		if (currentPtr != NULL) {
			for (j = 0; j < 10; j++)
				currentPtr->a[j] = 0;
			Ptr->nextPtr = currentPtr;
			Ptr = currentPtr;
		}
	}
	Ptr->nextPtr = NULL;
}

void destroylist(listnodePtr headPtr) {
	listnodePtr tempPtr;
	while (headPtr != NULL) {
		tempPtr = headPtr;
		headPtr = headPtr->nextPtr;
		free(tempPtr);
	}
}

void putI(listnodePtr headPtr) {
	int i, j, put = 0;
	listnodePtr Ptr = headPtr, lastPtr = NULL;
	for (j = 0; j <= 4; j++) {
		for (i = 0; i <= 6; i++)
			if (Ptr->a[i] == 0 && Ptr->a[i + 1] == 0 && Ptr->a[i + 2] == 0 && Ptr->a[i + 3] == 0 && (Ptr->nextPtr)->a[i] == 0 && (Ptr->nextPtr)->a[i + 1] == 0 && (Ptr->nextPtr)->a[i + 2] == 0 && (Ptr->nextPtr)->a[i + 3] == 0)
				if (lastPtr == NULL || (lastPtr != NULL && lastPtr->a[i] == 1 && lastPtr->a[i + 1] == 1 && lastPtr->a[i + 2] == 1 && lastPtr->a[i + 3] == 1)) {
					printf("0 %d\n", i);
					Ptr->a[i] = Ptr->a[i + 1] = Ptr->a[i + 2] = Ptr->a[i + 3] = 1;
					put = 1;
					break;
				}
		if (put == 0) {
			lastPtr = Ptr;
			Ptr = Ptr->nextPtr;
		}
		else
			break;
	}
	Ptr = headPtr;
	while (put == 0) {
		for (i = 0; i < 10; i++)
			if (Ptr->a[i] == 0 && (Ptr->nextPtr)->a[i] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i] == 0 && (((Ptr->nextPtr)->nextPtr)->nextPtr)->a[i] == 0) {
				printf("1 %d\n", i);
				Ptr->a[i] = (Ptr->nextPtr)->a[i] = ((Ptr->nextPtr)->nextPtr)->a[i] = (((Ptr->nextPtr)->nextPtr)->nextPtr)->a[i] = 1;
				put = 1;
				break;
			}
		Ptr = Ptr->nextPtr;
	}
}

void putT(listnodePtr headPtr) {
	int i, put = 0, j = 0;
	listnodePtr Ptr = headPtr, lastPtr = NULL;
	while (put == 0 && j < 15) {
		for (i = 0; i <= 7; i++)
			if (Ptr->a[i] == 0 && Ptr->a[i + 1] == 0 && Ptr->a[i + 2] == 0 && (Ptr->nextPtr)->a[i] == 0 && (Ptr->nextPtr)->a[i + 1] == 0 && (Ptr->nextPtr)->a[i + 2] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i + 1] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i + 2] == 0)
				if (lastPtr == NULL || (lastPtr != NULL && lastPtr->a[i] == 1 && lastPtr->a[i + 1] == 1 && lastPtr->a[i + 2] == 1)) {
					printf("0 %d\n", i);
					Ptr->a[i] = Ptr->a[i + 1] = Ptr->a[i + 2] = (Ptr->nextPtr)->a[i + 1] = 1;
					put = 1;
					break;
				}
		for (i = 0; i <= 7 && put == 0; i++)
			if (Ptr->a[i + 1] == 0 && Ptr->a[i] == 1 && Ptr->a[i + 2] == 1 && (Ptr->nextPtr)->a[i + 1] == 0 && (Ptr->nextPtr)->a[i] == 0 && (Ptr->nextPtr)->a[i + 2] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i + 1] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i + 2] == 0)
				if (lastPtr == NULL || (lastPtr != NULL && lastPtr->a[i + 1] == 1)) {
					printf("2 %d\n", i);
					Ptr->a[i + 1] = (Ptr->nextPtr)->a[i + 1] = (Ptr->nextPtr)->a[i] = (Ptr->nextPtr)->a[i + 2] = 1;
					put = 1;
					break;
				}
		for (i = 0; i <= 8 && put == 0 && j < 14; i++) {
			if (Ptr->a[i] == 0 && Ptr->a[i + 1] == 1 && (Ptr->nextPtr)->a[i + 1] == 0 && (Ptr->nextPtr)->a[i] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i + 1] == 0) {
				if (lastPtr == NULL || lastPtr != NULL && lastPtr->a[i] == 1) {
					printf("1 %d\n", i);
					Ptr->a[i] = (Ptr->nextPtr)->a[i] = (Ptr->nextPtr)->a[i + 1] = ((Ptr->nextPtr)->nextPtr)->a[i] = 1;
					put = 1;
					break;
				}
			}
			else if (Ptr->a[i] == 1 && Ptr->a[i + 1] == 0 && (Ptr->nextPtr)->a[i] == 0 && (Ptr->nextPtr)->a[i + 1] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i + 1] == 0) {
				if (lastPtr == NULL || lastPtr != NULL && lastPtr->a[i + 1] == 1) {
					printf("3 %d\n", i);
					Ptr->a[i + 1] = (Ptr->nextPtr)->a[i] = (Ptr->nextPtr)->a[i + 1] = ((Ptr->nextPtr)->nextPtr)->a[i + 1] = 1;
					put = 1;
					break;
				}
			}
		}
		lastPtr = Ptr;
		Ptr = Ptr->nextPtr;
		j++;
	}
	Ptr = headPtr;
	while (put == 0) {
		for (i = 0; i <= 7 && put == 0; i++)
			if (Ptr->a[i + 1] == 0 && Ptr->a[i] == 1 && Ptr->a[i + 2] == 1 && (Ptr->nextPtr)->a[i + 1] == 0 && (Ptr->nextPtr)->a[i] == 0 && (Ptr->nextPtr)->a[i + 2] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i + 1] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i + 2] == 0) {
				printf("2 %d\n", i);
				Ptr->a[i + 1] = (Ptr->nextPtr)->a[i + 1] = (Ptr->nextPtr)->a[i] = (Ptr->nextPtr)->a[i + 2] = 1;
				put = 1;
				break;
			}
		for (i = 0; i <= 8 && put == 0; i++) {
			if (Ptr->a[i] == 0 && Ptr->a[i + 1] == 1 && (Ptr->nextPtr)->a[i + 1] == 0 && (Ptr->nextPtr)->a[i] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i + 1] == 0) {
				printf("1 %d\n", i);
				Ptr->a[i] = (Ptr->nextPtr)->a[i] = (Ptr->nextPtr)->a[i + 1] = ((Ptr->nextPtr)->nextPtr)->a[i] = 1;
				put = 1;
				break;
			}
			else if (Ptr->a[i] == 1 && Ptr->a[i + 1] == 0 && (Ptr->nextPtr)->a[i] == 0 && (Ptr->nextPtr)->a[i + 1] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i + 1] == 0) {
				printf("3 %d\n", i);
				Ptr->a[i + 1] = (Ptr->nextPtr)->a[i] = (Ptr->nextPtr)->a[i + 1] = ((Ptr->nextPtr)->nextPtr)->a[i + 1] = 1;
				put = 1;
				break;
			}
		}
		Ptr = Ptr->nextPtr;
	}
}

void putO(listnodePtr headPtr) {
	int i, put = 0, j = 0;
	listnodePtr Ptr = headPtr, lastPtr = NULL;
	while (put == 0 && j < 15) {
		for (i = 0; i <= 8; i++)
			if (Ptr->a[i] == 0 && Ptr->a[i + 1] == 0 && (Ptr->nextPtr)->a[i] == 0 && (Ptr->nextPtr)->a[i + 1] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i + 1] == 0)
				if (lastPtr == NULL || (lastPtr != NULL && lastPtr->a[i] == 1 && lastPtr->a[i + 1] == 1)) {
					printf("0 %d\n", i);
					Ptr->a[i] = Ptr->a[i + 1] = (Ptr->nextPtr)->a[i] = (Ptr->nextPtr)->a[i + 1] = 1;
					put = 1;
					break;
				}
		lastPtr = Ptr;
		Ptr = Ptr->nextPtr;
		j++;
	}
	Ptr = headPtr;
	while (put == 0) {
		for (i = 0; i <= 8; i++)
			if (Ptr->a[i] == 0 && Ptr->a[i + 1] == 0 && (Ptr->nextPtr)->a[i] == 0 && (Ptr->nextPtr)->a[i + 1] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i + 1] == 0) {
				printf("0 %d\n", i);
				Ptr->a[i] = Ptr->a[i + 1] = (Ptr->nextPtr)->a[i] = (Ptr->nextPtr)->a[i + 1] = 1;
				put = 1;
				break;
			}
		Ptr = Ptr->nextPtr;
	}
}

void putJ(listnodePtr headPtr) {
	int i, put = 0, j = 0;
	listnodePtr Ptr = headPtr, lastPtr = NULL;
	while (put == 0 && j <= 14) {
		for (i = 0; i <= 7; i++)
			if (Ptr->a[i] == 0 && Ptr->a[i + 1] == 0 && Ptr->a[i + 2] == 0 && (Ptr->nextPtr)->a[i] == 0 && (Ptr->nextPtr)->a[i + 1] == 0 && (Ptr->nextPtr)->a[i + 2] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i + 1] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i + 2] == 0)
				if (lastPtr == NULL || (lastPtr != NULL && lastPtr->a[i] == 1 && lastPtr->a[i + 1] == 1 && lastPtr->a[i + 2] == 1)) {
					printf("0 %d\n", i);
					Ptr->a[i] = Ptr->a[i + 1] = Ptr->a[i + 2] = (Ptr->nextPtr)->a[i] = 1;
					put = 1;
					break;
				}
		for (i = 2; i <= 9 && put == 0; i++)
			if (Ptr->a[i] == 0 && (Ptr->nextPtr)->a[i] == 0 && (Ptr->nextPtr)->a[i - 1] == 0 && (Ptr->nextPtr)->a[i - 2] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i - 1] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i - 2] == 0)
				if ((lastPtr == NULL || (lastPtr != NULL && lastPtr->a[i] == 1)) && Ptr->a[i - 1] == 1 && Ptr->a[i - 2] == 1) {
					printf("2 %d\n", i - 2);
					Ptr->a[i] = (Ptr->nextPtr)->a[i] = (Ptr->nextPtr)->a[i - 1] = (Ptr->nextPtr)->a[i - 2] = 1;
					put = 1;
					break;
				}
		for (i = 0; i <= 8 && put == 0 && j <= 13; i++)
			if (Ptr->a[i] == 0 && Ptr->a[i + 1] == 0 && (Ptr->nextPtr)->a[i] == 0 && (Ptr->nextPtr)->a[i + 1] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i + 1] == 0)
				if (lastPtr == NULL || (lastPtr != NULL && lastPtr->a[i] == 1 && lastPtr->a[i + 1] == 1)) {
					printf("3 %d\n", i);
					Ptr->a[i] = Ptr->a[i + 1] = (Ptr->nextPtr)->a[i + 1] = ((Ptr->nextPtr)->nextPtr)->a[i + 1] = 1;
					put = 1;
					break;
				}
		for (i = 0; i <= 8 && put == 0 && j <= 13; i++)
			if (Ptr->a[i] == 0 && (Ptr->nextPtr)->a[i] == 0 && (Ptr->nextPtr)->a[i + 1] == 1 && ((Ptr->nextPtr)->nextPtr)->a[i + 1] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i] == 0)
				if (lastPtr == NULL || (lastPtr != NULL && lastPtr->a[i] == 1)) {
					printf("1 %d\n", i);
					Ptr->a[i] = (Ptr->nextPtr)->a[i] = ((Ptr->nextPtr)->nextPtr)->a[i] = ((Ptr->nextPtr)->nextPtr)->a[i + 1] = 1;
					put = 1;
					break;
				}
		lastPtr = Ptr;
		Ptr = Ptr->nextPtr;
		j++;
	}
	Ptr = headPtr;
	while (put == 0) {
		for (i = 0; i <= 8 && put == 0; i++)
			if (Ptr->a[i] == 0 && Ptr->a[i + 1] == 0 && (Ptr->nextPtr)->a[i] == 0 && (Ptr->nextPtr)->a[i + 1] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i + 1] == 0) {
				printf("3 %d\n", i);
				Ptr->a[i] = Ptr->a[i + 1] = (Ptr->nextPtr)->a[i + 1] = ((Ptr->nextPtr)->nextPtr)->a[i + 1] = 1;
				put = 1;
				break;
			}
		for (i = 0; i <= 8 && put == 0; i++)
			if (Ptr->a[i] == 0 && (Ptr->nextPtr)->a[i] == 0 && (Ptr->nextPtr)->a[i + 1] == 1 && ((Ptr->nextPtr)->nextPtr)->a[i + 1] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i] == 0) {
				printf("1 %d\n", i);
				Ptr->a[i] = (Ptr->nextPtr)->a[i] = ((Ptr->nextPtr)->nextPtr)->a[i] = ((Ptr->nextPtr)->nextPtr)->a[i + 1] = 1;
				put = 1;
				break;
			}
		Ptr = Ptr->nextPtr;
	}
}

void putL(listnodePtr headPtr) {
	int i, put = 0, j = 0;
	listnodePtr Ptr = headPtr, lastPtr = NULL;
	while (put == 0 && j <= 14) {
		for (i = 0; i <= 7; i++)
			if (Ptr->a[i] == 0 && Ptr->a[i + 1] == 0 && Ptr->a[i + 2] == 0 && (Ptr->nextPtr)->a[i] == 0 && (Ptr->nextPtr)->a[i + 1] == 0 && (Ptr->nextPtr)->a[i + 2] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i + 1] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i + 2] == 0)
				if (lastPtr == NULL || (lastPtr != NULL && lastPtr->a[i] == 1 && lastPtr->a[i + 1] == 1 && lastPtr->a[i + 2] == 1)) {
					printf("0 %d\n", i);
					Ptr->a[i] = Ptr->a[i + 1] = Ptr->a[i + 2] = (Ptr->nextPtr)->a[i + 2] = 1;
					put = 1;
					break;
				}
		for (i = 0; i <= 7 && put == 0; i++)
			if (Ptr->a[i] == 0 && (Ptr->nextPtr)->a[i] == 0 && (Ptr->nextPtr)->a[i + 1] == 0 && (Ptr->nextPtr)->a[i + 2] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i + 1] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i + 2] == 0)
				if ((lastPtr == NULL || (lastPtr != NULL && lastPtr->a[i] == 1)) && Ptr->a[i + 1] == 1 && Ptr->a[i + 2] == 1) {
					printf("2 %d\n", i);
					Ptr->a[i] = (Ptr->nextPtr)->a[i] = (Ptr->nextPtr)->a[i + 1] = (Ptr->nextPtr)->a[i + 2] = 1;
					put = 1;
					break;
				}
		for (i = 0; i <= 8 && put == 0 && j <= 13; i++)
			if (Ptr->a[i] == 0 && Ptr->a[i + 1] == 0 && (Ptr->nextPtr)->a[i] == 0 && (Ptr->nextPtr)->a[i + 1] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i + 1] == 0)
				if (lastPtr == NULL || (lastPtr != NULL && lastPtr->a[i] == 1 && lastPtr->a[i + 1] == 1)) {
					printf("1 %d\n", i);
					Ptr->a[i] = Ptr->a[i + 1] = (Ptr->nextPtr)->a[i] = ((Ptr->nextPtr)->nextPtr)->a[i] = 1;
					put = 1;
					break;
				}
		for (i = 1; i <= 9 && put == 0 && j <= 13; i++)
			if (Ptr->a[i] == 0 && (Ptr->nextPtr)->a[i - 1] == 1 && ((Ptr->nextPtr)->nextPtr)->a[i - 1] == 0 && (Ptr->nextPtr)->a[i] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i] == 0)
				if (lastPtr == NULL || (lastPtr != NULL && lastPtr->a[i] == 1)) {
					printf("3 %d\n", i - 1);
					Ptr->a[i] = (Ptr->nextPtr)->a[i] = ((Ptr->nextPtr)->nextPtr)->a[i] = ((Ptr->nextPtr)->nextPtr)->a[i - 1] = 1;
					put = 1;
					break;
				}
		lastPtr = Ptr;
		Ptr = Ptr->nextPtr;
		j++;
	}
	Ptr = headPtr;
	while (put == 0) {
		for (i = 0; i <= 8 && put == 0; i++)
			if (Ptr->a[i] == 0 && Ptr->a[i + 1] == 0 && (Ptr->nextPtr)->a[i] == 0 && (Ptr->nextPtr)->a[i + 1] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i + 1] == 0) {
				printf("1 %d\n", i);
				Ptr->a[i] = Ptr->a[i + 1] = (Ptr->nextPtr)->a[i] = ((Ptr->nextPtr)->nextPtr)->a[i] = 1;
				put = 1;
				break;
			}
		for (i = 1; i <= 9 && put == 0; i++)
			if (Ptr->a[i] == 0 && (Ptr->nextPtr)->a[i - 1] == 1 && ((Ptr->nextPtr)->nextPtr)->a[i - 1] == 0 && (Ptr->nextPtr)->a[i] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i] == 0) {
				printf("3 %d\n", i - 1);
				Ptr->a[i] = (Ptr->nextPtr)->a[i] = ((Ptr->nextPtr)->nextPtr)->a[i] = ((Ptr->nextPtr)->nextPtr)->a[i - 1] = 1;
				put = 1;
				break;
			}
		Ptr = Ptr->nextPtr;
	}
}

void putS(listnodePtr headPtr) {
	int i, put = 0, j = 0;
	listnodePtr Ptr = headPtr, lastPtr = NULL;
	while (put == 0 && j < 15) {
		for (i = 0; i <= 7; i++)
			if (Ptr->a[i] == 0 && Ptr->a[i + 1] == 0 && Ptr->a[i + 2] == 1 && (Ptr->nextPtr)->a[i] == 0 && (Ptr->nextPtr)->a[i + 1] == 0 && (Ptr->nextPtr)->a[i + 2] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i + 1] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i + 2] == 0)
				if (lastPtr == NULL || lastPtr != NULL && lastPtr->a[i] == 1 && lastPtr->a[i + 1] == 1) {
					printf("0 %d\n", i);
					Ptr->a[i] = Ptr->a[i + 1] = (Ptr->nextPtr)->a[i + 1] = (Ptr->nextPtr)->a[i + 2] = 1;
					put = 1;
					break;
				}
		for (i = 0; i <= 8 && put == 0 && j <= 13; i++)
			if (Ptr->a[i] == 1 && Ptr->a[i + 1] == 0 && (Ptr->nextPtr)->a[i] == 0 && (Ptr->nextPtr)->a[i + 1] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i + 1] == 0)
				if (lastPtr == NULL || lastPtr != NULL && lastPtr->a[i + 1] == 1) {
					printf("1 %d\n", i);
					Ptr->a[i + 1] = (Ptr->nextPtr)->a[i] = (Ptr->nextPtr)->a[i + 1] = ((Ptr->nextPtr)->nextPtr)->a[i] = 1;
					put = 1;
					break;
				}
		lastPtr = Ptr;
		Ptr = Ptr->nextPtr;
		j++;
	}
	Ptr = headPtr;
	while (put == 0) {
		for (i = 0; i <= 7; i++)
			if (Ptr->a[i] == 0 && Ptr->a[i + 1] == 0 && (Ptr->nextPtr)->a[i] == 0 && (Ptr->nextPtr)->a[i + 1] == 0 && (Ptr->nextPtr)->a[i + 2] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i + 1] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i + 2] == 0) {
				printf("0 %d\n", i);
				Ptr->a[i] = Ptr->a[i + 1] = (Ptr->nextPtr)->a[i + 1] = (Ptr->nextPtr)->a[i + 2] = 1;
				put = 1;
				break;
			}
		for (i = 0; i <= 8 && put == 0; i++)
			if (Ptr->a[i + 1] == 0 && (Ptr->nextPtr)->a[i] == 0 && (Ptr->nextPtr)->a[i + 1] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i + 1] == 0) {
				printf("1 %d\n", i);
				Ptr->a[i + 1] = (Ptr->nextPtr)->a[i] = (Ptr->nextPtr)->a[i + 1] = ((Ptr->nextPtr)->nextPtr)->a[i] = 1;
				put = 1;
				break;
			}
		Ptr = Ptr->nextPtr;
	}
}

void putZ(listnodePtr headPtr) {
	int i, put = 0, j = 0;
	listnodePtr Ptr = headPtr, lastPtr = NULL;
	while (put == 0 && j < 15) {
		for (i = 0; i <= 7; i++)
			if (Ptr->a[i] == 1 && Ptr->a[i + 1] == 0 && Ptr->a[i + 2] == 0 && (Ptr->nextPtr)->a[i] == 0 && (Ptr->nextPtr)->a[i + 1] == 0 && (Ptr->nextPtr)->a[i + 2] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i + 1] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i + 2] == 0)
				if (lastPtr == NULL || lastPtr != NULL && lastPtr->a[i + 2] == 1 && lastPtr->a[i + 1] == 1) {
					printf("0 %d\n", i);
					Ptr->a[i + 2] = Ptr->a[i + 1] = (Ptr->nextPtr)->a[i + 1] = (Ptr->nextPtr)->a[i] = 1;
					put = 1;
					break;
				}
		for (i = 0; i <= 8 && put == 0 && j <= 13; i++)
			if (Ptr->a[i] == 0 && Ptr->a[i + 1] == 1 && (Ptr->nextPtr)->a[i] == 0 && (Ptr->nextPtr)->a[i + 1] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i + 1] == 0)
				if (lastPtr == NULL || lastPtr != NULL && lastPtr->a[i] == 1) {
					printf("1 %d\n", i);
					Ptr->a[i] = (Ptr->nextPtr)->a[i] = (Ptr->nextPtr)->a[i + 1] = ((Ptr->nextPtr)->nextPtr)->a[i + 1] = 1;
					put = 1;
					break;
				}
		lastPtr = Ptr;
		Ptr = Ptr->nextPtr;
		j++;
	}
	Ptr = headPtr;
	while (put == 0) {
		for (i = 0; i <= 7; i++)
			if (Ptr->a[i + 1] == 0 && Ptr->a[i + 2] == 0 && (Ptr->nextPtr)->a[i] == 0 && (Ptr->nextPtr)->a[i + 1] == 0 && (Ptr->nextPtr)->a[i + 2] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i + 1] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i + 2] == 0) {
				printf("0 %d\n", i);
				Ptr->a[i + 2] = Ptr->a[i + 1] = (Ptr->nextPtr)->a[i + 1] = (Ptr->nextPtr)->a[i] = 1;
				put = 1;
				break;
			}
		for (i = 0; i <= 8 && put == 0; i++)
			if (Ptr->a[i] == 0 && (Ptr->nextPtr)->a[i] == 0 && (Ptr->nextPtr)->a[i + 1] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i] == 0 && ((Ptr->nextPtr)->nextPtr)->a[i + 1] == 0) {
				printf("1 %d\n", i);
				Ptr->a[i] = (Ptr->nextPtr)->a[i] = (Ptr->nextPtr)->a[i + 1] = ((Ptr->nextPtr)->nextPtr)->a[i + 1] = 1;
				put = 1;
				break;
			}
		Ptr = Ptr->nextPtr;
	}
}
