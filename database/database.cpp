#include <list>
#include <algorithm>
#include <cstdlib>
#include <string>
using namespace std;
#include "database.h"
#include "relationType.h"

extern int data_number;
extern int Global_block_count;

template <class T> int Maindata<T>::insert(patient_f* p)
{   
    int a=-1, b =-1, c = -1, d = -1;
    a = person.insert(p);
    b = medical_status.insert(p);
    c = registration.insert(p);
    d = treatment.insert(p);
    if(a== b==c == d  && a!= -1)
    return a ;
    else
    return -1;
}
template <class T> bool Maindata<T>::search(int id)
{
    return person.search(id);
}
template <class T> void Maindata<T>::modify(int id,patient_f* p)
{
    person.modify(id,p);
    medical_status.modify(id,p);
    registration.modify(id,p);
    treatment.modify(id,p);
    return;
}
template <class T> void Maindata<T>::modifyperson(int id,patient_f* p)
{
    person.modify(id,p);
    
    return;
}
template <class T> void Maindata<T>::modifystatus(int id,patient_f* p)
{
    
    medical_status.modify(id,p);
    
    return;
}
template <class T> void Maindata<T>::modifyregistration(int id,patient_f* p)
{
    
    registration.modify(id,p);
    return;
}
template <class T> void Maindata<T>::modifytreatment(int id,patient_f* p)
{
    
    treatment.modify(id,p);
    return;

}
template <class T> void Maindata<T>::remove(patient_f* p)
{
    person.remove(p);
    medical_status.remove(p);
    registration.remove(p);
    treatment.remove(p);
    return;
}
template <class T> bool Maindata<T>::add_patient(patient_f* p)
{
    switch (p->treatment_type)
    {
    case 0/* constant-expression */:
        center1->add_patient(p);
        break;
    case 1
        center2->add_patient(p);
        break;

    case 2
        center3->add_patient(p);
        break;
    default:
        cout<<"wrong treatment type!"<<endl; 
        break;
    }
}
template <class T> T Maindata<T>::retrieveperson(int id)
{
    return person.retrieve(id);
}
template <class T> T Maindata<T>::retrievestatus(int id)
{
    return medical_status.retrieve(id);
}
template <class T> T Maindata<T>::retrieveregistration(int id)
{
    return registration.retrieve(id);
}
template <class T> T Maindata<T>::retrievetreatment(int id)
{
    return treatment.retrieve(id);
}






//relation 's member function

template <class T> int relation<T>::insert(patient_f* p)// 永远先插入未满的空桶, 返回当前插入的是第几个位置(从1开始)
{
    
    bool all_full = true;
    T temp=new T(patient_f* p;);
    extern int Global_Block_count;
    int block_count = 0;
    // 遍历relation中的所有block
    typename list< Block<T> >::iterator iterator=this->blocks.begin();
    for ( iterator=this->blocks.begin(); iterator != this->blocks.end(); ++iterator, ++block_count)
    {
        if (!iterator->full()) { //若当前block未满, 放入overflowblock
        iterator->overflowBlock.push_back(temp);
        //若插入后满, sort
        if (iterator->full()) iterator->Sort();
        all_full = false;
        vector<T>& Blocker = (iterator->full()) ? iterator->array : iterator->overflowBlock;
        int result = Blocker.size() + block_count*MAX_BLOCK_CAPACITY; // result 返回当前插入block 是第几个, 从1开始
        return result;
        }
    }
    // 若当前relation为空或已满
    if (blocks.empty() || all_full) {
        block<T> newBlock;
        newBlock.overflowBlock.push_back(temp);
        blocks.push_back(newBlock);
        Global_Block_count++;
        int result = block_count* MAX_BLOCK_CAPACITY +1;
        return Global_Block_count;
    }

    // unreachable
    return false;
}
template <class T> bool relation<T>::search(int id)
{
    T* x = this->retrieve(id);
    return (x->getid() != -1);
}

template <class T> int relation<T> ::indx_to_id(int block_rank)
{
    int block_row = (block_rank-1) / MAX_BLOCK_CAPACITY; //记录是第几个block
    int block_column = block_rank - block_row * MAX_BLOCK_CAPACITY; //记录是该block 的第几个元素
    int i = 0;
    typename list< Block<T> >::iterator iterator=this->blocks.begin();
    for (iterator=this->blocks.begin(); iterator != this->blocks.end() && i < block_row; ++iterator)
    vector<T>& Blocker = (iterator->full()) ? iterator->array : iterator->overflowBlock;
    return Blocker[block_column -1].getid();
}
template <class T> T relation<T>::retrieve(int id)
{   
    typename list< Block<T> >::iterator iterator=this->blocks.begin();
    for (iterator=this->blocks.begin(); iterator != this->blocks.end(); ++iterator) {
        vector<T>& Blocker = (iterator->full()) ? iterator->array : iterator->overflowBlock;
        for (int i=0;i<(int)Blocker.size();i++){
            if (Blocker[i].getid() == id)
            return Blocker[i];
        }
    }
    T temp;
    temp.setid(-1);
    return temp;
}
template <class T> void relation<T>::modify(int id,patient_f* p)
{
    T tmp=retrieve(id);
    if (T->getid()==-1)
    {
        return;
    }
    tmp.modify(p);
    return;

}
template<class T> bool relation<T>::remove(int id) {
    typename list< Block<T> >::iterator iterator=this->blocks.begin();
    for (iterator=this->blocks.begin(); iterator != this->blocks.end(); ++iterator) {
        vector<T>& Blocker = (iterator->full()) ? iterator->array : iterator->overflowBlock;
        for (int i=0;i<(int)Blocker.size();i++)
        if (Blocker[i].getID() == id) {
            bool judge_full = iterator->full();
            // 删除该元素
            swap(Blocker[i], Blocker[(int)Blocker.size()-1]);
            Blocker.pop_back();
            data_number--;// 记录datanumber的全局变量递减
            if (judge_full) { //若删除前block是满的, 则在删除后将主block里的元素倒进overflowBlock中
                iterator->array.swap(iterator->overflowBlock);
                iterator->array.clear();
            }
            if (iterator->size() == 0){
                this->blocks.erase(iterator);
                extern int Global_Block_count;
                Global_Block_count--;
                }
            return true;
        }
    }
    return false;
}
