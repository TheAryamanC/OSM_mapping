/*node.h*/

/// <sumary>
/// Header file for node.cpp
/// <summary>

#pragma once

// node class definition
class Node
{
private:
  long long ID;
  double Lat;
  double Lon;
  bool   IsEntrance;

  // static variables (for optimization purposes)
  inline static int CallsToGetID = 0;
  inline static int Created = 0;
  inline static int Copied = 0;

public:
  // constructor
  Node(long long id, double lat, double lon, bool entrance);
  
  // copy constructor:
  Node(const Node& other);

  long long getID();
  double getLat() const;
  double getLon() const;
  bool getIsEntrance() const;

  static int getCallsToGetID();
  static int getCreated();
  static int getCopied();
};
