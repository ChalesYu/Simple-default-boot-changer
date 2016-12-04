template <class ElemType>
struct DblNode
{
    ElemType data;
    DblNode <ElemType> *back;
    DblNode <ElemType> *next;
    DblNode() {}
    DblNode(ElemType e,DblNode <ElemType> *linkback=NULL,DblNode <ElemType> *linknext=NULL):data(e),back(linkback),next(linknext) {}
};

template <class ElemType>
class DblLinkList
{
protected:
    DblNode <ElemType> *head;
    DblNode <ElemType> *GetElemPtr(int position) const
    {

    if(position==0)
    {
        return head;
    }
    DblNode <ElemType> *tmpPtr=head->next;
    int pos=1;
    while(tmpPtr!=head&&pos<position)
    {
        tmpPtr=tmpPtr->next;
        pos++;
    }
    if(tmpPtr!=head&&pos==position)
    {
        return tmpPtr;
    }
    else
        return NULL;

    	}

public:
    DblLinkList()
    {
    head=new DblNode <ElemType>;
    head->next=head;
}
    virtual ~DblLinkList()
    {
   // ElemType tmpPtr;
    while(!Empty())
    {
        Delete(1);
    }
}
char pushchar(int position)
{
   return  GetElemPtr(position)->data;
}
//
    void strstr_replace_once(const char *old,const char *ne); //replace string node
//
    bool Empty()
    {
    return (head->next==head);
}
    int Length()
    {
    int count=0;
    DblNode <ElemType> *tmpPtr;
    for(tmpPtr=head->next; tmpPtr!=head; tmpPtr=tmpPtr->next)
        count++;
    return count;
}
    bool Insert(int position,const ElemType &e)
    {
    if(position<1||position>Length()+1)
        return false;
    else
    {
        DblNode <ElemType> *tmpPtr,*nextPtr,*newPtr;
        tmpPtr=GetElemPtr(position-1);
        nextPtr=tmpPtr->next;
        newPtr=new DblNode<ElemType>(e,tmpPtr,nextPtr);
        tmpPtr->next=newPtr;
        nextPtr->back=newPtr;
        return true;
    }
}
    bool Delete(int position);

    void Traverse(void (*visit)(const ElemType &)) const
    {
    DblNode <ElemType> *tmpPtr;
    for(tmpPtr=head->next; tmpPtr!=head; tmpPtr=tmpPtr->next)
        (*visit)(tmpPtr->data);
}

};
//

template <class ElemType>
 bool DblLinkList<ElemType> ::Delete(int position)
  {
    if(position<1||position>Length())
        return false;
    else
    {
        DblNode <ElemType> *tmpPtr;
        tmpPtr=GetElemPtr(position);
        tmpPtr->back->next=tmpPtr->next;
        tmpPtr->next->back=tmpPtr->back;
        delete tmpPtr;
        return true;
    }
}
///
template <class ElemType>
void show(const ElemType &e)
{
    cout<<e;

}
///
template <class ElemType>
void DblLinkList<ElemType> ::strstr_replace_once(const char *old,const char *ne)
{
    int old_length = (int)strlen(old);//��ý����滻���ַ����Ĵ�С
    int new_length = (int)strlen(ne);
    if(old_length!=new_length) cout<<"ע��! ���滻���ַ��������ַ����ĳ��Ȳ�ͬ"<<endl;

    int i=0, k,founded = 0;
     DblNode <ElemType> *tmpPtr,*possiblePtr,*ifind_startPtr = NULL,*ifind_stopPtr = NULL,*newPtr;
    for (tmpPtr=head->next; tmpPtr!=head && (founded == 0);tmpPtr=tmpPtr->next)//founded���ҽ����滻���ַ�����λ��
    {
        ifind_startPtr=tmpPtr;
        for (possiblePtr=tmpPtr , k = 0; possiblePtr->data == old[k];possiblePtr=possiblePtr->next,k++)
        {
            if (!old[k + 1])
            {
                founded = 1;
                ifind_stopPtr=possiblePtr;
            }
        }
    }
//    ifind_startPtr=tmpPtr;

    if(founded==1)cout<<"���ҵ����ַ���!"<<endl;
    else {cout<<"û���ҵ���������ַ���!"<<endl;cout<<"�ļ�����ԭ�����"<<endl;}


    if (founded != 0)
    {
    ifind_startPtr=ifind_startPtr->back; //get currect location
    ifind_stopPtr=ifind_stopPtr->next;      //  -----|<->--<->|-----   ->  ----<->|----|<->----

    ifind_startPtr->next=ifind_stopPtr;//delete data in middle
    ifind_stopPtr->back=ifind_startPtr;        //   ----<->||<->----

    while (i<new_length)
    {
    newPtr=new DblNode<ElemType>(ne[i],ifind_startPtr,ifind_stopPtr);
    ifind_startPtr->next=newPtr;
    ifind_stopPtr->back=newPtr;
        ifind_startPtr=newPtr;
        i++;
    }
    cout<<"���滻���"<<endl;
    }
    /*  reference :

    if (founded != 0)//��ʼ�滻
    {for(i=0;ne[i];i++)
       Insert(location_num+i,ne[i]);



       for (j = 0; j<location; j++)//�Ȱѱ��滻���ַ�����ǰһ����COPY��temp
            temp[j] = source[j];
        for (i = 0; ne[i]; i++, j++)//�ٰ��滻�����ַ���COPY��temp
            temp[j] = ne[i];
        for (k = location + old_length; source[k]; k++, j++)//��ʣ�µ�����COPY��temp
            temp[j] = source[k];
        //   temp[j]=NULL;
        for(i=0;source[i]=temp[i];i++); //����ʱ�ַ���temp���Ƹ�source

    }
    */
}