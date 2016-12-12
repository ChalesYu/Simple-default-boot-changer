template <class ElemType>
struct DblNode
{
	ElemType data;
	DblNode <ElemType> *back;
	DblNode <ElemType> *next;
	DblNode() {}
	DblNode(ElemType e, DblNode <ElemType> *linkback = NULL, DblNode <ElemType> *linknext = NULL) :data(e), back(linkback), next(linknext) {}
};
template <class ElemType>
class DblLinkList
{
protected:
	DblNode <ElemType> *head;
	DblNode <ElemType> *GetElemPtr(int position) const
	{
		if (position == 0)
		{
			return head;
		}
		DblNode <ElemType> *tmpPtr = head->next;
		int pos = 1;
		while (tmpPtr != head&&pos<position)
		{
			tmpPtr = tmpPtr->next;
			pos++;
		}
		if (tmpPtr != head&&pos == position)
		{
			return tmpPtr;
		}
		else
			return NULL;
	}
public:
	DblLinkList()
	{
		head = new DblNode <ElemType>;
		head->next = head;
	}
	virtual ~DblLinkList()
	{
		while (!Empty())
		{
			Delete(1);
		}
	}
	void strstr_replace_once(const char *old, const char *ne); //replace string node
	bool Empty()
	{
		return (head->next == head);
	}
	int Length()
	{
		int count = 0;
		DblNode <ElemType> *tmpPtr;
		for (tmpPtr = head->next; tmpPtr != head; tmpPtr = tmpPtr->next)
			count++;
		return count;
	}
	bool Insert_file(int positon, const char *file_location);
	bool push_out_file(const char *file_location);
	bool Delete(int position);
	void Traverse(void(*visit)(const ElemType &)) const
	{
		DblNode <ElemType> *tmpPtr;
		for (tmpPtr = head->next; tmpPtr != head; tmpPtr = tmpPtr->next)
			(*visit)(tmpPtr->data);
	}
};
template <class ElemType>
void DblLinkList<ElemType> ::strstr_replace_once(const char *old, const char *ne)
{
	int old_length = (int)strlen(old);//获得将被替换的字符串的大小
	int new_length = (int)strlen(ne);
	if (old_length != new_length) cout << "注意! 被替换的字符串与新字符串的长度不同" << endl;

	int i = 0, k, founded = 0;
	DblNode <ElemType> *tmpPtr, *possiblePtr, *ifind_startPtr = NULL, *ifind_stopPtr = NULL, *newPtr;
	for (tmpPtr = head->next; tmpPtr != head && (founded == 0); tmpPtr = tmpPtr->next)//founded查找将被替换的字符串的位置
	{
		ifind_startPtr = tmpPtr;
		for (possiblePtr = tmpPtr, k = 0; possiblePtr->data == old[k]; possiblePtr = possiblePtr->next, k++)
		{
			if (!old[k + 1])
			{
				founded = 1;
				ifind_stopPtr = possiblePtr;
			}
		}
	}
	if (founded == 1)cout << "已找到了字符串!" << endl;
	else { cout << "没有找到您输入的字符串!" << endl; cout << "文件将以原样输出" << endl; }
	if (founded != 0)
	{
		ifind_startPtr = ifind_startPtr->back; //delete data in middle
		ifind_stopPtr = ifind_stopPtr->next;
		ifind_startPtr->next = ifind_stopPtr;
		ifind_stopPtr->back = ifind_startPtr;
		while (i<new_length)
		{
			newPtr = new DblNode<ElemType>(ne[i], ifind_startPtr, ifind_stopPtr);
			ifind_startPtr->next = newPtr;
			ifind_stopPtr->back = newPtr;
			ifind_startPtr = newPtr;
			i++;
		}
		cout << "replacd" << endl;
	}
}
template <class ElemType>
bool DblLinkList<ElemType> ::Delete(int position)
{
	if (position<1 || position>Length())
		return false;
	else
	{
		DblNode <ElemType> *tmpPtr;
		tmpPtr = GetElemPtr(position);
		tmpPtr->back->next = tmpPtr->next;
		tmpPtr->next->back = tmpPtr->back;
		delete tmpPtr;
		return true;
	}
}
template <class ElemType>
bool DblLinkList<ElemType> ::Insert_file(int position, const char *file_location)
{
	char temp_char;
	fstream outfile(file_location, ios::out | ios::in);
	if (!outfile)
	{
		cout << "can't open file" << '\n';
		exit(1);
	}
	outfile.unsetf(ios::skipws); //取消跳过空字符
	DblNode <ElemType> *tmpPtr, *nextPtr, *newPtr;
	tmpPtr = GetElemPtr(position - 1);
	if (position<1 || position>Length() + 1)
		return false;
	else
	{
		while (outfile >> temp_char)
		{//读入
			nextPtr = tmpPtr->next;
			newPtr = new DblNode<ElemType>(temp_char, tmpPtr, nextPtr);
			tmpPtr->next = newPtr;
			nextPtr->back = newPtr;
			tmpPtr = tmpPtr->next;
		}
		outfile.close();
		return true;
	}
}
template <class ElemType>
bool DblLinkList<ElemType> ::push_out_file(const char *file_location)
{
	DblNode <ElemType> *tmpPtr;
	if (Length() == 0) return false;
	else
	{
		ofstream outfile(file_location);
		for (tmpPtr = head->next; tmpPtr != head; tmpPtr = tmpPtr->next)
		{
			outfile << tmpPtr->data;
		}
		outfile.close();
		return true;
	}
}
template <class ElemType>
void show(const ElemType &e) { cout << e; }