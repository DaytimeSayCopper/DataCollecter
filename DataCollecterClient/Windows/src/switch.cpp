#include "switch.h"

void OnState::handle(Context *pContext)
{
    cout<<"打开开关"<<endl;
    if(pContext!=NULL)
    {
    AbsState  *ppState=new OffState();
    pContext->setState(ppState);
    delete this;
    }
}

void OffState::handle(Context *pContext)
{
      cout<<"关闭开关"<<endl;
    if(pContext!=NULL)
    {
    AbsState  *ppState=new  OnState();
    pContext->setState(ppState);
    delete this;
    }
}


void Context::setState(AbsState *ppState)
{
        pState=ppState;
}

void Context::PressSwitch()
{
      pState->handle(this);
}

int main()
{
   Context  *con=new Context();
   AbsState  *on_state=new  OnState();
   AbsState   *off_state=new  OffState();
   con->setState(on_state);
   con->PressSwitch();
   con->PressSwitch();
   con->PressSwitch();
   con->PressSwitch();
}
