#include <stdio.h>
#include <stdlib.h>

#include "MyHeader.h"

int main() {
	//SqList L;
	//CreateSqList(L, "SqList_Data.txt");
	//InsertSort(L);
	//BInsertSort(L);
	//TwoInsertSort(L);
	//ListTraverse_Sq(L, display_Sq);
	//DestroyList_Sq(L);
	SLinkListType SL;
	CreateLinkList(SL, "SqList_Data.txt");
	TableInsertSort(SL);
	for (int i = SL.r[0].next, j = 1; j<=SL.length ; i = SL.r[i].next, j++) {
		printf("%d ", SL.r[i].key);
	}
	printf("\n");
	system("pause");
	return 0;
}