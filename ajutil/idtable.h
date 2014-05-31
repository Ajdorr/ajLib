#ifndef IDTABLE_H
#define IDTABLE_H
#include <stdint.h>
#include <stdlib.h>

// WIP

// single entry to keep track of 0-255 ids [0 bits]
// 1 is empty, 0 is in use
// think in terms of available IDs
class IDEntry
{
private:
  uint64_t ent[4];

  uint64_t getIDfromEntry(uint64_t);
public:
  IDEntry();

  uint64_t getID(); // returns an available ID, does not mark it
  void markID(uint64_t);
  void retID(uint64_t);
};

class IDHeaderLeaf
{
protected:
  uint64_t shift, mask;
  IDEntry table;
public:
  IDHeaderLeaf();
  virtual ~IDHeaderLeaf(){}

  virtual uint64_t getID();
  virtual void retID(uint64_t);
};

class IDHeader : public IDHeaderLeaf
{
protected:
  // IDEntry *entlist[256];
  uint64_t hints;
  IDHeaderLeaf *uselist[256];
public:
  IDHeader();
  IDHeader(IDHeader*); // Not a copy constructor, used to extend the table
  IDHeader(uint64_t shft, uint64_t msk);
  virtual ~IDHeader();

  virtual uint64_t getID();
  virtual void retID(uint64_t);
};

// automatically expanding table to keep track of unsigned integer IDs
class IDTable
{
private:
  int tablelen;
  IDHeader *_root;

public:
  IDTable();
  IDTable(unsigned int); // create a table with at least this many entries
  ~IDTable();

  uint64_t getID();
  void retID(uint64_t);
};

#endif // IDTABLE_H
