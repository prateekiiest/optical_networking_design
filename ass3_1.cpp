// Importing required libraries
#include <cstdlib>
#include <iostream>
#include <string> 
#include <sstream>
#include <math.h> 
#include <ctime> 


using namespace std;


// Constants
#define INVALID -1
#define CITY_AMOUNT 6
#define POPULATION_SIZE 30
#define PHEROMONE_RATE 0.1
#define ALFA 1
#define BETA 1

#define ch 35 // no of channels  per edge 35
#define MAX_ITERATIONS 30
#define EVAPORATION_RATE 0.5
#define POSITIVE_CONTS 0.75






struct ant{
	double distance;
//	double fitness;
	double channels = 35;
	int position;
	int next[CITY_AMOUNT-1];
	//int route[CITY_AMOUNT];  //City = 6   route is nothing  but next node
};

//edit



// Variables
ant ants[CITY_AMOUNT];    //ants[0] to ants[29]   BUT WE NEED ANTS[0] TO ANTS[5] SO POPSIZE TO CITY_AMNT

double pheromone_links[CITY_AMOUNT][CITY_AMOUNT] =  { { INVALID, 0, 0, 0, 0, 0 }, {
 0, INVALID, 0, 0, 0, 0 }, { 0, 0, INVALID, 0, 0, 0 }, { 0, 0, 0,
 INVALID, 0, 0 }, { 0, 0, 0, 0, INVALID, 0 },                                           // UNWEIGHTED GRAPH HAVING EACH EDGE LENGTH '1'
 { 0, 0, 0, 0, 0, INVALID } };   // PHEROMONE_LINKS[0][1] , _[0][0]   ... .. .. .. 



                                                       //BIDIRECTIONAL GRAPH
                                                       
// Declaring array for the edges. (Assuming a complete graph of 6 nodes)  // CITY_AMOUNT IS THE NUMBER OF NODES OF THE GRAPH
int distance_links[CITY_AMOUNT][CITY_AMOUNT] = { { INVALID, 7, 4, 3, 11, INVALID }, {
 7, INVALID, 2, 8, INVALID, 8 }, { 4, 2, INVALID, INVALID, 9, 3 }, { 3, 8, INVALID,
 INVALID, 5, 4 }, { 11, INVALID, 9, 5, INVALID, 3 },
 { INVALID, 8, 3, 4, 3, INVALID } };



// Declaring array for channels
int channel_links[CITY_AMOUNT][CITY_AMOUNT] = { { INVALID, ch, ch, ch, ch, INVALID }, {
 ch, INVALID, ch, ch, INVALID, ch }, { ch, ch, INVALID, INVALID, ch, ch }, { ch, ch, INVALID,
 INVALID, ch, ch }, { ch, INVALID , ch, ch, INVALID, ch },
 { INVALID, ch, ch, ch, ch, INVALID } };

 
 

// REQUEST SET
/* All to all nodes request set. So here m nodes. Hence request set will be of size m(m-1)*/


/*-----------EXAMPLE----------------------

IF REQUEST SET IS   NODE 0    TO    NODE 1

THEN         request_set[0][1] will be called                                      !!!!!ASSUMPTION  == NODES ARE NUMBERED FROM 0 TO 5 IN THIS CASE

So we have here  2*(mC2) request here where m  = 6

*/


// PROGRAM IS RUN FOR 5m times. HERE m is taken as 6. So 5m = 30




// -------------------------------------------------- FUNCTIONS-----------------------------------------------------------


// Defining some functions
int best_distance = 1000000000;   // setting the best distance = INF
int worse_distance = 0;  // setting the worst distance = 0
double best_fitness;
double worse_fitness;
int best_route[CITY_AMOUNT];
int worse_route[CITY_AMOUNT];
double average = 0.0;
double variance = 0.0;
double standard_deviation = 0.0;
int greater_distance = INVALID;

void init_ant(int index);
//void seed_initial_pheromone(bool random);
//void get_greater_distance();
bool check_visit(int ant_index, int position);
void build_solution();
//void check_best_distance();
void calculate_fitness();
void pheromone_evaporates();
void update_pheromone();




double calculate_time(clock_t start, clock_t end);
int get_random_number(int from, int to);
void print_route(int ant_index, int route[CITY_AMOUNT], double distance, double channels);
void print_pheromone();
string number_to_String(double n);
void print_result();
void calculate_metrics();




// ------------------------------------------------------------------------------------------------------------------------------------








//-----------------------------------   DECLARATION OF THE ABOVE FUNCTIONS  -----------------------------------------------------------
 
 
 

// INITIALIZE THE ANTS  FUNCTION


void init_ant(int index) {
	ants[index].distance = 0;                                   /*  PLACING EACH ANT IN EACH OF THE 6 NODES  (INDEX REPRESENTING EACH OF THE ANTS)
	                                                                             */
	ants[index].fitness = 0;
	ants[index].position = get_random_number(0, (CITY_AMOUNT - 1));
	/*for (int j = 0; j < CITY_AMOUNT; j++) {
		ants[index].route[j] = INVALID;
	}
	*/
	// Positioning the ant in a random city
	//int random_city = get_random_number(0, (CITY_AMOUNT - 1));    //  POSITIONING THE ANTS RANDOMLY IN EACH OF THE 6  NODES.
	//ants[index].route[0] = random_city;
	
}

/*

  
example

 
  ants[0].route[0] = 0 
  ants[1].route[0] = 2
  ants[2].route[0] = 3
 
  ants[3].route[0] = 4
  ants[4].route[0] = 5 
  ants[5].route[0] = 1



  */


  
  // PLACING INITIAL VALUE OF PHEROMONE

/*
void seed_initial_pheromone(bool random) {
	for (int i = 0; i < CITY_AMOUNT; i++) {
		for (int j = 0; j < CITY_AMOUNT; j++) {
			if (i != j) {
				double random_pheromone = 0; // placing random pheromone values ranging from  0 to 100 for each of the edges
						
				pheromone_links[i][j] = (random == true) ? random_pheromone
						: PHEROMONE_RATE;            // updating pheromone links in the edges
			} else {
				pheromone_links[i][j] = INVALID;
			}
		}
	}
}

*/


/*
// Getting the largest distance possible in the given graph
void get_greater_distance() {
	for (int i = 0; i < CITY_AMOUNT; i++) {
		for (int j = 0; j < CITY_AMOUNT; j++) {
			if (distance_links[i][j] > greater_distance) {
				greater_distance = distance_links[i][j];
			}
		}
	}
	greater_distance += 1;
}
*/





bool check_visit(int ant_index, int position) {
	for (int i = 0; i < CITY_AMOUNT; i++) {
		if (ants[ant_index].position == position) {       // CHECKING WHETHER THE GIVEN ANT HAS REACHED THE PARTICULAR NODE
			return true;
		}
	}
	return false;
}



// JUST CALCULATING THE PROBABILITY OF THE REACHING A PARTICULAR NODE FROM A GIVEN NODE


void build_solution(){
	// For each ant
	for (int i = 0; i < CITY_AMOUNT; i++) {    // **************** POPULATION_SIZE CHANGED TO CITY_AMOUNT
		// inicialize ant
		init_ant(i);

		// While not passing through all the nodes                 
		while (ants[i].position < (CITY_AMOUNT - 1)) {              
			int position = ants[i].position;
                                                            
															 
															 
															 
												 
															   /* 
					BUILDING THE MAIN SOLUTION  										   
															   
	 transition_probability		Pij = (pi^a * nij ^b) / sum((pi^a)* (nij^b))								   
															   
															   
															   */
			double transition_probability[CITY_AMOUNT];

			double link_rate_sum = 0;
			// Adding the pheromone and heuristic rates
			for (int j = 0; j < CITY_AMOUNT; j++) {
				// If the city already visited, do not enter the analysis
				if (check_visit(i, j) == false) {
				    if (pheromone_links[position][j] >= 0
							and distance_links[position][j] >= 0) {
						link_rate_sum
								+= pow(pheromone_links[position][j], ALFA)
										* pow(
												distance_links[position][j],
												((-1.0)*BETA));
					}
				}
			}
			// Calculating the transition probability
			for (int j = 0; j < CITY_AMOUNT; j++) {
				// If the Node already visited, do not enter the analysis
				if (check_visit(i, j) == false) {
					if (pheromone_links[position][j] >= 0
							and distance_links[position][j] >= 0) {
						transition_probability[j] = (pow(
								pheromone_links[position][j], ALFA) * pow(
								distance_links[position][j],
								((-1.0)*BETA))) / link_rate_sum;
					} else {
						transition_probability[j] = 0;
					}
				} else {
					transition_probability[j] = 0;
				}
			}

			// Making roulette
			double roulette = (double) get_random_number(0, 100) / 100.0;     // 0 =< roulette <= 1
			double minor = 0;
			double major = 0;

			// Selecting the next node
			for (int j = 0; j < CITY_AMOUNT; j++) {
				// If the node already visited, do not enter the analysis
				if (check_visit(i, j) == false) {
					major += transition_probability[j];
					if (roulette >= minor and roulette <= major) {
						//ants[i].route[position + 1] = j;
						ants[i].position = j;
						//ants[i].channels = ants[i].channels - 1;
						ants[i].distance += distance_links[position][j];
						//ants[i].position += 1;
						break;
					} else {
						minor = major;
					}
				}
			}
		}
	}
}





/*
void check_best_distance() {
	for (int i = 0; i < CITY_AMOUNT; i++) {   /// ************** POPULATION SIZE CHANGE TO CITY AMOUNT
		if (ants[i].distance < best_distance) {
			best_distance = ants[i].distance;
			for (int j = 0; j < CITY_AMOUNT; j++) {
				best_route[j] = ants[i].route[j];                      //  Check the best distance --  THE SHORTEST PATH
			}
		} else if (ants[i].distance > worse_distance) {
			worse_distance = ants[i].distance;
			for (int j = 0; j < CITY_AMOUNT; j++) {
				worse_route[j] = ants[i].route[j];      // Check the worst distance  --  THE LONGEST PATH
			}
		}
	}
}

*/



void calculate_fitness() {
	for (int i = 0; i < POPULATION_SIZE; i++) {
		double fitness = (double) ants[i].distance / (double) best_distance;
		if (fitness < best_fitness) {
			best_fitness = fitness;
		} else if (fitness > worse_fitness) {
			worse_fitness = fitness;
		}
		ants[i].fitness = fitness;
	}
}







void pheromone_evaporates() {
	for (int i = 0; i < CITY_AMOUNT; i++) {
		for (int j = 0; j < CITY_AMOUNT; j++) {
			if (pheromone_links[i][j] != INVALID) {
				pheromone_links[i][j] = (1 - EVAPORATION_RATE) * pheromone_links[i][j];    // Pij <- (1- p)Pij    where P == pi 
			}
		}
	}
}







void update_pheromone() {
	for (int i = 0; i < CITY_AMOUNT; i++) {                                // POPULATION SIZE CHANGED TO CITY_AMOUNT
		double pheromone_to_sum = POSITIVE_CONTS / ants[i].fitness;
		for (int j = 0; j < (CITY_AMOUNT - 1); j++) {
			int city = ants[i].position;
			ants[i].position = j;
			int next_city = ants[i].position;                              // ADD NEW PHEROMONE CHANGE TO THE INITIAL PHEROMONE VALUE
			
			if (pheromone_links[city][next_city] != INVALID) {                         // Pij <-- Pij + summation_(delta_pij)
				pheromone_links[city][next_city] += pheromone_to_sum;
			}
		}
	}

}





int get_random_number(int from, int to) {
	return (from < to) ? (rand() % to) + from : 0;
}





double calculate_time(clock_t start, clock_t end) {
	return 1000.0 * ((double) (end - start) / (double) CLOCKS_PER_SEC);
}



void print_route(int ant_index, int route[CITY_AMOUNT], double distance, double channels) {
	string temp = "Ant " + number_to_String(ant_index) + " Index" +" : ";
	for (unsigned int i = 0; i < CITY_AMOUNT; i++) {
		temp += number_to_String(route[i]);
		if ((i + 1) != CITY_AMOUNT) {
			temp += ", ";
		}
	}
	temp += ".Size: " + number_to_String(distance) ;
	
	//temp += "Channels Remaining" + number_to_String(channels) + " ," +"\n";
	
	cout << temp << endl;
}



void print_pheromone() {
	string temp = "Pheromone Rates:";
	temp += "\n{";
	for (int i = 0; i < CITY_AMOUNT; i++) {
		temp += "{";
		for (int j = 0; j < CITY_AMOUNT; j++) {
			temp += number_to_String(pheromone_links[i][j]);
			if ((j + 1) != CITY_AMOUNT) {
				temp += ", ";
			}
		}
		if ((i + 1) != CITY_AMOUNT) {
			temp += "}, ";
		} else {
			temp += "}";
		}
	}
	temp += "}\n";
	cout << temp << endl;
}





void print_result() {
	cout << "Worst Result:" << endl;
	cout << "f(x):" << worse_fitness << endl;
	//print_route(0, worse_route, worse_distance);

	cout << "Best result:" << endl;
	cout << "f(x):" << best_fitness << endl;
	//print_route(0, best_route, best_distance);

	calculate_metrics();
	cout << "Average:" << average << endl;
	cout << "Variance:" << variance << endl;
	cout << "Standard deviation:" << standard_deviation << endl;
}




string number_to_String(double n) {
	stringstream out;
	out << n;
	return out.str();
}








void calculate_metrics() {
	// Calculate the mean
	double sum = 0;
	for (int i = 0; i < POPULATION_SIZE; i++) {
		sum += ants[i].distance;
	}
	average = (double) sum / (double) POPULATION_SIZE;
	// Calculate the variances
	sum = 0;
	for (int i = 0; i < POPULATION_SIZE; i++) {
		sum += pow(ants[i].distance - average, 2);
	}
	variance = (double) sum / (double) POPULATION_SIZE;
	// Calculating the standard deviation
	standard_deviation = pow(variance, 0.5);
} 


struct result_ant{
	double distance;
	int next_node;
	//double fitness;
	double channels = 35;
	int position;
	int path[36];
};

/*
void route(int source , int destination){
	result_ant.position =source;
	int i,j;
	int best=0;
	for(i=0;i<CITY_AMOUNT;i++){
		if (distance_link[source][i]!=INVALID){
			if(distance_link[source][i]<=best){
				best=
			}
		}
	}
	
	
}
*/





// ------------------------------------------------------- MAIN BODY ----------------------------------------------------------------------------



int main(int argc, char *argv[]) {
	clock_t time_start = clock();
	// Initializing the random number generator with a temporal seed
	srand(time(0));
	// Initialize the interaction counter
	int iteration = 0;

	// Setting the initial pheromone concentrations
	seed_initial_pheromone(false);
	// Taking the longest distance with 1
	get_greater_distance();

	// Stopping condition
	while (iteration < 1) {      // RUNNING THE PROGRAM FOR 30 TIMES
	
		build_solution();
		check_best_distance();
		calculate_fitness();
		pheromone_evaporates();
		update_pheromone();
		for (int i = 0; i < 1; i++){
		
		
			//print_route(i, ants[i].route, ants[i].distance, ants[i].channels);
			
			
		   // reducing the no of channels
	
}
	     // REDUCE THE NUMBER OF CHANNELS FOR THE INTERMEDIATE EDGES BETWEEN THE TWO NODES
	    
		iteration++;
	
	
	}

	// Printing the final result
	//print_result();

	cout << "\n Runtime (ACO): "
			<< calculate_time(time_start, clock()) << " ms" << endl;
	//cin.get(); // Waits for a new character to terminate the application
	return 0;
}
