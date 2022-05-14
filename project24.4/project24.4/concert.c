// Q5

#include "concert.h"

Concert* createConcertArr(InstrumentTree tree) {
	Concert* concertArr;
	Concert newConcert;
	char ch;
	char* instrumentName;
	int id;
	int amount;
	int importance;
	int logSize = 0;
	int phySize = 1;
	bool endOfInput = false;
	int numOfConcerts = 0;
	int phyConcertArrSize = 1;

	concertArr = (Concert*)malloc(sizeof(Concert));
	checkMemoryAllocation(concertArr);

	(newConcert.name) = (char*)malloc(sizeof(char));
	checkMemoryAllocation(newConcert.name);


	ch = getchar();


	// maybe to do this in one loop ! 

	while (!endOfInput) { // get the whole concerts

		// get one line, one concert

		makeEmptyCIList(&(newConcert.instruments));

		// get concert name
		while (ch != ' ') {

			if (logSize == phySize) {
				phySize *= 2;
				(newConcert.name) = (char*)realloc(newConcert.name, sizeof(char) * phySize);
				checkMemoryAllocation(newConcert.name);
			}

			(newConcert.name)[logSize] = ch;
			logSize++;

			ch = getchar();
		}

		shrinkAllocationStr(&(newConcert.name));

		// get date and hour of concert dd mm yyyy hh:mm  
		scanf("%d", &(newConcert.date_of_concert.day));
		scanf("%d", &(newConcert.date_of_concert.month));
		scanf("%d", &(newConcert.date_of_concert.year));
		newConcert.date_of_concert.hour = getAndConvertHourOfConcert();

		printf("%d", (newConcert.date_of_concert.day));
		printf("%d", (newConcert.date_of_concert.month));
		printf("%d", (newConcert.date_of_concert.year));
		printf("%0.2f", (newConcert.date_of_concert.hour));

		// FIX: think about better solution
		instrumentName = (char*)malloc(sizeof(char) * MAX_INSTRUMENT_LENGTH);
		checkMemoryAllocation(instrumentName);

		scanf("%s", instrumentName);// name

		while (instrumentName != '\n') {

			// get CInstrument data

			shrinkAllocationStr(&instrumentName);

			id = findInsId(tree, instrumentName);
			scanf("%d", &amount); // amount
			scanf("%d", &importance); // importance

			// update CI list
			insertDataToEndCIList(&(newConcert.instruments), id, amount, importance);

			instrumentName = (char*)malloc(sizeof(char) * MAX_INSTRUMENT_LENGTH);
			checkMemoryAllocation(instrumentName);

			scanf("%s", instrumentName);// name
			
		}

		// add concert to concertArr

		if (numOfConcerts == phyConcertArrSize) {
			phyConcertArrSize *= 2;
			concertArr = (Concert*)realloc(concertArr, sizeof(Concert)*phyConcertArrSize);
			checkMemoryAllocation(concertArr);
		}

		concertArr[numOfConcerts] = newConcert;

		ch = getchar();

		if (ch == '\n') { // if there is an empty line, its end of input

			endOfInput = true;
		}
		else {
			newConcert.instruments.head->CI.num;

		}


	}

	// fix: shrink array, we dont have a general function for that
	// fix: we need to to add this condition for all shrinks arrays. (?) !!!!!!!!
	if (numOfConcerts < phyConcertArrSize) {
		concertArr = (Concert*)realloc(concertArr, sizeof(Concert) * numOfConcerts);
		checkMemoryAllocation(concertArr);
	}

	return concertArr;
}

void manageMusiciansForConcerts(Concert* concertArr, Musician*** musiciansCollection, int concertNum, int* indicesArr) {
	// MS[insID] -> sort by importance and price
// if important -> expensive to cheap
// else -> cheap to expensive

	CIListNode* curr;
	Musician** musiciansForConcertArr;
	int logSize = 0;
	int index;
	bool isConcertOn = true;

	musiciansForConcertArr = (Musician**)malloc(musiciansForConcertArr, sizeof(Musician*));
	checkMemoryAllocation(musiciansForConcertArr);

	for (index = 0; index < concertNum; index++) { // loop concerts

		// ������ ��� �� ������ �� �� ����� ������ �� ���� ��������� �� ������� �������
		curr = concertArr[index].instruments.head;
		logSize = 0;


		while (curr = !NULL && isConcertOn) // loop instruments per concert
		{

			// arg1 - arr of musicians, arg2 - importance
			sortMusiciansArrByImportance(musiciansCollection[curr->CI.inst], curr->CI.importance);

			// loop Musicians of same instrument

			musiciansForConcertArr = (Musician**)realloc(musiciansForConcertArr, logSize + sizeof(Musician*) * (curr->CI.num));
			checkMemoryAllocation(musiciansForConcertArr);

			for (int i = 0; i < curr->CI.num; i++)
			{
				if (curr->CI.num > indicesArr[curr->CI.inst]) { // ���� ������ �� ����� ���� ������ ������� ���� �� ���� ������� �� 
																	// curr->(CI.num)
					isConcertOn = false;

					// ����� ���� ������ �������� ����� ��� �����
					printf("Could not find musicians for the concert %s", concertArr[index].name);
					break; 	// go to next concert


				}

				// check if Musician was not picked
				else if (musiciansCollection[curr->CI.inst][i]->concertInstrument_id == DEFUALT_ID)
				{
					musiciansForConcertArr[logSize] = musiciansCollection[curr->CI.inst][i];
					musiciansCollection[curr->CI.inst][i]->concertInstrument_id = curr->CI.inst;
					logSize++;
				}
				else {
					(curr->CI.num)++;
				}
			}

			curr = curr->next;

		}

		if (isConcertOn) {
			printConcertDetails(concertArr[index], musiciansForConcertArr, logSize);
		}
	}

	free(musiciansForConcertArr);

}

void printConcertDetails(Concert concert, int numOfConcertMusicians) {
	printCIList();
}

bool checkIfMusicianAlreadyPlays(Musician** musiciansForConcertArr, int size, Musician* musician) {

	for (int i = 0; i < size; i++)
	{
		if (musiciansForConcertArr[i] == musician) {
			return true;
		}
	}

	return false;
}

float getAndConvertHourOfConcert() {
	int min, sec;

	scanf("%d", &min);
	getchar();
	scanf("%d", &sec);

	return min + (sec / TOTAL_SECONDS);
}

void sortMusiciansArrByImportance(Musician** musiciansArr, int importance) {

	if (importance == 0) {
		ascendingBubbleSort(musiciansArr);
	}
	else { // its equal 1
		descendingBubbleSort(musiciansArr);
	}
}

void ascendingBubbleSort(Musician** musiciansArr, int size) {
	int i, j;
	for (i = 0; i < n - 1; i++)
	{
		for (j = 0; j < n - i - 1; j++)
		{
			if (array[j] > array[j + 1]) /* For decreasing order use '<' instead of '>' */
			{
				swap = array[j];
				array[j] = array[j + 1];
				array[j + 1] = swap;
			}
		}
	}

}

