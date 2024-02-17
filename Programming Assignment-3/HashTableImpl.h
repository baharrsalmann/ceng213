#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP
//=======================//
// Implemented Functions //
//=======================//
template<int MAX_SIZE>
int HashTable<MAX_SIZE>::PRIMES[3] = {102523, 100907, 104659};

template<int MAX_SIZE>
void HashTable<MAX_SIZE>::PrintLine(int tableIndex) const
{
    const HashData& data = table[tableIndex];

    // Using printf here it is easier to format
    if(data.sentinel == SENTINEL_MARK)
    {
        printf("[%03d]         : SENTINEL\n", tableIndex);
    }
    else if(data.sentinel == EMPTY_MARK)
    {
        printf("[%03d]         : EMPTY\n", tableIndex);
    }
    else
    {
        printf("[%03d] - [%03d] : ", tableIndex, data.lruCounter);
        printf("(%-5s) ", data.isCostWeighted ? "True" : "False");
        size_t sz = data.intArray.size();
        for(size_t i = 0; i < sz; i++)
        {
            if(i % 2 == 0)
                printf("[%03d]", data.intArray[i]);
            else
                printf("/%03d/", data.intArray[i]);

            if(i != sz - 1)
                printf("-->");
        }
        printf("\n");
    }
}

template<int MAX_SIZE>
void HashTable<MAX_SIZE>::PrintTable() const
{
    printf("____________________\n");
    printf("Elements %d\n", elementCount);
    printf("[IDX] - [LRU] | DATA\n");
    printf("____________________\n");
    for(int i = 0; i < MAX_SIZE; i++)
    {
        PrintLine(i);
    }
}

//=======================//
//          TODO         //
//=======================//
template<int MAX_SIZE>
int HashTable<MAX_SIZE>::Hash(int startInt, int endInt, bool isCostWeighted)
{
    /* TODO */
    int h=PRIMES[0]*startInt + PRIMES[1]*endInt + PRIMES[2]*int(isCostWeighted);
    return h;
}

template<int MAX_SIZE>
HashTable<MAX_SIZE>::HashTable()
{
    /* TODO */
    for(int i=0;i<MAX_SIZE;i++){
        HashData* temp = new HashData;
        temp->lruCounter=0; 
        temp->sentinel=EMPTY_MARK; 
        table[i]=*temp;
        delete temp;
    }
    elementCount=0;
}

template<int MAX_SIZE>
int HashTable<MAX_SIZE>::Insert(const std::vector<int>& intArray, bool isCostWeighted)
{
    /* TODO */
    if(intArray.empty()){ throw InvalidTableArgException(); }
    int startInt=intArray[0];
    int endInt=intArray[intArray.size()-1];
    int h=Hash(startInt,endInt,isCostWeighted);
    int step=0;
    int i=0;
    std::vector<int> my_array = intArray;
    HashData *temp;
    temp=&table[h%MAX_SIZE];

if(Find(my_array,startInt,endInt,isCostWeighted,0)==false){

    if(elementCount*CAPACITY_THRESHOLD>=MAX_SIZE) {throw TableCapFullException(elementCount);}
    while(temp->sentinel==OCCUPIED_MARK){ //while içinde bir value varsa

        if(temp->startInt==startInt && temp->endInt==endInt && temp->isCostWeighted==isCostWeighted){ //value eşitse
            temp->lruCounter ++;
            return temp->lruCounter-1;
        }
        //value eşit değilse 
        i++;
        step=i*i;
        temp=&table[(h+step) % MAX_SIZE];
    }
 

        HashData new_comer;
        new_comer.startInt=startInt;
        new_comer.endInt=endInt;
        new_comer.isCostWeighted=isCostWeighted;
        new_comer.lruCounter=1;
        new_comer.sentinel=OCCUPIED_MARK;
        new_comer.intArray=my_array; //??????issue
        elementCount++;
        table[(h+step) % MAX_SIZE]=new_comer;
        return new_comer.lruCounter-1;

    }
else if(Find(my_array,startInt,endInt,isCostWeighted,0)==true){
    while(temp->sentinel!=EMPTY_MARK){ //removed veya value varsa devam

        if(temp->startInt==startInt && temp->endInt==endInt && temp->isCostWeighted==isCostWeighted){ //value eşitse
            temp->lruCounter ++;
            return temp->lruCounter -1;
        }
        //value eşit değilse 
        i++;
        step=i*i;
        temp=&table[(h+step) % MAX_SIZE];
    }

}
}

template<int MAX_SIZE>
bool HashTable<MAX_SIZE>::Find(std::vector<int>& intArray,
                               int startInt, int endInt, bool isCostWeighted,
                               bool incLRU)
{
    /* TODO */
    int h=Hash(startInt,endInt,isCostWeighted);
    int step=0;
    int i=0;
    HashData *temp;
    temp=&table[h%MAX_SIZE];
    while(temp->sentinel!=EMPTY_MARK){

        if(temp->startInt==startInt && temp->endInt==endInt && temp->isCostWeighted==isCostWeighted){
            if(incLRU) temp->lruCounter ++;
            intArray=temp->intArray;
            return true;
        }
        i++;
        step=i*i;
        temp=&table[(h+step) % MAX_SIZE];
    }
    return false;
}

template<int MAX_SIZE>
void HashTable<MAX_SIZE>::InvalidateTable()
{
    /* TODO */

    for(int i=0;i<MAX_SIZE;i++){
        table[i].intArray.clear();
        table[i].sentinel=EMPTY_MARK;
    }
    elementCount=0;
}

template<int MAX_SIZE>
void HashTable<MAX_SIZE>::GetMostInserted(std::vector<int>& intArray) const
{
    /* TODO */
    //    HashData* temp=&(table[0]); consttan dolayı bu error veriyor. Const hakkında birazcık oku.
    int i=0;
    int maxlru=table[0].lruCounter;
    for(;i<MAX_SIZE;i++){

        if(table[i].sentinel==EMPTY_MARK || table[i].sentinel==SENTINEL_MARK) continue;

        if(table[i].lruCounter > maxlru){
            maxlru=table[i].lruCounter;
            intArray=table[i].intArray;
        }
    }

}

template<int MAX_SIZE>
void HashTable<MAX_SIZE>::Remove(std::vector<int>& intArray,
                                 int startInt, int endInt, bool isCostWeighted)
{
    /* TODO */
    if(Find(intArray,startInt,endInt,isCostWeighted,0)==false) return;
    int h=Hash(startInt,endInt,isCostWeighted);
    int step=0;
    int i=0;
    HashData *temp;
    temp=&table[h%MAX_SIZE];
    while(temp->sentinel!=EMPTY_MARK){ //removed veya value varsa devam

        if(temp->startInt==startInt && temp->endInt==endInt && temp->isCostWeighted==isCostWeighted){ //value eşitse
            intArray=temp->intArray;
            elementCount--;
            temp->sentinel=SENTINEL_MARK;
            temp->lruCounter=0;

            return;
        }
        //value eşit değilse 
        i++;
        step=i*i;
        temp=&table[(h+step) % MAX_SIZE];
    }
}

class Compare {
    public:
       bool operator()(HashData x, HashData y){
           if(x.lruCounter < y.lruCounter){
               return true;
           }
           return false;
      }
};

template<int MAX_SIZE>
void HashTable<MAX_SIZE>::RemoveLRU(int lruElementCount)
{
    /* TODO */
    int i=0;
    std::priority_queue<HashData, std::vector<HashData>, Compare> my_heap;
    for(;i<MAX_SIZE;i++){
        if(my_heap.size()==lruElementCount) break;
        else if(table[i].sentinel==OCCUPIED_MARK) my_heap.push(table[i]);
    }
    //table[i] ekledin en son, bir daha conditiona geldim ve breakledi, bu sefer i+1den başlıyor diğer for loop, doğru yani.
    for(;i<MAX_SIZE;i++){
        if(table[i].sentinel==OCCUPIED_MARK && table[i].lruCounter<my_heap.top().lruCounter) {
            my_heap.pop();
            my_heap.push(table[i]);
        }
    }
    while(!my_heap.empty()){
        std::vector<int> my_array = my_heap.top().intArray;
        Remove(my_array,my_heap.top().startInt,my_heap.top().endInt,my_heap.top().isCostWeighted);
        my_heap.pop();
    }

    //lruelementcount boyutunda bir maxheap<HASHDATA>?? nası olacak o kısım, max minin lrucounttan geldiğini nasıl anlayacak?Daha sonra bunu fulleyecek şekilde Hashdataları içine göm. 
    //Sonra tableda gezerken heapın en üstündekiyle lrucounterlarını karşılaştır. Büyükse dokunma.
    //Küçükse heap.remove() sonra, heap.add(table[i]). Tüm tableı gezince çıkarılması gerekenler bulmuş oldun.
    //Şimdi heap.top() Removea gönder, datalarını vererek. Sonra da heap.remove(), bu döngü de lruelementcount kadar dönecek.

}

template<int MAX_SIZE>
void HashTable<MAX_SIZE>::PrintSortedLRUEntries() const
{
    /* TODO */
    int i=0;
    MaxPairHeap<int, int>  my_heap;
    Pair<int,int> temp;
    for(;i<MAX_SIZE;i++){
        if(table[i].sentinel==OCCUPIED_MARK){
            temp.key=table[i].lruCounter;
            temp.value=i;
            my_heap.push(temp); }
    }
    while(!my_heap.empty()){
        PrintLine(my_heap.top().value);
        my_heap.pop();
    }
}

#endif // HASH_TABLE_HPP