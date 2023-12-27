#include "synch.h"
#include "stable.h"
//Constructor
STable::STable()
{
    this->bm= new Bitmap(MAX_SEMAPHORE);
    for(int i=0;i<MAX_SEMAPHORE; i++)
    {
        this->semTab[i]=NULL;
    }
}
//Destructor
STable::~STable()
{
    if(this->bm)
    {
        delete this->bm;
        this->bm=NULL;
    }
    for(int i=0;i<MAX_SEMAPHORE;i++)
    {
        if(this->semTab[i])
        {
            delete this->semTab[i];
            this->semTab[i]=NULL;

        }
    }
}
// Method FindFreeSlot
int STable::FindFreeSlot()
{
    return this->bm->FindAndSet();
}
// Method Create Semaphore
int STable::Create(char* name, int init)
{
    //Kiem tra xem da ton tai semaphore hay chua
    for(int i=0;i<MAX_SEMAPHORE ;i++)
    {
        if(bm->Test(i))
        {
            if(strcmp(name,semTab[i]->GetName())==0)
            {
                // Neu da ton tai thi name se bang semTab[i]->GetName
                // Luc nay khong can tao semaphore nua nen se return -1;
                return -1;
            }
        }
    }
    // Neu chua co semaphore, Bat dau tim slot trong
    int id= this->FindFreeSlot();

    // Neu khong tim thay , tuc la khong co slot trong thi tra ve -1
    if(id<0)
    {
        return -1;
    }

    // Neu tim thay slot thi bat dau nap semaphore
    this->semTab[id]= new Sem(name,init);
    printf("Tao Thanh Cong, id: %d",id);
    // return 0 : thanh cong
    return 0;
}

// Method Wait
int STable::Wait(char* name)
{
    printf(name);
    for(int i=0;i<MAX_SEMAPHORE;i++)
    {
        //Kiem tra xem i (id) da duoc nap semaphore hay chua
        if(bm->Test(i))
        {
            printf(semTab[i]->GetName());
            // neu co thi tien hanh so xanh name cua semaphore vs name trong semTab
            if(strcmp(name, semTab[i]->GetName())==0)
            {
                // Neu ton tai thi cho semaphore down()
                printf("Wait semaphore");
                semTab[i]->wait();
                //return 0 : thanh cong
                return 0;
            }
        }
    }
    printf("Loi Wait, Khong ton tai semaphore vs name: %s",name);
    return -1;
}

//Method Signal
int STable::Signal(char*  name)
{
     for(int i=0;i<MAX_SEMAPHORE;i++)
    {
        //Kiem tra xem i (id) da duoc nap semaphore hay chua
        if(bm->Test(i))
        {
            // neu co thi tien hanh so xanh name cua semaphore vs name trong semTab
            if(strcmp(name, semTab[i]->GetName())==0)
            {
                // Neu ton tai thi cho semaphore up()
                semTab[i]->signal();
                printf("Signal semaphore");
                //return 0 : thanh cong
                return 0;
            }
        }
    }
    printf("Loi Signal,Khong ton tai semaphore vs name: %s",name);
    return -1;
}