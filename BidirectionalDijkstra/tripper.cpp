#include "tripper.h"
#include "RoadRunner.h"
#include "BinaryHeap.h"
#include <iostream>
using namespace std;

Tripper::Tripper(Road *roads, int numRoads, int size)
{
  temp_pathA = new int[size * size];
  temp_pathB = new int[size * size];
  road = new Road[numRoads];
  // declare one array for Dijkstra in each direction
  arrA = new City[size * size];
  arrB = new City[size * size];
  for(int i = 0; i < numRoads; i++){
   road[i].num = roads[i].num;
   road[i].city1 = roads[i].city1;
   road[i].city2 = roads[i].city2;
   road[i].distance = roads[i].distance;
  }
  numberRoads = numRoads;
  sizeWorld = size;
  adjacencyList = new ListNode[size * size];
  for(int i = 0; i < size * size; i++){ // initialize adjacency list
    (adjacencyList)[i] = ListNode(i, 0, NULL, 0);
  }

  buildAdjacencyList(); // build adjacency list for trip
} // Tripper()

void Tripper::buildAdjacencyList(){
  ListNode* temp;

  for(int i = 0; i < numberRoads; i++){
    if(road[i].distance == -1 || road[i].distance == 0){ // if road does not exist skip
      continue;
    }
    else{
      temp = new ListNode(road[i].city2, road[i].distance, adjacencyList[road[i].city1].next, road[i].num);
      (adjacencyList)[road[i].city1].next = temp; // add road to adjacency list
    }
  }
}

Tripper::~Tripper()
{
  for(int i = 0; i< sizeWorld * sizeWorld; i++){
    while(adjacencyList[i].next != NULL){
      ListNode* oldNode = adjacencyList[i].next;
      adjacencyList[i].next = oldNode->next;
      delete oldNode;
    }
  }

  delete [] adjacencyList;
  delete [] road;
  delete [] arrA;
  delete [] arrB;
  delete [] temp_pathA;
  delete [] temp_pathB;
} // ~Tripper()

int Tripper::findPath(int city1, int city2, int path[], int *pathCount)
{
  BinaryHeap<City> heapA(sizeWorld * sizeWorld);
  BinaryHeap<City> heapB(sizeWorld * sizeWorld);

  for(int i = 0; i<sizeWorld * sizeWorld; i++){
     arrA[i] = City(i, -1, false, -1);
     arrB[i] = City(i, -1, false, -1);
  }

  *pathCount = 0;
  City cityA;
  City cityB;
  int pathCountA = 0;
  int pathCountB = 0;

  for(int i = 0; i < sizeWorld * sizeWorld; i++){
    path[i] = 0;
    temp_pathA[i] = 0;
    temp_pathB[i] = 0;
  }

  arrA[city1].distance_to_vertex = 0;
  arrB[city2].distance_to_vertex = 0;
  heapA.insert(arrA[city1]); // insert starting city as initial vertex
  heapB.insert(arrB[city2]); // insert destination as initial vertex

  City city;
  int shortest_path = 0;

  while(!heapA.isEmpty() && !heapB.isEmpty()){
    heapA.deleteMin(cityA); // pop city off heap
    if(arrB[cityA.city_num].known){
      city = cityA;

      shortest_path = arrA[city.city_num].distance_to_vertex + arrB[city.city_num].distance_to_vertex;
      for(int i = 0; i < sizeWorld * sizeWorld; i++){
        if(arrA[i].distance_to_vertex >= 0 && arrB[i].distance_to_vertex >= 0){
          if(arrA[i].distance_to_vertex + arrB[i].distance_to_vertex <= shortest_path){
            city = arrA[i];
            shortest_path = arrA[i].distance_to_vertex + arrB[i].distance_to_vertex;
          }
        }
      }

      pathCountA = findActualPathA(arrA[city.city_num], pathCountA);
      pathCountB = findActualPathB(arrB[city.city_num], pathCountB);

      *pathCount = pathCountA + pathCountB; // find total path count or number of roads

      for(int i = 0; i < pathCountA; i++){ // add roads to path
        path[pathCountA - i - 1] = temp_pathA[i];
      }
      for(int i = 0 ; i < pathCountB; i++){
        path[pathCountA + i] = temp_pathB[i];
      }

      return arrA[city.city_num].distance_to_vertex + arrB[city.city_num].distance_to_vertex;
    }
    else{
      dijkstraA(cityA, &heapA, city2, path, pathCount); // Dijkstra algorithm
    }

    heapB.deleteMin(cityB); // pop city off heap
    if(arrA[cityB.city_num].known){
      city = cityB;

      shortest_path = arrA[city.city_num].distance_to_vertex + arrB[city.city_num].distance_to_vertex;

      for(int i = 0; i < sizeWorld * sizeWorld; i++){
        if(arrA[i].distance_to_vertex >= 0 && arrB[i].distance_to_vertex >= 0){
          if(arrA[i].distance_to_vertex + arrB[i].distance_to_vertex <= shortest_path){
            city = arrA[i];
            shortest_path = arrA[i].distance_to_vertex + arrB[i].distance_to_vertex;
          }
        }
      }
      pathCountA = findActualPathA(arrA[city.city_num], pathCountA);
      pathCountB = findActualPathB(arrB[city.city_num], pathCountB);

      *pathCount = pathCountA + pathCountB;

      for(int i = 0; i < pathCountA; i++){
        path[pathCountA - i - 1] = temp_pathA[i];
      }
      for(int i = 0 ; i < pathCountB; i++){
        path[pathCountA + i] = temp_pathB[i];
      }

      return arrA[city.city_num].distance_to_vertex + arrB[city.city_num].distance_to_vertex;
    }
    else{
      dijkstraB(cityB, &heapB, city1, path, pathCount);
    }
  }

  return city.distance_to_vertex;
}  // findPath()


void Tripper::dijkstraA(City city, BinaryHeap<City>* heap, int city2, int path[], int* pathCount){
    // implement Dijkstra algorithm from starting city
    ListNode* temp = NULL;
    if(!arrA[city.city_num].known){
      arrA[city.city_num].known = true;

      ListNode tempAdj;

      temp = adjacencyList[city.city_num].next;
      while(temp != NULL){
        if(arrA[temp->city].known){
          temp = temp-> next;
          continue;
        }
        if(arrA[temp->city].distance_to_vertex == -1){
          arrA[temp->city].distance_to_vertex = arrA[city.city_num].distance_to_vertex + temp->road_distance;
          arrA[temp->city].previous_vertex = city.city_num;
          heap->insert(arrA[temp->city]);
        }
        else if(arrA[temp->city].distance_to_vertex > (arrA[city.city_num].distance_to_vertex + temp->road_distance)){
          arrA[temp->city].distance_to_vertex = arrA[city.city_num].distance_to_vertex + temp->road_distance;
          arrA[temp->city].previous_vertex = city.city_num;
          heap->insert(arrA[temp->city]);
        }
        if(temp->next == NULL) break;
        temp = temp->next;
      }
    }

}

void Tripper::dijkstraB(City city, BinaryHeap<City>* heap, int city2, int path[], int* pathCount){
    // implement dijkstra algorithm from destination
    ListNode* temp = NULL;

    if(!arrB[city.city_num].known){
      arrB[city.city_num].known = true;

      ListNode tempAdj;

      temp = adjacencyList[city.city_num].next;
      while(temp != NULL){
        if(arrB[temp->city].known){
          temp = temp-> next;
          continue;
        }
        if(arrB[temp->city].distance_to_vertex == -1){
          arrB[temp->city].distance_to_vertex = arrB[city.city_num].distance_to_vertex + temp->road_distance;
          arrB[temp->city].previous_vertex = city.city_num;
          heap->insert(arrB[temp->city]);
        }
        else if(arrB[temp->city].distance_to_vertex > (arrB[city.city_num].distance_to_vertex + temp->road_distance)){
          arrB[temp->city].distance_to_vertex = arrB[city.city_num].distance_to_vertex + temp->road_distance;
          arrB[temp->city].previous_vertex = city.city_num;
          heap->insert(arrB[temp->city]);
        }
        if(temp->next == NULL) break;
        temp = temp->next;
      }
    }

}

int Tripper::findActualPathA(City city, int pathCount){
  // adds roads to path from starting city to meetup point
  int index = 0;
  ListNode tempAdj;
  City city_final;
  ListNode* nextTemp;

  city_final = city;

  while(arrA[city_final.city_num].previous_vertex != -1){
    (pathCount)++;
    tempAdj = adjacencyList[city_final.previous_vertex];
    nextTemp = tempAdj.next;
    while(nextTemp != NULL){
      if(nextTemp->city == city_final.city_num){
        temp_pathA[index] = nextTemp->road_id;
        index++;
        city_final = arrA[city_final.previous_vertex];
        break;
      }
      nextTemp = nextTemp->next;
    }
  }

  return pathCount;

}

int Tripper::findActualPathB(City city, int pathCount){
  // adds roads to path from meetup point to ending city
  int index = 0;
  ListNode tempAdj;
  City city_final;
  ListNode tempAdj2;
  ListNode* nextTemp;
  ListNode* prevTemp;

  city_final = city;

  while(arrB[city_final.city_num].previous_vertex != -1){
    (pathCount)++;
    tempAdj = adjacencyList[city_final.previous_vertex];
    nextTemp = tempAdj.next;
    while(nextTemp != NULL){
      if(nextTemp->city == city_final.city_num){
        tempAdj2 = adjacencyList[nextTemp->city];
        prevTemp = tempAdj2.next;
        while(prevTemp != NULL){
          if(prevTemp->city == city_final.previous_vertex){
            temp_pathB[index] = prevTemp->road_id;
            index++;
            break;
          }
          prevTemp = prevTemp->next;
        }
        city_final = arrB[city_final.previous_vertex];
        break;
      }
      nextTemp = nextTemp->next;
    }
  }

  return pathCount;

}
