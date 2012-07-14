#pragma warning( disable : 4786 )
#include "stdafx.h"
using namespace std;
#include <vector>
#include <map>

struct cmp_str
{
   bool operator()(char const *a, char const *b) const
   {
      return strcmp(a, b) < 0;
   }
};

///////////////////////////////////////////////////////////////////////////////////////
////////////////////////////// CTibiaList Implementation //////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
class CTibiaListData{
	int val;
	char* s;
	int val2;
	int type;
public:
	CTibiaListData(int a_val,char* a_s){
		s=(char*)malloc(strlen(a_s)+1);
		strcpy(s,a_s);

		val=a_val;
		val2=0;
		SetType(0);
	}
	CTibiaListData(int a_val,char* a_s,int a_val2, int a_val3){
		s=(char*)malloc(strlen(a_s)+1);
		strcpy(s,a_s);

		val=a_val;
		val2=a_val2;
		SetType(a_val3);
	}
	char* GetText(){
		return s;
	}
	int GetValue(){
		return val;
	}
	int GetType(){
		return type;
	}
	int GetExtraInfo(){
		return val2;
	}
	void SetExtraInfo(int a_val2){
		val2=a_val2;
	}
	void SetValue(int a_val){
		val=a_val;
	}
	void SetType(int a_val){
		type=a_val;
	}
	void SetText(char* a_s){
		free(s);
		s=(char*)malloc(strlen(a_s)+1);
		strcpy(s,a_s);
	}
	~CTibiaListData(){
		free(s);
	}
	void toString(char* outStr){
		int ind = strlen(outStr);
		sprintf(outStr+ind,"(%d,%s,%d)\n",val,s,val2);
	}
};

typedef map<char *, CTibiaListData*, cmp_str> StrMap;
class CTibiaList{
private:
public:
	StrMap strMap;// Important Note:  NEVER use strMap[] except to change the key.  Use strMap.find() for lookups
	CTypedPtrArray<CPtrArray,CTibiaListData*> dataList;
	CUIntArray valList;
	int memSize;
	CTibiaList(){
		SetMemSize(8);
	}
	~CTibiaList(){
		RemoveAll();
	}

	bool Add(int a_val,char* a_s,int a_val2 = 0, int a_val3 = 0) {
		CTibiaListData* data=new CTibiaListData(a_val, a_s, a_val2, a_val3);
		if (Add(data)) return TRUE;
		delete data;
		return FALSE;
	}
	bool Add(CTibiaListData* data){
		if (data==NULL) return FALSE;
		int a_val=data->GetValue();
		int type=data->GetType();
		char* a_s=data->GetText();
		if (HasText(a_s)) return FALSE;

		dataList.Add(data);
		valList.Add(a_val);
		strMap[a_s]=data;
		if(GetCount()>memSize*1.5){
			SetMemSize(memSize*2);
		}
		return TRUE;
	}
	bool HasValue(int val){
		int size=dataList.GetSize();
		for (int i=0;i<size;i++){
			if (valList[i]==val) return TRUE;
		}
		return FALSE;
	}
	bool HasText(char* s){
		return strMap.find(s)!=strMap.end();
	}
	int GetCount(){
		return dataList.GetSize();
	}
	int GetIndex(int val){
		int size=dataList.GetSize();
		for (int i=0;i<size;i++){
			if (valList[i]==val) return i;
		}
		return -1;
	}
	char* GetText(int val){
		int size=dataList.GetSize();
		for (int i=0;i<size;i++){
			if (valList[i]==val) return dataList[i]->GetText();
		}
		return NULL;
	}
	int GetValue(char* s){
		StrMap::iterator iter=strMap.find(s);
		if(iter==strMap.end()) return 0;
		return iter->second->GetValue();
	}
	int GetExtraInfo(char* s){
		StrMap::iterator iter=strMap.find(s);
		if(iter==strMap.end()) return 0;
		return iter->second->GetExtraInfo();
	}
	int GetExtraInfo(int val){
		int size=dataList.GetSize();
		for (int i=0;i<size;i++){
			if (valList[i]==val) return dataList[i]->GetExtraInfo();
		}
		return 0;
	}
	int GetValueAtIndex(int ind){
		if (ind>=0 && ind<dataList.GetSize()){
			return valList[ind];
		}
		return 0;
	}
	char* GetTextAtIndex(int ind){
		if (ind>=0 && ind<dataList.GetSize()){
			return dataList[ind]->GetText();
		}
		return NULL;
	}

	int GetTypeAtIndex(int ind) {
		if (ind>=0 && ind<dataList.GetSize()) {
			return dataList[ind]->GetType();
		}
		return NULL;
	}

	int GetExtraInfoAtIndex(int ind){
		if (ind>=0 && ind<dataList.GetSize()){
			return dataList[ind]->GetExtraInfo();
		}
		return 0;
	}
	void SetValueAtIndex(int ind, int val){
		if (!(ind>=0 && ind<dataList.GetSize())) AfxMessageBox("CTibiaList index out of bounds!");
		dataList[ind]->SetValue(val);
		valList[ind]=val;
	}
	void SetTextAtIndex(int ind, char* s){
		if (!(ind>=0 && ind<dataList.GetSize())) AfxMessageBox("CTibiaList index out of bounds!");
		if (HasText(s)) return;
		CTibiaListData* data=dataList[ind];
		StrMap::iterator iter=strMap.find(data->GetText());
		if(iter==strMap.end()) AfxMessageBox("Internal Error, strMap missing entry!");
		//free(iter->first);  string key is same as string within data
		strMap.erase(iter);
		data->SetText(s);
		strMap[data->GetText()]=data;
	}
	void SetExtraInfoAtIndex(int ind,int val2){
		if (!(ind>=0 && ind<dataList.GetSize())) AfxMessageBox("CTibiaList index out of bounds!");
		dataList[ind]->SetExtraInfo(val2);
	}
	bool SetExtraInfo(char* s,int val2){
		StrMap::iterator iter=strMap.find(s);
		if(iter==strMap.end()) return FALSE;
		iter->second->SetExtraInfo(val2);
		return TRUE;
	}
	bool SetExtraInfo(int val,int val2){
		int ind=GetIndex(val);
		if (ind==-1) return FALSE;
		dataList[ind]->SetExtraInfo(val2);
		return TRUE;
	}
	void SetTypeAtIndex(int ind,int val2){
		if (!(ind>=0 && ind<dataList.GetSize())) AfxMessageBox("CTibiaList index out of bounds!");
		dataList[ind]->SetType(val2);
	}
	bool SetType(char* s,int val2){
		StrMap::iterator iter=strMap.find(s);
		if(iter==strMap.end()) return FALSE;
		iter->second->SetType(val2);
		return TRUE;
	}
	bool SetType(int val,int val2){
		int ind=GetIndex(val);
		if (ind==-1) return FALSE;
		dataList[ind]->SetType(val2);
		return TRUE;
	}
	bool Remove(char* s){
		StrMap::iterator iter=strMap.find(s);
		if (iter==strMap.end()) return FALSE;
		int val=iter->second->GetValue();
		int i;
		int size=dataList.GetSize();
		for (i=0;i<size;i++){
			if (dataList[i]->GetValue()==val && !strcmp(dataList[i]->GetText(),s)) break;
		}
		if (i>=size) return FALSE;
		dataList.RemoveAt(i);
		valList.RemoveAt(i);
		Free(iter);

		if (GetCount()*4<=memSize) SetMemSize(memSize/2);
		return TRUE;
	}
	bool Remove(int val){
		int i;
		int size=dataList.GetSize();
		for (i=0;i<size;i++){
			if (valList[i]==val) break;
		}
		if (i>=size) return FALSE;
		StrMap::iterator iter=strMap.find(dataList[i]->GetText());
		if (iter==strMap.end()) return FALSE;
		dataList.RemoveAt(i);
		valList.RemoveAt(i);
		Free(iter);

		if (GetCount()*4<=memSize) SetMemSize(memSize/2);
		return TRUE;
	}
	bool RemoveAtIndex(int ind){
		if (!(ind>=0 && ind<dataList.GetSize())) AfxMessageBox("CTibiaList index out of bounds!");
		StrMap::iterator iter=strMap.find(dataList[ind]->GetText());
		if (iter==strMap.end()) return FALSE;
		dataList.RemoveAt(ind);
		valList.RemoveAt(ind);
		Free(iter);

		if (GetCount()*4<=memSize) SetMemSize(memSize/2);
		return TRUE;
	}

	CUIntArray* GetArrayPtr(){
		return &valList;
	}

	void RemoveAll(){
		StrMap::iterator iter=strMap.begin();
		while (iter!=strMap.end()){
			StrMap::iterator iterTmp=iter;
			iter++;
			Free(iterTmp);
		}
		strMap.clear();
		dataList.RemoveAll();
		valList.RemoveAll();
		SetMemSize(8);
	}
	void toString2(char* outStr){
		int ind=strlen(outStr);
		sprintf(outStr+ind,"List:");
		StrMap::iterator iter=strMap.begin();
		while (iter!=strMap.end()){
			CTibiaListData* data=iter->second;
			data->toString(outStr);
			iter++;
		}
	}
	void toString(char* outStr){
		int ind=strlen(outStr);
		sprintf(outStr,"List:");
		int size=GetCount();
		for (int i=0;i<size;i++){
			CTibiaListData* data=dataList[i];
			data->toString(outStr);
		}
		StrMap::iterator iter=strMap.begin();
		while (iter!=strMap.end()){
			sprintf(outStr+strlen(outStr),"%s-",iter->first);
			iter++;
		}


	}
private:
	void Free(StrMap::iterator it)
	{
		delete it->second;//data contains same char* as map key
		strMap.erase(it);
	}
	void SetMemSize(int new_size){
		memSize=max(new_size,1);
		valList.SetSize(GetCount(),memSize);
		dataList.SetSize(GetCount(),memSize);
	}
};
///////////////////////////////////////////////////////////////////////////////////////
////////////////////////////// CTibiaHashMap Implementation INCOMPLETE //////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
typedef map<int, CTibiaListData*> IntMap;
class CTibiaHashMap{
private:
	StrMap strMap;
	IntMap intMap;
	int counter;
	map<int,StrMap::iterator> iterSetS;
	map<int,IntMap::iterator> iterSetI;
	map<int,int> isNewIter;
	int count;
	bool uniqueInt;
	bool uniqueStr;
public:
	CTibiaHashMap(){
		counter=0x10000;
		count=0;
		uniqueInt=TRUE;
		uniqueStr=TRUE;
	}
	// At least one should be true in order to use the map properly
	CTibiaHashMap(bool a_uniqueInt,bool a_uniqueStr){
		counter=0x10000;
		count=0;
		uniqueInt=a_uniqueInt;
		uniqueStr=a_uniqueStr;
	}
	~CTibiaHashMap(){
		RemoveAll();
	}

	int InitIter(){
		int code=counter++;
		//Used to prevent race condition ;P
		if (isNewIter.find(code)==isNewIter.end()){
			AfxMessageBox("You Lucky Bastard!");
			return InitIter();
		}
		isNewIter[code]=1;
		return code;
	}

	//Must iterate through all elements in order for iterator to be cleaned.
	bool IncrementIter(int code){
		int* isNew=&isNewIter[code];
		if (uniqueStr){
			StrMap::iterator iter=iterSetS[code];
			if (*isNew==1){
				iter=strMap.begin();
				iterSetS[code] = iter;
			} else if (iter!=NULL){
				iter++;
			} else { return 0;}
			*isNew=0;
			if (iter!=strMap.end()){
				return 1;
			} else {
				iterSetS.erase(iterSetS.find(code));
				isNewIter.erase(isNewIter.find(code));
				return 0;
			}
		} else {
			IntMap::iterator iter=iterSetI[code];
			if (*isNew==1){
				iter=intMap.begin();
				iterSetI[code] = iter;
			} else if (iter!=NULL){
				iter++;
			} else { return 0;}
			*isNew=0;
			if (iter!=intMap.end()){
				return 1;
			} else {
				iterSetI.erase(iterSetI.find(code));
				isNewIter.erase(isNewIter.find(code));
				return 0;
			}
		}
	}
	int GetValueAtIter(int code){
		if (uniqueStr){
			StrMap::iterator iter=iterSetS[code];
			if (iter==NULL || iter==strMap.end()) return 0;
			return iter->second->GetValue();
		} else {
			IntMap::iterator iter=iterSetI[code];
			if (iter==NULL || iter==intMap.end()) return 0;
			return iter->second->GetValue();
		}
	}
	char* GetTextAtIter(int code){
		if (uniqueStr){
			StrMap::iterator iter=iterSetS[code];
			if (iter==NULL || iter==strMap.end()) return NULL;
			return iter->second->GetText();
		} else {
			IntMap::iterator iter=iterSetI[code];
			if (iter==NULL || iter==intMap.end()) return NULL;
			return iter->second->GetText();
		}
	}
	int GetExtraInfoAtIter(int code){
		if (uniqueStr){
			StrMap::iterator iter=iterSetS[code];
			if (iter==NULL || iter==strMap.end()) return 0;
			return iter->second->GetExtraInfo();
		} else {
			IntMap::iterator iter=iterSetI[code];
			if (iter==NULL || iter==intMap.end()) return 0;
			return iter->second->GetExtraInfo();
		}
	}
	bool Add(int a_val,char* a_s,int a_val2, int a_val3 = 0){
		CTibiaListData* data=new CTibiaListData(a_val, a_s, a_val2, a_val3);
		if (Add(data)) return TRUE;
		delete data;
		return FALSE;
	}
	bool Add(CTibiaListData* data){
		if (data==NULL) return FALSE;
		int a_val=data->GetValue();
		char* a_s=data->GetText();
		//Important and ensures that no null or 0 entries are entered depending on whether
		//strings or ints are unique.  Also prevents duplicate values in the maps which are indicated as unique.
		if ((HasText(a_s) || a_s==NULL)  && uniqueStr || (HasValue(a_val) || a_val==0) && uniqueInt) return FALSE;

		char* s=(char*)malloc(strlen(a_s)+1);
		strcpy(s,a_s);
		if (uniqueInt) intMap[a_val]=data;
		if (uniqueStr) strMap[s]=data;
		count++;
		return TRUE;
	}
	bool HasValue(int val){
		return intMap.find(val)!=intMap.end();
	}
	bool HasText(char* s){
		return strMap.find(s)!=strMap.end();
	}
	int GetCount(){
		return count;
	}
	char* GetText(int val){
		if (!HasValue(val)){
			return NULL;
		}
		CTibiaListData* data=intMap[val];
		return data->GetText();
	}
	int GetValue(char* s){
		if (!HasText(s)) return 0;
		CTibiaListData* data=strMap[s];
		return data->GetValue();
	}
	int GetExtraInfo(char* s){
		if (!HasText(s)) return 0;
		CTibiaListData* data=strMap[s];
		return data->GetExtraInfo();
	}
	int GetExtraInfo(int val){
		if (!HasValue(val)) return 0;
		CTibiaListData* data=intMap[val];
		return data->GetExtraInfo();
	}
	bool SetExtraInfo(char* s,int val2){
		if (!HasText(s)) return FALSE;
		CTibiaListData* data=strMap[s];
		data->SetExtraInfo(val2);
		return TRUE;
	}
	bool SetExtraInfo(int val,int val2){
		if (!HasValue(val)) return FALSE;
		CTibiaListData* data=intMap[val];
		data->SetExtraInfo(val2);
		return TRUE;
	}
	bool Remove(char* s){
		StrMap::iterator iter1=strMap.find(s);
		CTibiaListData* data=iter1->second;
		if (data==NULL) return FALSE;
		int val=data->GetValue();
		IntMap::iterator iter2=intMap.find(val);
		if (iter1==strMap.end()) return FALSE;
		Free(iter1);
		if (iter2==intMap.end()) return FALSE;
		Free(iter2);
		count--;
		return TRUE;
	}
	bool Remove(int val){
		IntMap::iterator iter1=intMap.find(val);
		CTibiaListData* data=iter1->second;
		if (data==NULL) return FALSE;
		StrMap::iterator iter2=strMap.find(data->GetText());
		if (iter1==intMap.end()) return FALSE;
		Free(iter1);
		if (iter2==strMap.end()) return FALSE;
		Free(iter2);
		count--;
		return TRUE;
	}

	CTibiaListData** GetAll(){
		CTibiaListData** ret=(CTibiaListData**)malloc(sizeof(CTibiaListData*)*(count+1));
		IntMap::const_iterator iter=intMap.begin();
		int i=0;
		while (iter!=intMap.end()){
			ret[i++]=iter->second;
			iter++;
		}
		ret[i]=NULL;
		return ret;
	}
	void RemoveAll(){
		StrMap::iterator iter1=strMap.begin();
		while (iter1!=strMap.end()){
			Free(iter1);
			iter1++;
		}
		IntMap::iterator iter2=intMap.begin();
		while (iter2!=intMap.end()){
			Free(iter2);
			iter2++;
		}
		count=0;
		strMap.clear();
		intMap.clear();
	}
	void toString(char* outStr){
		int ind=strlen(outStr);
		sprintf(outStr+ind,"Map:");
		IntMap::const_iterator iter=intMap.begin();
		while (iter!=intMap.end()){
			CTibiaListData* data=iter->second;
			data->toString(outStr);
			iter++;
		}
	}
private:
	void Free(StrMap::iterator it)
	{
		strMap.erase(it);
		free(it->first);
		delete it->second;
	}
	void Free(IntMap::iterator it)
	{
		intMap.erase(it);
		delete it->second;
	}

};

///////////////////////////////////////////////////////////////////////////////////////
////////////////////////////// CTibiaTree Implementation //////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
typedef enum {
	TT_BRANCH_NODE=1,
	TT_ITEM_NODE=2
}CTibiaTreeDataType;

class CTibiaTreeData{
protected:
	CTibiaTreeDataType nodeType;
public:
	CTibiaTreeData(){
		nodeType=TT_ITEM_NODE;
	}
	CTibiaTreeData(CTibiaTreeDataType a_type){
		nodeType=a_type;
	}
	CTibiaTreeDataType GetType(){
		return nodeType;
	}
	virtual ~CTibiaTreeData(){
		//gets called after inherited class' destructor
	}
	virtual void toString(char* outStr){
		int ind=strlen(outStr);
		sprintf(outStr+ind,"\n");
	}
};

class CTibiaTreeBranchData:public CTibiaTreeData
{
	char *name;
public:
	CTibiaTreeBranchData(char *a_name){
		nodeType=TT_BRANCH_NODE;

		int len=strlen(a_name)+1;
		name=(char*)malloc(len);
		memcpy(name,a_name,len);
	}
	static CTibiaTreeBranchData* newCTibiaTreeBranchData(char *a_name){
		return new CTibiaTreeBranchData(a_name);
	}
	virtual ~CTibiaTreeBranchData(){
		free(name);
		name=NULL;
	}
	char* GetName(){
		return name;
	}
	virtual void CTibiaTreeBranchData::toString(char* outStr){
		int ind=strlen(outStr);
		sprintf(outStr+ind,"(Branch:%s)\n",this->name);
		
	}
};

class CTibiaTreeItemData:public CTibiaTreeData
{
public:
	CTibiaTreeItemData(char *a_name,int a_id, bool a_looted, int i_type = 0){
		if (!strcmp(a_name,"Wooden Doll"))
			int a=0;
		nodeType=TT_ITEM_NODE;
		id=a_id;
		looted=a_looted;
		type = i_type;
		
		int len=strlen(a_name)+1;
		name=(char*)malloc(len);
		memcpy(name,a_name,len);
	}
	static CTibiaTreeItemData* newCTibiaTreeItemData(char *a_name,int a_id, bool a_looted, int i_type = 0){
		return new CTibiaTreeItemData(a_name,a_id,a_looted,i_type);
	}
	virtual ~CTibiaTreeItemData(){
		free(name);
		name=NULL;
	}
	void SetId(int idIn){
		id = idIn;
	}
	int GetId(){
		return id;
	}
	int GetItemType(){
		return type;
	}
	void SetType(int typeIn){
		type = typeIn;
	}
	bool IsLooted(){
		return looted;
	}
	void SetIsLooted(bool b_looted){
		looted = b_looted;
	}
	char* GetName(){
		return name;
	}
	void SetName(char* nameIn){
		memcpy(name, nameIn, strlen(nameIn)+1);
	}
	virtual void CTibiaTreeItemData::toString(char* outStr){
		int ind=strlen(outStr);
		sprintf(outStr+ind,"(Item:%s,%d,%d)\n",this->name,this->id,this->looted);
	}
private:
	int type;
	char *name;
	int id;
	bool looted;
};

class CTibiaTree{
public:
	CTibiaTreeData* data;
	vector<CTibiaTree*> children;
	CTibiaTree(CTibiaTreeData* a_data){
		data=a_data;
	}
	~CTibiaTree(){
		delete data;
		data=NULL;
		int size=children.size();
		for (int i=size-1;i>=0;i--){
			CTibiaTree* ptTree=children[i];
			children.pop_back();
			delete ptTree;
		}
	}
	CTibiaTree* AddChild(CTibiaTreeData* a_data){
		CTibiaTree* ret = new CTibiaTree(a_data);
		children.push_back(ret);
		return ret;
	}

	bool HasChildren(){
		return children.size()>0;
	}
	void toString(char* outStr){
		sprintf(outStr,"Tree:");
		toString(outStr,0);
	}
	void toString(char* outStr,int level){
		int ind=strlen(outStr);
		memset(outStr+ind,'-',level);
		memset(outStr+ind+level,0,1);
		data->toString(outStr);
		int size=children.size();
		for (int i=0;i<size;i++){
			children[i]->toString(outStr,level+1);
		}
	}


};

///////////////////////////////////////////////////////////////////////////////////////
////////////////////////////// CTibiaQueue Implementation //////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
template <class T>
class CTibiaQueue{
private:
	int count;
	int origTabSize;
	int start;
	int end;
public:
	int tabSize;
	T*tab;
	CTibiaQueue(){
		origTabSize=15;
		tabSize=origTabSize;
		count=0;
		tab=(T*)malloc(sizeof(T)*tabSize);
		memset(tab,0,sizeof(T)*tabSize);
		start=0;
		end=0;
	}
	~CTibiaQueue(){
		free(tab);
	}
	void Add(T ptr){
		growCheck();
		tab[end]=ptr;
		end=(end+1) % tabSize;
		count++;
	}
	T Remove(){
		if (!count) return T();
		T ret=tab[start];
		tab[start]=T();
		start = (start+1)%tabSize;
		count--;
		shrinkCheck();
		return ret;
	}
	T Peek(){
		if (!count) return T();
		return tab[start];
	}
	int GetCount(){
		return count;
	}
	char* toString(){
		return toString(tab,tabSize);
	}
private:
	char* toString(T* tab, int tabSize){
		char * ret=(char*)malloc(tabSize*10+100);
		ret[0]=0;
		sprintf(ret+strlen(ret),"[s:%d,e:%d,c:%d,sz:%d][",start,end,count,tabSize);
		for (int i=0;i<tabSize;i++){
			sprintf(ret+strlen(ret),"%d ",tab[i]);
		}
		ret[strlen(ret)-1]=0;
		sprintf(ret+strlen(ret),"]");
		return ret;
	}
	void growCheck(){
		if (count==tabSize){//start==end
			int tmpTabSize=tabSize*2;
			T* tmpTab=(T*)malloc(sizeof(T)*tmpTabSize);
			memset(tmpTab,0,sizeof(T)*tmpTabSize);

			memcpy(tmpTab,tab+start,(tabSize-start)*sizeof(T));
			memcpy(tmpTab+tabSize-start,tab,(end)*sizeof(T));

			free(tab);
			tab=tmpTab;
			tabSize=tmpTabSize;
			start=0;
			end=count;
		}
	}
	void shrinkCheck(){
		if (tabSize>origTabSize && count==tabSize/4) {//start!=end
			int tmpTabSize=tabSize/2;
			T* tmpTab=(T*)malloc(sizeof(T)*tmpTabSize);
			memset(tmpTab,0,sizeof(T)*tmpTabSize);

			memcpy(tmpTab,tab+start,min(count,tabSize-start)*sizeof(T));
			memcpy(tmpTab+min(count,tabSize-start),tab,(start>=end?end:0)*sizeof(T));

			free(tab);
			tabSize=tmpTabSize;
			tab=tmpTab;
			start=0;
			end=count;
		}
	}
	/*
	void testAddUntilFull(){
		for (int i=0;i<origTabSize;i++){
			Add (i+1);
		}
	}
	void testPop(){
		Remove();
		for (int i=0;i<origTabSize;i++){
			Add (i+1);
		}
		while (count>4){
			Remove();
		}
	}
	void testGrowAligned(){
		for (int i=0;i<origTabSize*1.5;i++){
			Add (i+1);
		}
	}
	void testGrowUnaligned(){
		for (int i=0;i<origTabSize*1.5;i++){
			Add (i+1);
			if(i==2){
				Remove();
				Remove();
			}
		}
	}
	void testGrowLooped(){
		for (int i=0;i<origTabSize*2;i++){
			Add (i+1);
			if(i==3){
				Remove();
				Remove();
				Remove();
				Remove();
			}
		}
	}
	void testShrinkAligned(){
		for (int i=0;i<origTabSize*4;i++){
			Add (i+1);
		}
		for (i=0;i<origTabSize*3;i++){
			Remove ();
		}
	}
	void testShrinkUnaligned(){
		origTabSize=1;
		for (int i=0;i<18;i++){
			if (i==7){
				while (count>1+tabSize/4){Remove();}
			}
			Add (i+1);
		}
		while(Remove()){}
	}
	void testMass(){
		int runtime=0;
		int i=1;
		while(count<1000){
			if (rand()%100>51) Remove();
			else Add(i++);
			runtime++;
		}
		runtime=0;
		while(count>0){
			if (rand()%100>49) Remove();
			else Add(i++);
			runtime++;
		}
	}
	*/
};


///////////////////////////////////////////////////////////////////////////////////////
////////////////////////////// CTibiaPriorityQueue Implementation //////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
class PQitem{
public:
	int val;
	DWORD data;
	PQitem(){
		val=0;
		data=NULL;
	}
	PQitem(int a_val,DWORD a_data){
		val=a_val;
		data=a_data;
	}
};
class CTibiaPriorityQueue{
	vector<PQitem> pq;
public:
	CTibiaPriorityQueue(){
	}
	~CTibiaPriorityQueue(){
	}
	void CTibiaPriorityQueue::Add(int val,DWORD ptr){
		int ind=pq.size();
		pq.push_back(PQitem(val,ptr));
		int ind2=(ind-1)/2;
		if (pq[ind2].val > val){
			while (pq[ind2].val > val && ind!=0){
				pq[ind]=pq[ind2];
				ind=ind2;
				ind2=(ind-1)/2;
			}
			pq[ind]=PQitem(val,ptr);
		}
	}
	DWORD CTibiaPriorityQueue::Remove(){
		if (pq.size()==0) return 0;
		DWORD ret=pq[0].data;
		pq[0].data=0;
		int ind=0;
		while (true){
			if (ind*2+2<pq.size() && pq.back().val>pq[ind*2+2].val){
				if (pq[ind*2+2].val<pq[ind*2+1].val){
					pq[ind]=pq[ind*2+2];
					ind=ind*2+2;
				} else {
					pq[ind]=pq[ind*2+1];
					ind=ind*2+1;
				}
			} else if(ind*2+1<pq.size() && pq.back().val>pq[ind*2+1].val){
				pq[ind]=pq[ind*2+1];
				ind=ind*2+1;
			} else {
				break;
			}
		}
		pq[ind]=pq.back();
		pq.pop_back();
		return ret;
	}
	DWORD CTibiaPriorityQueue::Peek(){
		if (pq.size()==0) return 0;
		return pq[0].data;
	}
	int CTibiaPriorityQueue::GetCount(){
		return pq.size();
	}
	char* CTibiaPriorityQueue::toString2(){
		char* ret=(char*)malloc(pq.size()*10+100);
		char* tmp=ret;
		ret[0]='-';
		ret[1]=0;
		for (int i=0;i<pq.size();i++){
			tmp=tmp+strlen(tmp);
			sprintf(tmp,"%d,",pq[i].val);
		}
		return ret;
	}

	char* CTibiaPriorityQueue::toString(){
		char* ret=(char*)malloc(pq.size()*10+100);
		char* tmp=ret;
		ret[0]='-';
		ret[1]=0;
		int ind=0;
		int wentBack=0;
		while (true && pq.size()!=0){
			if (!wentBack){
				tmp=tmp+strlen(tmp);
				sprintf(tmp,"%d",pq[ind].val);
			}
			if (ind*2+1<pq.size() && !wentBack){
				tmp=tmp+strlen(tmp);
				sprintf(tmp," [");
				ind=ind*2+1;
			} else if(ind%2==1 && ind+1<pq.size()){
				tmp=tmp+strlen(tmp);
				sprintf(tmp,",");
				ind=ind+1;
				wentBack=0;
			} else if(ind%2==0 && ind!=0){
				tmp=tmp+strlen(tmp);
				sprintf(tmp,"] ");
				ind=(ind-1)/2;
				wentBack=1;
			} else {
				break;
			}
		}
		return ret;
	}
private:
	void CTibiaPriorityQueue::testAddBack(){
		for (int i=15;i>0;i--){
			Add (i,i);
		}
		//cout<<toString();
	}
	void CTibiaPriorityQueue::testAddFor(){
		for (int i=0;i<15;i++){
			Add (i,i);
		}
		//cout<<toString2();
	}
	void CTibiaPriorityQueue::testAddAlt(){
		int n=1;
		for (int i=0;i<15;i++){
			Add (i*n+20,i*n+20);
			n=-n;
		}
		//cout<<toString();
	}
	void CTibiaPriorityQueue::testAddRandom(){
		for (int i=0;i<15;i++){
			Add (rand()%100,i);
		}
		//cout<<toString();
	}
	void CTibiaPriorityQueue::testRemove(){
		for (int i=7;i>0;i--){
			Add (i,i);
		}
		Remove();
		//cout<<toString();
	}
	void CTibiaPriorityQueue::testManyRemove(){
		for (int i=0;i<15;i++){
			Add (rand()%100,i);
		}
		for (i=0;i<15;i++){
			//cout<<toString()<<endl;
			Remove();
		}
		//cout<<toString2()<<endl;
	}
	void CTibiaPriorityQueue::testRemoveRandom(){
		for (int i=0;i<10000;i++){
			if (rand()%100<49){
				Add (rand()%100,i);
			} else {
				Remove();
			}
			//cout<<toString2()<<endl;
		}
	}
};
