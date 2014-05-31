#ifndef KDTREE_H
#define KDTREE_H

class kdTree
{
private:
  int _k;
public:
  kdTree(int k);

  int insert();
  void* search();
  void execAll();
  void traverse();
  int remove();
};

#endif // KDTREE_H
