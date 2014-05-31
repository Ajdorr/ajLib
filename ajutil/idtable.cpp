#include "idtable.h"

#define TABLE_EMPTY 0xFFFFFFFFFFFFFFFF

/*
 *
 * IDEntry Class
 *
 */

uint64_t IDEntry::getIDfromEntry(uint64_t a) {
  if (a & 0xFFFFFFFFull) {
    if (a & 0xFFFFull) {
      if (a & 0xFFull) {
        if (a & 0xFull) {
          if (a & 0x3ull) { if (a & 0x1ull) return 0; else return 1;}
          else { if (a & 0x4ull) return 2; else return 3; }
        } else {
          if (a & 0x30ull) { if (a & 0x10ull) return 4; else return 5; }
          else { if (a & 0x40ull) return 6; else return 7; }
        }
      } else {
        if (a & 0xF00ull) {
          if (a & 0x300ull) { if (a & 0x100ull) return 8; else return 9; }
          else { if (a & 0x400ull) return 10; else return 11; }
        }
        else {
          if (a & 0x3000) { if (a & 0x1000) return 12; else return 13; }
          else { if (a & 0x4000) return 14; else return 15; }
        }
      }
    } else {
      if (a & 0xFF0000) {
        if (a & 0xF0000) {
          if (a & 0x30000) { if (a & 0x10000) return 16; else return 17;}
          else { if (a & 0x40000) return 18; else return 19; }
        } else {
          if (a & 0x300000) { if (a & 0x100000) return 20; else return 21; }
          else { if (a & 0x400000) return 22; else return 23; }
        }
      } else {
        if (a & 0xF000000) {
          if (a & 0x3000000) { if (a & 0x1000000) return 24; else return 25; }
          else { if (a & 0x4000000) return 26; else return 27; }
        }
        else {
          if (a & 0x30000000) { if (a & 0x10000000) return 28; else return 29; }
          else { if (a & 0x40000000) return 30; else return 31; }
        }
      }
    }
  } else {
    if (a & 0xFFFF00000000) {
      if (a & 0xFF00000000) {
        if (a & 0xF00000000) {
          if (a & 0x300000000) { if (a & 0x100000000) return 32; else return 33;}
          else { if (a & 0x400000000) return 34; else return 35; }
        } else {
          if (a & 0x3000000000) { if (a & 0x1000000000) return 36; else return 37; }
          else { if (a & 0x4000000000) return 38; else return 39; }
        }
      } else {
        if (a & 0xF0000000000) {
          if (a & 0x30000000000) { if (a & 0x10000000000) return 40; else return 41; }
          else { if (a & 0x40000000000) return 42; else return 43; }
        }
        else {
          if (a & 0x300000000000) { if (a & 0x100000000000) return 44; else return 45; }
          else { if (a & 0x400000000000) return 46; else return 47; }
        }
      }
    } else {
      if (a & 0xFF000000000000) {
        if (a & 0xF000000000000) {
          if (a & 0x3000000000000) { if (a & 0x1000000000000) return 48; else return 49;}
          else { if (a & 0x4000000000000) return 50; else return 51; }
        } else {
          if (a & 0x30000000000000) { if (a & 0x10000000000000) return 52; else return 53; }
          else { if (a & 0x40000000000000) return 54; else return 55; }
        }
      } else {
        if (a & 0xF00000000000000) {
          if (a & 0x300000000000000) { if (a & 0x100000000000000) return 56; else return 57; }
          else { if (a & 0x400000000000000) return 58; else return 59; }
        }
        else {
          if (a & 0x3000000000000000) { if (a & 0x1000000000000000) return 60; else return 61; }
          else { if (a & 0x4000000000000000) return 62; else return 63; }
        }
      }
    }
  }
}

IDEntry::IDEntry() {
  ent[0] = TABLE_EMPTY;
  ent[1] = TABLE_EMPTY;
  ent[2] = TABLE_EMPTY;
  ent[3] = TABLE_EMPTY;
}

uint64_t IDEntry::getID()
{
  uint64_t a;

  if (ent[0] != 0) {
    a = getIDfromEntry(ent[0]);
  }
  else if (ent[1] != 0) {
    a = getIDfromEntry(ent[1]);
    a |= 0x40;
  }
  else if (ent[2] != 0) {
    a = getIDfromEntry(ent[2]);
    a |= 0x80;
  }
  else if (ent[3] != 0) {
    a = getIDfromEntry(ent[3]);
    a |= 0xC0;
  }
  else a = TABLE_EMPTY;

  return a;
}

void IDEntry::markID(uint64_t a)
{
  uint64_t t;

  t = 0x1ull << (a & 0x3Full);

  if (a >= 0xC0) ent[3] &= ~t;
  else if (a >= 0x80) ent[2] &= ~t;
  else if (a >= 0x40) ent[1] &= ~t;
  else ent[0] &= ~t;

}

void IDEntry::retID(uint64_t a)
{
  uint64_t t;

  t = 0x1ull << (a & 0x3Full);

  if (a >= 0xC0) ent[3] |= t;
  else if (a >= 0x80) ent[2] |= t;
  else if (a >= 0x40) ent[1] |= t;
  else ent[0] |= t;

}


/*
 *
 * IDHeaderLeaf Class
 *
 */

IDHeaderLeaf::IDHeaderLeaf()
{
  shift = 0;
  mask = 0xFF;
}

uint64_t IDHeaderLeaf::getID()
{
  uint64_t ret;

  ret = table.getID();
  if (ret != TABLE_EMPTY) table.markID(ret);

  return ret;
}

void IDHeaderLeaf::retID(uint64_t a)
{
  table.retID(a & mask);
}

/*
 *
 * IDHeader Class
 *
 */

IDHeader::IDHeader()
{
  int i;
  hints = 0;
  shift = 8;
  mask = 0xFF00;
  uselist[0] = new IDHeaderLeaf();
  for (i = 1; i < 256; i++) uselist[i] = NULL;
}


IDHeader::IDHeader(IDHeader *subtree)
{
  int i;
  hints = 0;
  this->shift = subtree->shift + 8;
  this->mask = subtree->mask << 8;
  uselist[0] = subtree;
  for (i = 1; i < 256; i++) uselist[i] = NULL;
}

IDHeader::IDHeader(uint64_t s, uint64_t m)
{
  int i;
  hints = 0;
  shift = s;
  mask = m;
  if (s == 8) uselist[0] = new IDHeaderLeaf();
  else uselist[0] = new IDHeader(s - 8, m >> 8);
  for (i = 1; i < 256; i++) uselist[i] = NULL;
}

IDHeader::~IDHeader()
{
  int i;
  for (i = 0; i < 256; i++)
  {
    delete uselist[i];
    uselist[i] = NULL;
  }
}

uint64_t IDHeader::getID()
{

 uint64_t i, ret;

  for (i = hints; i < 256; i++)
  {
    if (uselist[i] == NULL)
    {
      if (shift == 8) uselist[i] = new IDHeaderLeaf();
      else uselist[i] = new IDHeader(shift - 8, mask >> 8);
    }
    ret = uselist[i]->getID();

    if (ret == TABLE_EMPTY)
    {
      table.markID(i);
      hints = (i > hints) ? i+1 : hints;
    }
    else break;
  }

  if (i == 256) return TABLE_EMPTY;
  else return (i << shift) | (ret);
}

void IDHeader::retID(uint64_t a)
{
  uint64_t i = ((a & mask) >> shift);
  if (uselist[i] != NULL)
  {
    uselist[i]->retID(a);
    if (hints > i) hints = i;
  }
}

IDTable::IDTable()
{
  _root = new IDHeader();
  tablelen = 1;
}

uint64_t IDTable::getID()
{
  IDHeader *hdrp;
  uint64_t ret = _root->getID();

  if (ret == TABLE_EMPTY) {
    hdrp = new IDHeader(_root);

    _root = hdrp;
    ret = hdrp->getID();
  }

  return ret;
}


IDTable::~IDTable()
{
  delete _root;
}


void IDTable::retID(uint64_t a)
{
  _root->retID(a);
}
