#include<iostream>
#include<sstream>
#include<string>

using namespace std;

int minWeight = 999;
string path = "0 ", minPath;
int counter = 0;

struct element;
void getPath(int*, int, int);
void setElement(struct element*, struct element*, int);
struct element* copyElement(struct element*);
void getMinPath(struct element*, int);

string to_string(int i)
{
    stringstream ss;
    ss << i;
    return ss.str();
}

struct element
{
    int vertex;
    int weight;
    struct element* nextStage;
    struct element* sameStage;
};
struct element* source = NULL;

int main()
{
    int a=5, b=6;
    string s1 = "";
    s1 += to_string(a);
    s1 += to_string(b);
    cout<<s1<<endl;
    int n;
    cout<<"Enter the Number of Vertex in graph :";
    cin>>n;
    int graph[n][n];
    cout<<"Enter the Adjacency Matrix for Graph! (0|>0)\n";
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin>>graph[i][j];
    for(int i=0; i<n-1; i++)
        getPath(graph[i], i, n);
    getMinPath(source, n-1);
    //cout<<source->sameStage->nextStage->vertex<<"  ";
    //cout<<source->sameStage->nextStage->weight<<endl;
    //cout<<source->sameStage->sameStage->nextStage->vertex<<"  ";
    //cout<<source->sameStage->sameStage->nextStage->weight<<endl;
    cout<<"\nMin weight = "<<minWeight<<endl;
    cout<<"Path: "<<minPath<<endl;
}

void getPath(int *adjacent, int row, int n)
{
    int column = 0;
    while(column<n)
    {
        if(*adjacent!=0)
        {
            struct element* temp = new element;
            temp->sameStage = NULL;
            temp->nextStage = NULL;
            temp->vertex = column;
            temp->weight = *adjacent;
            if(row==0)
            {
                if(source==NULL)
                {
                    source = temp;
                }
                else
                {
                    struct element* traverse = source;
                    while(traverse->sameStage!=NULL)
                    {
                        traverse = traverse->sameStage;
                    }
                    traverse->sameStage = temp;
                }
            }
            else
            {
                setElement(source, temp, row);
                delete temp;
            }
        }
        adjacent++;
        column++;
    }
}


void setElement(struct element* traverse, struct element* temp, int currentVertex)
{
    if(traverse==NULL)
        return;
    if(traverse->vertex == currentVertex)
    {
        //cout<<"HI"<<endl;
        struct element* tempTraverse = traverse;
        //cout<<temp->vertex<<"  "<<temp->weight<<endl;
        struct element* tempCopy = copyElement(temp);
        tempCopy->weight += traverse->weight;
        //cout<<"Current Element: "<<currentVertex<<"  ";
        //cout<<temp->vertex<<"  "<<temp->weight<<endl;
        if(tempTraverse->nextStage==NULL)
        {
            tempTraverse->nextStage = tempCopy;
            return;
        }
        tempTraverse = tempTraverse->nextStage;
        while(tempTraverse->sameStage!=NULL)
            tempTraverse = tempTraverse->sameStage;
        tempTraverse->sameStage = tempCopy;
        return;
    }
    setElement(traverse->nextStage, temp, currentVertex);
    setElement(traverse->sameStage, temp, currentVertex);
}

struct element* copyElement(struct element* temp)
{
    struct element* tempCopy = new element;
    tempCopy->nextStage = temp->nextStage;
    tempCopy->sameStage = temp->sameStage;
    tempCopy->vertex = temp->vertex;
    tempCopy->weight = temp->weight;
    return tempCopy;
}

void getMinPath(struct element* traverse, int destination)
{
    if(traverse==NULL)
        return;
    if(traverse->vertex==destination)
    {
        path += to_string(traverse->vertex) + " ";
        if(minWeight>traverse->weight)
        {
            minWeight = traverse->weight;
            minPath = path;
        }
        path.pop_back();
        path.pop_back();
    }
    path += to_string(traverse->vertex) + " ";
    getMinPath(traverse->nextStage, destination);
    path.pop_back();
    path.pop_back();
    getMinPath(traverse->sameStage, destination);
}

