#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_STRING 100
#define MAX_MODELS 10

// describes person
struct person{
	char name[MAX_STRING];
	int age;
};

// describes car
struct car_id {
	char descr[MAX_STRING]; 
	int year_made;
};

// describes owner and its cars
struct cars_person {
	struct person owner;
	struct car_id *cars_own;
	int number_cars;
};

// 8.1
struct car_comp{
	char brand[MAX_STRING];
	struct car_id cars[MAX_MODELS];
	struct person *owned_cars[MAX_MODELS];
	int ncars;
};

// 8.2
struct cars_person* create_car( struct person _ow, char _descr[], int _year_made ) {
	struct cars_person* scar = (struct cars_person *) malloc(sizeof(struct cars_person));
	scar->cars_own = (struct car_id*) malloc(sizeof(struct car_id));

	scar->owner = _ow;
	scar->number_cars = 1;

	strcpy(scar->cars_own->descr, _descr);
	scar->cars_own->year_made = _year_made;
	
	return scar;
}

// 8.3
void add_car(struct cars_person *_carArray[], int _lenArray, struct person _ow, struct car_id _id) {
	int i;

	for ( i = 0; i < _lenArray; i++ ) {
		if ( strcmp(_carArray[i]->owner.name, _ow.name) == 0 ) {
			_carArray[i]->number_cars++;
			_carArray[i]->cars_own = (struct car_id *) realloc(_carArray[i]->cars_own, _carArray[i]->number_cars*sizeof(struct car_id));
			_carArray[i]->cars_own[_carArray[i]->number_cars - 1] = _id;
			break;
		}
	}
	if ( i != _lenArray )
	{
		_carArray[i] = create_car(_ow, _id->descr, _id->_year_made); 
	}
}

int main ( void )
{
	struct cars_person *vect_cars[100];
	struct person ow[4] = {{"Joao", 1975}, {"Manel", 1985}, {"Francisco", 1980}, {"Catarina", 1980}};
	char descr[4][100] = {"Toyota Avensis", "VW Golf", "Citroen C3", "Opel Astra"};
	int years[4] = {2000, 2003, 2005, 2007};

	for (int i = 0; i < 4; i++)
		vect_cars[i] = create_car(ow[i], descr[i], years[i]);

	struct car_id newCar1 = {"Audi Q2", 2008};
	add_car(vect_cars, 4, ow[0], newCar1);

	struct car_id newCar2 = {"BMW S5", 2008};
	add_car(vect_cars, 4, ow[1], newCar2);

	for (int i = 0; i < 4; i++){
		printf("\n(%s, %d) - %d: \n", vect_cars[i]->owner.name, vect_cars[i]->owner.age, vect_cars[i]->number_cars);
		for (int j = 0; j < vect_cars[i]->number_cars; j++){
			printf("%s - %d ", vect_cars[i]->cars_own[j].descr, vect_cars[i]->cars_own[j].year_made);
		}
	}
	printf("\n");

    return EXIT_SUCCESS;
}
