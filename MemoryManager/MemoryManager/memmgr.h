#ifndef __MEMMGR_H_
#define __MEMMGR_H_

#include <vector>
#include <set>
#include <forward_list>

class IMemoryManager 
  {
  public:
    virtual void* allocate(size_t) = 0;
    virtual void   deallocate(void*) = 0;
  };

class MemoryManager : public IMemoryManager 
  {
  //the block sizes can be determined by the user based on approximating 
  //the sizes of object types used in the application 
  //The MemoryPool can be initialised partially or completely , based on the 
  //need and the frequency of occurence of certain types of object; 
  //each block shall contain 4 extra bytes to store metadata information 
  //One such information is that indicating whether this block is free 
  //or not. Another tentative information could be guard bytes which detect 
  //heap memory corruption , ie , when someone writes beyond the boundary 
  //of an object accidentally via  memcpy or memset functions.In our 
  //implementation everyblock is guarded by 4 bytes in the end.The first two 
  //bytes of these four are marked with  special characters 0xde,0xad indicating
  //the end of the block .The next byte will contain the size of block and the 
  //of the byte shall indicate wheteher this block is free or available.
  private:
    std::forward_list<void*>     Byte8PtrList;
    std::forward_list<void*>     Byte16PtrList;
    std::forward_list<void*>     Byte24PtrList;
    std::forward_list<void*>     Byte32PtrList;
    std::forward_list<void*>     Byte40PtrList;
    std::vector<void*>    MemoryPoolList;
    friend class JobScheduler;
    friend class Coordinate;
    friend class Complex;
    void InitialiseByte24List(void* );
    void InitialiseByte32List(void* );
    void InitialiseByte40List(void* );

    const char* guardByte1;
    const char* guardByte2;
  public: 
      MemoryManager() { guardByte1 = nullptr; guardByte2 = nullptr; }
    ~MemoryManager( ) {}
    void* allocate(size_t);
    void   deallocate(void*);

  };

#endif