// Author Sean Davis
#ifndef _TRIPPER_H
#define	_TRIPPER_H

#include "RoadRunner.h"
#include "BinaryHeap.h"

class ListNode{
public:
  ListNode(){
    city = 0;
    road_distance = 0;
    next = NULL;
    road_id = 0;
  }
  ListNode(int citynum, int distance, ListNode* listNode, int road_num){
    city = citynum;
    road_distance = distance;
    next = listNode;
    road_id = road_num;
  }

  int city;
  int road_distance;
  ListNode* next;
  int road_id;

  ~ListNode(){
  }
};

class City{
public:
  City(){
    city_num = 0;
    distance_to_vertex= -1;
    known = false;
    previous_vertex = -1;
  }

  City(int num, int distance, bool isKnown, int previous){
    city_num = num;
    distance_to_vertex = distance;
    known = isKnown;
    previous_vertex = previous;
  }

  friend bool operator< (const City& obj1, const City& obj2){
    return obj1.distance_to_vertex < obj2.distance_to_vertex;
  }

  City& operator= (const City& other){
    if(&other == this) return *this;
    previous_vertex = other.previous_vertex;
    known = other.known;
    distance_to_vertex = other.distance_to_vertex;
    city_num = other.city_num;
    return *this;
  }

  int previous_vertex;
  int city_num;
  int distance_to_vertex;
  bool known;
};

class Tripper {
public:
  Tripper(Road *roads, int numRoads, int size);
  int findPath(int city1, int city2, int path[], int *pathCount);
  ~Tripper();
  void buildAdjacencyList();
  void dijkstraA(City city, BinaryHeap<City>* heap, int city2, int path[], int* pathCount);
  void dijkstraB(City city, BinaryHeap<City>* heap, int city2, int path[], int* pathCount);
  int findActualPathA(City city, int pathCount);
  int findActualPathB(City city, int pathCount);

  int* temp_pathA;
  int* temp_pathB;
  ListNode* adjacencyList;
  City* arrA;
  City* arrB;
  Road* road;
  int numberRoads;
  int sizeWorld;
}; // class Tripper

#endif
