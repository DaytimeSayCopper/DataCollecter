#ifndef INTERFACE_DEFINE_AND_REALIZE
#define INTERFACE_DEFINE_AND_REALIZE
#include<iostream>
#include<stdio.h>
using std::cout;
using std::endl;

class  Context;

class  AbsState
{
public :
     virtual void handle(Context *pContext)=0;
};

class  OnState:public AbsState
{
  public :
   virtual void handle(Context *pContext);
};

class   OffState:public AbsState
{
  public :
    virtual void handle(Context *pContext);
};

class    Context{
   private:
       AbsState *pState;
   public :
      void setState(AbsState *ppState);
      void PressSwitch ();
};
#endif // INTERFACE_DEFINE_AND_REALIZE