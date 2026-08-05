// #include <catch2/catch_test_macros.hpp>
// #include <iostream>

// // change if you choose to use a different header name
// #include "CampusCompass.h"

// using namespace std;

// TEST_CASE("Incorrect Commands", "[Test 1]") {
//   CampusCompass c;
//   c.parseCSV("data/edges.csv", "data/classes.csv");

//   //insert invalid name
//   REQUIRE(c.insert("\"A11y\" 45679999 1 1 COP3530") == false);

//   //insert 7 numbers id
//   REQUIRE(c.insert("\"Bob\" 4567999 1 1 COP3530")   == false);
  
//   //insert invalid class code name
//   REQUIRE(c.insert("\"Bob\" 45679999 1 1 cop3530")  == false); 

//   //insert invalid class code number (must be more than 0)
//   REQUIRE(c.insert("\"Bob\" 45679999 1 0") == false);
  
//   //drop class from invalid ID 
//   REQUIRE(c.dropClass("111122", "COP3530") == false);

//   //remove class that does not exist
//   REQUIRE(c.removeClass("3033030") == false);
// }


// TEST_CASE("Edge Cases", "[Test 2]") {
//   CampusCompass c;
//   c.parseCSV("data/edges.csv", "data/classes.csv");
  
//   //remove a non-existent student
//   REQUIRE(c.remove("11111111") == false);

//   //check unique ID insertion
//   REQUIRE(c.insert("\"John\" 22222222 20 1 COP3530") == true);
//   REQUIRE(c.insert("\"Alberto\" 22222222 20 1 COP3530") == false);


//   //remove students that are already removed
//   REQUIRE(c.dropClass("22222222", "COP3530") == true);   // still successful
//   REQUIRE(c.remove("22222222") == false);

//   //more than 6 classes
//   REQUIRE(c.insert("\"Steph\" 44444444 20 7 COP3502 COP3503 COP3504 COT3100 MAC2311 MAC2312 CDA3101") == false);

//   //edges that do not exist return DNE
//   REQUIRE(c.checkEdgeStatus(1, 3) == "DNE");
//   REQUIRE(c.checkEdgeStatus(99, 100) == "DNE");

// }

// TEST_CASE("Check Functions", "[Test 3]") {
//   CampusCompass c;
//   c.parseCSV("data/edges.csv", "data/classes.csv");

//   REQUIRE(c.insert("\"Brandon\" 45679999 20 2 COP3530 MAC2311") == true);
//   REQUIRE(c.insert("\"Brian\" 35459999 21 3 COP3530 CDA3101 MAC2311") == true);
//   REQUIRE(c.insert("\"Briana\" 87879999 22 3 CDA3101 MAC2311 EEL3701") == true);

//   //removes one class, leaves the rest
//   REQUIRE(c.dropClass("35459999", "CDA3101") == true);

//   //swaps one for the other, count unchanged
//   REQUIRE(c.replaceClass("45679999", "COP3530", "CDA3101") == true);

//   //returns how many students it was dropped from
//   REQUIRE(c.removeClass("MAC2311") == 3);

//   //succeeds once, fails the second time
//   REQUIRE(c.remove("87879999") == true);
//   REQUIRE(c.remove("87879999") == false);

// }

// TEST_CASE("printShortestEdges Test", "[Test 4]") {
//   CampusCompass c;
//   c.parseCSV("data/edges.csv", "data/classes.csv");
  
  
//   REQUIRE(c.insert("\"Brian\" 35459999 20 2 PHY2048 COP3530") == true);

//   //check shortest path before closing edges
//   auto before = c.printShortestEdges("35459999");
//   REQUIRE(before["PHY2048"] == 14);
//   REQUIRE(before["COP3530"] == 20);
//   REQUIRE(c.checkEdgeStatus(56, 49) == "open");

//   //toggle edge to close it 
//   REQUIRE(c.toggleEdgesClosure("1 56 49") == true);
//   REQUIRE(c.checkEdgeStatus(56, 49) == "closed");

//   //PHY2048 becomes unreachable as 56-49 is the 
//   //only edge to reach building 56 where PHY2048 takes place
//   auto after = c.printShortestEdges("35459999");
//   REQUIRE(after["PHY2048"] == -1);
//   REQUIRE(after["COP3530"] == 20);
//   REQUIRE(c.isConnected(20, 56) == false);

//   //reopen the 56-49 edge
//   REQUIRE(c.toggleEdgesClosure("1 56 49") == true);
//   REQUIRE(c.printShortestEdges("35459999")["PHY2048"] == 14);
//   REQUIRE(c.checkEdgeStatus(56, 49) == "open");

// }